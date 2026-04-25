#include<windows.h>
#include <GL/glut.h>
#define PI 3.141516
#include<math.h>
GLfloat txf = 0.0f;      // airplane movement (X direction)
GLfloat scalef = 1.0f;   // airplane size
int tFlagf = 0;
//SHOHAG
GLfloat tx1 = 0;
GLfloat ty1 = 0;
GLfloat tx2 = 0;
GLfloat ty2 = 0;
GLfloat tx3 = 0;
GLfloat ty3 = 0;
GLfloat scale1 = 1;
GLfloat scale2 = 1;
GLfloat scale3 = 1;
GLfloat angle = 0;
GLfloat scale = 1;
GLfloat zoom = 1;
int tFlag = 0;
int rFlag = 0;
GLfloat speed = 1.0f;


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
    glVertex2f(-0.1f, 0.45f);
    glVertex2f(-0.12f, 0.45f);
    glVertex2f(-0.55f, -1.0f);
    glVertex2f(-0.45f, -1.0f);
    glEnd();

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

    // original
   glPushMatrix();
    drawOneCloud();
    glPopMatrix();

    // SECOND shift right
    glPushMatrix();
    glTranslatef(0.5f, 0.13f, 0.0f); // move right
    drawCloud2();
    glPopMatrix();

    // THIRD shift middle top
    glPushMatrix();
    glTranslatef(1.5f, 0.15f, 0.0f); // move right
    drawOneCloud();
    glPopMatrix();
}

void drawMountain()
{
    glColor3f(0.78f,0.50f,0.28f);
    glBegin(GL_POLYGON);
    // base
    glVertex2f(-1.0f, 0.45f);
    // start outside
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

    // Hill 6
    glVertex2f(-0.10f,0.550f);
    glVertex2f(-0.08f,0.535f);
    glVertex2f(-0.04f,0.525f);
    glVertex2f(-0.03f,0.515f);
    // SHARED
    glVertex2f(0.0f,0.510f);
    glVertex2f(0.0f,0.45f);
    glEnd();

            glBegin(GL_POLYGON);
    // Shared
    glVertex2f(0.0f,0.45f);
    glVertex2f(0.0f,0.510f);

    // Hill6
    glVertex2f(0.03f,0.515f);
    glVertex2f(0.04f,0.525f);
    glVertex2f(0.08f,0.535f);
    glVertex2f(0.10f,0.550f);
    //  Hill 5
    glVertex2f(0.18f,0.515f);
    glVertex2f(0.22f,0.525f);
    glVertex2f(0.26f,0.540f);
    glVertex2f(0.30f,0.565f);
    //  Hill 4
    glVertex2f(0.36f,0.545f);
    glVertex2f(0.40f,0.555f);
    glVertex2f(0.44f,0.570f);
    glVertex2f(0.48f,0.585f);
    //  Hill 3
    glVertex2f(0.52f,0.595f);
    glVertex2f(0.56f,0.605f);
    glVertex2f(0.60f,0.600f);
    glVertex2f(0.64f,0.590f);
    // Hill 2
    glVertex2f(0.68f,0.590f);
    glVertex2f(0.72f,0.605f);
    glVertex2f(0.76f,0.615f);
    glVertex2f(0.80f,0.605f);
    //  Hill 1
    glVertex2f(0.84f,0.496f);
    glVertex2f(0.88f,0.605f);
    glVertex2f(0.92f,0.625f);
    glVertex2f(0.96f,0.635f);
    // right outside
    glVertex2f(1.0f,0.64f);
    // base
    glVertex2f(1.0f,0.45f);

    glEnd();
}

