#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float cloudX = 0.0f;
float carX = -6.0f;
float sunY = 0.0f;

void init() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f); // sky blue
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.1416f * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawGround() {
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-10, -10);
    glVertex2f(10, -10);
    glVertex2f(10, -3);
    glVertex2f(-10, -3);
    glEnd();
}

void drawRoad() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-10, -8);
    glVertex2f(10, -8);
    glVertex2f(10, -6);
    glVertex2f(-10, -6);
    glEnd();
}

void drawHouse() {
    // House body
    glColor3f(1.0f, 0.8f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-7, -3);
    glVertex2f(-3, -3);
    glVertex2f(-3, 1);
    glVertex2f(-7, 1);
    glEnd();

    // Roof
    glColor3f(0.7f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-7.5f, 1);
    glVertex2f(-2.5f, 1);
    glVertex2f(-5, 4);
    glEnd();

    // Door
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.7f, -3);
    glVertex2f(-4.3f, -3);
    glVertex2f(-4.3f, -0.5f);
    glVertex2f(-5.7f, -0.5f);
    glEnd();

    // Window
    glColor3f(0.6f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-6.7f, -0.5f);
    glVertex2f(-5.8f, -0.5f);
    glVertex2f(-5.8f, 0.5f);
    glVertex2f(-6.7f, 0.5f);
    glEnd();
}

void drawTree(float x, float y) {
    // trunk
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.3f, y - 2);
    glVertex2f(x + 0.3f, y - 2);
    glVertex2f(x + 0.3f, y);
    glVertex2f(x - 0.3f, y);
    glEnd();

    // leaves
    glColor3f(0.0f, 0.7f, 0.0f);
    drawCircle(x, y + 0.8f, 1.2f);
}

void drawSun() {
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(6.5f, 6.5f + sunY, 1.2f);
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.7f);
    drawCircle(x + 0.8f, y + 0.2f, 0.8f);
    drawCircle(x + 1.6f, y, 0.7f);
}

void drawCar() {
    // car body
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(carX, -7);
    glVertex2f(carX + 3, -7);
    glVertex2f(carX + 3, -5.8f);
    glVertex2f(carX, -5.8f);
    glEnd();

    // upper body
    glColor3f(0.0f, 0.2f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(carX + 0.6f, -5.8f);
    glVertex2f(carX + 2.3f, -5.8f);
    glVertex2f(carX + 1.9f, -5.0f);
    glVertex2f(carX + 0.9f, -5.0f);
    glEnd();

    // wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(carX + 0.7f, -7.2f, 0.35f);
    drawCircle(carX + 2.3f, -7.2f, 0.35f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();
    drawRoad();
    drawSun();
    drawCloud(-6 + cloudX, 7);
    drawCloud(-1 + cloudX, 6.5f);
    drawHouse();
    drawTree(2, 0);
    drawTree(4.5f, 0.5f);
    drawCar();

    glFlush();
}

void update(int value) {
    cloudX += 0.05f;
    if (cloudX > 12) cloudX = -12;

    carX += 0.08f;
    if (carX > 10) carX = -10;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("2D Village Scene");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutMainLoop();

    return 0;
}