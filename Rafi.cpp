#include <bits/stdc++.h>
#include <windows.h>
#include <GL/glut.h>
using namespace std;

float minuteAngle = 0.0f;
float hourAngle = 0.0f;

float cloud1Offset = 0.0f;
float cloud2Offset = 0.0f;
float cloud3Offset = 0.0f;
float cloud4Offset = 0.0f;
float cloud5Offset = 0.0f;
float cloud6Offset = 0.0f;
float cloud7Offset = 0.0f;

float balloonOffset1 = 0.0f;
float balloonOffset2 = 0.0f;
float balloonOffset3 = 0.0f;

void drawPoint(float x, float y, float size = 1.0, float r = 0.0, float g = 0.0, float b = 0.0) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2f(x, y);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawCircleMidpointFilled(float cx, float cy, float r, float R = 0, float G = 0, float B = 0) {
    float pk = 1 - r;
    float x = 0, y = r;

    glColor3f(R, G, B);

    while (x <= y) {
        glBegin(GL_LINES);
        glVertex2f(-x + cx, y + cy);
        glVertex2f(x + cx, y + cy);
        glVertex2f(-x + cx, -y + cy);
        glVertex2f(x + cx, -y + cy);
        glVertex2f(-y + cx, x + cy);
        glVertex2f(y + cx, x + cy);
        glVertex2f(-y + cx, -x + cy);
        glVertex2f(y + cx, -x + cy);
        glEnd();

        if (pk < 0) {
            pk = pk + 2 * x + 3;
            x++;
        }
        else {
            pk = pk + 2 * x - 2 * y + 5;
            x++;
            y--;
        }
    }
}

void bresenhams(int x1, int y1, int x2, int y2, float size = 1, float R = 0, float G = 0, float B = 0) {
    int x = x1, y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;

    double m = double(dy) / double(dx);

    drawPoint(x, y, size, R, G, B);
    // Case 01
    if (0 <= m and m <= 1) {
        int pk = 2 * dy - dx;
        for (int i = 0; i < (x2 - x1); ++i) {
            if (pk < 0) {
                x += 1;
                pk = pk + 2 * dy;
            }
            else {
                x += 1;
                y += 1;
                pk = pk + 2 * dy - 2 * dx;
            }
        }
    }

    // Case 2
    if (m > 1) {
        int pk = 2 * dx - dy;
        for (int i = 0; i < (y2 - y1); ++i) {
            if (pk < 0) {
                y += 1;
                pk = pk + 2 * dx;
            }
            else {
                x += 1;
                y += 1;
                pk = pk + 2 * dx - 2 * dy;
            }
            drawPoint(x, y, size, R, G, B);
        }
    }

    // Case 3
    if (m < 0 && m >= -1) {
        int pk = 2 * dy - dx;
        for (int i = 0; i < (x2 - x1); ++i) {
            if (pk < 0) {
                x += 1;
                pk = pk + 2 * (y1 - y2);
            }
            else {
                x += 1;
                y -= 1;
                pk = pk + 2 * (y1 - y2) - 2 * dx;
            }
            drawPoint(x, y, size, R, G, B);
        }
    }

    // Case 4
    if (m < -1) {
        int pk = 2 * dx - dy;
        for (int i = 0; i < (y1 - y2); ++i) {
            if (pk < 0) {
                y -= 1;
                pk = pk + 2 * dx;
            }
            else {
                x += 1;
                y -= 1;
                pk = pk + 2 * dx - 2 * (y1 - y2);
            }
            drawPoint(x, y, size, R, G, B);
        }
    }

}

void drawConnectedLines(vector<pair<float, float>> v) {
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 0, 0);
    for (int i = 0; i < v.size(); ++i) {
        glVertex2f(v[i].first, v[i].second);
    }
    glEnd();
}

void drawTriangle(vector<pair<float, float>> v) {
    assert(v.size() == 3);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    for (int i = 0; i < v.size(); ++i) {
        glVertex2f(v[i].first, v[i].second);
    }
    glEnd();
}

void drawQuads(vector<pair<float, float>> v) {
    assert(v.size() == 4);
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    for (int i = 0; i < v.size(); ++i) {
        glVertex2f(v[i].first, v[i].second);
    }
    glEnd();
}

void translateDown(vector<pair<float, float>>& v) {

}

void drawPolygon(vector<pair<float, float>>& v) {
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    for (int i = 0; i < v.size(); ++i) {
        glVertex2f(v[i].first, v[i].second);
    }
    glEnd();
}

void drawLineDDA(float x1, float y1, float x2, float y2, int size = 1, float r = 0.0, float g = 0.0, float b = 0.0) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float abs_dx = (dx < 0) ? -dx : dx;
    float abs_dy = (dy < 0) ? -dy : dy;
    float steps = (abs_dx > abs_dy) ? abs_dx : abs_dy;

    float inc_x = dx / steps;
    float inc_y = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        drawPoint(x, y, size, r, g, b);
        x += inc_x;
        y += inc_y;
    }
}

