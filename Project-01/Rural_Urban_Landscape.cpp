#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// ---------------- GLOBAL VARIABLES ----------------
int currentScene = 1;

float sunX = -0.8f;
float cloudX = -1.2f;
float birdX = -1.0f;

float highwayCarX = -1.3f;
float highwayBusX = 1.3f;

float cityCarX = -1.4f;
float cityBusX = 1.4f;

float trafficTimer = 0.0f;

// ---------------- UTILITY FUNCTIONS ----------------
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

// ---------------- BASIC OBJECTS ----------------
void drawSun()
{
    glColor3f(1.0f, 0.9f, 0.0f);
    drawCircle(sunX, 0.8f, 0.08f);
}

void drawCloud(float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.05f);
    drawCircle(x + 0.05f, y + 0.02f, 0.06f);
    drawCircle(x + 0.10f, y, 0.05f);
    drawCircle(x + 0.05f, y - 0.02f, 0.05f);
}

void drawTree(float x, float y)
{
    glColor3f(0.55f, 0.27f, 0.07f);
    drawRect(x - 0.015f, y - 0.12f, x + 0.015f, y + 0.03f);

    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle(x, y + 0.08f, 0.06f);
    drawCircle(x - 0.04f, y + 0.05f, 0.05f);
    drawCircle(x + 0.04f, y + 0.05f, 0.05f);
}

void drawHouse(float x, float y)
{
    glColor3f(0.9f, 0.75f, 0.55f);
    drawRect(x, y, x + 0.18f, y + 0.14f);

    glColor3f(0.65f, 0.15f, 0.15f);
    drawTriangle(x - 0.02f, y + 0.14f, x + 0.09f, y + 0.24f, x + 0.20f, y + 0.14f);

    glColor3f(0.4f, 0.2f, 0.1f);
    drawRect(x + 0.07f, y, x + 0.11f, y + 0.08f);

    glColor3f(0.4f, 0.8f, 1.0f);
    drawRect(x + 0.02f, y + 0.06f, x + 0.055f, y + 0.10f);
    drawRect(x + 0.125f, y + 0.06f, x + 0.16f, y + 0.10f);
}

void drawBird(float x, float y)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x - 0.03f, y);
    glVertex2f(x, y + 0.02f);
    glVertex2f(x, y + 0.02f);
    glVertex2f(x + 0.03f, y);
    glEnd();
}

void drawCar(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.1f, 0.3f, 0.9f);
    drawRect(-0.10f, 0.00f, 0.10f, 0.07f);
    drawRect(-0.05f, 0.07f, 0.05f, 0.12f);

    glColor3f(0.7f, 0.9f, 1.0f);
    drawRect(-0.04f, 0.08f, 0.04f, 0.11f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.06f, -0.005f, 0.025f);
    drawCircle(0.06f, -0.005f, 0.025f);

    glPopMatrix();
}

void drawBus(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.9f, 0.2f, 0.2f);
    drawRect(-0.16f, 0.00f, 0.16f, 0.10f);

    glColor3f(0.75f, 0.9f, 1.0f);
    for (float i = -0.12f; i <= 0.08f; i += 0.05f)
        drawRect(i, 0.04f, i + 0.035f, 0.08f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.10f, -0.005f, 0.025f);
    drawCircle(0.10f, -0.005f, 0.025f);

    glPopMatrix();
}

void drawBuilding(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    drawRect(x, y, x + w, y + h);

    glColor3f(0.8f, 0.95f, 1.0f);
    for (float row = y + 0.05f; row < y + h - 0.03f; row += 0.08f)
    {
        for (float col = x + 0.03f; col < x + w - 0.03f; col += 0.06f)
        {
            drawRect(col, row, col + 0.03f, row + 0.04f);
        }
    }
}

