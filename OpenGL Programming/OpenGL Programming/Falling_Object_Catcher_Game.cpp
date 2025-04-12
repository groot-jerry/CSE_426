#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 700;

struct Object {
    float x, y;
    bool isBomb;
};

std::vector<Object> objects;

float basketX = 0.0f;
int score = 0;
int lives = 3;
int highScore = 0;
bool isPaused = false;

// Cross-platform save folder path
std::string getSaveFolderPath() {
    std::string saveFolder;

#ifdef _WIN32
    char documentsPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documentsPath);
    saveFolder = std::string(documentsPath) + "\\FruitCatcher_Saves\\";
    CreateDirectoryA(saveFolder.c_str(), NULL);
#else
    const char* homeDir = getpwuid(getuid())->pw_dir;
    saveFolder = std::string(homeDir) + "/FruitCatcher_Saves/";
    mkdir(saveFolder.c_str(), 0777);
#endif

    return saveFolder;
}

void loadHighScore() {
    std::string filePath = getSaveFolderPath() + "highscore.txt";
    std::ifstream file(filePath);
    if (file >> highScore) {
        file.close();
    }
}

void saveHighScore() {
    std::string filePath = getSaveFolderPath() + "highscore.txt";
    std::ofstream file(filePath);
    if (file) {
        file << highScore;
        file.close();
        std::cout << "High score saved to: " << filePath << std::endl;
    }
    else {
        std::cerr << "Failed to save high score!" << std::endl;
    }
}

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawBasket() {
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(basketX - 0.2f, -0.9f);
    glVertex2f(basketX + 0.2f, -0.9f);
    glVertex2f(basketX + 0.2f, -0.85f);
    glVertex2f(basketX - 0.2f, -0.85f);
    glEnd();
}

void drawObject(Object obj) {
    if (obj.isBomb) {
        glColor3f(0.8f, 0.0f, 0.0f); // Red bomb
    }
    else {
        glColor3f(0.0f, 0.8f, 0.0f); // Green fruit
    }

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; ++i) {
        float angle = i * 2.0f * 3.1416f / 100;
        glVertex2f(obj.x + 0.03f * cos(angle), obj.y + 0.03f * sin(angle));
    }
    glEnd();
}

void spawnObject() {
    Object obj;
    obj.x = (rand() % 200 - 100) / 100.0f;
    obj.y = 1.1f;
    obj.isBomb = (rand() % 4 == 0);
    objects.push_back(obj);
}

void init() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    srand(static_cast<unsigned>(time(nullptr)));
    loadHighScore();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBasket();

    for (const auto& obj : objects) {
        drawObject(obj);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.95f, 0.95f, "Score: " + std::to_string(score));
    drawText(0.6f, 0.95f, "Lives: " + std::to_string(lives));
    drawText(-0.95f, 0.9f, "High: " + std::to_string(highScore));

    if (isPaused) {
        glColor3f(1.0f, 1.0f, 0.0f);
        drawText(-0.1f, 0.0f, "PAUSED");
    }
    else if (lives <= 0) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(-0.2f, 0.0f, "GAME OVER");
    }

    glutSwapBuffers();
}

void update(int value) {
    if (!isPaused && lives > 0) {
        for (auto& obj : objects) {
            obj.y -= 0.02f;

            if (obj.y < -0.85f && obj.y > -0.9f &&
                obj.x > basketX - 0.2f && obj.x < basketX + 0.2f) {
                if (obj.isBomb) {
                    lives--;
                }
                else {
                    score++;
                    if (score > highScore) {
                        highScore = score;
                    }
                }
                obj.y = -2.0f;
            }
        }

        objects.erase(std::remove_if(objects.begin(), objects.end(),
            [](const Object& o) { return o.y < -1.2f; }), objects.end());

        if (rand() % 10 < 2) {
            spawnObject();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void specialKeys(int key, int, int) {
    if (!isPaused && lives > 0) {
        if (key == GLUT_KEY_LEFT && basketX > -0.8f) {
            basketX -= 0.05f;
        }
        else if (key == GLUT_KEY_RIGHT && basketX < 0.8f) {
            basketX += 0.05f;
        }
    }
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
    case ' ':
        isPaused = !isPaused;
        break;
    case 'r':
    case 'R':
        lives = 3;
        score = 0;
        basketX = 0.0f;
        objects.clear();
        isPaused = false;
        break;
    case 27: // ESC
        saveHighScore();
        exit(0);
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Fruit Catcher Game");

    // Register atexit handler for cleanup
    atexit(saveHighScore);

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}