void drawHouse(float x, float y) {
    glBegin(GL_POLYGON);
    glColor3f(0.98, 0.92, 0.85); // softer cream
    glVertex2f(x, y);
    glVertex2f(x, y + 80);
    glVertex2f(x + 55, y + 80 + 50);
    glVertex2f(x + 55 + 55, y + 80);
    glVertex2f(x + 55 + 55, y);
    glEnd();

    // roof
    glBegin(GL_POLYGON);
    glColor3f(0.45, 0.78, 0.55); // muted green
    glVertex2f(x + 55, y + 80 + 50);
    glVertex2f(x + 55 + 115, y + 80 + 50);
    glVertex2f(x + 55 + 120 + 55, y + 80);
    glVertex2f(x + 55 + 55, y + 80);
    glEnd();

    // edge
    glBegin(GL_QUADS);
    glColor3f(0.40, 0.70, 0.50);
    glVertex2f(x, y + 80);
    glVertex2f(x - 13, y + 80);
    glVertex2f(x + 55, y + 80 + 50);
    glVertex2f(x + 55 + 15, y + 80 + 50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.90, 0.80, 0.55); // warm sand tone
    glVertex2f(x + 55 + 55, y + 80);
    glVertex2f(x + 55 + 55 + 105, y + 80);
    glVertex2f(x + 55 + 55 + 105, y);
    glVertex2f(x + 55 + 55, y);
    glEnd();

    int translate = 130;

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.25, 0.15); // richer wood
    glVertex2f(x + 20 + translate, y);
    glVertex2f(x + 20 + translate, y + 50);
    glVertex2f(x + 20 + 30 + translate, y + 50);
    glVertex2f(x + 20 + 30 + translate, y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.75, 0.65, 0.55); // soft wood highlight
    glVertex2f(x + 25 + translate, y + 5);
    glVertex2f(x + 25 + translate, y + 45);
    glVertex2f(x + 45 + translate, y + 45);
    glVertex2f(x + 45 + translate, y + 5);
    glEnd();

    translate = 25;

    glBegin(GL_QUADS);
    glColor3f(0.25, 0.25, 0.28); // charcoal window frame
    glVertex2f(x + 38, y + 58 - translate);
    glVertex2f(x + 38, y + 94 - translate);
    glVertex2f(x + 72, y + 94 - translate);
    glVertex2f(x + 72, y + 58 - translate);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.65, 0.85, 0.95); // sky glass
    glVertex2f(x + 41, y + 61 - translate);
    glVertex2f(x + 41, y + 91 - translate);
    glVertex2f(x + 69, y + 91 - translate);
    glVertex2f(x + 69, y + 61 - translate);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.25, 0.25, 0.28);
    glVertex2f(x + 55, y + 61 - translate);
    glVertex2f(x + 55, y + 91 - translate);
    glVertex2f(x + 41, y + 76 - translate);
    glVertex2f(x + 69, y + 76 - translate);
    glEnd();
}

void drawHouse2(float x, float y) {
    glBegin(GL_POLYGON);
    glColor3f(0.75, 0.88, 0.98);
    glVertex2f(x, y);
    glVertex2f(x, y + 100);
    glVertex2f(x + 60, y + 150);
    glVertex2f(x + 120, y + 100);
    glVertex2f(x + 120, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.35, 0.35, 0.55);
    glVertex2f(x - 10, y + 100);
    glVertex2f(x + 60, y + 175);
    glVertex2f(x + 130, y + 100);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55, 0.30, 0.20);
    glVertex2f(x + 45, y);
    glVertex2f(x + 45, y + 60);
    glVertex2f(x + 75, y + 60);
    glVertex2f(x + 75, y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.80, 0.70, 0.60);
    glVertex2f(x + 50, y + 5);
    glVertex2f(x + 50, y + 55);
    glVertex2f(x + 70, y + 55);
    glVertex2f(x + 70, y + 5);
    glEnd();

    float cx = x + 60;
    float cy = y + 105;

    drawCircleMidpointFilled(cx, cy, 18, 0.25, 0.25, 0.30);
    drawCircleMidpointFilled(cx, cy, 14, 0.70, 0.90, 1.00);

    glBegin(GL_LINES);
    glColor3f(0.25, 0.25, 0.30);
    glVertex2f(cx - 14, cy);
    glVertex2f(cx + 14, cy);
    glVertex2f(cx, cy - 14);
    glVertex2f(cx, cy + 14);
    glEnd();
}
void drawHouse3(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.78, 0.60); // warm peach
    glVertex2f(x, y);
    glVertex2f(x, y + 90);
    glVertex2f(x + 140, y + 90);
    glVertex2f(x + 140, y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55, 0.30, 0.30); // cocoa top
    glVertex2f(x + 30, y + 90);
    glVertex2f(x + 30, y + 140);
    glVertex2f(x + 110, y + 140);
    glVertex2f(x + 110, y + 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.35, 0.20, 0.20);
    glVertex2f(x + 25, y + 140);
    glVertex2f(x + 25, y + 150);
    glVertex2f(x + 115, y + 150);
    glVertex2f(x + 115, y + 140);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.25, 0.15);
    glVertex2f(x + 15, y);
    glVertex2f(x + 15, y + 55);
    glVertex2f(x + 45, y + 55);
    glVertex2f(x + 45, y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.80, 0.70, 0.60);
    glVertex2f(x + 20, y + 5);
    glVertex2f(x + 20, y + 50);
    glVertex2f(x + 40, y + 50);
    glVertex2f(x + 40, y + 5);
    glEnd();

    float cx1 = x + 105;
    float cy1 = y + 50;

    drawCircleMidpointFilled(cx1, cy1, 16, 0.25, 0.25, 0.30);
    drawCircleMidpointFilled(cx1, cy1, 12, 0.75, 0.90, 1.00);

    float cx2 = x + 70;
    float cy2 = y + 115;

    drawCircleMidpointFilled(cx2, cy2, 14, 0.25, 0.25, 0.30);
    drawCircleMidpointFilled(cx2, cy2, 10, 0.75, 0.90, 1.00);

    glBegin(GL_LINES);
    glColor3f(0.25, 0.25, 0.30);
    glVertex2f(cx2 - 10, cy2);
    glVertex2f(cx2 + 10, cy2);
    glVertex2f(cx2, cy2 - 10);
    glVertex2f(cx2, cy2 + 10);
    glEnd();
}