void drawForest()
{
    glColor3f(0.12f, 0.42f, 0.26f);
    glBegin(GL_POLYGON);
    // base
    glVertex2f(-1.0f, 0.45f);
    // left outer
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

    // lowest center
    glVertex2f(-0.20f,0.495f);
    glVertex2f(-0.17f,0.505f);
    glVertex2f(-0.14f,0.515f);
    glVertex2f(-0.12f,0.490f);
    glVertex2f(-0.09f,0.485f);
    glVertex2f(-0.06f,0.500f);
    glVertex2f(-0.04f,0.493f);
    // shared
    glVertex2f(0.00f,0.480f);
    glVertex2f(0.00f,0.45f);
    glEnd();

            glBegin(GL_POLYGON);
    // shared
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

    // right outer
    glVertex2f(1.0f,0.55f);
    // close base
    glVertex2f(1.0f,0.45f);

    glEnd();
}
void Airplane(){

     glColor3f(0.90f, 0.92f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.75f,0.79f);
        glVertex2f(-0.5f,0.79f);
        glVertex2f(-0.5f,0.71f);
        glVertex2f(-0.75f,0.71f);
    glEnd();

    glColor3f(0.82f, 0.05f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.75f,0.87f);
        glVertex2f(-0.72f,0.87f);
        glVertex2f(-0.68f,0.79f);
        glVertex2f(-0.75f,0.79f);
    glEnd();
    glBegin(GL_POLYGON);//up middle
        glVertex2f(-0.64f,0.855f);
        glVertex2f(-0.59f,0.855f);
        glVertex2f(-0.54f,0.79f);
        glVertex2f(-0.61f,0.79f);
    glEnd();
    //down
    glBegin(GL_POLYGON);
        glVertex2f(-0.60f,0.73f);
        glVertex2f(-0.52f,0.73f);
        glVertex2f(-0.59f,0.64f);
        glVertex2f(-0.64f,0.64);
    glEnd();

    // front
  glColor3f(0.85f, 0.87f, 0.90f);
  glBegin(GL_POLYGON);
    glVertex2f(-0.5f,0.79f);
    glVertex2f(-0.49f,0.788f);
    glVertex2f(-0.48f,0.783f);
    glVertex2f(-0.47f,0.775f);
    glVertex2f(-0.45f,0.760f);
    glVertex2f(-0.43f,0.740f);
    glVertex2f(-0.43f,0.720f);
    glVertex2f(-0.45f,0.715f);
    glVertex2f(-0.47f,0.71f);
    glVertex2f(-0.5f,0.71f);
glEnd();
glColor3f(0.6f, 0.6f, 0.6f); //nose
 glBegin(GL_POLYGON);
 glVertex2f(-0.5f,0.760f);
 glVertex2f(-0.45f,0.760f);
  glVertex2f(-0.43f,0.740f);
  glVertex2f(-0.5f,0.740f);
  glEnd();
  glColor3f(0.1f, 0.2f, 0.4f);
    Circle(-0.72f,0.75f,0.008f,100);
    //Circle(-0.68f,0.75f,0.008f,100);
    //Circle(-0.64f,0.75f,0.008f,100);
    //Circle(-0.60f,0.75f,0.008f,100);
    // Circle(-0.56f,0.75f,0.008f,100);
    Circle(-0.515f,0.75f,0.008f,100);

    }

    void drawText(float x, float y, const char *text)
{
    glRasterPos2f(x, y);
    for(int i = 0; text[i] != '\0'; i++)
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[i]);
    }
}

 void Airplane2(){
  glPushMatrix();
    glTranslatef(-0.47f, 0.4f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);   // makes smaller
    Airplane();
   glColor3f(0.05f, 0.10f, 0.30f);
drawText(-0.7f, 0.737f, "F&F Airlines");
    glPopMatrix();
 }

