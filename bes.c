#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int endpoints[8][4];
int x0, y0, x1, y1;
int n;
void draw_pixel(int x, int y)
{
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(0.5);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x0, int y0, int x1, int y1)
{
    int x, y;
    int dx, dy;
    dx = x1 - x0;
    dy = y1 - y0;
    if (y0 > y1)
        dy = -dy;
    if (x0 > x1)
        dx = -dx;
    int incx = 1, incy = 1, p, inc1, inc2;
    if (y0 > y1)
        incy = -1;
    if (x0 > x1)
        incx = -1;
    x = x0;
    y = y0;
    if (dx > dy)
    {
        p = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        draw_pixel(x, y);
        for (int i = 0; i < dx; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p += inc1;
            }
            else
                p += inc2;
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        p = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (int i = 0; i < dy; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p += inc1;
            }
            else
                p += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void bres()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    for (int i = 0; i < n; i++)
    {
        x0 = endpoints[i][0];
        y0 = endpoints[i][1];
        x1 = endpoints[i][2];
        y1 = endpoints[i][3];
        draw_line(x0, y0, x1, y1);

        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x0, y0);
        glEnd();
        glFlush();
    }
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    // glMatrixMode(GL_MODELVIEW);
}
void main(int argc, char **argv)
{
    printf("Enter the number of lines\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter for line %d\n", i + 1);
        scanf("%d%d%d%d", &endpoints[i][0], &endpoints[i][1], &endpoints[i][2], &endpoints[i][3]);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("bresh");
    glutDisplayFunc(bres);
    myinit();
    glutMainLoop();
}