// ---------------- SCENE 1: VILLAGE ----------------
void drawVillageScene()
{
    // Sky
    glColor3f(0.55f, 0.85f, 1.0f);
    drawRect(-1.0f, 0.2f, 1.0f, 1.0f);

    // Ground
    glColor3f(0.25f, 0.75f, 0.25f);
    drawRect(-1.0f, -1.0f, 1.0f, 0.2f);

    // Pond
    glColor3f(0.25f, 0.65f, 0.95f);
    drawRect(-0.95f, -0.65f, -0.45f, -0.35f);

    // Field
    glColor3f(0.4f, 0.8f, 0.2f);
    drawRect(-0.35f, -0.70f, 0.55f, -0.20f);

    // Crops lines
    glColor3f(0.2f, 0.55f, 0.1f);
    for (float x = -0.30f; x <= 0.50f; x += 0.08f)
    {
        glBegin(GL_LINES);
        glVertex2f(x, -0.70f);
        glVertex2f(x, -0.20f);
        glEnd();
    }

    drawSun();
    drawCloud(cloudX, 0.75f);
    drawCloud(cloudX + 0.50f, 0.65f);

    // Houses
    drawHouse(-0.75f, -0.10f);
    drawHouse(-0.40f, -0.05f);

    // Trees
    drawTree(0.70f, 0.10f);
    drawTree(0.85f, 0.12f);
    drawTree(0.55f, 0.08f);
    drawTree(-0.15f, 0.08f);

    // Birds
    drawBird(birdX, 0.62f);
    drawBird(birdX + 0.10f, 0.67f);
    drawBird(birdX + 0.20f, 0.63f);

    drawText(-0.95f, 0.92f, "Scene 1: Village View");
    drawText(-0.95f, 0.86f, "A peaceful rural landscape with fields, trees, ponds, and simple homes.");
}

// ---------------- SCENE 2: HIGHWAY ----------------
void drawHighwayScene()
{
    // Sky
    glColor3f(0.60f, 0.85f, 1.0f);
    drawRect(-1.0f, 0.1f, 1.0f, 1.0f);

    // Ground
    glColor3f(0.35f, 0.8f, 0.3f);
    drawRect(-1.0f, -1.0f, 1.0f, 0.1f);

    drawSun();
    drawCloud(cloudX, 0.75f);
    drawCloud(cloudX + 0.60f, 0.68f);

    // Highway
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRect(-1.0f, -0.55f, 1.0f, -0.10f);

    // Divider lines
    glColor3f(1.0f, 1.0f, 0.0f);
    for (float x = -0.95f; x <= 0.95f; x += 0.18f)
    {
        drawRect(x, -0.335f, x + 0.10f, -0.315f);
    }

    // Trees beside road
    for (float x = -0.90f; x <= 0.90f; x += 0.25f)
    {
        drawTree(x, -0.02f);
    }

    // Electric poles
    glColor3f(0.3f, 0.3f, 0.3f);
    for (float x = -0.85f; x <= 0.85f; x += 0.30f)
    {
        drawRect(x, -0.10f, x + 0.01f, 0.18f);
        glBegin(GL_LINES);
        glVertex2f(x + 0.01f, 0.16f);
        glVertex2f(x + 0.15f, 0.16f);
        glEnd();
    }

    // Signboard
    glColor3f(0.1f, 0.5f, 0.1f);
    drawRect(0.65f, 0.00f, 0.88f, 0.12f);
    glColor3f(0.4f, 0.2f, 0.1f);
    drawRect(0.75f, -0.10f, 0.78f, 0.00f);

    drawCar(highwayCarX, -0.48f);
    drawBus(highwayBusX, -0.26f);

    drawText(-0.95f, 0.92f, "Scene 2: Highway View");
    drawText(-0.95f, 0.86f, "A panoramic highway connecting rural and urban landscapes.");
}

// ---------------- SCENE 3: CITY ----------------
void drawTrafficLight(float x, float y)
{
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRect(x, y, x + 0.04f, y + 0.18f);
    drawRect(x + 0.015f, y - 0.14f, x + 0.025f, y);

    // 3 states based on timer
    int state = ((int)trafficTimer / 120) % 3;

    if (state == 0) glColor3f(1.0f, 0.0f, 0.0f); else glColor3f(0.3f, 0.0f, 0.0f);
    drawCircle(x + 0.02f, y + 0.14f, 0.012f);

    if (state == 1) glColor3f(1.0f, 1.0f, 0.0f); else glColor3f(0.3f, 0.3f, 0.0f);
    drawCircle(x + 0.02f, y + 0.09f, 0.012f);

    if (state == 2) glColor3f(0.0f, 1.0f, 0.0f); else glColor3f(0.0f, 0.3f, 0.0f);
    drawCircle(x + 0.02f, y + 0.04f, 0.012f);
}

