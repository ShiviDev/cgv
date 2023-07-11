#include <stdlib.h>
#include <GL/glut.h>

GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shine[] = {50.0};
GLfloat light_intensity[] = {0.7, 0.7, 0.7, 1.0};
GLfloat light_postion[] = {2.0, 6.0, 3.0, 0.0};

void myinit()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
    glLightfv(GL_LIGHT0, GL_POSITION, light_postion);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 1.0, 2.0, 0.0, 0.2, 0.2, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void teapot()
{
    glPushMatrix();
    glTranslated(0.4, 0.0, 0.4);
    glRotated(30, 0.0, 1, 0.0);
    glutSolidTeapot(0.2);
    glPopMatrix();
}

void tabletop()
{
    glPushMatrix();
    glTranslated(0.0, -0.3, 0.0);
    glScaled(7.0, 0.5, 7.0);
    glutSolidCube(0.2);
    glPopMatrix();
}

void frontleg()
{
    glPushMatrix();
    glTranslated(0.5, -0.7, 0.5);
    glScaled(0.5, 7.0, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();
}

void leftleg()
{
    glPushMatrix();
    glTranslated(-0.5, -0.7, 0.5);
    glScaled(0.5, 7.0, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();
}
void backleg()
{
    glPushMatrix();
    glTranslated(-0.5, -0.7, -0.5);
    glScaled(0.5, 7.0, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();
}

void rightleg()
{
    glPushMatrix();
    glTranslated(0.5, -0.7, -0.5);
    glScaled(0.5, 7.0, 0.5);
    glutSolidCube(0.1);
    glPopMatrix();
}

void leftwall()
{
    glPushMatrix();
    glTranslated(-1.0, 0.0, 0.0);
    glScaled(0.1, 10.0, 10.0);
    glutSolidCube(0.2);
    glPopMatrix();
}

void backwall()
{
    glPushMatrix();
    glTranslated(0.0, 0.0, -1.0);
    glScaled(10., 10.0, 0.1);
    glutSolidCube(0.2);
    glPopMatrix();
}

void bottomfloor()
{
    glPushMatrix();
    glTranslated(0.0, -1.0, 0.0);
    glScaled(10.0, 0.1, 10.0);
    glutSolidCube(0.2);
    glPopMatrix();
}

void display()
{
    myinit();
    teapot();
    tabletop();
    frontleg();
    backleg();
    leftleg();
    rightleg();
    bottomfloor();
    leftwall();
    backwall();
    glFlush();
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("is it teapot");
    glutInitWindowSize(500, 500);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    glutMainLoop();
}