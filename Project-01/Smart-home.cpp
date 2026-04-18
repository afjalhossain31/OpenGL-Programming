#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

float tractorX = -320.0f;
float droneX = -250.0f;
float cloudX = -150.0f;
float windmillAngle = 0.0f;
float propellerAngle = 0.0f;
float waterOffset = 0.0f;
float cropScale = 0.7f;
bool cropGrow = true;

void plotPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        plotPoint(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void drawBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        plotPoint(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void drawMidpointCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 1 - r;

    while (x <= y) {
        plotPoint(xc + x, yc + y);
        plotPoint(xc - x, yc + y);
        plotPoint(xc + x, yc - y);
        plotPoint(xc - x, yc - y);
        plotPoint(xc + y, yc + x);
        plotPoint(xc - y, yc + x);
        plotPoint(xc + y, yc - x);
        plotPoint(xc - y, yc - x);

        x++;
        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void fillRect(int x1, int y1, int x2, int y2) {
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
}

void drawFilledCircle(float xc, float yc, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc, yc);
    for (int i = 0; i <= 360; i++) {
        float a = i * 3.1416f / 180.0f;
        glVertex2f(xc + cos(a) * r, yc + sin(a) * r);
    }
    glEnd();
}

void drawGround() {
    glColor3f(0.82f, 0.94f, 0.65f);
    fillRect(-400, -50, 400, 300);

    glColor3f(0.40f, 0.75f, 0.30f);
    fillRect(-400, -220, 400, -50);
}

void drawSun() {
    glColor3f(1.0f, 0.75f, 0.0f);
    drawFilledCircle(280, 220, 30);

    glColor3f(1.0f, 0.55f, 0.0f);
    for (int i = 0; i < 360; i += 30) {
        float a = i * 3.1416f / 180.0f;
        int x1 = 280 + cos(a) * 40;
        int y1 = 220 + sin(a) * 40;
        int x2 = 280 + cos(a) * 55;
        int y2 = 220 + sin(a) * 55;
        drawDDA(x1, y1, x2, y2);
    }
}

void drawCloud(float x, float y) {
    glColor3f(1, 1, 1);
    drawFilledCircle(x, y, 18);
    drawFilledCircle(x + 20, y + 10, 22);
    drawFilledCircle(x + 40, y, 18);
    drawFilledCircle(x + 18, y - 8, 18);
}

void drawFarmHouse() {
    // main body
    glColor3f(0.95f, 0.92f, 0.85f);
    fillRect(-320, -20, -200, 80);

    glColor3f(0, 0, 0);
    drawDDA(-320, -20, -200, -20);
    drawDDA(-200, -20, -200, 80);
    drawDDA(-200, 80, -320, 80);
    drawDDA(-320, 80, -320, -20);

    // roof
    glColor3f(0.65f, 0.22f, 0.18f);
    glBegin(GL_TRIANGLES);
    glVertex2i(-340, 80);
    glVertex2i(-180, 80);
    glVertex2i(-260, 140);
    glEnd();

    glColor3f(0, 0, 0);
    drawBresenham(-340, 80, -260, 140);
    drawBresenham(-260, 140, -180, 80);
    drawBresenham(-340, 80, -180, 80);

    // door
    glColor3f(0.45f, 0.28f, 0.15f);
    fillRect(-275, -20, -245, 35);

    glColor3f(0, 0, 0);
    drawDDA(-275, -20, -245, -20);
    drawDDA(-245, -20, -245, 35);
    drawDDA(-245, 35, -275, 35);
    drawDDA(-275, 35, -275, -20);

    // window
    glColor3f(0.55f, 0.82f, 0.95f);
    fillRect(-235, 20, -210, 50);

    glColor3f(0, 0, 0);
    drawDDA(-235, 20, -210, 20);
    drawDDA(-210, 20, -210, 50);
    drawDDA(-210, 50, -235, 50);
    drawDDA(-235, 50, -235, 20);
    drawDDA(-222, 20, -222, 50);
    drawDDA(-235, 35, -210, 35);
}

void drawWindmill() {
    // pole
    glColor3f(0.60f, 0.60f, 0.65f);
    fillRect(220, -40, 240, 130);

    glColor3f(0, 0, 0);
    drawBresenham(220, -40, 240, -40);
    drawBresenham(240, -40, 240, 130);
    drawBresenham(240, 130, 220, 130);
    drawBresenham(220, 130, 220, -40);

    // blades
    glPushMatrix();
    glTranslatef(230, 140, 0);
    glRotatef(windmillAngle, 0, 0, 1);

    glColor3f(0.95f, 0.95f, 0.98f);
    glBegin(GL_TRIANGLES);
    glVertex2i(0, 0); glVertex2i(65, 8); glVertex2i(65, -8);
    glVertex2i(0, 0); glVertex2i(-65, 8); glVertex2i(-65, -8);
    glVertex2i(0, 0); glVertex2i(8, 65); glVertex2i(-8, 65);
    glVertex2i(0, 0); glVertex2i(8, -65); glVertex2i(-8, -65);
    glEnd();

    glColor3f(0, 0, 0);
    drawMidpointCircle(0, 0, 6);

    glPopMatrix();
}

void drawFieldLines() {
    glColor3f(0.25f, 0.55f, 0.18f);
    for (int y = -70; y >= -180; y -= 20) {
        drawDDA(-380, y, 380, y);
    }
}

void drawCrops() {
    glColor3f(0.10f, 0.55f, 0.10f);

    for (int x = -360; x <= 360; x += 25) {
        for (int y = -85; y >= -185; y -= 20) {
            glPushMatrix();
            glTranslatef(x, y, 0);
            glScalef(1.0f, cropScale, 1.0f);

            glBegin(GL_TRIANGLES);
            glVertex2i(0, 0);
            glVertex2i(-4, 16);
            glVertex2i(0, 12);

            glVertex2i(0, 0);
            glVertex2i(4, 16);
            glVertex2i(0, 12);
            glEnd();

            glPopMatrix();
        }
    }
}

void drawIrrigationSystem() {
    // pipe
    glColor3f(0.3f, 0.3f, 0.35f);
    fillRect(-100, -40, 130, -25);

    glColor3f(0, 0, 0);
    drawDDA(-100, -40, 130, -40);
    drawDDA(130, -40, 130, -25);
    drawDDA(130, -25, -100, -25);
    drawDDA(-100, -25, -100, -40);

    // sprinkler stand
    glColor3f(0.4f, 0.4f, 0.45f);
    fillRect(10, -25, 20, 15);

    // water spray
    glColor3f(0.4f, 0.8f, 1.0f);
    for (int i = -5; i <= 5; i++) {
        float dx = i * 12.0f;
        float dy = sin((waterOffset + i) * 0.4f) * 8.0f;
        drawFilledCircle(15 + dx, 20 + dy, 2.5f);
        drawFilledCircle(15 + dx * 0.7f, 5 + dy * 0.7f, 2.0f);
    }
}

void drawTractor() {
    glPushMatrix();
    glTranslatef(tractorX, -145, 0);

    // body
    glColor3f(0.15f, 0.6f, 0.18f);
    glBegin(GL_POLYGON);
    glVertex2i(0, 15);
    glVertex2i(50, 15);
    glVertex2i(55, 35);
    glVertex2i(25, 35);
    glVertex2i(15, 50);
    glVertex2i(0, 50);
    glEnd();

    // engine/front
    glColor3f(0.12f, 0.48f, 0.15f);
    fillRect(50, 20, 85, 38);

    // window
    glColor3f(0.65f, 0.88f, 0.95f);
    fillRect(8, 28, 22, 45);

    // outline
    glColor3f(0, 0, 0);
    drawBresenham(0, 15, 50, 15);
    drawBresenham(50, 15, 55, 35);
    drawBresenham(55, 35, 25, 35);
    drawBresenham(25, 35, 15, 50);
    drawBresenham(15, 50, 0, 50);
    drawBresenham(0, 50, 0, 15);

    drawBresenham(50, 20, 85, 20);
    drawBresenham(85, 20, 85, 38);
    drawBresenham(85, 38, 50, 38);
    drawBresenham(50, 38, 50, 20);

    // wheels
    glColor3f(0, 0, 0);
    drawMidpointCircle(18, 10, 13);
    drawMidpointCircle(67, 10, 18);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawFilledCircle(18, 10, 5);
    drawFilledCircle(67, 10, 7);

    glPopMatrix();
}

void drawDrone() {
    glPushMatrix();
    glTranslatef(droneX, 120, 0);

    // body
    glColor3f(0.18f, 0.18f, 0.22f);
    fillRect(-18, -6, 18, 6);

    glColor3f(0, 0, 0);
    drawBresenham(-18, -6, 18, -6);
    drawBresenham(18, -6, 18, 6);
    drawBresenham(18, 6, -18, 6);
    drawBresenham(-18, 6, -18, -6);

    // arms
    drawBresenham(-18, 0, -35, 18);
    drawBresenham(18, 0, 35, 18);
    drawBresenham(-18, 0, -35, -18);
    drawBresenham(18, 0, 35, -18);

    // propellers
    int px[4] = {-35, 35, -35, 35};
    int py[4] = {18, 18, -18, -18};

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(px[i], py[i], 0);
        glRotatef(propellerAngle, 0, 0, 1);

        glColor3f(0.3f, 0.3f, 0.35f);
        glBegin(GL_TRIANGLES);
        glVertex2i(0, 0); glVertex2i(12, 2); glVertex2i(12, -2);
        glVertex2i(0, 0); glVertex2i(-12, 2); glVertex2i(-12, -2);
        glEnd();

        glColor3f(0, 0, 0);
        drawMidpointCircle(0, 0, 2);

        glPopMatrix();
    }

    glPopMatrix();
}

void drawTechPanel() {
    glColor3f(0.15f, 0.18f, 0.25f);
    fillRect(100, 40, 180, 95);

    glColor3f(0, 0, 0);
    drawDDA(100, 40, 180, 40);
    drawDDA(180, 40, 180, 95);
    drawDDA(180, 95, 100, 95);
    drawDDA(100, 95, 100, 40);

    glColor3f(0.0f, 1.0f, 0.4f);
    fillRect(110, 78, 170, 85);
    fillRect(110, 62, 155, 69);
    fillRect(110, 46, 165, 53);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();
    drawSun();
    drawCloud(cloudX, 210);
    drawCloud(cloudX + 100, 185);

    drawFarmHouse();
    drawWindmill();
    drawTechPanel();

    drawFieldLines();
    drawCrops();
    drawIrrigationSystem();
    drawDrone();
    drawTractor();

    glFlush();
}

void update(int value) {
    tractorX += 2.0f;
    if (tractorX > 420) tractorX = -420;

    droneX += 1.5f;
    if (droneX > 420) droneX = -420;

    cloudX += 0.4f;
    if (cloudX > 420) cloudX = -220;

    windmillAngle += 2.0f;
    if (windmillAngle > 360) windmillAngle -= 360;

    propellerAngle += 12.0f;
    if (propellerAngle > 360) propellerAngle -= 360;

    waterOffset += 1.0f;

    if (cropGrow) cropScale += 0.002f;
    else cropScale -= 0.002f;

    if (cropScale >= 1.05f) cropGrow = false;
    if (cropScale <= 0.7f) cropGrow = true;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void init() {
    glClearColor(0.58f, 0.84f, 0.98f, 1.0f);
    glPointSize(2.0);
    gluOrtho2D(-400, 400, -250, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1100, 700);
    glutInitWindowPosition(100, 50);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Smart Farming System");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);
    glutMainLoop();
    return 0;
}