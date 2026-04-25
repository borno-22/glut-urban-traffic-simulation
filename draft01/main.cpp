#include<windows.h>
#include <GL/glut.h>
#define PI 3.141516
#include<math.h>

void Circle(GLfloat x, GLfloat y, GLfloat radius, int triangleAmount)
{
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MIM
//
//
//tree
//

//type1-basic tree
void treeType1(float x, float y, float s)
{
    // trunk
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.015f*s, y);
    glVertex2f(x + 0.015f*s, y);
    glVertex2f(x + 0.015f*s, y + 0.12f*s);
    glVertex2f(x - 0.015f*s, y + 0.12f*s);
    glEnd();

    // leaves (round cluster)
    glColor3f(0.1f, 0.6f, 0.05f);
    Circle(x - 0.04f*s, y + 0.12f*s, 0.05f*s, 100);
    Circle(x,          y + 0.16f*s, 0.06f*s, 100);
    Circle(x + 0.04f*s, y + 0.12f*s, 0.05f*s, 100);
}


//type2-wide
void treeType2(float x, float y, float s)
{
    // trunk
    glColor3f(0.40f, 0.22f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f*s, y);
    glVertex2f(x + 0.02f*s, y);
    glVertex2f(x + 0.02f*s, y + 0.14f*s);
    glVertex2f(x - 0.02f*s, y + 0.14f*s);
    glEnd();

    // wide leaves
    glColor3f(0.10f, 0.45f, 0.10f);
    Circle(x - 0.06f*s, y + 0.15f*s, 0.06f*s, 100);
    Circle(x - 0.02f*s, y + 0.18f*s, 0.07f*s, 100);
    Circle(x + 0.04f*s, y + 0.15f*s, 0.06f*s, 100);

    // highlight top
    glColor3f(0.25f, 0.70f, 0.25f);
    Circle(x, y + 0.22f*s, 0.05f*s, 100);
}

