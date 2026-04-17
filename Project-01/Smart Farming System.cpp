#include <GL/glut.h>
#include <cmath>

// ----------------------------
// Global variables
// ----------------------------
float tractorX = -1.2f;
float droneX = -1.1f;
float cropGrowth = 0.2f;
float sprayOffset = 0.0f;
float irrigationOffset = 0.0f;

bool tractorMove = true;
bool droneMove = true;
bool irrigationOn = true;
bool cropGrow = true;
bool sprayOn = true;

// ----------------------------
// Utility functions
// ----------------------------
void drawCircle(float cx, float cy, float r, int segments = 100)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1416f * i / segments;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawRect(float x1, float y1, float x2, float y2)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// ----------------------------
// Background
// ----------------------------
void drawSky()
{
    glColor3f(0.53f, 0.81f, 0.98f);
    drawRect(-1.0f, 0.2f, 1.0f, 1.0f);
}

void drawSun()
{
    glColor3f(1.0f, 0.9f, 0.0f);
    drawCircle(0.75f, 0.78f, 0.08f);
}

void drawGround()
{
    glColor3f(0.35f, 0.75f, 0.30f);
    drawRect(-1.0f, -1.0f, 1.0f, 0.2f);
}

void drawFieldRows()
{
    glColor3f(0.55f, 0.27f, 0.07f);

    for (float y = -0.8f; y <= 0.05f; y += 0.2f)
    {
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
        glVertex2f(1.0f, y + 0.08f);
        glVertex2f(-1.0f, y + 0.08f);
        glEnd();
    }
}

void drawHouse()
{
    glColor3f(0.85f, 0.65f, 0.45f);
    drawRect(0.65f, 0.10f, 0.90f, 0.35f);

    glColor3f(0.65f, 0.15f, 0.15f);
    drawTriangle(0.62f, 0.35f, 0.775f, 0.50f, 0.93f, 0.35f);

    glColor3f(0.4f, 0.2f, 0.1f);
    drawRect(0.74f, 0.10f, 0.81f, 0.24f);

    glColor3f(0.2f, 0.4f, 0.8f);
    drawRect(0.67f, 0.20f, 0.73f, 0.28f);
    drawRect(0.82f, 0.20f, 0.88f, 0.28f);
}

void drawTree(float x, float y)
{
    glColor3f(0.55f, 0.27f, 0.07f);
    drawRect(x - 0.015f, y - 0.12f, x + 0.015f, y + 0.05f);

    glColor3f(0.0f, 0.5f, 0.0f);
    drawCircle(x, y + 0.10f, 0.08f);
    drawCircle(x - 0.05f, y + 0.05f, 0.06f);
    drawCircle(x + 0.05f, y + 0.05f, 0.06f);
}

// ----------------------------
// Crops
// ----------------------------
void drawSingleCrop(float x, float y, float h)
{
    // stem
    glColor3f(0.0f, 0.6f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glEnd();

    // leaves
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + h * 0.45f);
    glVertex2f(x - 0.02f, y + h * 0.35f);
    glVertex2f(x, y + h * 0.30f);

    glVertex2f(x, y + h * 0.60f);
    glVertex2f(x + 0.02f, y + h * 0.50f);
    glVertex2f(x, y + h * 0.45f);
    glEnd();

    // top grain
    glColor3f(0.95f, 0.85f, 0.2f);
    drawCircle(x, y + h + 0.01f, 0.01f);
}

void drawCrops()
{
    for (float row = -0.72f; row <= -0.02f; row += 0.2f)
    {
        for (float x = -0.92f; x <= 0.92f; x += 0.10f)
        {
            drawSingleCrop(x, row, cropGrowth);
        }
    }
}

// ----------------------------
// Tractor
// ----------------------------
void drawTractor()
{
    glPushMatrix();
    glTranslatef(tractorX, -0.38f, 0.0f);

    // body
    glColor3f(0.85f, 0.1f, 0.1f);
    drawRect(-0.10f, 0.00f, 0.08f, 0.08f);

    // cabin
    glColor3f(0.9f, 0.2f, 0.2f);
    drawRect(0.00f, 0.08f, 0.08f, 0.15f);

    // window
    glColor3f(0.6f, 0.85f, 1.0f);
    drawRect(0.015f, 0.10f, 0.065f, 0.14f);

    // exhaust
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRect(0.06f, 0.15f, 0.075f, 0.22f);

    // wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(-0.06f, -0.01f, 0.045f);
    drawCircle(0.06f, -0.01f, 0.06f);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(-0.06f, -0.01f, 0.018f);
    drawCircle(0.06f, -0.01f, 0.022f);

    glPopMatrix();
}