void drawHouse4(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.80, 0.85);
    glVertex2f(x, y);
    glVertex2f(x, y + 85);
    glVertex2f(x + 130, y + 85);
    glVertex2f(x + 130, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.45, 0.25, 0.30);
    glVertex2f(x - 10, y + 85);
    glVertex2f(x + 65, y + 155);
    glVertex2f(x + 140, y + 85);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55, 0.30, 0.30);
    glVertex2f(x + 95, y + 120 - 12);
    glVertex2f(x + 95, y + 165 - 12);
    glVertex2f(x + 115, y + 165 - 12);
    glVertex2f(x + 115, y + 120 - 12);
    glEnd();

    drawCircleMidpointFilled(x + 105, y + 175 - 12, 6, 0.92, 0.92, 0.92);
    drawCircleMidpointFilled(x + 112, y + 185 - 12, 5, 0.92, 0.92, 0.92);
    drawCircleMidpointFilled(x + 118, y + 195 - 12, 4, 0.92, 0.92, 0.92);

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.25, 0.15);
    glVertex2f(x + 45, y);
    glVertex2f(x + 45, y + 55);
    glVertex2f(x + 85, y + 55);
    glVertex2f(x + 85, y);
    glEnd();

    drawPoint(x + 78, y + 28, 5, 1.0, 0.85, 0.25);

    float cx = x + 65;
    float cy = y + 105;

    drawCircleMidpointFilled(cx, cy, 16, 0.25, 0.25, 0.30);
    drawCircleMidpointFilled(cx, cy, 12, 0.70, 0.90, 1.00);

    glBegin(GL_LINES);
    glColor3f(0.25, 0.25, 0.30);
    glVertex2f(cx - 12, cy);
    glVertex2f(cx + 12, cy);
    glVertex2f(cx, cy - 12);
    glVertex2f(cx, cy + 12);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.85, 0.60, 0.40);
    glVertex2f(x + 40, y + 80);
    glVertex2f(x + 40, y + 90);
    glVertex2f(x + 90, y + 90);
    glVertex2f(x + 90, y + 80);
    glEnd();

    drawPoint(x + 50, y + 88, 4, 1.0, 0.3, 0.6);
    drawPoint(x + 65, y + 88, 4, 1.0, 0.65, 0.25);
    drawPoint(x + 80, y + 88, 4, 0.35, 0.85, 0.45);
}