//type3-tall thin
void treeType3(float x, float y, float s)
{
    // thin trunk
    glColor3f(0.35f, 0.20f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.01f*s, y);
    glVertex2f(x + 0.01f*s, y);
    glVertex2f(x + 0.01f*s, y + 0.18f*s);
    glVertex2f(x - 0.01f*s, y + 0.18f*s);
    glEnd();

    // vertical leaf stack
    glColor3f(0.20f, 0.70f, 0.20f);
    Circle(x, y + 0.18f*s, 0.04f*s, 100);
    Circle(x, y + 0.23f*s, 0.045f*s, 100);
    Circle(x, y + 0.28f*s, 0.04f*s, 100);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ORNOB
//

//
//bush
//

//type1-classic dense bush
void bushType1(float x, float y, float s)
{
    glColor3f(0.12f, 0.50f, 0.12f);

    Circle(x - 0.04f*s, y, 0.05f*s, 100);
    Circle(x, y + 0.02f*s, 0.06f*s, 100);
    Circle(x + 0.04f*s, y, 0.05f*s, 100);

    glColor3f(0.20f, 0.65f, 0.20f);
    Circle(x, y + 0.05f*s, 0.045f*s, 100);
}


//type2-wide bush
void bushType2(float x, float y, float s)
{
    glColor3f(0.10f, 0.40f, 0.10f);

    Circle(x - 0.06f*s, y, 0.05f*s, 100);
    Circle(x - 0.02f*s, y + 0.02f*s, 0.055f*s, 100);
    Circle(x + 0.02f*s, y + 0.02f*s, 0.055f*s, 100);
    Circle(x + 0.06f*s, y, 0.05f*s, 100);

    glColor3f(0.25f, 0.70f, 0.25f);
    Circle(x, y + 0.05f*s, 0.04f*s, 100);
}

//type3-tall bush
void bushType3(float x, float y, float s)
{
    glColor3f(0.08f, 0.35f, 0.08f);

    Circle(x, y, 0.05f*s, 100);
    Circle(x, y + 0.05f*s, 0.055f*s, 100);
    Circle(x, y + 0.10f*s, 0.05f*s, 100);

    glColor3f(0.20f, 0.60f, 0.20f);
    Circle(x - 0.03f*s, y + 0.05f*s, 0.04f*s, 100);
    Circle(x + 0.03f*s, y + 0.05f*s, 0.04f*s, 100);
}


void water()
{
    //
    //water
    //
    glColor3f(0.60f, 0.85f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-.15,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-1.0);
    glVertex2f(-.45,-1.0);
    glEnd();

}

void ship()
{
    //
    // Boat background
    //
    glColor3f(0.1f, 0.2f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();

    //
    // Upper body
    //
    // Boat upper body 1 (Main cabin front)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-.88,-.35);
    glVertex2f(-.75,-.35);
    glVertex2f(-.75,-.2);
    glVertex2f(-.88,-.2);
    glEnd();

    // Boat upper body 2 (Roof)
    glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-.88,-.2);
    glVertex2f(-.75,-.2);
    glVertex2f(-.71,-.19);
    glVertex2f(-.83,-.19);
    glEnd();

    // Boat upper body 3 (Cabin side wall)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-.71,-.19);
    glVertex2f(-.75,-.2);
    glVertex2f(-.75,-.4);
    glVertex2f(-.71,-.4);
    glEnd();

    //
    // Lower body
    //
    glColor3f(0.0f, 0.0f, 0.0f);

    // Polygon 1: The Left side
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.35f);
    glEnd();

    // Polygon 2: The right side
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.37f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();

    // Polygon 3: The middle side
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, -0.35f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.37f);
    glEnd();

    // Deep Maritime Red Colour
    glColor3f(0.6f, 0.1f, 0.1f);

    // Polygon 1: The Left side
    glBegin(GL_POLYGON);
    glVertex2f(-0.875f, -0.43f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.43f);
    glEnd();

    // Polygon 2: The right side
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.425f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.49f, -0.355f);
    glEnd();

    // Polygon 3: The middle side
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, -0.43f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.425f);
    glEnd();


    //
    // Containers
    //
    // Container 1
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-.70,-.285);
    glVertex2f(-.70,-.365);
    glVertex2f(-.6,-.335);
    glVertex2f(-.6,-.26);
    glEnd();

    // Container 2
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-.60,-.26);
    glVertex2f(-.60,-.335);
    glVertex2f(-.5,-.31);
    glVertex2f(-.5,-.235);
    glEnd();


    //
    // WINDOWS (in cabin)
    //
    glColor3f(0.2f, 0.6f, 0.9f);

    // Window 1
    glBegin(GL_QUADS);
    glVertex2f(-0.87f, -0.30f);
    glVertex2f(-0.84f, -0.30f);
    glVertex2f(-0.84f, -0.26f);
    glVertex2f(-0.87f, -0.26f);
    glEnd();

    // Window 2
    glBegin(GL_QUADS);
    glVertex2f(-0.83f, -0.30f);
    glVertex2f(-0.80f, -0.30f);
    glVertex2f(-0.80f, -0.26f);
    glVertex2f(-0.83f, -0.26f);
    glEnd();

    // Window 3
    glBegin(GL_QUADS);
    glVertex2f(-0.79f, -0.30f);
    glVertex2f(-0.76f, -0.30f);
    glVertex2f(-0.76f, -0.26f);
    glVertex2f(-0.79f, -0.26f);
    glEnd();
}


void riverSide()
{
    //
    //land
    //
    glColor3f(0.20f, 0.0f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-.695,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-.26);
    glEnd();

    glColor3f(0.60f, 0.90f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-.7,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-.25);
    glEnd();

    //
    //bush + tree
    //
    bushType1(-1.0f, .35f, .8f);
    bushType1(-.9f, .35f, .8f);
    bushType1(-.82f, .35f, .8f);
    bushType1(-.84f, .35f, .8f);
    bushType1(-.95f, .3f, .8f);
    bushType1(-.85f, .3f, .85f);
    bushType1(-.95f, .25f, .85f);
    bushType1(-.95f, .15f, .85f);
    bushType1(-.88f, .25f, .85f);
    bushType1(-.88f, .2f, .85f);
    bushType1(-.95f, .1f, .9f);
    bushType1(-.93f, .1f, .85f);
    bushType1(-1.0f, .0f, .85f);
    treeType1(-.9f, .0f, .85f);
    bushType1(-1.02f, -.07f, .85f);
    treeType1(-.947f, -.1f, .9f);

}

