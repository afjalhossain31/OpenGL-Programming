#include <windows.h>
#include <GL/glut.h>

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);

    // Line 1 (Vertical - Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0, 3);
    glVertex2f(0, -3);

    // Line 2 (Horizontal - Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(3, 0);
    glVertex2f(-3, 0);

    // ✅ New Line (Diagonal - Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-3, -3);
    glVertex2f(3, 3);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Two lines");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}