void drawCityScene()
{
    // Sky
    glColor3f(0.70f, 0.88f, 1.0f);
    drawRect(-1.0f, 0.0f, 1.0f, 1.0f);

    drawSun();
    drawCloud(cloudX, 0.78f);

    // Buildings
    drawBuilding(-0.95f, -0.10f, 0.18f, 0.65f, 0.55f, 0.55f, 0.70f);
    drawBuilding(-0.72f, -0.10f, 0.20f, 0.80f, 0.40f, 0.45f, 0.65f);
    drawBuilding(-0.45f, -0.10f, 0.18f, 0.55f, 0.60f, 0.50f, 0.75f);
    drawBuilding(-0.20f, -0.10f, 0.22f, 0.90f, 0.50f, 0.55f, 0.60f);
    drawBuilding(0.08f, -0.10f, 0.18f, 0.70f, 0.65f, 0.50f, 0.55f);
    drawBuilding(0.32f, -0.10f, 0.20f, 0.82f, 0.45f, 0.55f, 0.72f);
    drawBuilding(0.58f, -0.10f, 0.16f, 0.58f, 0.55f, 0.45f, 0.55f);
    drawBuilding(0.78f, -0.10f, 0.17f, 0.75f, 0.45f, 0.48f, 0.65f);

    // Road
    glColor3f(0.15f, 0.15f, 0.15f);
    drawRect(-1.0f, -0.75f, 1.0f, -0.25f);

    // Divider
    glColor3f(1.0f, 1.0f, 0.0f);
    for (float x = -0.95f; x <= 0.95f; x += 0.18f)
    {
        drawRect(x, -0.51f, x + 0.10f, -0.49f);
    }

    // Footpath
    glColor3f(0.6f, 0.6f, 0.6f);
    drawRect(-1.0f, -0.25f, 1.0f, -0.15f);

    // Street lights
    for (float x = -0.90f; x <= 0.90f; x += 0.30f)
    {
        glColor3f(0.25f, 0.25f, 0.25f);
        drawRect(x, -0.15f, x + 0.01f, 0.18f);
        glBegin(GL_LINES);
        glVertex2f(x + 0.01f, 0.16f);
        glVertex2f(x + 0.06f, 0.16f);
        glEnd();

        glColor3f(1.0f, 1.0f, 0.6f);
        drawCircle(x + 0.065f, 0.16f, 0.012f);
    }

    drawTrafficLight(-0.10f, -0.02f);

    drawCar(cityCarX, -0.68f);
    drawBus(cityBusX, -0.42f);

    drawText(-0.95f, 0.92f, "Scene 3: City View");
    drawText(-0.95f, 0.86f, "A busy urban landscape with tall buildings, roads, and vehicles.");
}

// ---------------- DISPLAY ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScene == 1)
        drawVillageScene();
    else if (currentScene == 2)
        drawHighwayScene();
    else if (currentScene == 3)
        drawCityScene();

    drawText(-0.95f, -0.95f, "Press 1 = Village, 2 = Highway, 3 = City, R = Reset, ESC = Exit");

    glutSwapBuffers();
}

// ---------------- ANIMATION ----------------
void update(int value)
{
    sunX += 0.0008f;
    if (sunX > 1.2f)
        sunX = -1.2f;

    cloudX += 0.0015f;
    if (cloudX > 1.2f)
        cloudX = -1.3f;

    birdX += 0.006f;
    if (birdX > 1.2f)
        birdX = -1.2f;

    highwayCarX += 0.010f;
    if (highwayCarX > 1.3f)
        highwayCarX = -1.3f;

    highwayBusX -= 0.008f;
    if (highwayBusX < -1.4f)
        highwayBusX = 1.3f;

    cityCarX += 0.012f;
    if (cityCarX > 1.3f)
        cityCarX = -1.4f;

    cityBusX -= 0.010f;
    if (cityBusX < -1.4f)
        cityBusX = 1.4f;

    trafficTimer += 1.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ---------------- KEYBOARD ----------------
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        currentScene = 1;
        break;
    case '2':
        currentScene = 2;
        break;
    case '3':
        currentScene = 3;
        break;
    case 'r':
    case 'R':
        currentScene = 1;
        sunX = -0.8f;
        cloudX = -1.2f;
        birdX = -1.0f;
        highwayCarX = -1.3f;
        highwayBusX = 1.3f;
        cityCarX = -1.4f;
        cityBusX = 1.4f;
        trafficTimer = 0.0f;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ---------------- INIT ----------------
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

// ---------------- MAIN ----------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 700);
    glutCreateWindow("A Journey Through Perspectives: Rural to Urban Landscapes");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}