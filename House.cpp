#include <windows.h>
#include <GL/glut.h>

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glOrtho(-10, 10, -10, 10, -1, 1);

    // House body (rectangle)
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-4, -4);
    glVertex2f(4, -4);
    glVertex2f(4, 4);
    glVertex2f(-4, 4);
    glEnd();

    // Roof 
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-5, 4);
    glVertex2f(5, 4);
    glVertex2f(0, 8);
    glEnd();

    // Door
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -4);
    glVertex2f(1, -4);
    glVertex2f(1, 0);
    glVertex2f(-1, 0);
    glEnd();

    // Window
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-3, -1);
    glVertex2f(-2, -1);
    glVertex2f(-2, 0);
    glVertex2f(-3, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(2, -1);
    glVertex2f(3, -1);
    glVertex2f(3, 0);
    glVertex2f(2, 0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("House using GL_POLYGON");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
