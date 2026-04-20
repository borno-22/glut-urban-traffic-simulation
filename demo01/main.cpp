#include<windows.h>
#include <GL/glut.h>
#define PI          3.141516
#include<math.h>

void drawShape(GLfloat p1, GLfloat q1,GLfloat r1)
{
    int i;
    int tringle2 = 40;

    GLfloat tp2 = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(p1, q1);

    for (i = 0; i <= tringle2; i++)
    {
        glVertex2f(
            p1 + (r1 * cos(i * tp2 / tringle2)),q1 + (r1 * sin(i * tp2 / tringle2)));
    }

    glEnd();
}

void ship(){
    //
    //water
    //
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-.1,.2);
    glVertex2f(-1.0,.2);
    glVertex2f(-1.0,-1.0);
    glVertex2f(-.4,-1.0);
    glEnd();

    //
    //boat background
    //
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();


    //
    //upper body
    //
    //boat upper body 1
    glColor3f(0.5f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-.88,-.35);
    glVertex2f(-.76,-.35);
    glVertex2f(-.76,-.2);
    glVertex2f(-.88,-.2);
    glEnd();

    //boat upper body 2
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-.88,-.2);
    glVertex2f(-.76,-.2);
    glVertex2f(-.71,-.19);
    glVertex2f(-.83,-.19);
    glEnd();

    //boat upper body 3
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-.71,-.19);
    glVertex2f(-.76,-.2);
    glVertex2f(-.76,-.4);
    glVertex2f(-.71,-.4);
    glEnd();




    //
    //lower body
    //
    //boat lower body 1
    glColor3f(0.0f, 0.0f, 0.0f);

    // Polygon 1: The Left side
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.35f);
    glEnd();

    // Polygon 2: The middle side
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.37f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();

    // Polygon 3: The right side
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, -0.35f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.37f);
    glEnd();



    //
    //containers
    //
    //container 1
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-.70,-.285);
    glVertex2f(-.70,-.365);
    glVertex2f(-.6,-.335);
    glVertex2f(-.6,-.26);
    glEnd();

    //container 2
    glColor3f(1.0f, 0.0f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-.60,-.26);
    glVertex2f(-.60,-.335);
    glVertex2f(-.5,-.31);
    glVertex2f(-.5,-.235);
    glEnd();

}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    ship();

    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(960,540);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Rocket");
    glutDisplayFunc(display);
    glClearColor(1,1,1,1);
    glutMainLoop();

    return 0;
}