// ----------------------------
// Drone + Spray
// ----------------------------
void drawDrone()
{
    glPushMatrix();
    glTranslatef(droneX, 0.58f, 0.0f);

    // main body
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRect(-0.05f, -0.02f, 0.05f, 0.02f);

    // arms
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(-0.09f, 0.05f);
    glVertex2f(-0.03f, 0.01f);

    glVertex2f(0.09f, 0.05f);
    glVertex2f(0.03f, 0.01f);

    glVertex2f(-0.09f, -0.05f);
    glVertex2f(-0.03f, -0.01f);

    glVertex2f(0.09f, -0.05f);
    glVertex2f(0.03f, -0.01f);
    glEnd();

    // propellers
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.09f, 0.05f, 0.015f);
    drawCircle(0.09f, 0.05f, 0.015f);
    drawCircle(-0.09f, -0.05f, 0.015f);
    drawCircle(0.09f, -0.05f, 0.015f);

    // spray
    if (sprayOn)
    {
        glColor3f(0.7f, 0.9f, 1.0f);
        glLineWidth(2);
        glBegin(GL_LINES);
        for (float i = -0.035f; i <= 0.035f; i += 0.02f)
        {
            glVertex2f(i, -0.02f);
            glVertex2f(i + 0.01f * sin(sprayOffset * 5), -0.18f);
        }
        glEnd();
    }

    glPopMatrix();
}

// ----------------------------
// Irrigation system
// ----------------------------
void drawIrrigation()
{
    // pipe line
    glColor3f(0.35f, 0.35f, 0.35f);
    drawRect(-0.95f, 0.07f, 0.95f, 0.10f);

    for (float x = -0.8f; x <= 0.8f; x += 0.4f)
    {
        glColor3f(0.25f, 0.25f, 0.25f);
        drawRect(x - 0.01f, 0.04f, x + 0.01f, 0.10f);

        if (irrigationOn)
        {
            glColor3f(0.4f, 0.8f, 1.0f);
            glBegin(GL_LINES);
            glVertex2f(x, 0.04f);
            glVertex2f(x - 0.03f, -0.08f - 0.02f * sin(irrigationOffset));
            glVertex2f(x, 0.04f);
            glVertex2f(x + 0.03f, -0.08f - 0.02f * sin(irrigationOffset));
            glEnd();
        }
    }
}

// ----------------------------
// Text
// ----------------------------
void drawText(float x, float y, const char *str)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);
    while (*str)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);
        str++;
    }
}

// ----------------------------
// Display
// ----------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawSun();
    drawGround();
    drawFieldRows();
    drawHouse();
    drawTree(-0.82f, 0.16f);
    drawTree(-0.65f, 0.18f);
    drawTree(0.48f, 0.17f);

    drawIrrigation();
    drawCrops();
    drawTractor();
    drawDrone();

    drawText(-0.98f, 0.92f, "Smart Farming System");
    drawText(-0.98f, 0.86f, "Keys: T=Tractor D=Drone I=Irrigation G=Grow S=Spray");

    glutSwapBuffers();
}

// ----------------------------
// Animation
// ----------------------------
void update(int value)
{
    if (tractorMove)
    {
        tractorX += 0.01f;
        if (tractorX > 1.2f)
            tractorX = -1.2f;
    }

    if (droneMove)
    {
        droneX += 0.012f;
        if (droneX > 1.2f)
            droneX = -1.2f;
    }

    if (cropGrow)
    {
        cropGrowth += 0.0008f;
        if (cropGrowth > 0.11f)
            cropGrowth = 0.11f;
    }

    sprayOffset += 0.08f;
    irrigationOffset += 0.10f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ----------------------------
// Keyboard control
// ----------------------------
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 't':
    case 'T':
        tractorMove = !tractorMove;
        break;

    case 'd':
    case 'D':
        droneMove = !droneMove;
        break;

    case 'i':
    case 'I':
        irrigationOn = !irrigationOn;
        break;

    case 'g':
    case 'G':
        cropGrow = !cropGrow;
        break;

    case 's':
    case 'S':
        sprayOn = !sprayOn;
        break;

    case 'r':
    case 'R':
        // reset
        tractorX = -1.2f;
        droneX = -1.1f;
        cropGrowth = 0.02f;
        tractorMove = true;
        droneMove = true;
        irrigationOn = true;
        cropGrow = true;
        sprayOn = true;
        break;

    case 27:
        exit(0);
        break;
    }
}

// ----------------------------
// Init
// ----------------------------
void init()
{
    glClearColor(0.85f, 0.95f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

// ----------------------------
// Main
// ----------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Smart Farming System - Modern Agriculture Scene");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}