void keyboardf(unsigned char key, int x, int y)
{
    if(key == 'f')
        tFlagf = 1;

    if(key == 'g')
        tFlagf = 0;
}

 void updatef(int value)
{
    if(tFlagf == 1)
    {
        txf = txf + 0.006f;
        scalef = scalef - 0.001f;

        // exits
        if(txf >= 2.0f)
        {
            txf = 0.0f;      // return to start
            scalef = 1.0f;   // restore original size
            tFlagf = 0;      // stop
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updatef, 0);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SHOHAG
//


void road(){
    //Road Shape Left 1 (Silver)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.10f, 0.45f);
        glVertex2f(-0.50f, -1.0f);
        glVertex2f(-0.41f, -1.0f);
        glVertex2f(-0.090f, 0.45f);
    glEnd();

    //Road Shape Left 2 (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.090f, 0.447f);
        glVertex2f(-0.41f, -1.0f);
        glVertex2f(-0.38f, -1.0f);
        glVertex2f(-0.087f, 0.447f);
    glEnd();

    //Road Shape Left 3 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.087f, 0.447f);
        glVertex2f(-0.38f, -1.0f);
        glVertex2f(-0.30f, -1.0f);
        glVertex2f(-0.080f, 0.447f);
    glEnd();


    //Road Shape Left 4 (White)
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.080f, 0.447f);
        glVertex2f(-0.30f, -1.0f);
        glVertex2f(-0.275f, -1.0f);
        glVertex2f(-0.077f, 0.447f);
    glEnd();

     //Road Shape Left 5 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.077f, 0.447f);
        glVertex2f(-0.275f, -1.0f);
        glVertex2f(0.0187, -1.0f);
        glVertex2f(-0.033f, 0.447f);
    glEnd();

    //Road Middle Line (White)
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.033f, 0.447f);
        glVertex2f(0.017f, -1.0f);
        glVertex2f(0.045f, -1.0f);
        glVertex2f(0.015f, 0.425f);
    glEnd();



    //Road Shape Right 1 (Silver)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(0.03f, 0.45f);
        glVertex2f(0.45f, -1.0f);
        glVertex2f(0.55f, -1.0f);
        glVertex2f(0.04f, 0.45f);
    glEnd();

    //Road Shape Right 2 (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.030f, 0.447f);
        glVertex2f(0.026f, 0.447f);
        glVertex2f(0.42f, -1.0f);
        glVertex2f(0.45f, -1.0f);
    glEnd();

    //Road Shape Right 3 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(0.026f, 0.447f);
        glVertex2f(0.018f, 0.447f);
        glVertex2f(0.35f, -1.0f);
        glVertex2f(0.42f, -1.0f);
    glEnd();

    //Road Shape Right 4 (White)
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(0.015f, 0.447f);
        glVertex2f(0.018f, 0.447f);
        glVertex2f(0.325f, -1.0f);
        glVertex2f(0.35f, -1.0f);
    glEnd();

    //Road Shape right 5 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.029f, 0.447f);
        glVertex2f(0.045f, -1.0f);
        glVertex2f(0.325f, -1.0f);
        glVertex2f(0.015f, 0.447f);
    glEnd();

    //Road Top (Blue)
    glColor3f(0.0f, 0.0f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.09f, 0.45f);
        glVertex2f(-0.09f, 0.447f);
        glVertex2f(0.02f, 0.447f);
        glVertex2f(0.03f, 0.45f);
    glEnd();


    //Road Middle Line dot 1 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, -0.65f);
        glVertex2f(-0.02f, -0.80);
        glVertex2f(0.04f, -0.80f);
        glVertex2f(0.04f, -0.65f);
    glEnd();

    //Road Middle Line dot 2 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, -0.35f);
        glVertex2f(-0.02f, -0.47);
        glVertex2f(0.02f, -0.47f);
        glVertex2f(0.02f, -0.35f);
    glEnd();

    //Road Middle Line dot 3 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, -0.12f);
        glVertex2f(-0.02f, -0.220);
        glVertex2f(0.02f, -0.22f);
        glVertex2f(0.02f, -0.12f);
    glEnd();

    //Road Middle Line dot 4 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, 0.06f);
        glVertex2f(-0.02f, -0.02);
        glVertex2f(0.02f, -0.02f);
        glVertex2f(0.02f, 0.06f);
    glEnd();

    //Road Middle Line dot 5 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f, 0.21f);
        glVertex2f(-0.03f, 0.14f);
        glVertex2f(0.01f, 0.14f);
        glVertex2f(0.01f, 0.21f);
    glEnd();

    //Road Middle Line dot 6 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.325f);
        glVertex2f(-0.04f, 0.275f);
        glVertex2f(0.01f, 0.275f);
        glVertex2f(0.01f, 0.325f);
    glEnd();

     //Road Middle Line dot 7 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.4f);
        glVertex2f(-0.04f, 0.365f);
        glVertex2f(0.0f, 0.365f);
        glVertex2f(0.0f, 0.4f);
    glEnd();

    //Road Middle Line dot 8 (Black)
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.06f, 0.447f);
        glVertex2f(-0.06f, 0.43f);
        glVertex2f(-0.01f, 0.43f);
        glVertex2f(-0.01f, 0.447f);
    glEnd();



}


