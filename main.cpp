#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

int width = 900, height = 650;

enum GameState { MENU, PLAYING, PAUSED, HELP, GAME_OVER };
enum ObjectType { NORMAL_EGG, BLUE_EGG, GOLDEN_EGG, POOP, BIG_BASKET, SLOW_SPEED, EXTRA_TIME };

GameState gameState = MENU;

float basketX = 380;
float basketY = 45;
float basketWidth = 120;
float basketHeight = 35;

float chickenX = 100;
float chickenSpeed = 3;

int score = 0;
int highScore = 0;
int timeLeft = 90;

float globalFallSpeed = 4;
int slowTimeLeft = 0;
int bigBasketTimeLeft = 0;

int brokenEggVisible = 0;
float brokenEggX = 0;
float brokenEggY = 85;
int brokenEggTimer = 0;

struct FallingObject {
    float x, y;
    float speed;
    ObjectType type;
    int active;
};

FallingObject obj;

void playCatchSound()
{
    waveOutSetVolume(0, MAKELONG(15000, 15000));

    PlaySound(TEXT("F:\\com graphics\\catch the egg\\catch.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playMissSound()
{
    waveOutSetVolume(0, MAKELONG(12000, 12000));

     PlaySound(TEXT("F:\\com graphics\\catch the egg\\miss.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void drawText(float x, float y, const char *text)
{
    glRasterPos2f(x, y);
    while (*text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
}

void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float rad = i * 3.1416 / 180;
        glVertex2f(x + cos(rad) * r, y + sin(rad) * r);
    }
    glEnd();
}

void drawCloud(float x, float y)
{
    glColor3f(1, 1, 1);

    drawCircle(x, y, 25);
    drawCircle(x + 25, y + 10, 32);
    drawCircle(x + 55, y, 25);
    drawCircle(x + 30, y - 12, 24);

    glBegin(GL_QUADS);
        glVertex2f(x - 10, y - 22);
        glVertex2f(x + 70, y - 22);
        glVertex2f(x + 70, y + 5);
        glVertex2f(x - 10, y + 5);
    glEnd();
}

void drawBackground()
{
    glColor3f(0.45, 0.75, 0.95);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
    glEnd();

    drawCloud(80, 570);
    drawCloud(250, 470);
    drawCloud(500, 570);
    drawCloud(680, 460);

    glColor3f(0.0, 0.65, 0.15);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, 80);
        glVertex2f(0, 80);
    glEnd();
}

void drawBambooStick()
{
    glColor3f(0.55, 0.35, 0.1);
    glBegin(GL_QUADS);
        glVertex2f(80, 520);
        glVertex2f(820, 520);
        glVertex2f(820, 535);
        glVertex2f(80, 535);
    glEnd();

    glColor3f(0.35, 0.22, 0.08);
    for (int i = 120; i <= 780; i += 80)
    {
        glBegin(GL_LINES);
            glVertex2f(i, 520);
            glVertex2f(i, 535);
        glEnd();
    }
}

void drawChicken()
{
    float y = 560;

    glColor3f(0.95, 0.75, 0.25);
    drawCircle(chickenX, y, 32);

    glColor3f(0.85, 0.55, 0.15);
    drawCircle(chickenX - 8, y - 3, 17);

    glColor3f(0.95, 0.75, 0.25);
    drawCircle(chickenX + 30, y + 25, 20);

    glColor3f(0, 0, 0);
    drawCircle(chickenX + 37, y + 31, 3);

    glColor3f(1.0, 0.55, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(chickenX + 48, y + 25);
        glVertex2f(chickenX + 70, y + 32);
        glVertex2f(chickenX + 48, y + 18);
    glEnd();

    glColor3f(1, 0, 0);
    drawCircle(chickenX + 17, y + 48, 7);
    drawCircle(chickenX + 28, y + 55, 8);
    drawCircle(chickenX + 39, y + 48, 7);

    glColor3f(0.9, 0.4, 0.1);
    glBegin(GL_TRIANGLES);
        glVertex2f(chickenX - 28, y + 8);
        glVertex2f(chickenX - 55, y + 25);
        glVertex2f(chickenX - 35, y - 5);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(chickenX - 25, y);
        glVertex2f(chickenX - 55, y - 18);
        glVertex2f(chickenX - 35, y + 10);
    glEnd();

    glColor3f(1.0, 0.55, 0.0);
    glBegin(GL_LINES);
        glVertex2f(chickenX - 10, y - 28);
        glVertex2f(chickenX - 10, y - 50);

        glVertex2f(chickenX + 10, y - 28);
        glVertex2f(chickenX + 10, y - 50);

        glVertex2f(chickenX - 10, y - 50);
        glVertex2f(chickenX - 22, y - 55);

        glVertex2f(chickenX - 10, y - 50);
        glVertex2f(chickenX, y - 55);

        glVertex2f(chickenX + 10, y - 50);
        glVertex2f(chickenX, y - 55);

        glVertex2f(chickenX + 10, y - 50);
        glVertex2f(chickenX + 22, y - 55);
    glEnd();
}

void drawBasket()
{
    glColor3f(0.85, 0.5, 0.2);
    glBegin(GL_POLYGON);
        glVertex2f(basketX, basketY + basketHeight);
        glVertex2f(basketX + basketWidth, basketY + basketHeight);
        glVertex2f(basketX + basketWidth - 25, basketY);
        glVertex2f(basketX + 25, basketY);
    glEnd();

    glColor3f(0.95, 0.75, 0.45);
    glBegin(GL_QUADS);
        glVertex2f(basketX - 5, basketY + basketHeight);
        glVertex2f(basketX + basketWidth + 5, basketY + basketHeight);
        glVertex2f(basketX + basketWidth + 5, basketY + basketHeight + 12);
        glVertex2f(basketX - 5, basketY + basketHeight + 12);
    glEnd();
}

void spawnObject()
{
    obj.x = chickenX;
    obj.y = 510;
    obj.active = 1;
    obj.speed = globalFallSpeed;

    int r = rand() % 100;

    if (r < 45) obj.type = NORMAL_EGG;
    else if (r < 65) obj.type = BLUE_EGG;
    else if (r < 80) obj.type = GOLDEN_EGG;
    else if (r < 90) obj.type = POOP;
    else if (r < 94) obj.type = BIG_BASKET;
    else if (r < 98) obj.type = SLOW_SPEED;
    else obj.type = EXTRA_TIME;
}

void drawFallingObject()
{
    if (!obj.active) return;

    if (obj.type == NORMAL_EGG) glColor3f(1.0, 0.95, 0.75);
    else if (obj.type == BLUE_EGG) glColor3f(0.1, 0.4, 1.0);
    else if (obj.type == GOLDEN_EGG) glColor3f(1.0, 0.75, 0.0);
    else if (obj.type == POOP) glColor3f(0.25, 0.12, 0.02);
    else if (obj.type == BIG_BASKET) glColor3f(0.8, 0.2, 1.0);
    else if (obj.type == SLOW_SPEED) glColor3f(0.0, 1.0, 1.0);
    else if (obj.type == EXTRA_TIME) glColor3f(0.0, 1.0, 0.3);

    if (obj.type == POOP)
    {
        drawCircle(obj.x, obj.y, 12);
        drawCircle(obj.x + 8, obj.y + 6, 10);
    }
    else if (obj.type == BIG_BASKET || obj.type == SLOW_SPEED || obj.type == EXTRA_TIME)
    {
        glBegin(GL_QUADS);
            glVertex2f(obj.x - 14, obj.y - 14);
            glVertex2f(obj.x + 14, obj.y - 14);
            glVertex2f(obj.x + 14, obj.y + 14);
            glVertex2f(obj.x - 14, obj.y + 14);
        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++)
        {
            float rad = i * 3.1416 / 180;
            glVertex2f(obj.x + cos(rad) * 10, obj.y + sin(rad) * 16);
        }
        glEnd();
    }
}

void drawBrokenEgg()
{
    if (!brokenEggVisible) return;

    glColor3f(1.0, 0.95, 0.75);

    glBegin(GL_POLYGON);
        glVertex2f(brokenEggX - 25, brokenEggY);
        glVertex2f(brokenEggX - 10, brokenEggY + 10);
        glVertex2f(brokenEggX, brokenEggY + 2);
        glVertex2f(brokenEggX + 12, brokenEggY + 12);
        glVertex2f(brokenEggX + 25, brokenEggY);
        glVertex2f(brokenEggX + 10, brokenEggY - 8);
        glVertex2f(brokenEggX - 12, brokenEggY - 8);
    glEnd();

    glColor3f(1.0, 0.8, 0.0);
    drawCircle(brokenEggX, brokenEggY, 8);

    glColor3f(0.8, 0.6, 0.3);
    glBegin(GL_LINES);
        glVertex2f(brokenEggX - 22, brokenEggY + 2);
        glVertex2f(brokenEggX - 35, brokenEggY + 12);

        glVertex2f(brokenEggX + 20, brokenEggY + 2);
        glVertex2f(brokenEggX + 35, brokenEggY + 12);
    glEnd();
}

void showBrokenEgg(float x)
{
    brokenEggVisible = 1;
    brokenEggX = x;
    brokenEggTimer = 20;
}

void applyCatchEffect()
{
    playCatchSound();

    if (obj.type == NORMAL_EGG) score += 1;
    else if (obj.type == BLUE_EGG) score += 5;
    else if (obj.type == GOLDEN_EGG) score += 10;
    else if (obj.type == POOP) score -= 10;
    else if (obj.type == BIG_BASKET)
    {
        basketWidth = 180;
        bigBasketTimeLeft = 10;
    }
    else if (obj.type == SLOW_SPEED)
    {
        slowTimeLeft = 10;
    }
    else if (obj.type == EXTRA_TIME)
    {
        timeLeft += 10;
    }

    if (score < 0) score = 0;

    spawnObject();
}
void resetGame()
{
    score = 0;
    timeLeft = 25;
    basketX = 380;
    basketWidth = 120;
    chickenX = 100;
    chickenSpeed = 3;
    globalFallSpeed = 4;
    slowTimeLeft = 0;
    bigBasketTimeLeft = 0;
    brokenEggVisible = 0;
    brokenEggTimer = 0;
    spawnObject();
}

void drawHUD()
{
    char text[100];

    glColor3f(1, 1, 1);

    sprintf(text, "Score: %d", score);
    drawText(20, 620, text);

    sprintf(text, "Time: %d", timeLeft);
    drawText(750, 620, text);

    sprintf(text, "Speed: %.1f", globalFallSpeed);
    drawText(370, 620, text);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();

    if (gameState == MENU)
    {
        glColor3f(0, 1, 0);
        drawText(330, 450, "CATCH THE EGGS");
        drawText(310, 390, "Press ENTER to Start");
        drawText(310, 350, "Press H for Help");
        drawText(310, 310, "Press ESC to Exit");
    }
    else if (gameState == HELP)
    {
        glColor3f(0, 1, 0);
        drawText(250, 520, "HELP MENU");
        drawText(150, 460, "Left/Right Arrow: Move Basket");
        drawText(150, 420, "Mouse Move: Control Basket");
        drawText(150, 380, "P: Pause or Resume");
        drawText(150, 340, "Normal Egg = +1");
        drawText(150, 310, "Blue Egg = +5");
        drawText(150, 280, "Golden Egg = +10");
        drawText(150, 250, "Poop = -10");
        drawText(150, 220, "Blocks give perks: Big Basket, Slow Speed, Extra Time");
        drawText(150, 170, "Press M to go back to Menu");
    }
    else if (gameState == PLAYING || gameState == PAUSED)
    {
        drawHUD();
        drawBambooStick();
        drawChicken();
        drawFallingObject();
        drawBrokenEgg();
        drawBasket();

        if (gameState == PAUSED)
        {
            glColor3f(1, 0, 0);
            drawText(400, 330, "PAUSED");
            drawText(330, 290, "Press P to Resume");
        }
    }
    else if (gameState == GAME_OVER)
    {
        char text[100];

        glColor3f(1, 0, 0);
        drawText(390, 390, "GAME OVER");

        glColor3f(1, 1, 1);
        sprintf(text, "Final Score: %d", score);
        drawText(370, 340, text);

        sprintf(text, "High Score: %d", highScore);
        drawText(370, 310, text);

        drawText(300, 250, "Press ENTER to Play Again");
        drawText(300, 220, "Press M for Menu");
        drawText(300, 190, "Press ESC to Exit");
    }

    glutSwapBuffers();
}

void update(int value)
{
    if (gameState == PLAYING)
    {
        chickenX += chickenSpeed;

        if (chickenX > 780 || chickenX < 100)
            chickenSpeed *= -1;

        float currentSpeed = obj.speed;

        if (slowTimeLeft > 0)
            currentSpeed = obj.speed * 0.5;

        obj.y -= currentSpeed;

        if (obj.y <= basketY + basketHeight + 15 &&
            obj.x >= basketX &&
            obj.x <= basketX + basketWidth)
        {
            applyCatchEffect();
        }

        if (obj.y < 80)
        {
            playMissSound();
            showBrokenEgg(obj.x);
            spawnObject();
        }

        if (brokenEggVisible)
        {
            brokenEggTimer--;

            if (brokenEggTimer <= 0)
                brokenEggVisible = 0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void gameTimer(int value)
{
    if (gameState == PLAYING)
    {
        timeLeft--;

        if (slowTimeLeft > 0)
            slowTimeLeft--;

        if (bigBasketTimeLeft > 0)
        {
            bigBasketTimeLeft--;

            if (bigBasketTimeLeft == 0)
                basketWidth = 120;
        }

        if (timeLeft <= 0)
        {
            gameState = GAME_OVER;

            if (score > highScore)
                highScore = score;
        }
    }

    glutTimerFunc(1000, gameTimer, 0);
}

void increaseEggSpeed(int value)
{
    if (gameState == PLAYING)
    {
        globalFallSpeed += 0.7;

        if (globalFallSpeed > 12)
            globalFallSpeed = 12;

        obj.speed = globalFallSpeed;
    }

    glutTimerFunc(10000, increaseEggSpeed, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 13)
    {
        resetGame();
        gameState = PLAYING;
    }

    if (key == 'p' || key == 'P')
    {
        if (gameState == PLAYING)
            gameState = PAUSED;
        else if (gameState == PAUSED)
            gameState = PLAYING;
    }

    if (key == 'h' || key == 'H')
        gameState = HELP;

    if (key == 'm' || key == 'M')
        gameState = MENU;

    if (key == 27)
        exit(0);
}

void specialKeyboard(int key, int x, int y)
{
    if (gameState == PLAYING)
    {
        if (key == GLUT_KEY_LEFT)
            basketX -= 30;

        if (key == GLUT_KEY_RIGHT)
            basketX += 30;

        if (basketX < 0)
            basketX = 0;

        if (basketX > width - basketWidth)
            basketX = width - basketWidth;
    }
}

void mouseMove(int x, int y)
{
    if (gameState == PLAYING)
    {
        basketX = x - basketWidth / 2;

        if (basketX < 0)
            basketX = 0;

        if (basketX > width - basketWidth)
            basketX = width - basketWidth;
    }
}

void init()
{
    glClearColor(0.45, 0.75, 0.95, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, width, 0, height);
}

int main(int argc, char **argv)
{
    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Catch The Eggs Game");

    init();

    spawnObject();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutPassiveMotionFunc(mouseMove);

    glutTimerFunc(25, update, 0);
    glutTimerFunc(1000, gameTimer, 0);
    glutTimerFunc(10000, increaseEggSpeed, 0);

    glutMainLoop();

    return 0;
}
