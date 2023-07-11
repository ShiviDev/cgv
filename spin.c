#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat vertex[][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};
GLfloat normal[][3] = {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}};
GLfloat color[][3] = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0}};

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(color[a]);
    glVertex3fv(vertex[a]);
    glNormal3fv(normal[a]);

    glColor3fv(color[b]);
    glVertex3fv(vertex[b]);
    glNormal3fv(normal[b]);

    glColor3fv(color[c]);
    glVertex3fv(vertex[c]);
    glNormal3fv(normal[c]);

    glColor3fv(color[d]);
    glVertex3fv(vertex[d]);
    glNormal3fv(normal[d]);
    glEnd();
}

void colorcube()
{
    polygon(0, 1, 2, 3);
    polygon(0, 3, 7, 4);
    polygon(0, 1, 5, 4);
    polygon(3, 2, 6, 7);
    polygon(1, 2, 6, 5);
    polygon(4, 5, 6, 7);
}

int axis = 2;
GLfloat theta[] = {0, 0, 0};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();
    glFlush();
    glutSwapBuffers();
}

void spincube()
{
    theta[axis] += 0.1;
    if (theta[axis] >= 360)
        theta[axis] -= 360.0;
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
}
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * ((GLfloat)w / (GLfloat)h), 2.0 * ((GLfloat)w / (GLfloat)h), -2.0, 2.0);
    else
        glOrtho(-2.0 * ((GLfloat)h / (GLfloat)w), 2.0 * ((GLfloat)h / (GLfloat)w), -2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("spinny");
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutIdleFunc(spincube);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}