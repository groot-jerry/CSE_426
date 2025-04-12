#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

struct HumanShape {
    float x, y;
    float dx, dy;
};

std::vector<HumanShape> humans;

void initHumans(int count) {
    srand(time(0));
    for (int i = 0; i < count; i++) {
        HumanShape h;
        h.x = (rand() % 200 - 100) / 100.0;
        h.y = (rand() % 200 - 100) / 100.0;
        h.dx = ((0.6 - h.x) / 500.0); // Move towards picnic booth
        h.dy = ((0.0 - h.y) / 500.0);
        humans.push_back(h);
    }
}

void updateHumans() {
    for (auto& h : humans) {
        if (h.x < 0.5) { // Stop when reaching the booth
            h.x += h.dx;
            h.y += h.dy;
        }
    }
    glutPostRedisplay();
}

void drawHuman(float x, float y) {
    glBegin(GL_LINES);
    // Body
    glVertex2f(x, y);
    glVertex2f(x, y - 0.1);
    // Legs
    glVertex2f(x, y - 0.1);
    glVertex2f(x - 0.05, y - 0.2);
    glVertex2f(x, y - 0.1);
    glVertex2f(x + 0.05, y - 0.2);
    // Arms
    glVertex2f(x, y - 0.05);
    glVertex2f(x - 0.05, y - 0.1);
    glVertex2f(x, y - 0.05);
    glVertex2f(x + 0.05, y - 0.1);
    glEnd();

    // Head
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + 0.03 * cos(angle), y + 0.03 * sin(angle));
    }
    glEnd();
}

void drawBooth(float x, float y, const char* label) {
    glColor3f(1.0, 0.0, 0.0); // Booths are now red
    glBegin(GL_QUADS);
    glVertex2f(x - 0.3, y - 0.2);
    glVertex2f(x + 0.3, y - 0.2);
    glVertex2f(x + 0.3, y + 0.2);
    glVertex2f(x - 0.3, y + 0.2);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x - 0.25, y); // Adjusted position to keep text inside block
    for (const char* c = label; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw booths
    drawBooth(0.6, 0.0, "Picnic e Gele A+");
    drawBooth(-0.6, 0.0, "Picnic e Na Gele Fail");

    glColor3f(1.0, 0.0, 0.0);
    for (const auto& h : humans) {
        drawHuman(h.x, h.y);
    }

    glutSwapBuffers();
}

void timer(int) {
    updateHumans();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    initHumans(10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("UAP Picnic Chaos: Stick Figure Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
