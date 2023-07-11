#include <stdlib.h>
#include <GL/glut.h>
#define BLACK 0

float x1, y1, x2, y2, x3, y3, x4, y4;

void edgedetected(float x1, float y1, float x2, float y2, int *le, int *re)
{
    float mx;
    float temp;
    if (y2 < y1)
    {
        temp = y1;
        y1 = y2;
        y2 = temp;

        temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y2 - y1 != 0)
    {
        mx = (x2 - x1) / (y2 - y1);
    }
    else
        mx = x2 - x1;
    int x = x1;
    for (int i = y1; i <= y2; i++)
    {
        if (x < le[i])
            le[i] = (int)x;
        if (x > re[i])
            re[i] = (int)x;
        x += mx;
    }
}

void draw_pixel(int x, int y, float value)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void scanline(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    int le[500], re[500];
    int i, y;
    for (i = 0; i < 500; i++)
    {
        le[i] = 500;
        re[i] = 0;
    }
    edgedetected(x1, y1, x2, y2, le, re);
    edgedetected(x2, y2, x3, y3, le, re);
    edgedetected(x3, y3, x4, y4, le, re);
    edgedetected(x4, y4, x1, y1, le, re);

    for (y = 0; y < 500; y++)
    {
        if (le[y] < re[y])
            for (i = le[y]; i <= re[y]; i++)
            {
                draw_pixel(i, y, BLACK);
            }
    }
}

void menu(int c)
{
    switch (c)
    {
    case 1:
        glColor3f(1.0, 0.0, 0.0);
        break;
    case 2:
        glColor3f(0.0, 1.0, 0.0);
        break;
    case 3:
        glColor3f(0.0, 0.0, 1.0);
        break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float x1 = 200, y1 = 200, x2 = 100, y2 = 300, x3 = 200, y3 = 400, x4 = 300, y4 = 300;
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
    scanline(x1, y1, x2, y2, x3, y3, x4, y4);
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("fuck this");
    glutInitWindowSize(500, 500);
    glutCreateMenu(menu);
    glutAddMenuEntry("RED", 1);
    glutAddMenuEntry("BLUE", 3);
    glutAddMenuEntry("GREEN", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
