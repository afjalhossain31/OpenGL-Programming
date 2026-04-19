#include <windows.h>
#include <GL/glut.h>
float x = 0;
float y = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int r = 100;
    int pk = 1 - r;
    float x = 0, y = r;
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f); 

    while (x < y) {
        glVertex2f(x, y);
        glVertex2f(y, x);
        glVertex2f(-y, x);
        glVertex2f(x, -y);
        glVertex2f(-y, -x);
        glVertex2f(-x, -y);
        glVertex2f(-x, y);
        glVertex2f(y, -x);

        if (pk < 0) {
            pk = pk + 2 * x + 3;
            x = x + 1;
        }
        else {
            pk = pk + 2 * x - 2 * y + 5;
            x = x + 1;
            y = y - 1;
        }
    }
    glEnd();
    glFlush();   
}
void properties() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(-400, 400, -400, 400, -400, 400);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Two lines");
    properties();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}