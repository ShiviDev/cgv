#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.14
float theta = 0;
struct wcPts3D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
typedef struct wcPts3D cp;
cp ctrlPts[4] = {
    {20, 100, 0},
    {30, 110, 0},
    {50, 90, 0},
    {60, 100, 0}};

GLint nCtrlPts = 4, nBezPts = 20;

void bino(int n, int *C)
{
    int k, j;
    for (k = 0; k <= n; k++)
    {
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void compute(float u, cp *bezf, cp *ctrlPts, int nCtrlPts, int *C)
{
    int k, n = nCtrlPts - 1;
    bezf->x = bezf->y = bezf->z = 0;
    float blend;
    for (k = 0; k < nCtrlPts; k++)
    {
        blend = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezf->x += ctrlPts[k].x * blend;
        bezf->y += ctrlPts[k].y * blend;
        bezf->z += ctrlPts[k].z * blend;
    }
}

void bez(int nCtrlPts, int nBezPts, cp *ctrlPts)
{
    cp bezf;
    float u;
    int C[nCtrlPts];
    bino(nCtrlPts - 1, C);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= nBezPts; i++)
    {
        u = (GLfloat)i / (GLfloat)nBezPts;
        compute(u, &bezf, ctrlPts, nCtrlPts, C);
        glVertex2f(bezf.x, bezf.y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glPointSize(4.0);
    glLineWidth(0.9);
    glColor3f(1.0, 153.0 / 255.0, 51.0 / 255.0);
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0.0, -0.8, 0.0);
        bez(nCtrlPts, nBezPts, ctrlPts);
    }
    glColor3f(1, 1, 1);
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0.0, -0.8, 0.0);
        bez(nCtrlPts, nBezPts, ctrlPts);
    }
    glColor3f(19.0 / 255.0, 136.0 / 255.0, 8 / 255.0);
    for (int i = 0; i < 8; i++)
    {
        glTranslatef(0.0, -0.8, 0.0);
        bez(nCtrlPts, nBezPts, ctrlPts);
    }
    glPopMatrix();

    glColor3f(0.7, 0.5, 0.3);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(20, 100);
    glVertex2f(20, 20);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void menu(int n)
{
    switch (n)
    {
    case 1:
        ctrlPts[1].x += 10 * sin(theta * PI / 180.0);
        ctrlPts[1].y += 5 * sin(theta * PI / 180.0);
        ctrlPts[2].x -= 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[2].y -= 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[3].x -= 4 * sin(theta * PI / 180.0);
        ctrlPts[3].y += sin((theta - 30) * PI / 180.0);
        theta += 0.1;
        break;
    case 2:
        ctrlPts[1].x -= 10 * sin(theta * PI / 180.0);
        ctrlPts[1].y -= 5 * sin(theta * PI / 180.0);
        ctrlPts[2].x += 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[2].y += 10 * sin((theta + 30) * PI / 180.0);
        ctrlPts[3].x += 4 * sin((theta)*PI / 180.0);
        ctrlPts[3].y -= sin((theta - 30) * PI / 180.0);
        theta -= 0.1;
        break;
    case 3:
        exit(0);
    }
}

void winReshapeFun(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 130.0, 0, 130.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bezier");

    glutCreateMenu(menu);
    glutAddMenuEntry("Dwn-mov", 1);
    glutAddMenuEntry("Up-mov", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutReshapeFunc(winReshapeFun);
    glutMainLoop();
    return 0;
}