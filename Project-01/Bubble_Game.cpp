#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int WIDTH = 540;
const int HEIGHT = 348;

const float PLAY_LEFT = 114.0f;
const float PLAY_RIGHT = 396.0f;
const float PLAY_TOP = 8.0f;
const float PLAY_BOTTOM = 338.0f;

const float RADIUS = 15.0f;
const float DIAMETER = 30.0f;
const float ROW_GAP = 25.0f;
const float COL_GAP = 30.0f;

int score = 0;
int timerValue = 120;
bool gameOver = false;

struct Color {
    float r, g, b;
};

vector<Color> palette = {
    {1.0f, 0.0f, 0.0f},   // red
    {1.0f, 1.0f, 0.0f},   // yellow
    {0.0f, 1.0f, 1.0f},   // cyan
    {1.0f, 0.0f, 1.0f},   // magenta
    {0.0f, 1.0f, 0.0f},   // green
    {0.0f, 0.0f, 1.0f}    // blue
};

struct Bubble {
    float x, y;
    int colorIndex;
    bool active;
};

vector<Bubble> gridBubbles;

struct ShooterBubble {
    float x, y;
    float dx, dy;
    int colorIndex;
    bool moving;
};

ShooterBubble shooter;

void drawText(float x, float y, const string& text, void* font = GLUT_BITMAP_TIMES_ROMAN_24) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}

void drawFilledCircle(float cx, float cy, float r, const Color& c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100.0f;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCircleBorder(float cx, float cy, float r) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100.0f;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawBubble(float x, float y, int colorIndex) {
    drawFilledCircle(x, y, RADIUS, palette[colorIndex]);
    drawCircleBorder(x, y, RADIUS);
}

void resetShooter() {
    shooter.x = (PLAY_LEFT + PLAY_RIGHT) / 2.0f;
    shooter.y = PLAY_BOTTOM - 25.0f;
    shooter.dx = 0.0f;
    shooter.dy = 0.0f;
    shooter.colorIndex = rand() % palette.size();
    shooter.moving = false;
}

void initGrid() {
    gridBubbles.clear();

    int rows = 9;
    int counts[] = { 8, 8, 8, 8, 7, 6, 4, 3, 1 };

    float startY = 25.0f;

    for (int row = 0; row < rows; row++) {
        int cols = counts[row];
        float y = startY + row * ROW_GAP;

        float totalWidth = (cols - 1) * COL_GAP;
        float startX = (PLAY_LEFT + PLAY_RIGHT) / 2.0f - totalWidth / 2.0f;

        for (int col = 0; col < cols; col++) {
            Bubble b;
            b.x = startX + col * COL_GAP;
            b.y = y;
            b.colorIndex = rand() % palette.size();
            b.active = true;
            gridBubbles.push_back(b);
        }
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, HEIGHT, 0);

    srand((unsigned)time(0));
    initGrid();
    resetShooter();
}

void drawBorders() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(PLAY_LEFT, PLAY_TOP);
    glVertex2f(PLAY_RIGHT, PLAY_TOP);
    glVertex2f(PLAY_RIGHT, PLAY_BOTTOM);
    glVertex2f(PLAY_LEFT, PLAY_BOTTOM);
    glEnd();
}

void drawSidePanels() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
    glVertex2f(PLAY_LEFT, PLAY_TOP);
    glVertex2f(PLAY_LEFT, PLAY_BOTTOM);

    glVertex2f(PLAY_RIGHT, PLAY_TOP);
    glVertex2f(PLAY_RIGHT, PLAY_BOTTOM);
    glEnd();
}

void drawHUD() {
    glColor3f(1.0f, 0.0f, 0.0f);

    stringstream ss1, ss2;
    ss1 << "score = " << score;

    int minutes = timerValue / 60;
    int seconds = timerValue % 60;

    ss2 << "timer = ";
    if (minutes < 10) ss2 << "0";
    ss2 << minutes << ":";
    if (seconds < 10) ss2 << "0";
    ss2 << seconds;

    drawText(38, 32, ss1.str(), GLUT_BITMAP_HELVETICA_18);
    drawText(38, 55, ss2.str(), GLUT_BITMAP_HELVETICA_18);
}

void drawGridBubbles() {
    for (auto& b : gridBubbles) {
        if (b.active) {
            drawBubble(b.x, b.y, b.colorIndex);
        }
    }
}

bool areTouching(int i, int j) {
    if (!gridBubbles[i].active || !gridBubbles[j].active) return false;

    float dx = gridBubbles[i].x - gridBubbles[j].x;
    float dy = gridBubbles[i].y - gridBubbles[j].y;
    float dist = sqrt(dx * dx + dy * dy);

    return dist <= DIAMETER + 2.0f;
}

bool isConnectedToTop(int index) {
    return gridBubbles[index].active && gridBubbles[index].y <= PLAY_TOP + 35.0f;
}