void drawHouse5(float x, float y) {
    glBegin(GL_POLYGON);
    glColor3f(0.92, 0.86, 0.95);
    glVertex2f(x, y);
    glVertex2f(x, y + 80);
    glVertex2f(x + 55, y + 80 + 50);
    glVertex2f(x + 55 + 55, y + 80);
    glVertex2f(x + 55 + 55, y);
    glEnd();

    // roof
    glBegin(GL_POLYGON);
    glColor3f(0.65, 0.45, 0.80);
    glVertex2f(x + 55, y + 80 + 50);
    glVertex2f(x + 55 + 115, y + 80 + 50);
    glVertex2f(x + 55 + 120 + 55, y + 80);
    glVertex2f(x + 55 + 55, y + 80);
    glEnd();

    // left edge
    glBegin(GL_QUADS);
    glColor3f(0.55, 0.40, 0.70);
    glVertex2f(x, y + 80);
    glVertex2f(x - 13, y + 80);
    glVertex2f(x + 55, y + 80 + 50);
    glVertex2f(x + 55 + 15, y + 80 + 50);
    glEnd();

    // right side wall
    glBegin(GL_QUADS);
    glColor3f(0.98, 0.88, 0.70);
    glVertex2f(x + 55 + 55, y + 80);
    glVertex2f(x + 55 + 55 + 105, y + 80);
    glVertex2f(x + 55 + 55 + 105, y);
    glVertex2f(x + 55 + 55, y);
    glEnd();

    int translate = 130;

    // door frame
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.28, 0.18);
    glVertex2f(x + 20 + translate, y);
    glVertex2f(x + 20 + translate, y + 50);
    glVertex2f(x + 20 + 30 + translate, y + 50);
    glVertex2f(x + 20 + 30 + translate, y);
    glEnd();

    // door panel
    glBegin(GL_QUADS);
    glColor3f(0.75, 0.65, 0.55);
    glVertex2f(x + 25 + translate, y + 5);
    glVertex2f(x + 25 + translate, y + 45);
    glVertex2f(x + 45 + translate, y + 45);
    glVertex2f(x + 45 + translate, y + 5);
    glEnd();

    translate = 25;

    // window frame
    glBegin(GL_QUADS);
    glColor3f(0.20, 0.20, 0.25);
    glVertex2f(x + 38, y + 58 - translate);
    glVertex2f(x + 38, y + 94 - translate);
    glVertex2f(x + 72, y + 94 - translate);
    glVertex2f(x + 72, y + 58 - translate);
    glEnd();

    // window glass
    glBegin(GL_QUADS);
    glColor3f(0.60, 0.85, 0.95);
    glVertex2f(x + 41, y + 61 - translate);
    glVertex2f(x + 41, y + 91 - translate);
    glVertex2f(x + 69, y + 91 - translate);
    glVertex2f(x + 69, y + 61 - translate);
    glEnd();

    // cross
    glBegin(GL_LINES);
    glColor3f(0.20, 0.20, 0.25);
    glVertex2f(x + 55, y + 61 - translate);
    glVertex2f(x + 55, y + 91 - translate);
    glVertex2f(x + 41, y + 76 - translate);
    glVertex2f(x + 69, y + 76 - translate);
    glEnd();
}

void church(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0.93, 0.82, 0.68);
    glVertex2f(x, y);
    glVertex2f(x, y + 170);
    glVertex2f(x + 250, y + 170);
    glVertex2f(x + 250, y);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.85, 0.72, 0.58);
    glVertex2f(x + 25, y + 170);
    glVertex2f(x + 25, y + 170 + 65);
    glVertex2f(x + 25 + 200, y + 170 + 65);
    glVertex2f(x + 25 + 200, y + 170);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.78, 0.65, 0.52);
    glVertex2f(x - 5, y + 170);
    glVertex2f(x - 5, y + 175);
    glVertex2f(x + 255, y + 175);
    glVertex2f(x + 255, y + 170);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.961, 0.647, 0.29);
    glVertex2f(x + 25 + 15, y + 170 + 65);
    glVertex2f(x + 125, y + 170 + 65 + 150);
    glVertex2f(x + 25 + 200 - 15, y + 170 + 65);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.78, 0.65, 0.52);
    glVertex2f(x + 25 - 5, y + 170 + 65);
    glVertex2f(x + 25 - 5, y + 170 + 65 + 5);
    glVertex2f(x + 25 + 205, y + 170 + 65 + 5);
    glVertex2f(x + 25 + 205, y + 170 + 65);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.949, 0.749, 0.522);
    glVertex2f(x + 25 + 15, y + 170 + 65 + 5);
    glVertex2f(x + 125, y + 170 + 65 + 150);
    glVertex2f(x + 90, y + 170 + 65 + 5);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.878, 0.58, 0.235);
    glVertex2f(x + 160, y + 170 + 65 + 5);
    glVertex2f(x + 125, y + 170 + 65 + 150);
    glVertex2f(x + 25 + 200 - 15, y + 170 + 65 + 5);
    glEnd();

    bresenhams(x + 125, y + 170 + 65 + 150, x + 125, y + 170 + 65 + 150 + 20, 3, 0, 0, 0);
    drawLineDDA(x + 125 - 10, y + 170 + 65 + 150 + 10, x + 125 + 10, y + 170 + 65 + 150 + 10, 3, 0, 0, 0);
    // drawCircleMidpointFilled(x + 125, y + 170 + 65 + 150 + 20, 3);

    float glassR = 0.45, glassG = 0.75, glassB = 1.0;
    float frameR = 0.25, frameG = 0.18, frameB = 0.10;

    int transdown = 10;

    auto drawWindow = [&](float wx, float wy)
        {
            float x1 = wx;
            float y1 = wy;
            float x2 = wx + 32;
            float y2 = wy + 42;

            // frame
            glBegin(GL_QUADS);
            glColor3f(frameR, frameG, frameB);
            glVertex2f(x1, y1);
            glVertex2f(x1, y2);
            glVertex2f(x2, y2);
            glVertex2f(x2, y1);
            glEnd();

            // glass
            glBegin(GL_QUADS);
            glColor3f(glassR, glassG, glassB);
            glVertex2f(x1 + 2, y1 + 2);
            glVertex2f(x1 + 2, y2 - 2);
            glVertex2f(x2 - 2, y2 - 2);
            glVertex2f(x2 - 2, y1 + 2);
            glEnd();

            // cross 
            glBegin(GL_QUADS);
            glColor3f(frameR, frameG, frameB);

            glVertex2f(wx + 15, y1 + 2);
            glVertex2f(wx + 17, y1 + 2);
            glVertex2f(wx + 17, y2 - 2);
            glVertex2f(wx + 15, y2 - 2);

            glVertex2f(x1 + 2, wy + 20);
            glVertex2f(x2 - 2, wy + 20);
            glVertex2f(x2 - 2, wy + 22);
            glVertex2f(x1 + 2, wy + 22);

            glEnd();
        };

    drawWindow(x + 55, y + 198 - transdown);
    drawWindow(x + 108, y + 198 - transdown);
    drawWindow(x + 163, y + 198 - transdown);

    transdown = 95;

    drawWindow(x + 55, y + 198 - transdown);
    drawWindow(x + 108, y + 198 - transdown);
    drawWindow(x + 163, y + 198 - transdown);
}

