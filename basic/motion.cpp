#include <windows.h>
#include <GL/glut.h>

float x = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    if (x < 10) {
        glColor3f(1.0f, 0.0f, 0.0f); // Red
    }
    else if (x < 20) {
        glColor3f(0.0f, 1.0f, 0.0f); // Green
    }
    else if (x < 30) {
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
    }
    else {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(x, 0);
    glVertex2f(x, 10.0f);
    glVertex2f(x + 10, 0);
    glEnd();

    // Update position
    if (x < 40) {
        x = x + 0.5;
    }
    else {
        x = 0;
    }

    glFlush();

    glutPostRedisplay();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(-40, 40, -40, 40, -40, 40);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Simple Triangle");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    init();
    glutDisplayFunc(display);
    glutMainLoop();


    return 0;
}