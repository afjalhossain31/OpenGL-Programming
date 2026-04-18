#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

// Bresenham's Line Drawing Algorithm
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x1, y1);
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
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int xc = 300, yc = 300;
    int size = 200;
    glColor3f(1.0, 0.0, 0.0); // Red Diamond
    //2D Diamond using Bresenham's Line Algorithm
    bresenhamLine(xc, yc + size, xc + size, yc); // Top to Right
    bresenhamLine(xc + size, yc, xc, yc - size); // Right to Bottom
    bresenhamLine(xc, yc - size, xc - size, yc); // Bottom to Left
    bresenhamLine(xc - size, yc, xc, yc + size); // Left to Top

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1); // White background
    glPointSize(2.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bresenham 2D Diamond Shape");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}