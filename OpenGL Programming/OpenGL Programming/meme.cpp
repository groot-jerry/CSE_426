#include <GL/glut.h>
#include <cmath>
#include <iostream>

void drawWrongCircle() {
    glBegin(GL_POLYGON);  // আসলে বৃত্ত নয়, একটা বিকৃত আকৃতি হবে!
    for (int i = 0; i < 360; i += 30) {  // কম সেগমেন্ট, ভুল গণনা
        float angle = i * 3.1415926 / 180;
        float x = cos(angle);  // ভুল হতে পারে এখানে
        float y = sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);  // লাল রঙের বিকৃত বৃত্ত
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawWrongCircle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Math Bug - Distorted Circle");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