void drawClock(float cx, float cy, float r, float hourTheta, float minuteTheta)
{
    // clock base
    glBegin(GL_POLYGON);
    glColor3f(0.95, 0.95, 0.95);
    for (int i = 0; i < 360; i++)
    {
        float t = i * 3.14159f / 180.0f;
        glVertex2f(cx + r * cos(t), cy + r * sin(t));
    }
    glEnd();

    // border
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 360; i++)
    {
        float t = i * 3.14159f / 180.0f;
        glVertex2f(cx + r * cos(t), cy + r * sin(t));
    }
    glEnd();

    float hx = r * 0.5f * cos(hourTheta);
    float hy = r * 0.5f * sin(hourTheta);

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(cx, cy);
    glVertex2f(cx + hx, cy + hy);
    glEnd();

    float mx = r * 0.8f * cos(minuteTheta);
    float my = r * 0.8f * sin(minuteTheta);

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(cx, cy);
    glVertex2f(cx + mx, cy + my);
    glEnd();

    // center dot
    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2f(cx, cy);
    glEnd();
}

void drawTree(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.25, 0.1);
    glVertex2f(x + 15, y);
    glVertex2f(x + 15, y + 80);
    glVertex2f(x + 35, y + 80);
    glVertex2f(x + 35, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.6, 0.2);

    glVertex2f(x - 30, y + 60);
    glVertex2f(x + 25, y + 140);
    glVertex2f(x + 80, y + 60);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.12, 0.7, 0.25);

    glVertex2f(x - 25, y + 100);
    glVertex2f(x + 25, y + 180);
    glVertex2f(x + 75, y + 100);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15, 0.8, 0.3);

    glVertex2f(x - 15, y + 140);
    glVertex2f(x + 25, y + 210);
    glVertex2f(x + 65, y + 140);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.08, 0.45, 0.18);

    glVertex2f(x + 5, y + 70);
    glVertex2f(x + 25, y + 160);
    glVertex2f(x + 45, y + 70);
    glEnd();
}

void drawTreeSmall(float x, float y) {
    // base
    glBegin(GL_QUADS);
    glColor3f(0.45, 0.25, 0.1);
    glVertex2f(x + 8, y);
    glVertex2f(x + 8, y + 40);
    glVertex2f(x + 18, y + 40);
    glVertex2f(x + 18, y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.6, 0.2);
    glVertex2f(x - 15, y + 30);
    glVertex2f(x + 13, y + 80);
    glVertex2f(x + 40, y + 30);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.12, 0.7, 0.25);
    glVertex2f(x - 12, y + 60);
    glVertex2f(x + 13, y + 110);
    glVertex2f(x + 38, y + 60);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15, 0.8, 0.3);
    glVertex2f(x - 8, y + 90);
    glVertex2f(x + 13, y + 140);
    glVertex2f(x + 33, y + 90);
    glEnd();

    // shadow
    glBegin(GL_TRIANGLES);
    glColor3f(0.08, 0.45, 0.18);
    glVertex2f(x + 3, y + 35);
    glVertex2f(x + 13, y + 95);
    glVertex2f(x + 23, y + 35);
    glEnd();
}

void drawMountains()
{
    glBegin(GL_TRIANGLES);

    // far hill
    glColor3f(0.70, 0.85, 0.70);
    glVertex2f(-520, -200);
    glVertex2f(-250, 40);
    glVertex2f(20, -200);

    // mid hill
    glColor3f(0.50, 0.72, 0.50);
    glVertex2f(-200, -200);
    glVertex2f(50, 60);
    glVertex2f(300, -200);

    // mid-right hill
    glVertex2f(50, -200);
    glVertex2f(280, 55);
    glVertex2f(520, -200);

    // front hill 
    glColor3f(0.30, 0.55, 0.30);
    glVertex2f(-350, -200);
    glVertex2f(-80, 80);
    glVertex2f(200, -200);

    glEnd();
}