void drawCar1(float tx1, float ty1, float scale1, float angle)
{
    glPushMatrix();

    glTranslatef(tx1, ty1, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale1, scale1, 1);



     // Car 1 Back(Red)
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.33f, -0.240f);
        glVertex2f(-0.335f, -0.295f);
        glVertex2f(-0.335f, -0.335f);
        glVertex2f(-0.105f, -0.335f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.11f, -0.240f);
    glEnd();

    // Car 1 light Left
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.325f, -0.246f);
        glVertex2f(-0.325f, -0.276f);
        glVertex2f(-0.285f, -0.276f);
        glVertex2f(-0.285f, -0.246f);
    glEnd();

    // Car 1 light right
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.155f, -0.246f);
        glVertex2f(-0.155f, -0.276f);
        glVertex2f(-0.115f, -0.276f);
        glVertex2f(-0.115f, -0.246f);
    glEnd();

    // Car 1 spot
    glColor3f(1.0f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.335f, -0.295f);
        glVertex2f(-0.285f, -0.297f);
        glVertex2f(-0.155f, -0.297f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.155f, -0.285f);
        glVertex2f(-0.285f, -0.285f);

    glEnd();

    // Car 1 spot(Black)
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.257f, -0.257f);
        glVertex2f(-0.260f, -0.260f);
        glVertex2f(-0.260f, -0.285f);
        glVertex2f(-0.257f, -0.288f);
        glVertex2f(-0.173f, -0.288f);
        glVertex2f(-0.170f, -0.285f);
        glVertex2f(-0.170f, -0.260f);
        glVertex2f(-0.173f, -0.257f);

    glEnd();

    // Car 1 B1
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.30f, -0.21f);
        glVertex2f(-0.33f, -0.24f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.12f, -0.215f);
    glEnd();

    // Car 1 B2
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.28f, -0.14f);
        glVertex2f(-0.30f, -0.21f);
        glVertex2f(-0.12f, -0.215f);
        glVertex2f(-0.14f, -0.15f);
    glEnd();

     // Car 1 B2 glass
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.27f, -0.155f);
        glVertex2f(-0.29f, -0.205f);
        glVertex2f(-0.13f, -0.205f);
        glVertex2f(-0.15f, -0.158f);
    glEnd();

    // Car 1 roof
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.26f, -0.125f);
        glVertex2f(-0.28f, -0.14f);
        glVertex2f(-0.14f, -0.15f);
        glVertex2f(-0.13f, -0.130f);
    glEnd();

    // Car 1 Side
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.13f, -0.130f);
        glVertex2f(-0.14f, -0.15f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.090f, -0.17f);

    glEnd();

     // Car 1 Side glass
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.127f, -0.140f);
        glVertex2f(-0.135f, -0.160f);
        glVertex2f(-0.104f, -0.230f);
        glVertex2f(-0.095f, -0.175f);

    glEnd();

    // Car 1 Side
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.090f, -0.17f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.105f, -0.335f);
        glVertex2f(-0.09f, -0.23f);
        glVertex2f(-0.09f, -0.17f);
    glEnd();

    // Car 1 wheel
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.10f, -0.285f);
        glVertex2f(-0.11f, -0.330f);
        glVertex2f(-0.11f, -0.335f);
        glVertex2f(-0.10f, -0.335f);
    glEnd();

    // Car 1 wheel L
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.140f, -0.335f);
        glVertex2f(-0.145f, -0.385f);
        glVertex2f(-0.140f, -0.391f);
        glVertex2f(-0.11f, -0.390f);
        glVertex2f(-0.105f, -0.375f);
        glVertex2f(-0.105f, -0.335f);
    glEnd();

    // Car 1 wheel R
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.330f, -0.335f);
        glVertex2f(-0.330f, -0.380f);
        glVertex2f(-0.325f, -0.390f);
        glVertex2f(-0.295f, -0.390f);
        glVertex2f(-0.290f, -0.375f);
        glVertex2f(-0.290f, -0.335f);
    glEnd();

    // Car 1 wheel Middle Black
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.295f, -0.335f);
        glVertex2f(-0.295f, -0.360f);
        glVertex2f(-0.140f, -0.360f);
        glVertex2f(-0.140f, -0.335f);
    glEnd();

    // Car 1 wheel L
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.09f, -0.23f);
        glVertex2f(-0.105f, -0.30f);
        glVertex2f(-0.095f, -0.30f);

    glEnd();

    // Car 1 Side Mirror
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.095f, -0.158f);
        glVertex2f(-0.095f, -0.182f);
        glVertex2f(-0.077f, -0.187f);
        glVertex2f(-0.077f, -0.165f);

    glEnd();




    glPopMatrix();
}