void roadSide(){
    //
    //side
    //
    glColor3f(0.20f, 0.50f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, 0.45f);
    glVertex2f(-0.18f, 0.45f);
    glVertex2f(-0.54f, -1.0f);
    glVertex2f(-0.45f, -1.0f);
    glEnd();

    //
    //bush
    //
    bushType1(-0.165f, 0.43f, 0.3);
    bushType1(-0.17f, 0.4f, 0.33);
    bushType1(-0.175f, 0.37f, 0.36);
    bushType1(-0.18f, 0.34f, 0.38);
    bushType2(-0.18f, 0.34f, 0.38);






}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FAHIM
//


void drawOneCloud()
{

    Circle(-0.86f, 0.75f, 0.020f, 100);
    Circle(-0.88f, 0.75f, 0.020f, 100);
    Circle(-0.86f, 0.75f, 0.022f, 100);
    Circle(-0.84f, 0.75f, 0.021f, 100);
    Circle(-0.82f, 0.75f, 0.022f, 100);
    Circle(-0.80f, 0.75f, 0.023f, 100);
    Circle(-0.78f, 0.75f, 0.023f, 100);
    Circle(-0.76f, 0.75f, 0.022f, 100);
    Circle(-0.74f, 0.75f, 0.021f, 100);
    Circle(-0.72f, 0.75f, 0.021f, 100);
    Circle(-0.70f, 0.75f, 0.020f, 100);
    Circle(-0.68f, 0.75f, 0.020f, 100);//down line

    Circle(-0.84f, 0.78f, 0.027f, 100);//middle line
    Circle(-0.80f, 0.78f, 0.030f, 100);
    Circle(-0.76f, 0.77f, 0.030f, 100);
    Circle(-0.72f, 0.78f, 0.030f, 100);
    Circle(-0.78f, 0.81f, 0.035f, 100);//up

}
void drawCloud2()
{
    Circle(-0.86f, 0.75f, 0.018f, 100);
    Circle(-0.84f, 0.75f, 0.017f, 100);
    Circle(-0.82f, 0.75f, 0.018f, 100);
    Circle(-0.80f, 0.75f, 0.019f, 100);
    Circle(-0.78f, 0.75f, 0.019f, 100);
    Circle(-0.76f, 0.75f, 0.019f, 100);
    Circle(-0.74f, 0.75f, 0.017f, 100);
    Circle(-0.72f, 0.75f, 0.017f, 100);

    Circle(-0.82f, 0.76f, 0.027f, 100);
    Circle(-0.80f, 0.77f, 0.028f, 100);
    Circle(-0.78f, 0.76f, 0.029f, 100);
    Circle(-0.76f, 0.76f, 0.029f, 100);

    Circle(-0.78f, 0.79f, 0.023f, 100);
}
void drawCloud()
{

    glColor3f(1.0f, 1.0f, 1.0f);

    // ORIGINAL cloud (no movement)
    glPushMatrix();
    drawOneCloud();
    glPopMatrix();

    // SECOND cloud (shift right)
    glPushMatrix();
    glTranslatef(0.5f, 0.13f, 0.0f); // move right
    drawCloud2();
    glPopMatrix();

    // THIRD cloud (shift middle-top)
    glPushMatrix();
    glTranslatef(1.5f, 0.15f, 0.0f); // move right
    drawOneCloud();
    glPopMatrix();
}