void drawSky()
{
    glBegin(GL_QUADS);

    // Top sky 
    glColor3f(0.18, 0.35, 0.75);
    glVertex2f(-500, 350);
    glVertex2f(500, 350);

    // upper-mid sky
    glColor3f(0.25, 0.45, 0.85);
    glVertex2f(500, 220);
    glVertex2f(-500, 220);

    // mid sky
    glColor3f(0.32, 0.55, 0.92);
    glVertex2f(-500, 220);
    glVertex2f(500, 220);

    glColor3f(0.40, 0.68, 0.98);
    glVertex2f(500, 80);
    glVertex2f(-500, 80);

    // lower-mid sky
    glColor3f(0.55, 0.78, 1.00);
    glVertex2f(-500, 80);
    glVertex2f(500, 80);

    glColor3f(0.70, 0.88, 1.00);
    glVertex2f(500, -80);
    glVertex2f(-500, -80);

    // near horizon glow
    glColor3f(0.85, 0.94, 1.00);
    glVertex2f(-500, -80);
    glVertex2f(500, -80);

    glColor3f(0.92, 0.97, 1.00);
    glVertex2f(500, -200);
    glVertex2f(-500, -200);

    glEnd();
}

void cloud1(float cx, float cy, float s)
{
    // base ellipse
    glColor3f(0.90, 0.90, 0.92);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 5)
    {
        float r = i * 3.14159f / 180.0f;
        glVertex2f(cx + s * 50 * cos(r), cy + s * 20 * sin(r));
    }
    glEnd();

    drawCircleMidpointFilled(cx - 30, cy + 10, 22 * s, 0.95, 0.95, 0.97);
    drawCircleMidpointFilled(cx, cy + 18, 26 * s, 0.97, 0.97, 0.99);
    drawCircleMidpointFilled(cx + 30, cy + 10, 22 * s, 0.95, 0.95, 0.97);

    drawCircleMidpointFilled(cx - 10, cy + 5, 18 * s, 0.88, 0.88, 0.90);
    drawCircleMidpointFilled(cx + 15, cy + 3, 16 * s, 0.88, 0.88, 0.90);
}

void cloud2(float cx, float cy, float s)
{
    // base
    glColor3f(0.88, 0.88, 0.90);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 5)
    {
        float r = i * 3.14159f / 180.0f;
        glVertex2f(cx + s * 45 * cos(r), cy + s * 25 * sin(r));
    }
    glEnd();

    // fluffy clusters
    drawCircleMidpointFilled(cx - 25, cy + 15, 20 * s, 0.95, 0.95, 0.97);
    drawCircleMidpointFilled(cx + 5, cy + 22, 24 * s, 0.97, 0.97, 0.99);
    drawCircleMidpointFilled(cx + 30, cy + 12, 18 * s, 0.95, 0.95, 0.97);

    // shadows
    drawCircleMidpointFilled(cx, cy + 5, 18 * s, 0.85, 0.85, 0.88);
}

void cloud3(float cx, float cy, float s) {
    // long base
    glColor3f(0.92, 0.92, 0.95);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 5)
    {
        float r = i * 3.14159f / 180.0f;
        glVertex2f(cx + s * 70 * cos(r), cy + s * 18 * sin(r));
    }
    glEnd();

    // layered circles
    drawCircleMidpointFilled(cx - 40, cy + 8, 20 * s, 0.96, 0.96, 0.98);
    drawCircleMidpointFilled(cx - 10, cy + 15, 24 * s, 0.98, 0.98, 1.00);
    drawCircleMidpointFilled(cx + 25, cy + 10, 22 * s, 0.96, 0.96, 0.98);
    drawCircleMidpointFilled(cx + 50, cy + 5, 18 * s, 0.94, 0.94, 0.97);

    // subtle shadow
    drawCircleMidpointFilled(cx, cy + 2, 20 * s, 0.85, 0.85, 0.88);
}

void drawLampPost(float x, float y)
{
    // pole
    glBegin(GL_QUADS);
    glColor3f(0.25, 0.25, 0.28);
    glVertex2f(x, y);
    glVertex2f(x + 6, y);
    glVertex2f(x + 6, y + 120);
    glVertex2f(x, y + 120);
    glEnd();

    // base
    glBegin(GL_QUADS);
    glColor3f(0.18, 0.18, 0.20);
    glVertex2f(x - 5, y);
    glVertex2f(x + 11, y);
    glVertex2f(x + 11, y + 6);
    glVertex2f(x - 5, y + 6);
    glEnd();

    // holder
    glBegin(GL_QUADS);
    glColor3f(0.20, 0.20, 0.22);
    glVertex2f(x - 8, y + 120);
    glVertex2f(x + 14, y + 120);
    glVertex2f(x + 14, y + 128);
    glVertex2f(x - 8, y + 128);
    glEnd();

    // light
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.85, 0.35); // warm light
    glVertex2f(x - 5, y + 128);
    glVertex2f(x + 11, y + 128);
    glVertex2f(x + 11, y + 142);
    glVertex2f(x - 5, y + 142);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.9, 0.5);
    glVertex2f(x - 15, y + 142);
    glVertex2f(x + 21, y + 142);
    glVertex2f(x + 15, y + 165);
    glVertex2f(x - 9, y + 165);
    glEnd();
}

