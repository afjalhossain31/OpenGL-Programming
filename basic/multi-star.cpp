#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(120, 150);
    glVertex2f(120, 200);
    glVertex2f(170, 200);
    glVertex2f(170, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(120, 200);
    glVertex2f(145, 250);
    glVertex2f(170, 200);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(170, 200);
    glVertex2f(220, 175);
    glVertex2f(170, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(170, 150);
    glVertex2f(145, 100);
    glVertex2f(120, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(120, 150);
    glVertex2f(70, 175);
    glVertex2f(120, 200);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(270, 200);
    glVertex2f(218, 175);
    glVertex2f(270, 150);
    glEnd();
    glFlush();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(270, 150);
    glVertex2f(270, 200);
    glVertex2f(320, 200);
    glVertex2f(320, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(270, 200);
    glVertex2f(295, 250);
    glVertex2f(320, 200);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(320, 200);
    glVertex2f(375, 175);
    glVertex2f(320, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(320, 150);
    glVertex2f(295, 100);
    glVertex2f(270, 150);
    glEnd();
    glFlush();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(420, 150);
    glVertex2f(420, 200);
    glVertex2f(470, 200);
    glVertex2f(470, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(420, 200);
    glVertex2f(373, 175);
    glVertex2f(420, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(420, 200);
    glVertex2f(445, 250);
    glVertex2f(470, 200);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(470, 200);
    glVertex2f(520, 175);
    glVertex2f(470, 150);
    glEnd();
    glFlush();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(470, 150);
    glVertex2f(445, 100);
    glVertex2f(420, 150);
    glEnd();
    glFlush();

}
void properties() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(0, 700, 0, 700, 0, 700); // Set the coordinate 
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Two lines");
    glutDisplayFunc(display);
    properties();
    glutMainLoop();

    return 0;
}