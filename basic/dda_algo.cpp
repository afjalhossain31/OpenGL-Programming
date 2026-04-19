#include <windows.h>
#include <GL/glut.h>
#include <math.h>
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float x1 = 50, y1 = 50, x2 = 400, y2 = 400;
    float xdif = x2 - x1;
    float ydif = y2 - y1;
    int steps;
    if (fabs(xdif) > fabs(ydif))
    {
        steps = fabs(xdif);
    }
    else
    {
        steps = fabs(ydif);
    }
    float xinc = xdif / steps;
    float yinc = ydif / steps;
    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < steps; i++)
    {
        glVertex2f(x, y);
        x = x + xinc;
        y = y + yinc;
    }
    glEnd();
    glFlush();
}
void properties() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(50, 650, 50, 650, 0, 650);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");
    properties();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}