void drawBench(float x, float y)
{
    // seat
    glBegin(GL_QUADS);
    glColor3f(0.55, 0.35, 0.20);
    glVertex2f(x, y);
    glVertex2f(x + 120, y);
    glVertex2f(x + 120, y + 10);
    glVertex2f(x, y + 10);
    glEnd();

    // backrest
    glBegin(GL_QUADS);
    glColor3f(0.50, 0.30, 0.18);
    glVertex2f(x, y + 15);
    glVertex2f(x + 120, y + 15);
    glVertex2f(x + 120, y + 45);
    glVertex2f(x, y + 45);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.25, 0.25, 0.25);

    // left leg
    glVertex2f(x + 10, y);
    glVertex2f(x + 20, y);
    glVertex2f(x + 20, y - 25);
    glVertex2f(x + 10, y - 25);

    // right leg
    glVertex2f(x + 100, y);
    glVertex2f(x + 110, y);
    glVertex2f(x + 110, y - 25);
    glVertex2f(x + 100, y - 25);

    glEnd();

    // pa rakhar bar
    glBegin(GL_LINES);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(x + 15, y - 10);
    glVertex2f(x + 105, y - 10);
    glEnd();
}

void drawBush(float x, float y) {
    // base layer
    drawCircleMidpointFilled(x, y, 25, 0.1, 0.5, 0.2);
    drawCircleMidpointFilled(x + 20, y, 22, 0.1, 0.5, 0.2);
    drawCircleMidpointFilled(x - 20, y, 22, 0.1, 0.5, 0.2);

    // upper layer
    drawCircleMidpointFilled(x, y + 20, 20, 0.2, 0.7, 0.3);
    drawCircleMidpointFilled(x + 15, y + 15, 18, 0.2, 0.7, 0.3);
    drawCircleMidpointFilled(x - 15, y + 15, 18, 0.2, 0.7, 0.3);
}

void drawBushWithFlowers(float x, float y) {
    // base layer
    drawCircleMidpointFilled(x, y, 25, 0.1, 0.5, 0.2);
    drawCircleMidpointFilled(x + 20, y, 22, 0.1, 0.5, 0.2);
    drawCircleMidpointFilled(x - 20, y, 22, 0.1, 0.5, 0.2);

    // upper layer
    drawCircleMidpointFilled(x, y + 20, 20, 0.2, 0.7, 0.3);
    drawCircleMidpointFilled(x + 15, y + 15, 18, 0.2, 0.7, 0.3);
    drawCircleMidpointFilled(x - 15, y + 15, 18, 0.2, 0.7, 0.3);

    // pink flowers
    drawPoint(x - 10, y + 25, 4, 1.0, 0.4, 0.7);
    drawPoint(x + 5, y + 30, 4, 1.0, 0.4, 0.7);
    drawPoint(x + 18, y + 10, 4, 1.0, 0.4, 0.7);

    // yellow flowers
    drawPoint(x - 20, y + 10, 4, 1.0, 0.85, 0.2);
    drawPoint(x + 12, y + 22, 4, 1.0, 0.85, 0.2);

    // white flowers
    drawPoint(x, y + 35, 3, 1.0, 1.0, 1.0);
    drawPoint(x - 15, y + 18, 3, 1.0, 1.0, 1.0);
    drawPoint(x + 20, y + 28, 3, 1.0, 1.0, 1.0);
}