///////////

void drawCar2(float tx2, float ty2, float scale2, float angle)
{
    glPushMatrix();

    glTranslatef(tx2, ty2, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale2, scale2, 1);

     // Car 1 Back(Red)
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.33f, -0.240f);
        glVertex2f(-0.335f, -0.295f);
        glVertex2f(-0.335f, -0.335f);
        glVertex2f(-0.105f, -0.335f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.11f, -0.240f);
    glEnd();

    // Car 1 light Left
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.325f, -0.246f);
        glVertex2f(-0.325f, -0.276f);
        glVertex2f(-0.285f, -0.276f);
        glVertex2f(-0.285f, -0.246f);
    glEnd();

    // Car 1 light right
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.155f, -0.246f);
        glVertex2f(-0.155f, -0.276f);
        glVertex2f(-0.115f, -0.276f);
        glVertex2f(-0.115f, -0.246f);
    glEnd();

    // Car 1 spot
    glColor3f(1.0f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.335f, -0.295f);
        glVertex2f(-0.285f, -0.297f);
        glVertex2f(-0.155f, -0.297f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.155f, -0.285f);
        glVertex2f(-0.285f, -0.285f);

    glEnd();

    // Car 1 spot(Black)
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.257f, -0.257f);
        glVertex2f(-0.260f, -0.260f);
        glVertex2f(-0.260f, -0.285f);
        glVertex2f(-0.257f, -0.288f);
        glVertex2f(-0.173f, -0.288f);
        glVertex2f(-0.170f, -0.285f);
        glVertex2f(-0.170f, -0.260f);
        glVertex2f(-0.173f, -0.257f);

    glEnd();

    // Car 1 B1
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.30f, -0.21f);
        glVertex2f(-0.33f, -0.24f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.12f, -0.215f);
    glEnd();

    // Car 1 B2
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.28f, -0.14f);
        glVertex2f(-0.30f, -0.21f);
        glVertex2f(-0.12f, -0.215f);
        glVertex2f(-0.14f, -0.15f);
    glEnd();

     // Car 1 B2 glass
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.27f, -0.155f);
        glVertex2f(-0.29f, -0.205f);
        glVertex2f(-0.13f, -0.205f);
        glVertex2f(-0.15f, -0.158f);
    glEnd();

    // Car 1 roof
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.26f, -0.125f);
        glVertex2f(-0.28f, -0.14f);
        glVertex2f(-0.14f, -0.15f);
        glVertex2f(-0.13f, -0.130f);
    glEnd();

    // Car 1 Side
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.13f, -0.130f);
        glVertex2f(-0.14f, -0.15f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.090f, -0.17f);

    glEnd();

     // Car 1 Side glass
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.127f, -0.140f);
        glVertex2f(-0.135f, -0.160f);
        glVertex2f(-0.104f, -0.230f);
        glVertex2f(-0.095f, -0.175f);

    glEnd();

    // Car 1 Side
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.090f, -0.17f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.105f, -0.335f);
        glVertex2f(-0.09f, -0.23f);
        glVertex2f(-0.09f, -0.17f);
    glEnd();

    // Car 1 wheel
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.10f, -0.285f);
        glVertex2f(-0.11f, -0.330f);
        glVertex2f(-0.11f, -0.335f);
        glVertex2f(-0.10f, -0.335f);
    glEnd();

    // Car 1 wheel L
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.140f, -0.335f);
        glVertex2f(-0.145f, -0.385f);
        glVertex2f(-0.140f, -0.391f);
        glVertex2f(-0.11f, -0.390f);
        glVertex2f(-0.105f, -0.375f);
        glVertex2f(-0.105f, -0.335f);
    glEnd();

    // Car 1 wheel R
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.330f, -0.335f);
        glVertex2f(-0.330f, -0.380f);
        glVertex2f(-0.325f, -0.390f);
        glVertex2f(-0.295f, -0.390f);
        glVertex2f(-0.290f, -0.375f);
        glVertex2f(-0.290f, -0.335f);
    glEnd();

    // Car 1 wheel Middle Black
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.295f, -0.335f);
        glVertex2f(-0.295f, -0.360f);
        glVertex2f(-0.140f, -0.360f);
        glVertex2f(-0.140f, -0.335f);
    glEnd();

    // Car 1 wheel L
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.09f, -0.23f);
        glVertex2f(-0.105f, -0.30f);
        glVertex2f(-0.095f, -0.30f);

    glEnd();

    // Car 1 Side Mirror
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.095f, -0.158f);
        glVertex2f(-0.095f, -0.182f);
        glVertex2f(-0.077f, -0.187f);
        glVertex2f(-0.077f, -0.165f);

    glEnd();




    glPopMatrix();
}




