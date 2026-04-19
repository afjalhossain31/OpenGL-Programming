#include <windows.h>
#include <GL/glut.h>

float x = -500.0f;
float y = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + 120);
        glVertex2f(x + 200, y + 120);
        glVertex2f(x + 200, y);
    glEnd();

   
    float cx = x + 90;  
    float cy = y + 60;
    float r = 40;

    float c = 0;
    float d = r;
    int pk = 1 - r;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);

    while (c <= d) {
        glVertex2f(cx + c, cy + d);
        glVertex2f(cx + d, cy + c);
        glVertex2f(cx + d, cy - c);
        glVertex2f(cx + c, cy - d);
        glVertex2f(cx - c, cy - d);
        glVertex2f(cx - d, cy - c);
        glVertex2f(cx - d, cy + c);
        glVertex2f(cx - c, cy + d);

        if (pk < 0) {
            pk += 2 * c + 3;
        } else {
            pk += 2 * c - 2 * d + 5;
            c = c;
            d=d-1;
        }
        c = c + 1;
        d = d;
    }
    glEnd();


    if (x < 0 && y < 300) {
        x += 0.1f;
        y += 0.1f;
    }
   
    else if (x < 400 && y > 0) {
        x += 0.1f;
        y -= 0.1f;
    }
   
    else {
        x = -500;
        y = 0;
    }

    glFlush();
    glutPostRedisplay();
}

void properties() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glOrtho(-500, 500, -500, 500, -500, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Moving Bangladesh Flag");
    properties();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}