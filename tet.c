#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef GLfloat point[3];
int n;
point vertex[] = {{-1.0, -0.5, 0.0}, {1.0, -0.5, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
GLfloat color[][3] = {{1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 1.0}};

void triangle(point a, point b, point c)
{
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void tetra(point a, point b, point c, point d)
{
    glColor3fv(color[0]);
    triangle(a, b, c);
    glColor3fv(color[1]);
    triangle(a, b, d);
    glColor3fv(color[2]);
    triangle(a, c, d);
    glColor3fv(color[3]);
    triangle(b, c, d);
}

void divide(point a, point b, point c, point d, int m)
{
    point mid[6];
    if (m > 0)
    {
        for (int j = 0; j < 3; j++)
        {
            mid[0][j] = (a[j] + b[j]) / 2.0;
            mid[1][j] = (a[j] + c[j]) / 2.0;
            mid[2][j] = (a[j] + d[j]) / 2.0;
            mid[3][j] = (b[j] + c[j]) / 2.0;
            mid[4][j] = (b[j] + d[j]) / 2.0;
            mid[5][j] = (d[j] + c[j]) / 2.0;
        }
        divide(a, mid[0], mid[1], mid[2], m - 1);
        divide(mid[0], b, mid[3], mid[4], m - 1);
        divide(mid[1], mid[3], c, mid[5], m - 1);
        divide(mid[2], mid[4], mid[5], d, m - 1);
    }
    else
    {
        tetra(a, b, c, d);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    divide(vertex[0], vertex[1], vertex[2], vertex[3], n);
    glFlush();
    // glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    {
        glOrtho(-1.0, 1.0, -1.0 * ((GLfloat)h / (GLfloat)w), 1.0 * ((GLfloat)h / (GLfloat)w), -1.0, 1.0);
    }
    else
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    printf("Enter number of divisions\n");
    scanf("%d", &n);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("jdkjfdjf");
    glutInitWindowSize(500, 500);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}