void drawMountainLeft()
{
    glColor3f(0.78f,0.50f,0.28f);

    glBegin(GL_POLYGON);

    // base
    glVertex2f(-1.0f, 0.45f);

    // start peak outside frame
    glVertex2f(-1.0f, 0.64f);


    // Hill 1
    glVertex2f(-0.96f,0.635f);
    glVertex2f(-0.92f,0.625f);
    glVertex2f(-0.88f,0.605f);
    glVertex2f(-0.84f,0.590f);


    // Hill 2
    glVertex2f(-0.80f,0.605f);
    glVertex2f(-0.76f,0.610f);
    glVertex2f(-0.72f,0.605f);
    glVertex2f(-0.68f,0.590f);


    // Hill 3
    glVertex2f(-0.64f,0.590f);
    glVertex2f(-0.60f,0.600f);
    glVertex2f(-0.56f,0.605f);
    glVertex2f(-0.52f,0.595f);


    // Hill 4
    glVertex2f(-0.48f,0.585f);
    glVertex2f(-0.44f,0.570f);
    glVertex2f(-0.40f,0.555f);
    glVertex2f(-0.36f,0.545f);


    // Hill 5
    glVertex2f(-0.30f,0.565f);
    glVertex2f(-0.26f,0.540f);
    glVertex2f(-0.22f,0.525f);
    glVertex2f(-0.18f,0.515f);


    // Hill 5.2
    glVertex2f(-0.10f,0.550f);
    glVertex2f(-0.08f,0.535f);
    glVertex2f(-0.04f,0.525f);
    glVertex2f(-0.03f,0.515f);


    // 🔺 SHARED CENTER PEAK
    glVertex2f(0.0f,0.510f);
    glVertex2f(0.0f,0.45f);

    glEnd();
}
void drawMountainRight()
{
    glColor3f(0.78f,0.50f,0.28f);

    glBegin(GL_POLYGON);

    // 🔺 SAME SHARED CENTER PEAK
    glVertex2f(0.0f,0.45f);
    glVertex2f(0.0f,0.510f);


    // mirror of Hill 5.2
    glVertex2f(0.03f,0.515f);
    glVertex2f(0.04f,0.525f);
    glVertex2f(0.08f,0.535f);
    glVertex2f(0.10f,0.550f);


    // mirror of Hill 5
    glVertex2f(0.18f,0.515f);
    glVertex2f(0.22f,0.525f);
    glVertex2f(0.26f,0.540f);
    glVertex2f(0.30f,0.565f);


    // mirror of Hill 4
    glVertex2f(0.36f,0.545f);
    glVertex2f(0.40f,0.555f);
    glVertex2f(0.44f,0.570f);
    glVertex2f(0.48f,0.585f);


    // mirror of Hill 3
    glVertex2f(0.52f,0.595f);
    glVertex2f(0.56f,0.605f);
    glVertex2f(0.60f,0.600f);
    glVertex2f(0.64f,0.590f);


    // mirror of Hill 2
    glVertex2f(0.68f,0.590f);
    glVertex2f(0.72f,0.605f);
    glVertex2f(0.76f,0.615f);
    glVertex2f(0.80f,0.605f);


    // mirror of Hill 1
    glVertex2f(0.84f,0.496f);
    glVertex2f(0.88f,0.605f);
    glVertex2f(0.92f,0.625f);
    glVertex2f(0.96f,0.635f);


    // right edge peak
    glVertex2f(1.0f,0.64f);


    // base
    glVertex2f(1.0f,0.45f);

    glEnd();
}

