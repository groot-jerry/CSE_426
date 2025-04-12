#include <windows.h>
#include <GL/glut.h>

void draw_square() {
    glBegin(GL_QUADS);

    // Top line (Red)

    //glColor3f(0.0f, 1.0f, 0.0f);
    //glVertex2f(0.f, 3.f);

    // Bottom Right line (Green)

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-4.f, 4.f);
    glVertex2f(4.f, 4.f);
    glVertex2f(4.f, -4.f);
    glVertex2f(-4.f, -4.f);


    // Bottom Left line (Blue)

    //glColor3f(0.0f, 1.0f, 0.0f);
    //glVertex2f(-3.f, -3.f);

    glEnd();

}
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(-4, 4, -4, 4, -4, 4);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_square();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Square");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}