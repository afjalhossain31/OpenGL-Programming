#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glOrtho(-5, 5, -5, 5, -1, 1);

    glColor3f(0.0, 0.0, 1.0);   // Blue color

    glBegin(GL_POLYGON);

    // Pentagon vertices
    glVertex2f(0.0, 3.0);
    glVertex2f(2.8, 1.0);
    glVertex2f(1.7, -2.5);
    glVertex2f(-1.7, -2.5);
    glVertex2f(-2.8, 1.0);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pentagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