void drawForestLeft()
{
    glColor3f(0.12f, 0.42f, 0.26f); // greener forest tone

    glBegin(GL_POLYGON);

    // base
    glVertex2f(-1.0f, 0.45f);

    // left outer peak
    glVertex2f(-1.0f, 0.55f);


    // tree curve 1
    glVertex2f(-0.99f,0.555f);
    glVertex2f(-0.98f,0.560f);
    glVertex2f(-0.97f,0.550f);
    glVertex2f(-0.96f,0.540f);
    glVertex2f(-0.95f,0.530f);
    glVertex2f(-0.94f,0.540f);
    glVertex2f(-0.92f,0.552f);
    glVertex2f(-0.90f,0.554f);
    glVertex2f(-0.88f,0.560f);

    // tree curve 2
    glVertex2f(-0.86f,0.558f);
    glVertex2f(-0.84f,0.555f);
    glVertex2f(-0.82f,0.550f);
    glVertex2f(-0.80f,0.560f);
    glVertex2f(-0.78f,0.560f);
    glVertex2f(-0.76f,0.540f);

    // tree curve 3
    glVertex2f(-0.74f,0.550f);
    glVertex2f(-0.72f,0.530f);
    glVertex2f(-0.70f,0.535f);
    glVertex2f(-0.68f,0.550f);
    glVertex2f(-0.66f,0.555f);
    glVertex2f(-0.64f,0.535f);

    // tree curve 4
    glVertex2f(-0.62f,0.545f);
    glVertex2f(-0.60f,0.550f);
    glVertex2f(-0.58f,0.530f);
    glVertex2f(-0.52f,0.520f);

    // tree curve 5
    glVertex2f(-0.50f,0.525f);
    glVertex2f(-0.48f,0.530f);
    glVertex2f(-0.46f,0.535f);
    glVertex2f(-0.40f,0.520f);

    // tree curve 6
    glVertex2f(-0.34f,0.520f);
    glVertex2f(-0.30f,0.525f);
    glVertex2f(-0.28f,0.515f);

    // lowest valley before center
    glVertex2f(-0.20f,0.495f);
    glVertex2f(-0.17f,0.505f);
    glVertex2f(-0.14f,0.515f);
    glVertex2f(-0.12f,0.490f);
    glVertex2f(-0.09f,0.485f);
    glVertex2f(-0.06f,0.500f);
    glVertex2f(-0.04f,0.493f);


    // shared middle valley
    glVertex2f(0.00f,0.480f);
    glVertex2f(0.00f,0.45f);


    glEnd();
}
void drawForestRight()
{
    glColor3f(0.12f, 0.42f, 0.26f);

    glBegin(GL_POLYGON);

    // shared middle valley
    glVertex2f(0.00f,0.45f);
    glVertex2f(0.00f,0.480f);

    glVertex2f(0.04f,0.493f);
    glVertex2f(0.06f,0.500f);
    glVertex2f(0.09f,0.485f);
    glVertex2f(0.12f,0.490f);
    glVertex2f(0.14f,0.515f);
    glVertex2f(0.17f,0.505f);
    glVertex2f(0.20f,0.495f);

    glVertex2f(0.28f,0.515f);
    glVertex2f(0.30f,0.525f);
    glVertex2f(0.34f,0.520f);

    glVertex2f(0.40f,0.520f);
    glVertex2f(0.46f,0.535f);
    glVertex2f(0.48f,0.530f);
    glVertex2f(0.50f,0.525f);

    glVertex2f(0.52f,0.520f);
    glVertex2f(0.58f,0.530f);
    glVertex2f(0.60f,0.550f);
    glVertex2f(0.62f,0.545f);

    glVertex2f(0.64f,0.535f);
    glVertex2f(0.66f,0.555f);
    glVertex2f(0.68f,0.550f);
    glVertex2f(0.70f,0.535f);
    glVertex2f(0.72f,0.530f);
    glVertex2f(0.74f,0.550f);

    glVertex2f(0.76f,0.540f);
    glVertex2f(0.78f,0.560f);
    glVertex2f(0.80f,0.560f);
    glVertex2f(0.82f,0.550f);
    glVertex2f(0.84f,0.555f);
    glVertex2f(0.86f,0.558f);

    glVertex2f(0.88f,0.560f);
    glVertex2f(0.90f,0.554f);
    glVertex2f(0.92f,0.552f);
    glVertex2f(0.94f,0.540f);
    glVertex2f(0.95f,0.530f);
    glVertex2f(0.96f,0.540f);
    glVertex2f(0.97f,0.550f);
    glVertex2f(0.98f,0.560f);
    glVertex2f(0.99f,0.555f);

    // right outer peak
    glVertex2f(1.0f,0.55f);

    // close base
    glVertex2f(1.0f,0.45f);

    glEnd();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RABBY
//


void road()
{

    //Road Shape Left 1 (Silver)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.45f);
    glVertex2f(-0.45f, -1.0f);
    glVertex2f(-0.38f, -1.0f);
    glVertex2f(-0.131f, 0.447f);
    glEnd();

    //Road Shape Left 2 (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.131f, 0.447f);
    glVertex2f(-0.38f, -1.0f);
    glVertex2f(-0.35f, -1.0f);
    glVertex2f(-0.128f, 0.425f);
    glEnd();

    //Road Shape Left 3 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.128f, 0.425f);
    glVertex2f(-0.35f, -1.0f);
    glVertex2f(-0.26f, -1.0f);
    glVertex2f(-0.107f, 0.425f);
    glEnd();

    //Road Shape Left 4 (White)
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.107f, 0.425f);
    glVertex2f(-0.26f, -1.0f);
    glVertex2f(-0.235f, -1.0f);
    glVertex2f(-0.100f, 0.425f);
    glEnd();

    //Road Shape Left 5 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.100f, 0.425f);
    glVertex2f(-0.235f, -1.0f);
    glVertex2f(-0.015f, -1.0f);
    glVertex2f(-0.005f, 0.425f);
    glEnd();

    //Road Middle Line (White)
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.005f, 0.425f);
    glVertex2f(-0.015f, -1.0f);
    glVertex2f(0.015f, -1.0f);
    glVertex2f(0.005f, 0.425f);
    glEnd();



    //Road Shape Right 1 (Silver)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(0.130f, 0.447f);
    glVertex2f(0.38f, -1.0f);
    glVertex2f(0.45f, -1.0f);
    glVertex2f(0.15f, 0.45f);
    glEnd();

    //Road Shape Right 2 (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.131f, 0.447f);
    glVertex2f(0.128f, 0.425f);
    glVertex2f(0.35f, -1.0f);
    glVertex2f(0.38f, -1.0f);
    glEnd();

    //Road Shape Right 3 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(0.100f, 0.425f);
    glVertex2f(0.128f, 0.425f);
    glVertex2f(0.35f, -1.0f);
    glVertex2f(0.26f, -1.0f);
    glEnd();

    //Road Shape Right 4 (White)
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(0.100f, 0.425f);
    glVertex2f(0.107f, 0.425f);
    glVertex2f(0.26f, -1.0f);
    glVertex2f(0.235f, -1.0f);
    glEnd();

    //Road Shape right 5 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(0.100f, 0.425f);
    glVertex2f(0.005f, 0.425f);
    glVertex2f(0.015f, -1.0f);
    glVertex2f(0.235f, -1.0f);
    glEnd();


    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.65f);
    glVertex2f(-0.02f, -0.80);
    glVertex2f(0.02f, -0.80f);
    glVertex2f(0.02f, -0.65f);
    glEnd();

    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.35f);
    glVertex2f(-0.02f, -0.47);
    glVertex2f(0.02f, -0.47f);
    glVertex2f(0.02f, -0.35f);
    glEnd();

    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.10f);
    glVertex2f(-0.02f, -0.20);
    glVertex2f(0.02f, -0.20f);
    glVertex2f(0.02f, -0.10f);
    glEnd();

    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, 0.08f);
    glVertex2f(-0.02f, 0.0);
    glVertex2f(0.02f, 0.0f);
    glVertex2f(0.02f, 0.08f);
    glEnd();

    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, 0.24f);
    glVertex2f(-0.02f, 0.17f);
    glVertex2f(0.02f, 0.17f);
    glVertex2f(0.02f, 0.24f);
    glEnd();

    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, 0.35f);
    glVertex2f(-0.02f, 0.30f);
    glVertex2f(0.02f, 0.30f);
    glVertex2f(0.02f, 0.35f);
    glEnd();

    //Road Middle Line dot (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, 0.425f);
    glVertex2f(-0.02f, 0.40f);
    glVertex2f(0.02f, 0.40f);
    glVertex2f(0.02f, 0.425f);
    glEnd();


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SAIFUL
//
void initGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawHome()
{

    glColor3f(0.80f, 0.60f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(0.10f, 0.05f);
    glVertex2f(0.23f, 0.05f);
    glVertex2f(0.23f, 0.25f);
    glVertex2f(0.10f, 0.25f);
    glEnd();


    glColor3f(0.65f, 0.35f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.25f); // Base-left overhang
    glVertex2f(0.25f, 0.25f); // Base-right overhang
    glVertex2f(0.22f, 0.35f); // Top-right
    glVertex2f(0.11f, 0.35f); // Top-left
    glEnd();

    // 3. Centered Door (Dark Brown)
    glColor3f(0.45f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(0.15f, 0.05f);
    glVertex2f(0.18f, 0.05f);
    glVertex2f(0.18f, 0.16f);
    glVertex2f(0.15f, 0.16f);
    glEnd();

    // 4. Two Sky Blue Windows
    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_QUADS);
    // Left Window (to the left of the door)
    glVertex2f(0.11f, 0.12f);
    glVertex2f(0.14f, 0.12f);
    glVertex2f(0.14f, 0.18f);
    glVertex2f(0.11f, 0.18f);

    // Right Window (to the right of the door)
    glVertex2f(0.19f, 0.12f);
    glVertex2f(0.22f, 0.12f);
    glVertex2f(0.22f, 0.18f);
    glVertex2f(0.19f, 0.18f);
    glEnd();
}

void drawSchool()
{
    glColor3f(0.95f, 0.85f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0.42f, 0.00f);
    glVertex2f(0.70f, 0.00f);
    glVertex2f(0.70f, 0.30f);
    glVertex2f(0.42f, 0.30f);
    glEnd();

    // 2. Red Slanted Roof
    glColor3f(0.8f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0.40f, 0.30f);
    glVertex2f(0.72f, 0.30f);
    glVertex2f(0.68f, 0.40f);
    glVertex2f(0.44f, 0.40f);
    glEnd();



    // 4. Centered Door (Middle Down)
    glColor3f(0.4f, 0.2f, 0.1f); // Brown
    glBegin(GL_QUADS);
    glVertex2f(0.53f, 0.00f);
    glVertex2f(0.59f, 0.00f);
    glVertex2f(0.59f, 0.10f);
    glVertex2f(0.53f, 0.10f);
    glEnd();

    // 5. 6 Windows (Two rows of three)
    glColor3f(0.2f, 0.3f, 0.4f); // Dark Blue
    glBegin(GL_QUADS);
    // --- Top Row ---
    // Left
    glVertex2f(0.45f, 0.17f);
    glVertex2f(0.50f, 0.17f);
    glVertex2f(0.50f, 0.22f);
    glVertex2f(0.45f, 0.22f);
    // Middle
    glVertex2f(0.53f, 0.17f);
    glVertex2f(0.59f, 0.17f);
    glVertex2f(0.59f, 0.22f);
    glVertex2f(0.53f, 0.22f);
    // Right
    glVertex2f(0.62f, 0.17f);
    glVertex2f(0.67f, 0.17f);
    glVertex2f(0.67f, 0.22f);
    glVertex2f(0.62f, 0.22f);

    // --- Bottom Row ---
    // Left
    glVertex2f(0.45f, 0.05f);
    glVertex2f(0.50f, 0.05f);
    glVertex2f(0.50f, 0.10f);
    glVertex2f(0.45f, 0.10f);
    // Right
    glVertex2f(0.62f, 0.05f);
    glVertex2f(0.67f, 0.05f);
    glVertex2f(0.67f, 0.10f);
    glVertex2f(0.62f, 0.10f);

    glEnd();

}

void drawHospital()
{

    glColor3f(0.55f, 0.6f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(0.71f, -0.10f);
    glVertex2f(1.00f, -0.10f);
    glVertex2f(1.00f, 0.24f);
    glVertex2f(0.71f, 0.24f);
    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.73f, 0.12f);
    glVertex2f(0.81f, 0.12f);
    glVertex2f(0.81f, 0.22f);
    glVertex2f(0.73f, 0.22f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS); // Vertical
    glVertex2f(0.76f, 0.14f);
    glVertex2f(0.78f, 0.14f);
    glVertex2f(0.78f, 0.20f);
    glVertex2f(0.76f, 0.20f);
    // Horizontal
    glVertex2f(0.74f, 0.16f);
    glVertex2f(0.80f, 0.16f);
    glVertex2f(0.80f, 0.18f);
    glVertex2f(0.74f, 0.18f);
    glEnd();

    // 3. Yellow Windows
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    // Left Column (under + sign) - Row 1
    glVertex2f(0.73f, 0.06f);
    glVertex2f(0.76f, 0.06f);
    glVertex2f(0.76f, 0.10f);
    glVertex2f(0.73f, 0.10f);
    // Left Column (under + sign) - Row 2 (with gap)
    glVertex2f(0.73f, 0.00f);
    glVertex2f(0.76f, 0.00f);
    glVertex2f(0.76f, 0.04f);
    glVertex2f(0.73f, 0.04f);

    // Right Column (same height as left) - Row 1
    glVertex2f(0.78f, 0.06f);
    glVertex2f(0.81f, 0.06f);
    glVertex2f(0.81f, 0.10f);
    glVertex2f(0.78f, 0.10f);
    // Right Column (same height as left) - Row 2
    glVertex2f(0.78f, 0.00f);
    glVertex2f(0.81f, 0.00f);
    glVertex2f(0.81f, 0.04f);
    glVertex2f(0.78f, 0.04f);

    // Window upper right of door (not crossing the red box row)
    glVertex2f(0.93f, 0.06f);
    glVertex2f(0.97f, 0.06f);
    glVertex2f(0.97f, 0.11f);
    glVertex2f(0.93f, 0.11f);

    // Window left of the door
    glVertex2f(0.83f, 0.06f);
    glVertex2f(0.86f, 0.06f);
    glVertex2f(0.86f, 0.11f);
    glVertex2f(0.83f, 0.11f);
    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.88f, -0.10f); // Left bottom
    glVertex2f(0.92f, -0.10f); // Right bottom
    glVertex2f(0.92f, 0.04f);  // Right top (stays below windows)
    glVertex2f(0.88f, 0.04f);  // Left top
    glEnd();
}
void drawBuilding()
{
    // 1. Main Structure (Brown)
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(0.25f, 0.15f);
    glVertex2f(0.40f, 0.15f);
    glVertex2f(0.40f, 0.47f);
    glVertex2f(0.25f, 0.47f);
    glEnd();

    // 2. Windows (Sky Blue)
    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_QUADS);
    // --- ROW 1 (Top): 3 Windows ---
    // Left
    glVertex2f(0.27f, 0.40f);
    glVertex2f(0.30f, 0.40f);
    glVertex2f(0.30f, 0.45f);
    glVertex2f(0.27f, 0.45f);
    // Middle
    glVertex2f(0.31f, 0.40f);
    glVertex2f(0.34f, 0.40f);
    glVertex2f(0.34f, 0.45f);
    glVertex2f(0.31f, 0.45f);
    // Right
    glVertex2f(0.35f, 0.40f);
    glVertex2f(0.38f, 0.40f);
    glVertex2f(0.38f, 0.45f);
    glVertex2f(0.35f, 0.45f);


    // Left-Center
    glVertex2f(0.28f, 0.30f);
    glVertex2f(0.32f, 0.30f);
    glVertex2f(0.32f, 0.35f);
    glVertex2f(0.28f, 0.35f);
    // Right-Center
    glVertex2f(0.33f, 0.30f);
    glVertex2f(0.37f, 0.30f);
    glVertex2f(0.37f, 0.35f);
    glVertex2f(0.33f, 0.35f);

    // --- ROW 3 (Bottom): 2 Windows (Centered)
    glVertex2f(0.28f, 0.20f);
    glVertex2f(0.32f, 0.20f);
    glVertex2f(0.32f, 0.25f);
    glVertex2f(0.28f, 0.25f);
    // Right-Center
    glVertex2f(0.33f, 0.20f);
    glVertex2f(0.37f, 0.20f);
    glVertex2f(0.37f, 0.25f);
    glVertex2f(0.33f, 0.25f);
    glEnd();
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DISPLAY FUNCTION
//

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    ///////////////////////////////
    //FAHIM

    // Sky
    glColor3f(0.55f, 0.75f, 0.80f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(1.0f,1.0f);
    glVertex2f(1.0f,0.45f);
    glVertex2f(-1.0f,0.45f);
    glEnd();

    //sun
    glColor3ub(255, 255, 0);
    Circle(0.0f, 0.55f, 0.08f, 1000);

    drawMountainLeft();
    drawMountainRight();
    drawForestLeft();
    drawForestRight();
    drawCloud();

    //////////////////////////
    //RABBY
    road();

    ///////////////////////////////
    //SAIFUL
    drawHome();
    drawSchool();
    drawHospital();
    drawBuilding();

    ///////////////////////////////
    //ORNOB
    water();
    riverSide();
    ship();
    roadSide();






    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(960,540);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Scenario");
    glutDisplayFunc(display);
    glClearColor(1,1,1,1);
    glutMainLoop();

    return 0;
}
