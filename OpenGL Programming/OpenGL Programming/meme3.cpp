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
        h.dx = (rand() % 10 - 5) / 500.0;
        h.dy = (rand() % 10 - 5) / 500.0;
        humans.push_back(h);
    }
}

void updateHumans() {
    for (auto& h : humans) {
        h.x += h.dx;
        h.y += h.dy;
        if (h.x > 1 || h.x < -1) h.dx = -h.dx;
        if (h.y > 1 || h.y < -1) h.dy = -h.dy;
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
    // Head
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + 0.03 * cos(angle), y + 0.03 * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

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