///////////


void drawCar3(float tx3, float ty3, float scale3, float angle)
{
    glPushMatrix();

    glTranslatef(tx3, ty3, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale3, scale3, 1);

     // Car 1 Back(Red)
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.33f, -0.240f);
        glVertex2f(-0.335f, -0.295f);
        glVertex2f(-0.335f, -0.335f);
        glVertex2f(-0.105f, -0.335f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.11f, -0.240f);
    glEnd();

    // Car 1 light Left
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.325f, -0.246f);
        glVertex2f(-0.325f, -0.276f);
        glVertex2f(-0.285f, -0.276f);
        glVertex2f(-0.285f, -0.246f);
    glEnd();

    // Car 1 light right
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.155f, -0.246f);
        glVertex2f(-0.155f, -0.276f);
        glVertex2f(-0.115f, -0.276f);
        glVertex2f(-0.115f, -0.246f);
    glEnd();

    // Car 1 spot
    glColor3f(1.0f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.335f, -0.295f);
        glVertex2f(-0.285f, -0.297f);
        glVertex2f(-0.155f, -0.297f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.155f, -0.285f);
        glVertex2f(-0.285f, -0.285f);

    glEnd();

    // Car 1 spot(Black)
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.257f, -0.257f);
        glVertex2f(-0.260f, -0.260f);
        glVertex2f(-0.260f, -0.285f);
        glVertex2f(-0.257f, -0.288f);
        glVertex2f(-0.173f, -0.288f);
        glVertex2f(-0.170f, -0.285f);
        glVertex2f(-0.170f, -0.260f);
        glVertex2f(-0.173f, -0.257f);

    glEnd();

    // Car 1 B1
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.30f, -0.21f);
        glVertex2f(-0.33f, -0.24f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.12f, -0.215f);
    glEnd();

    // Car 1 B2
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.28f, -0.14f);
        glVertex2f(-0.30f, -0.21f);
        glVertex2f(-0.12f, -0.215f);
        glVertex2f(-0.14f, -0.15f);
    glEnd();

     // Car 1 B2 glass
    glColor3f(0.35f, 0.45f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.27f, -0.155f);
        glVertex2f(-0.29f, -0.205f);
        glVertex2f(-0.13f, -0.205f);
        glVertex2f(-0.15f, -0.158f);
    glEnd();

    // Car 1 roof
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.26f, -0.125f);
        glVertex2f(-0.28f, -0.14f);
        glVertex2f(-0.14f, -0.15f);
        glVertex2f(-0.13f, -0.130f);
    glEnd();

    // Car 1 Side
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.13f, -0.130f);
        glVertex2f(-0.14f, -0.15f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.090f, -0.17f);

    glEnd();

     // Car 1 Side glass
    glColor3f(0.35f, 0.45f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.127f, -0.140f);
        glVertex2f(-0.135f, -0.160f);
        glVertex2f(-0.104f, -0.230f);
        glVertex2f(-0.095f, -0.175f);

    glEnd();

    // Car 1 Side
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.090f, -0.17f);
        glVertex2f(-0.11f, -0.24f);
        glVertex2f(-0.105f, -0.295f);
        glVertex2f(-0.105f, -0.335f);
        glVertex2f(-0.09f, -0.23f);
        glVertex2f(-0.09f, -0.17f);
    glEnd();

    // Car 1 wheel
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.10f, -0.285f);
        glVertex2f(-0.11f, -0.330f);
        glVertex2f(-0.11f, -0.335f);
        glVertex2f(-0.10f, -0.335f);
    glEnd();

    // Car 1 wheel L
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.140f, -0.335f);
        glVertex2f(-0.145f, -0.385f);
        glVertex2f(-0.140f, -0.391f);
        glVertex2f(-0.11f, -0.390f);
        glVertex2f(-0.105f, -0.375f);
        glVertex2f(-0.105f, -0.335f);
    glEnd();

    // Car 1 wheel R
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.330f, -0.335f);
        glVertex2f(-0.330f, -0.380f);
        glVertex2f(-0.325f, -0.390f);
        glVertex2f(-0.295f, -0.390f);
        glVertex2f(-0.290f, -0.375f);
        glVertex2f(-0.290f, -0.335f);
    glEnd();

    // Car 1 wheel Middle Black
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.295f, -0.335f);
        glVertex2f(-0.295f, -0.360f);
        glVertex2f(-0.140f, -0.360f);
        glVertex2f(-0.140f, -0.335f);
    glEnd();

    // Car 1 wheel L
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.09f, -0.23f);
        glVertex2f(-0.105f, -0.30f);
        glVertex2f(-0.095f, -0.30f);

    glEnd();

    // Car 1 Side Mirror
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.095f, -0.158f);
        glVertex2f(-0.095f, -0.182f);
        glVertex2f(-0.077f, -0.187f);
        glVertex2f(-0.077f, -0.165f);

    glEnd();




    glPopMatrix();
}