void drawHotAirBalloon(float cx, float cy, float s, float r, float g, float b) {
    drawCircleMidpointFilled(cx, cy, 30 * s, r, g, b);
    drawCircleMidpointFilled(cx - 20 * s, cy + 10 * s, 22 * s, r * 0.9, g * 0.9, b * 0.9);
    drawCircleMidpointFilled(cx + 20 * s, cy + 10 * s, 22 * s, r * 0.9, g * 0.9, b * 0.9);
    drawCircleMidpointFilled(cx, cy + 20 * s, 24 * s, r * 1.1, g * 1.1, b * 1.1);

    // strips
    glBegin(GL_QUADS);
    glColor3f(r * 0.7, g * 0.7, b * 0.7);

    glVertex2f(cx - 8 * s, cy + 30 * s);
    glVertex2f(cx + 8 * s, cy + 30 * s);
    glVertex2f(cx + 5 * s, cy - 25 * s);
    glVertex2f(cx - 5 * s, cy - 25 * s);

    glEnd();

    // neck
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.2, 0.1);
    glVertex2f(cx - 8 * s, cy - 30 * s);
    glVertex2f(cx + 8 * s, cy - 30 * s);
    glVertex2f(cx + 5 * s, cy - 45 * s);
    glVertex2f(cx - 5 * s, cy - 45 * s);
    glEnd();

    // ropes
    glBegin(GL_LINES);
    glColor3f(0.2, 0.1, 0.05);

    glVertex2f(cx - 5 * s, cy - 45 * s);
    glVertex2f(cx - 10 * s, cy - 60 * s);

    glVertex2f(cx + 5 * s, cy - 45 * s);
    glVertex2f(cx + 10 * s, cy - 60 * s);

    glEnd();

    // basket
    glBegin(GL_QUADS);
    glColor3f(0.55, 0.30, 0.15);

    glVertex2f(cx - 12 * s, cy - 60 * s);
    glVertex2f(cx + 12 * s, cy - 60 * s);
    glVertex2f(cx + 12 * s, cy - 75 * s);
    glVertex2f(cx - 12 * s, cy - 75 * s);

    glEnd();

    // basket details
    glBegin(GL_LINES);
    glColor3f(0.3, 0.2, 0.1);

    glVertex2f(cx - 12 * s, cy - 67 * s);
    glVertex2f(cx + 12 * s, cy - 67 * s);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawLineDDA(-500, -200, 500, -200, 12, 0.702, 0.533, 0.31);
    drawMountains();

    cloud3(200 + cloud1Offset, 200, 1);
    cloud1(160 + cloud1Offset, 170, 1);

    cloud2(-440 + cloud2Offset, 300, 1);
    cloud3(-430 + cloud3Offset, 280, 1);

    cloud2(-200 + cloud4Offset, 180, 1);
    cloud3(-120 + cloud4Offset, 170, 1);
    cloud1(-130 + cloud4Offset, 140, 1);

    cloud3(490 + cloud5Offset, 35, 1);

    drawHotAirBalloon(-250 + balloonOffset1, 150, 0.5, 1.0, 0.4, 0.4); // red
    drawHotAirBalloon(150 + balloonOffset2, 100, 0.4, 0.75, 0.45, 0.9); // purple
    drawHotAirBalloon(300 + balloonOffset3, 200, 0.8, 1.0, 0.8, 0.3); // yellow

    church(-60, -200);
    drawTree(-470, -200);
    drawHouse(-400, -200);
    drawHouse4(-190, -200);
    drawHouse5(-60, -200);
    drawHouse3(145, -200);
    drawHouse2(280, -200);
    drawClock(65, 85, 30, hourAngle, minuteAngle);
    drawLampPost(-320, -200);

    drawTreeSmall(450, -200);

    glBegin(GL_QUADS);
    glColor3f(0.514, 0.839, 0.525);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, -206);
    glVertex2f(-500, -206);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.337, 0.729, 0.369);
    glVertex2f(-500, -300);
    glVertex2f(500, -300);
    glVertex2f(500, -350);
    glVertex2f(-500, -350);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.871, 0.694, 0.286);
    glVertex2f(-28 - 30, -300);
    glVertex2f(28 - 20, -300);
    glVertex2f(28, -206);
    glVertex2f(-28, -206);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.871, 0.694, 0.286);
    glVertex2f(-28 - 30 - 100, -350);
    glVertex2f(28 - 20 + 100, -350);
    glVertex2f(28, -300);
    glVertex2f(-28 - 50, -300);
    glEnd();

    drawBench(100, -280);
    drawBush(290, -280);
    drawBushWithFlowers(340, -280);

    drawBushWithFlowers(-290, -280);
    drawBushWithFlowers(-340, -280);
    drawBushWithFlowers(-120, -280);

    glutSwapBuffers();
}



void update(int value) {
    // clock
    minuteAngle -= 0.005f;
    hourAngle -= 0.0005f;

    // cloud 
    cloud1Offset += 0.3f;
    cloud2Offset += 0.2f;
    cloud3Offset += 0.25f;
    cloud4Offset += 0.22f;
    cloud5Offset += 0.28f;

    if (200 + cloud1Offset > 600) cloud1Offset = -1200;
    if (160 + cloud1Offset > 600) cloud1Offset = -1200;

    if (-440 + cloud2Offset > 600) cloud2Offset = -1200;

    if (-430 + cloud3Offset > 600) cloud3Offset = -1200;

    if (-200 + cloud4Offset > 600) cloud4Offset = -1200;
    if (-120 + cloud4Offset > 600) cloud4Offset = -1200;
    if (-130 + cloud4Offset > 600) cloud4Offset = -1200;

    if (490 + cloud5Offset > 600) cloud5Offset = -1200;

    // balloon
    balloonOffset1 += 0.15f;
    balloonOffset2 += 0.12f;
    balloonOffset3 += 0.18f;

    if (-250 + balloonOffset1 > 550) balloonOffset1 = -1100;
    if (150 + balloonOffset2 > 550) balloonOffset2 = -1100;
    if (300 + balloonOffset3 > 550) balloonOffset3 = -1100;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(1, 1, 1, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-500, 500, -350, 350);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1000, 700);

    glutCreateWindow("Project 1951");

    init();
    glutDisplayFunc(display);

    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}