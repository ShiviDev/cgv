#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat rotatemat[3][3] = {{0}, {0}, {0}};
GLfloat result[3][3] = {{0}, {0}, {0}};
GLfloat triangle[3][3] = {{100.0, 250.0, 175.0}, {100.0, 100.0, 300.0}, {1.0, 1.0, 1.0}};
GLfloat ang, x = 0.0, y = 0.0;

void multiply()
{
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            result[i][j] = 0.0;
            for (k = 0; k < 3; k++)
            {
                result[i][j] += rotatemat[i][k] * triangle[k][j];
            }
        }
    }
}

void rotate()
{
    float m, n;
    m = x * (1 - cos(ang)) + y * (sin(ang));
    n = y * (1 - cos(ang)) - x * (sin(ang));
    rotatemat[0][0] = cos(ang);
    rotatemat[0][1] = -sin(ang);
    rotatemat[0][2] = m;
    rotatemat[1][0] = sin(ang);
    rotatemat[1][1] = cos(ang);
    rotatemat[1][2] = n;
    rotatemat[2][0] = 0;
    rotatemat[2][1] = 0;
    rotatemat[2][2] = 1.0;
    multiply();
}

void tri()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangle[0][0], triangle[1][0]);
    glVertex2f(triangle[0][1], triangle[1][1]);
    glVertex2f(triangle[0][2], triangle[1][2]);
    glEnd();
}

void res()
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(result[0][0], result[1][0]);
    glVertex2f(result[0][1], result[1][1]);
    glVertex2f(result[0][2], result[1][2]);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(1.0, 1.0, 1.0, 1.0);
    rotate();
    res();
    tri();
    glFlush();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300.0, 500.0, -300.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
    int c;
    printf("\nEnter ur choice\n1.origin\n2.point\n");
    scanf("%d", &c);
    printf("\nEnter angle\n");
    scanf("%f", &ang);
    ang = (ang * 3.14) / 180.0;
    switch (c)
    {
    case 1:
        rotate();
        break;
    case 2:
        printf("Enter arbitrary x and y");
        scanf("%f%f", &x, &y);
        rotate();
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("tri");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}