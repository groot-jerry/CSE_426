#include <windows.h>
#include <GL/glut.h>
#include <math.h>


void draw_circle(float radius, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex2f(0.f, 0.f);


    for (int i = 0; i <= num_segments; i++)
    {
        float angle = 2.0f * 3.1416 * i / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }



    glEnd();

}
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(-4, 4, -4, 4, -4, 4);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_circle(3.0f, 100);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Circle");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}