#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h>

GLint TOP = 8, BOTTOM = 4, RIGHT = 2, LEFT = 1;
float xmin = 50, ymin = 50, xmax = 100, ymax = 100;
float xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

int computeOutCode(float x0, float y0);

void cohenClipping(float x0, float y0, float x1, float y1)
{
    int outCode0, outCode1, outCodeOut;
    outCode0 = computeOutCode(x0, y0);
    outCode1 = computeOutCode(x1, y1);
    bool done = false, accept = false;
    do
    {
        if ((outCode0 | outCode1) == 0)
        {
            done = true;
            accept = true;
        }
        else if (outCode0 & outCode1)
        {
            done = true;
        }
        else
        {
            float x, y;
            float slope = (y1 - y0) / (x1 - x0);
            outCodeOut = outCode0 ? outCode0 : outCode1;
            if (outCodeOut & TOP)
            {
                x = x0 + (1 / slope) * (ymax - y0);
                y = ymax;
            }
            else if (outCodeOut & BOTTOM)
            {
                x = x0 + (1 / slope) * (ymin - y0);
                y = ymin;
            }
            else if (outCodeOut & RIGHT)
            {
                y = y0 + slope * (xmax - x0);
                x = xmax;
            }
            else
            {
                y = y0 + slope * (xmin - x0);
                x = xmin;
            }

            if (outCodeOut == outCode0)
            {
                x0 = x;
                y0 = y;
                outCode0 = computeOutCode(x0, y0);
            }
            else
            {
                y1 = y;
                x1 = x;
                outCode1 = computeOutCode(x1, y1);
            }
        }

    } while (!done);
    if (accept)
    {
        float sx = (xvmax - xvmin) / (xmax - xmin);
        float sy = (yvmax - yvmin) / (ymax - ymin);
        float vx0 = xvmin + sx * (x0 - xmin);
        float vy0 = yvmin + sy * (y0 - ymin);
        float vy1 = yvmin + sy * (y1 - ymin);
        float vx1 = xvmin + sx * (x1 - xmin);
        printf("x0=%f", x0);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(xvmin, yvmin);
        glVertex2f(xvmax, yvmin);
        glVertex2f(xvmax, yvmax);
        glVertex2f(xvmin, yvmax);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(vx0, vy0);
        glVertex2f(vx1, vy1);
        glEnd();
    }
}
int computeOutCode(float x, float y)
{
    int code = 0;
    if (y > ymax)
        code |= TOP;
    else if (y < ymin)
        code |= BOTTOM;
    if (x > xmax)
        code |= RIGHT;
    else if (x < xmin)
        code |= LEFT;
    return code;
}

void display()
{
    float x0 = 60, y0 = 20, x1 = 80, y1 = 120;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
    cohenClipping(x0, y0, x1, y1);
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
    glutInitWindowSize(500, 500);
    glutCreateWindow("coh");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}