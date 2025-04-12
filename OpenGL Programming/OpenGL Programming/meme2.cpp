#include <GL/glut.h>
#include <cmath>
#include <iostream>

void drawBrokenSphere() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.5, 0.0);

    float radius = 1.0;
    for (int i = 0; i <= 360; i += 30) {
        float angle = i * 3.14159265 / 180.0;
        float distortion = (i % 60 == 0) ? 0.2 : -0.2; // Intentional distortion
        glVertex3f(radius * cos(angle) + distortion, radius * sin(angle) + distortion, 0.0);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);

    drawBrokenSphere();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Broken Sphere Meme");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