void keyboardS(unsigned char key, int x, int y) {
    switch(key) {
    case 'a':
        tFlag = 1;
        break;
    case 's':
        tFlag = 0;
        break;


    }
    glutPostRedisplay();
}

void updateS(int value) {

    if(tFlag == 1){

        //car1
        tx1 -= 0.0002f;
        ty1 += 0.01f;
        scale1 = 0.70f - (ty1 * 0.57f);

        if(ty1 >= 0.70f){
            tx1 = 0.0f;
            ty1 = -1.0f;
        }

        //car2
        tx2 = 0.004f;
        ty2 += 0.01f;
        scale2 = 0.33f - (ty2 * 0.5f);

        if(ty2 >= 0.14f){
            tx2 = 0.0f;
            ty2 = -1.4f;
        }

        //car3
        ty3 += 0.01f;
        tx3 = 0.0f - (ty3 * 0.25f);
        //ty3 += 0.01f;
        scale3 = 0.50f - (ty3 * 0.57f);

        if(ty3 >= 0.40f){
            //tx3 = 0.5f;
            ty3 = -1.0f;
        }





    }


    if(rFlag == 1){
        angle += speed;
    }


    if(scale1 < 0.25f) scale1 = 0.25f;
    if(scale1 > 0.75f) scale1 = 0.75f;
    if(scale2 < 0.25f) scale2 = 0.25f;
    if(scale2 > 0.50f) scale2 = 0.50f;
    if(scale3 < 0.25f) scale3 = 0.25f;
    if(scale3 > 0.70f) scale3 = 0.70f;

    glutPostRedisplay();
    glutTimerFunc(16, updateS, 0);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SAFIUL
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
    // 1. Main Structure (Brown Walls)
    // Shifted lower: y starts at -0.6 and ends at -0.3
    glColor3f(0.80f, 0.60f, 0.40f);
    glBegin(GL_QUADS);
        glVertex2f(0.75f, -0.60f); // Bottom-left
        glVertex2f(0.98f, -0.60f); // Bottom-right
        glVertex2f(0.98f, -0.30f); // Top-right
        glVertex2f(0.75f, -0.30f); // Top-left
    glEnd();

    // 2. Enlarged Roof (Red-Brown)
    // Peak is moved to -0.15 so it stays below the Hospital windows
    glColor3f(0.65f, 0.35f, 0.25f);
    glBegin(GL_POLYGON);
        glVertex2f(0.72f, -0.30f); // Base-left overhang
        glVertex2f(1.00f, -0.30f); // Base-right overhang
        glVertex2f(0.95f, -0.15f); // Top-right
        glVertex2f(0.77f, -0.15f); // Top-left
    glEnd();

    // 3. Bigger Door (Dark Brown)
    glColor3f(0.45f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0.84f, -0.60f);
        glVertex2f(0.89f, -0.60f);
        glVertex2f(0.89f, -0.40f);
        glVertex2f(0.84f, -0.40f);
    glEnd();

    // 4. Two Larger Sky Blue Windows
    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_QUADS);
        // Left Window
        glVertex2f(0.77f, -0.50f);
        glVertex2f(0.82f, -0.50f);
        glVertex2f(0.82f, -0.37f);
        glVertex2f(0.77f, -0.37f);

        // Right Window
        glVertex2f(0.91f, -0.50f);
        glVertex2f(0.96f, -0.50f);
        glVertex2f(0.96f, -0.37f);
        glVertex2f(0.91f, -0.37f);
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
void drawFlag() {
    // 1. Small Flagpole (Stick)
    // Positioned further left at x=0.38
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(0.380f, -0.05f); // Bottom
        glVertex2f(0.385f, -0.05f);
        glVertex2f(0.385f,  0.22f); // Top
        glVertex2f(0.380f,  0.22f);
    glEnd();

    // 2. Small Green Rectangle
    glColor3f(0.0f, 0.42f, 0.31f);
    glBegin(GL_QUADS);
        glVertex2f(0.385f, 0.14f);
        glVertex2f(0.460f, 0.14f);
        glVertex2f(0.460f, 0.20f);
        glVertex2f(0.385f, 0.20f);
    glEnd();

    // 3. Red Circle (Disk) using GL_TRIANGLE_FAN
    glColor3f(0.95f, 0.18f, 0.13f);

    float circleX = 0.415f;    // Center X
    float circleY = 0.170f;    // Center Y
    float radius = 0.015f;     // Circle size
    int triangleAmount = 40;   // Smoothness
    GLfloat twicePi = 2.0f * 3.14159f;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(circleX, circleY); // Center of circle
        for(int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                circleX + (radius * cos(i * twicePi / triangleAmount)),
                circleY + (radius * sin(i * twicePi / triangleAmount))
            );
        }
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
void drawTwinTowers() {
    // 1. Tower Body (Dark Gray/Navy)
    // We use the original width (0.06 units) and original height (0.56 units)
    // but starting from y = 0.25 (behind the Hospital)
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_QUADS);
        // Left Twin
        glVertex2f(0.85f, 0.25f); // Base starts at Hospital roof height
        glVertex2f(0.91f, 0.25f);
        glVertex2f(0.91f, 0.81f); // Restored tall shape (Height = 0.56)
        glVertex2f(0.85f, 0.81f);

        // Right Twin
        glVertex2f(0.93f, 0.25f);
        glVertex2f(0.99f, 0.25f);
        glVertex2f(0.99f, 0.81f); // Restored tall shape
        glVertex2f(0.93f, 0.81f);
    glEnd();

    // 2. Tower Windows (Sky Blue)
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
        // Loop restored to the original window count/size
        for(float h = 0.30f; h < 0.75f; h += 0.12f) {
            // Left Tower Windows
            glVertex2f(0.86f, h); glVertex2f(0.90f, h);
            glVertex2f(0.90f, h + 0.08f); glVertex2f(0.86f, h + 0.08f);

            // Right Tower Windows
            glVertex2f(0.94f, h); glVertex2f(0.98f, h);
            glVertex2f(0.98f, h + 0.08f); glVertex2f(0.94f, h + 0.08f);
        }
    glEnd();

    // 3. Antennas (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex2f(0.88f, 0.81f); glVertex2f(0.88f, 0.91f);
        glVertex2f(0.96f, 0.81f); glVertex2f(0.96f, 0.91f);
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
    Circle(0.0f, 0.55f, 0.075f, 40);

    drawMountain();
    drawForest();
    drawCloud();
// Airplane
    glPushMatrix();
    glTranslatef(txf, 0.0f, 0.0f);
    glScalef(scalef, scalef, 1.0f);
    Airplane2();
    glPopMatrix();



    //////////////////////////
    //SHOHAG
    road();
    drawCar1(0.02f + tx1, -0.2f + ty1, scale1, 7.0f);
    drawCar2(-0.01f + tx2, 0.35f + ty2, scale2, 7.0f);
    drawCar3(0.15f + tx3, 0.1f + ty3, scale3, 05.0f);


    ///////////////////////////////
    //SAFIUL
    drawHome();
    drawSchool();
    drawHospital();
    drawBuilding();
    drawTwinTowers();
    drawFlag();


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

    glutKeyboardFunc(keyboardf);
    glutKeyboardFunc(keyboardS);
    glutTimerFunc(16, updatef, 0);
    glutTimerFunc(16, updateS, 0);
     glClearColor(0.5f,0.8f,0.5f,1.0f);
    glutMainLoop();



    return 0;
}