void removeFloatingBubbles() {
    int n = (int)gridBubbles.size();
    vector<bool> visited(n, false);
    vector<int> stack;

    for (int i = 0; i < n; i++) {
        if (isConnectedToTop(i)) {
            visited[i] = true;
            stack.push_back(i);
        }
    }

    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();

        for (int i = 0; i < n; i++) {
            if (!visited[i] && gridBubbles[i].active && areTouching(current, i)) {
                visited[i] = true;
                stack.push_back(i);
            }
        }
    }

    int removedCount = 0;
    for (int i = 0; i < n; i++) {
        if (gridBubbles[i].active && !visited[i]) {
            gridBubbles[i].active = false;
            removedCount++;
        }
    }

    score += removedCount * 3;
}

void removeMatchedBubbles(int startIndex) {
    if (startIndex < 0 || startIndex >= (int)gridBubbles.size()) return;
    if (!gridBubbles[startIndex].active) return;

    int targetColor = gridBubbles[startIndex].colorIndex;

    vector<int> stack;
    vector<bool> visited(gridBubbles.size(), false);
    vector<int> group;

    stack.push_back(startIndex);
    visited[startIndex] = true;

    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();

        if (!gridBubbles[current].active) continue;
        if (gridBubbles[current].colorIndex != targetColor) continue;

        group.push_back(current);

        for (int i = 0; i < (int)gridBubbles.size(); i++) {
            if (!visited[i] &&
                gridBubbles[i].active &&
                gridBubbles[i].colorIndex == targetColor &&
                areTouching(current, i)) {
                visited[i] = true;
                stack.push_back(i);
            }
        }
    }

    if ((int)group.size() >= 3) {
        for (int idx : group) {
            gridBubbles[idx].active = false;
        }

        score += (int)group.size() * 5;
        removeFloatingBubbles();
    }
}

bool collisionWithGrid(float x, float y) {
    for (auto& b : gridBubbles) {
        if (!b.active) continue;

        float dx = x - b.x;
        float dy = y - b.y;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist <= DIAMETER - 2.0f) {
            return true;
        }
    }
    return false;
}

void snapShooterBubble() {
    if (shooter.x - RADIUS < PLAY_LEFT) shooter.x = PLAY_LEFT + RADIUS;
    if (shooter.x + RADIUS > PLAY_RIGHT) shooter.x = PLAY_RIGHT - RADIUS;
    if (shooter.y - RADIUS < PLAY_TOP) shooter.y = PLAY_TOP + RADIUS;
}

void attachShooterBubble() {
    snapShooterBubble();

    Bubble b;
    b.x = shooter.x;
    b.y = shooter.y;
    b.colorIndex = shooter.colorIndex;
    b.active = true;

    gridBubbles.push_back(b);
    int newIndex = (int)gridBubbles.size() - 1;

    score++;
    removeMatchedBubbles(newIndex);
    resetShooter();
}

void updateShooter() {
    if (!shooter.moving || gameOver) return;

    shooter.x += shooter.dx;
    shooter.y += shooter.dy;

    if (shooter.x - RADIUS <= PLAY_LEFT) {
        shooter.x = PLAY_LEFT + RADIUS;
        shooter.dx = -shooter.dx;
    }

    if (shooter.x + RADIUS >= PLAY_RIGHT) {
        shooter.x = PLAY_RIGHT - RADIUS;
        shooter.dx = -shooter.dx;
    }

    if (shooter.y - RADIUS <= PLAY_TOP) {
        attachShooterBubble();
        return;
    }

    if (collisionWithGrid(shooter.x, shooter.y)) {
        attachShooterBubble();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBorders();
    drawSidePanels();
    drawHUD();
    drawGridBubbles();

    if (!gameOver) {
        drawBubble(shooter.x, shooter.y, shooter.colorIndex);
    }
    else {
        drawBubble((PLAY_LEFT + PLAY_RIGHT) / 2.0f, PLAY_BOTTOM - 25.0f, shooter.colorIndex);
    }

    if (gameOver) {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(192, 284, "GAME OVER !", GLUT_BITMAP_TIMES_ROMAN_24);
        drawText(192, 312, "Press 'ESC' key for EXIT", GLUT_BITMAP_HELVETICA_18);
    }

    glFlush();
}

void timerFunc(int value) {
    if (!gameOver) {
        updateShooter();
        glutPostRedisplay();
        glutTimerFunc(16, timerFunc, 0);
    }
}

void countdown(int value) {
    if (!gameOver) {
        timerValue--;

        if (timerValue <= 0) {
            timerValue = 0;
            gameOver = true;
        }

        glutPostRedisplay();
        glutTimerFunc(1000, countdown, 0);
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

    if (gameOver) return;

    if ((key == 'a' || key == 'A') && !shooter.moving) {
        shooter.x -= 12;
        if (shooter.x - RADIUS < PLAY_LEFT)
            shooter.x = PLAY_LEFT + RADIUS;
    }

    if ((key == 'd' || key == 'D') && !shooter.moving) {
        shooter.x += 12;
        if (shooter.x + RADIUS > PLAY_RIGHT)
            shooter.x = PLAY_RIGHT - RADIUS;
    }

    if (key == ' ' && !shooter.moving) {
        shooter.dx = 0.0f;
        shooter.dy = -6.0f;
        shooter.moving = true;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(80, 80);
    glutCreateWindow("Bubble Shooter Game");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timerFunc, 0);
    glutTimerFunc(1000, countdown, 0);

    glutMainLoop();
    return 0;
}