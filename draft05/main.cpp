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


//
//ORNOB
//
float ornob_shipX = 0.0f;      // Current translation X
float ornob_shipY = 0.0f;      // Current translation Y
float ornob_shipScale = 1.0f;   // Starting size (100%)
float ornob_shipAngle = 0.0f;   // Slight tilt
bool ornob_isMoving = false;    // The Start/Stop switch



////////////////////////

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
    glVertex2f(-.1,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-1.0);
    glVertex2f(-.45,-1.0);
    glEnd();

}

void ship()
{
    // Set the outline thickness once at the top
    glLineWidth(1.0f);

    // ==========================================
    // Boat background
    // ==========================================
    glColor3f(0.1f, 0.2f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();

    // ==========================================
    // Upper body
    // ==========================================

    // Boat upper body 1 (Main cabin front)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-.88, -.35);
    glVertex2f(-.75, -.35);
    glVertex2f(-.75, -.2);
    glVertex2f(-.88, -.2);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.88, -.35);
    glVertex2f(-.75, -.35);
    glVertex2f(-.75, -.2);
    glVertex2f(-.88, -.2);
    glEnd();

    // Boat upper body 2 (Roof)
    glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-.88, -.2);
    glVertex2f(-.75, -.2);
    glVertex2f(-.71, -.19);
    glVertex2f(-.83, -.19);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.88, -.2);
    glVertex2f(-.75, -.2);
    glVertex2f(-.71, -.19);
    glVertex2f(-.83, -.19);
    glEnd();

    // Boat upper body 3 (Cabin side wall)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-.71, -.19);
    glVertex2f(-.75, -.2);
    glVertex2f(-.75, -.4);
    glVertex2f(-.71, -.4);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.71, -.19);
    glVertex2f(-.75, -.2);
    glVertex2f(-.75, -.4);
    glVertex2f(-.71, -.4);
    glEnd();

    // ==========================================
    // Lower body (Black base)
    // ==========================================

    // Polygon 1: The Left side
    glColor3f(0.0f, 0.0f, 0.0f);
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

    // (Note: Outlines skipped here because the fill is already black)

    // ==========================================
    // Lower body (Deep Maritime Red)
    // ==========================================

    // Polygon 1: The Left side
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.875f, -0.43f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.43f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.875f, -0.43f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.43f);
    glEnd();

    // Polygon 2: The right side
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.425f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.49f, -0.355f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.72f, -0.425f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.49f, -0.355f);
    glEnd();

    // Polygon 3: The middle side
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, -0.43f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.425f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.75f, -0.43f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.425f);
    glEnd();

    // ==========================================
    // Containers
    // ==========================================

    // Container 1
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-.70, -.285);
    glVertex2f(-.70, -.365);
    glVertex2f(-.6, -.335);
    glVertex2f(-.6, -.26);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.70, -.285);
    glVertex2f(-.70, -.365);
    glVertex2f(-.6, -.335);
    glVertex2f(-.6, -.26);
    glEnd();

    // Container 2
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-.60, -.26);
    glVertex2f(-.60, -.335);
    glVertex2f(-.5, -.31);
    glVertex2f(-.5, -.235);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.60, -.26);
    glVertex2f(-.60, -.335);
    glVertex2f(-.5, -.31);
    glVertex2f(-.5, -.235);
    glEnd();

    // ==========================================
    // WINDOWS (in cabin)
    // ==========================================

    // Window 1
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.87f, -0.30f);
    glVertex2f(-0.84f, -0.30f);
    glVertex2f(-0.84f, -0.26f);
    glVertex2f(-0.87f, -0.26f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.87f, -0.30f);
    glVertex2f(-0.84f, -0.30f);
    glVertex2f(-0.84f, -0.26f);
    glVertex2f(-0.87f, -0.26f);
    glEnd();

    // Window 2
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.83f, -0.30f);
    glVertex2f(-0.80f, -0.30f);
    glVertex2f(-0.80f, -0.26f);
    glVertex2f(-0.83f, -0.26f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.83f, -0.30f);
    glVertex2f(-0.80f, -0.30f);
    glVertex2f(-0.80f, -0.26f);
    glVertex2f(-0.83f, -0.26f);
    glEnd();

    // Window 3
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.79f, -0.30f);
    glVertex2f(-0.76f, -0.30f);
    glVertex2f(-0.76f, -0.26f);
    glVertex2f(-0.79f, -0.26f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.79f, -0.30f);
    glVertex2f(-0.76f, -0.30f);
    glVertex2f(-0.76f, -0.26f);
    glVertex2f(-0.79f, -0.26f);
    glEnd();
}

void ornob_house1()
{
    glLineWidth(.25f); // Set outline thickness

    // ==========================================
    // WALLS
    // ==========================================

    // body1 (Front Wall) - Light Slate Grey
    glColor3f(0.80f, 0.82f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.12f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.59f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.12f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.59f, 0.2f);
    glEnd();

    // body2 (Side Wall) - Medium Slate Grey for depth
    glColor3f(0.70f, 0.72f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.59f, 0.2f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.55f, 0.155f);
    glVertex2f(-0.55f, 0.23f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.59f, 0.2f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.55f, 0.155f);
    glVertex2f(-0.55f, 0.23f);
    glEnd();

    // ==========================================
    // ROOF
    // ==========================================

    // roof1 (Side Roof) - Dark Charcoal/Navy
    glColor3f(0.20f, 0.25f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(-0.575f, 0.28f);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.585f, 0.2f);
    glVertex2f(-0.54f, 0.23f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.575f, 0.28f);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.585f, 0.2f);
    glVertex2f(-0.54f, 0.23f);
    glEnd();

    // roof2 (Front Roof Triangle) - Deeper Charcoal
    glColor3f(0.15f, 0.20f, 0.25f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.65f, 0.2f);
    glVertex2f(-0.585f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.65f, 0.2f);
    glVertex2f(-0.585f, 0.2f);
    glEnd();

    // ==========================================
    // FRONT WALL ELEMENTS
    // ==========================================

    // Front Window 1 (Left) - Warm glowing yellow
    glColor3f(0.95f, 0.85f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-0.633f, 0.175f);
    glVertex2f(-0.633f, 0.148f);
    glVertex2f(-0.619f, 0.148f);
    glVertex2f(-0.619f, 0.175f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.633f, 0.175f);
    glVertex2f(-0.633f, 0.148f);
    glVertex2f(-0.619f, 0.148f);
    glVertex2f(-0.619f, 0.175f);
    glEnd();

    // Front Window 2 (Right) - Warm glowing yellow
    glColor3f(0.95f, 0.85f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-0.61f, 0.175f);
    glVertex2f(-0.61f, 0.148f);
    glVertex2f(-0.596f, 0.148f);
    glVertex2f(-0.596f, 0.175f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.61f, 0.175f);
    glVertex2f(-0.61f, 0.148f);
    glVertex2f(-0.596f, 0.148f);
    glVertex2f(-0.596f, 0.175f);
    glEnd();

    // ==========================================
    // SIDE WALL ELEMENTS
    // ==========================================

    // Side Window 1 (Left side of the angled wall)
    glColor3f(0.95f, 0.85f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-0.585f, 0.179f);
    glVertex2f(-0.585f, 0.152f);
    glVertex2f(-0.578f, 0.158f);
    glVertex2f(-0.578f, 0.185f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.585f, 0.179f);
    glVertex2f(-0.585f, 0.152f);
    glVertex2f(-0.578f, 0.158f);
    glVertex2f(-0.578f, 0.185f);
    glEnd();

    // Side Door (Centered on the angled wall) - Dark Walnut Wood
    glColor3f(0.30f, 0.15f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.575f, 0.185f);
    glVertex2f(-0.575f, 0.135f);
    glVertex2f(-0.565f, 0.143f);
    glVertex2f(-0.565f, 0.1925f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.575f, 0.185f);
    glVertex2f(-0.575f, 0.135f);
    glVertex2f(-0.565f, 0.143f);
    glVertex2f(-0.565f, 0.1925f);
    glEnd();

    // Side Window 2 (Right side of the angled wall)
    glColor3f(0.95f, 0.85f, 0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-0.562f, 0.195f);
    glVertex2f(-0.562f, 0.168f);
    glVertex2f(-0.554f, 0.176f);
    glVertex2f(-0.554f, 0.202f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.562f, 0.195f);
    glVertex2f(-0.562f, 0.168f);
    glVertex2f(-0.554f, 0.176f);
    glVertex2f(-0.554f, 0.202f);
    glEnd();
}

void ornob_house2()
{
    glLineWidth(.1f); // Set outline thickness once at the top

    // ==========================================
    // WALLS
    // ==========================================

    // body1 (Front Wall) - Cream/Beige
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7915f, 0.112f);
    glVertex2f(-0.7915f, 0.024f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.7365f, 0.112f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7915f, 0.112f);
    glVertex2f(-0.7915f, 0.024f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.7365f, 0.112f);
    glEnd();

    // body2 (Side Wall) - Darker Tan for shadow/depth
    glColor3f(0.8f, 0.7f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7365f, 0.112f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.6925f, 0.0625f);
    glVertex2f(-0.6925f, 0.145f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7365f, 0.112f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.6925f, 0.0625f);
    glVertex2f(-0.6925f, 0.145f);
    glEnd();

    // ==========================================
    // ROOF
    // ==========================================

    // roof1 - Terracotta Red
    glColor3f(0.8f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.720f, 0.200f);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.731f, 0.112f);
    glVertex2f(-0.6815f, 0.145f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.720f, 0.200f);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.731f, 0.112f);
    glVertex2f(-0.6815f, 0.145f);
    glEnd();

    // roof2 - Darker Terracotta Red
    glColor3f(0.6f, 0.2f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.8025f, 0.112f);
    glVertex2f(-0.731f, 0.112f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.8025f, 0.112f);
    glVertex2f(-0.731f, 0.112f);
    glEnd();

    // ==========================================
    // FRONT WALL ELEMENTS
    // ==========================================

    // Front Window 1 (Left) - Light Blue Glass
    glColor3f(0.5f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7838f, 0.0845f);
    glVertex2f(-0.7838f, 0.0548f);
    glVertex2f(-0.7684f, 0.0548f);
    glVertex2f(-0.7684f, 0.0845f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7838f, 0.0845f);
    glVertex2f(-0.7838f, 0.0548f);
    glVertex2f(-0.7684f, 0.0548f);
    glVertex2f(-0.7684f, 0.0845f);
    glEnd();

    // Front Window 2 (Right) - Light Blue Glass
    glColor3f(0.5f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7585f, 0.0845f);
    glVertex2f(-0.7585f, 0.0548f);
    glVertex2f(-0.7431f, 0.0548f);
    glVertex2f(-0.7431f, 0.0845f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7585f, 0.0845f);
    glVertex2f(-0.7585f, 0.0548f);
    glVertex2f(-0.7431f, 0.0548f);
    glVertex2f(-0.7431f, 0.0845f);
    glEnd();

    // ==========================================
    // SIDE WALL ELEMENTS
    // ==========================================

    // Side Window 1 (Left side of the angled wall) - Light Blue Glass
    glColor3f(0.5f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.731f, 0.0889f);
    glVertex2f(-0.731f, 0.0592f);
    glVertex2f(-0.7233f, 0.0658f);
    glVertex2f(-0.7233f, 0.0955f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.731f, 0.0889f);
    glVertex2f(-0.731f, 0.0592f);
    glVertex2f(-0.7233f, 0.0658f);
    glVertex2f(-0.7233f, 0.0955f);
    glEnd();

    // Side Door (Centered on the angled wall) - Dark Wood
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-0.720f, 0.0955f);
    glVertex2f(-0.720f, 0.0405f);
    glVertex2f(-0.709f, 0.0493f);
    glVertex2f(-0.709f, 0.1038f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.720f, 0.0955f);
    glVertex2f(-0.720f, 0.0405f);
    glVertex2f(-0.709f, 0.0493f);
    glVertex2f(-0.709f, 0.1038f);
    glEnd();

    // Side Window 2 (Right side of the angled wall) - Light Blue Glass
    glColor3f(0.5f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7057f, 0.1065f);
    glVertex2f(-0.7057f, 0.0768f);
    glVertex2f(-0.6969f, 0.0856f);
    glVertex2f(-0.6969f, 0.1142f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7057f, 0.1065f);
    glVertex2f(-0.7057f, 0.0768f);
    glVertex2f(-0.6969f, 0.0856f);
    glVertex2f(-0.6969f, 0.1142f);
    glEnd();
}

void ornob_house3()
{
    glLineWidth(.1f); // Set outline thickness

    // ==========================================
    // WALLS
    // ==========================================

    // body1 (Front Wall) - Pale Coastal Blue
    glColor3f(0.60f, 0.75f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-0.935f, 0.113f);
    glVertex2f(-0.935f, 0.025f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.880f, 0.113f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.935f, 0.113f);
    glVertex2f(-0.935f, 0.025f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.880f, 0.113f);
    glEnd();

    // body2 (Side Wall) - Slightly darker blue for shadow/depth
    glColor3f(0.50f, 0.65f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.880f, 0.113f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.836f, 0.0635f);
    glVertex2f(-0.836f, 0.146f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.880f, 0.113f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.836f, 0.0635f);
    glVertex2f(-0.836f, 0.146f);
    glEnd();

    // ==========================================
    // ROOF
    // ==========================================

    // roof1 (Side Roof) - Dark Slate Grey
    glColor3f(0.25f, 0.30f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8635f, 0.201f);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.8745f, 0.113f);
    glVertex2f(-0.825f, 0.146f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8635f, 0.201f);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.8745f, 0.113f);
    glVertex2f(-0.825f, 0.146f);
    glEnd();

    // roof2 (Front Roof Triangle) - Deeper Slate Grey
    glColor3f(0.20f, 0.25f, 0.30f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.946f, 0.113f);
    glVertex2f(-0.8745f, 0.113f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.946f, 0.113f);
    glVertex2f(-0.8745f, 0.113f);
    glEnd();

    // ==========================================
    // FRONT WALL ELEMENTS
    // ==========================================

    // Front Window 1 (Left) - Warm glowing yellow
    glColor3f(0.95f, 0.90f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(-0.9273f, 0.0855f);
    glVertex2f(-0.9273f, 0.0558f);
    glVertex2f(-0.9119f, 0.0558f);
    glVertex2f(-0.9119f, 0.0855f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.9273f, 0.0855f);
    glVertex2f(-0.9273f, 0.0558f);
    glVertex2f(-0.9119f, 0.0558f);
    glVertex2f(-0.9119f, 0.0855f);
    glEnd();

    // Front Window 2 (Right) - Warm glowing yellow
    glColor3f(0.95f, 0.90f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(-0.902f, 0.0855f);
    glVertex2f(-0.902f, 0.0558f);
    glVertex2f(-0.8866f, 0.0558f);
    glVertex2f(-0.8866f, 0.0855f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.902f, 0.0855f);
    glVertex2f(-0.902f, 0.0558f);
    glVertex2f(-0.8866f, 0.0558f);
    glVertex2f(-0.8866f, 0.0855f);
    glEnd();

    // ==========================================
    // SIDE WALL ELEMENTS
    // ==========================================

    // Side Window 1 (Left side of the angled wall) - Warm glowing yellow
    glColor3f(0.95f, 0.90f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8745f, 0.0899f);
    glVertex2f(-0.8745f, 0.0602f);
    glVertex2f(-0.8668f, 0.0668f);
    glVertex2f(-0.8668f, 0.0965f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8745f, 0.0899f);
    glVertex2f(-0.8745f, 0.0602f);
    glVertex2f(-0.8668f, 0.0668f);
    glVertex2f(-0.8668f, 0.0965f);
    glEnd();

    // Side Door (Centered) - Crisp White
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8635f, 0.0965f);
    glVertex2f(-0.8635f, 0.0415f);
    glVertex2f(-0.8525f, 0.0503f);
    glVertex2f(-0.8525f, 0.1048f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8635f, 0.0965f);
    glVertex2f(-0.8635f, 0.0415f);
    glVertex2f(-0.8525f, 0.0503f);
    glVertex2f(-0.8525f, 0.1048f);
    glEnd();

    // Side Window 2 (Right side) - Warm glowing yellow
    glColor3f(0.95f, 0.90f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8492f, 0.1075f);
    glVertex2f(-0.8492f, 0.0778f);
    glVertex2f(-0.8404f, 0.0866f);
    glVertex2f(-0.8404f, 0.1152f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8492f, 0.1075f);
    glVertex2f(-0.8492f, 0.0778f);
    glVertex2f(-0.8404f, 0.0866f);
    glVertex2f(-0.8404f, 0.1152f);
    glEnd();
}

void ornob_house4()
{
    glLineWidth(.1f); // Set outline thickness once at the top

    // ==========================================
    // WALLS
    // ==========================================

    // body1 (Front Wall) - Soft Sage Green
    glColor3f(0.55f, 0.68f, 0.55f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7235f, 0.248f);
    glVertex2f(-0.7235f, 0.176f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6785f, 0.248f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7235f, 0.248f);
    glVertex2f(-0.7235f, 0.176f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6785f, 0.248f);
    glEnd();

    // body2 (Side Wall) - Deeper Forest/Shadow Green
    glColor3f(0.45f, 0.58f, 0.45f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6785f, 0.248f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6425f, 0.2075f);
    glVertex2f(-0.6425f, 0.275f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6785f, 0.248f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6425f, 0.2075f);
    glVertex2f(-0.6425f, 0.275f);
    glEnd();

    // ==========================================
    // ROOF
    // ==========================================

    // roof1 (Side Roof) - Charcoal Grey
    glColor3f(0.35f, 0.35f, 0.38f);
    glBegin(GL_QUADS);
    glVertex2f(-0.665f, 0.320f);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.674f, 0.248f);
    glVertex2f(-0.6335f, 0.275f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.665f, 0.320f);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.674f, 0.248f);
    glVertex2f(-0.6335f, 0.275f);
    glEnd();

    // roof2 (Front Roof Triangle) - Darker Charcoal
    glColor3f(0.28f, 0.28f, 0.30f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.7325f, 0.248f);
    glVertex2f(-0.674f, 0.248f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.7325f, 0.248f);
    glVertex2f(-0.674f, 0.248f);
    glEnd();

    // ==========================================
    // FRONT WALL ELEMENTS
    // ==========================================

    // Front Window 1 (Left) - Warm Amber Glow
    glColor3f(0.95f, 0.80f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7172f, 0.2255f);
    glVertex2f(-0.7172f, 0.2012f);
    glVertex2f(-0.7046f, 0.2012f);
    glVertex2f(-0.7046f, 0.2255f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7172f, 0.2255f);
    glVertex2f(-0.7172f, 0.2012f);
    glVertex2f(-0.7046f, 0.2012f);
    glVertex2f(-0.7046f, 0.2255f);
    glEnd();

    // Front Window 2 (Right) - Warm Amber Glow
    glColor3f(0.95f, 0.80f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6965f, 0.2255f);
    glVertex2f(-0.6965f, 0.2012f);
    glVertex2f(-0.6839f, 0.2012f);
    glVertex2f(-0.6839f, 0.2255f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6965f, 0.2255f);
    glVertex2f(-0.6965f, 0.2012f);
    glVertex2f(-0.6839f, 0.2012f);
    glVertex2f(-0.6839f, 0.2255f);
    glEnd();

    // ==========================================
    // SIDE WALL ELEMENTS
    // ==========================================

    // Side Window 1 (Left side of the angled wall) - Warm Amber Glow
    glColor3f(0.95f, 0.80f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.674f, 0.2291f);
    glVertex2f(-0.674f, 0.2048f);
    glVertex2f(-0.6677f, 0.2102f);
    glVertex2f(-0.6677f, 0.2345f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.674f, 0.2291f);
    glVertex2f(-0.674f, 0.2048f);
    glVertex2f(-0.6677f, 0.2102f);
    glVertex2f(-0.6677f, 0.2345f);
    glEnd();

    // Side Door (Centered on the angled wall) - Crisp White
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-0.665f, 0.2345f);
    glVertex2f(-0.665f, 0.1895f);
    glVertex2f(-0.656f, 0.1967f);
    glVertex2f(-0.656f, 0.24125f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.665f, 0.2345f);
    glVertex2f(-0.665f, 0.1895f);
    glVertex2f(-0.656f, 0.1967f);
    glVertex2f(-0.656f, 0.24125f);
    glEnd();

    // Side Window 2 (Right side of the angled wall) - Warm Amber Glow
    glColor3f(0.95f, 0.80f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6533f, 0.2435f);
    glVertex2f(-0.6533f, 0.2192f);
    glVertex2f(-0.6461f, 0.2264f);
    glVertex2f(-0.6461f, 0.2498f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6533f, 0.2435f);
    glVertex2f(-0.6533f, 0.2192f);
    glVertex2f(-0.6461f, 0.2264f);
    glVertex2f(-0.6461f, 0.2498f);
    glEnd();
}

void ornob_mosque()
{
    glLineWidth(.5f); // Set outline thickness once at the top

    // ==========================================
    // WALLS
    // ==========================================

    // body1 (Main Hall Front Wall)
    glColor3f(0.95f, 0.93f, 0.88f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8912f, 0.222f);
    glVertex2f(-0.8087f, 0.222f);
    glVertex2f(-0.8087f, 0.310f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8912f, 0.222f);
    glVertex2f(-0.8087f, 0.222f);
    glVertex2f(-0.8087f, 0.310f);
    glEnd();

    // body2 (Main Hall Side Wall)
    glColor3f(0.85f, 0.82f, 0.77f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8087f, 0.222f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8087f, 0.222f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();

    // Minaret Shaft (Tall tower on the side)
    glColor3f(0.90f, 0.87f, 0.82f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7537f, 0.4805f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7331f, 0.2646f);
    glVertex2f(-0.7331f, 0.4888f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7537f, 0.4805f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7331f, 0.2646f);
    glVertex2f(-0.7331f, 0.4888f);
    glEnd();

    // ==========================================
    // ROOFS & DOMES
    // ==========================================

    // roof1 (Flat side roof connecting to minaret)
    glColor3f(0.75f, 0.72f, 0.67f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8362f, 0.3416f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8362f, 0.3416f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();

    // roof2 (Reshaped into the Main Golden Dome)
    glColor3f(1.0f, 0.84f, 0.0f); // Gold
    glBegin(GL_POLYGON);
    glVertex2f(-0.8912f, 0.310f);   // Left base
    glVertex2f(-0.9118f, 0.3361f);  // Left bulge
    glVertex2f(-0.8843f, 0.3705f);  // Curve up left
    glVertex2f(-0.8500f, 0.398f);   // Peak
    glVertex2f(-0.8156f, 0.3705f);  // Curve up right
    glVertex2f(-0.7881f, 0.3361f);  // Right bulge
    glVertex2f(-0.8087f, 0.310f);   // Right base
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.9118f, 0.3361f);
    glVertex2f(-0.8843f, 0.3705f);
    glVertex2f(-0.8500f, 0.398f);
    glVertex2f(-0.8156f, 0.3705f);
    glVertex2f(-0.7881f, 0.3361f);
    glVertex2f(-0.8087f, 0.310f);
    glEnd();

    // Minaret Dome (Golden Spire)
    glColor3f(1.0f, 0.84f, 0.0f); // Gold
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7606f, 0.4668f); // Base Left
    glVertex2f(-0.7427f, 0.5218f); // Peak
    glVertex2f(-0.7262f, 0.4668f); // Base Right
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7606f, 0.4668f);
    glVertex2f(-0.7427f, 0.5218f);
    glVertex2f(-0.7262f, 0.4668f);
    glEnd();

    // ==========================================
    // FRONT WALL ELEMENTS
    // ==========================================

    // Front Grand Entrance 1 (Left) - Emerald Green
    glColor3f(0.0f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8775f, 0.2811f);
    glVertex2f(-0.8775f, 0.222f); // Touches ground
    glVertex2f(-0.8568f, 0.222f);
    glVertex2f(-0.8568f, 0.2811f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8775f, 0.2811f);
    glVertex2f(-0.8775f, 0.222f);
    glVertex2f(-0.8568f, 0.222f);
    glVertex2f(-0.8568f, 0.2811f);
    glEnd();

    // Front Grand Entrance 2 (Right) - Emerald Green
    glColor3f(0.0f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8431f, 0.2811f);
    glVertex2f(-0.8431f, 0.222f);
    glVertex2f(-0.8225f, 0.222f);
    glVertex2f(-0.8225f, 0.2811f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8431f, 0.2811f);
    glVertex2f(-0.8431f, 0.222f);
    glVertex2f(-0.8225f, 0.222f);
    glVertex2f(-0.8225f, 0.2811f);
    glEnd();

    // ==========================================
    // SIDE WALL ELEMENTS
    // ==========================================

    // Side Door (Preserving perspective)
    glColor3f(0.3f, 0.15f, 0.05f); // Dark Wood
    glBegin(GL_QUADS);
    glVertex2f(-0.7881f, 0.2811f);
    glVertex2f(-0.7881f, 0.233f);
    glVertex2f(-0.7675f, 0.2454f);
    glVertex2f(-0.7675f, 0.2935f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7881f, 0.2811f);
    glVertex2f(-0.7881f, 0.233f);
    glVertex2f(-0.7675f, 0.2454f);
    glVertex2f(-0.7675f, 0.2935f);
    glEnd();
}

void ornob_cropSet1()
{
    glLineWidth(.5f);

    // Crop Row 1 - Golden Wheat
    glColor3f(0.85f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-0.43f, 0.43f);
    glVertex2f(-0.47f, 0.39f);
    glVertex2f(-0.33f, 0.39f);
    glVertex2f(-0.29f, 0.43f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.43f, 0.43f);
    glVertex2f(-0.47f, 0.39f);
    glVertex2f(-0.33f, 0.39f);
    glVertex2f(-0.29f, 0.43f);
    glEnd();

    // Crop Row 2 - Golden Wheat
    glColor3f(0.85f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-0.478f, 0.38f);
    glVertex2f(-0.518f, 0.34f);
    glVertex2f(-0.378f, 0.34f);
    glVertex2f(-0.338f, 0.38f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.478f, 0.38f);
    glVertex2f(-0.518f, 0.34f);
    glVertex2f(-0.378f, 0.34f);
    glVertex2f(-0.338f, 0.38f);
    glEnd();

    // Crop Row 3 - Golden Wheat
    glColor3f(0.85f, 0.75f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-0.526f, 0.33f);
    glVertex2f(-0.566f, 0.29f);
    glVertex2f(-0.426f, 0.29f);
    glVertex2f(-0.386f, 0.33f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.526f, 0.33f);
    glVertex2f(-0.566f, 0.29f);
    glVertex2f(-0.426f, 0.29f);
    glVertex2f(-0.386f, 0.33f);
    glEnd();
}

void ornob_cropSet2()
{
    glLineWidth(.5f);

    // Crop Row 1 - Bright Paddy Green
    glColor3f(0.45f, 0.75f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, 0.43f);
    glVertex2f(-0.66f, 0.37f);
    glVertex2f(-0.5f, 0.37f);
    glVertex2f(-0.44f, 0.43f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6f, 0.43f);
    glVertex2f(-0.66f, 0.37f);
    glVertex2f(-0.5f, 0.37f);
    glVertex2f(-0.44f, 0.43f);
    glEnd();

    // Crop Row 2 - Bright Paddy Green
    glColor3f(0.45f, 0.75f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(-0.67f, 0.36f);
    glVertex2f(-0.73f, 0.3f);
    glVertex2f(-0.58f, 0.3f);
    glVertex2f(-0.51f, 0.36f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.67f, 0.36f);
    glVertex2f(-0.73f, 0.3f);
    glVertex2f(-0.58f, 0.3f);
    glVertex2f(-0.51f, 0.36f);
    glEnd();
}

void ornob_cropSet3()
{
    glLineWidth(.5f);

    // Crop Row 1 - Deep Forest/Veggie Green
    glColor3f(0.25f, 0.55f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-0.81f, 0.43f);
    glVertex2f(-0.94f, 0.3f);
    glVertex2f(-0.75f, 0.3f);
    glVertex2f(-0.62f, 0.43f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.81f, 0.43f);
    glVertex2f(-0.94f, 0.3f);
    glVertex2f(-0.75f, 0.3f);
    glVertex2f(-0.62f, 0.43f);
    glEnd();

    // Crop Row 2 - Deep Forest/Veggie Green
    // *Note: Fixed the bottom-left coordinate from 0.29 to 0.3 to prevent a crooked edge
    glColor3f(0.25f, 0.55f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.1f, 0.43f);
    glVertex2f(-1.5f, 0.3f);   // FIXED ALIGNMENT HERE
    glVertex2f(-0.955f, 0.3f);
    glVertex2f(-0.83f, 0.43f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.1f, 0.43f);
    glVertex2f(-1.5f, 0.3f);   // FIXED ALIGNMENT HERE
    glVertex2f(-0.955f, 0.3f);
    glVertex2f(-0.83f, 0.43f);
    glEnd();
}


void ornob_PineTree()
{
    glLineWidth(1.0f);

    // 1. TRUNK
    glColor3f(0.4f, 0.2f, 0.1f); // Fill
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.05f, 0.2f);
    glVertex2f(-0.05f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.05f, 0.2f);
    glVertex2f(-0.05f, 0.2f);
    glEnd();

    // 2. BOTTOM LEAVES
    glColor3f(0.1f, 0.5f, 0.2f); // Fill
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25f, 0.2f);
    glVertex2f(0.25f, 0.2f);
    glVertex2f(0.0f, 0.55f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.25f, 0.2f);
    glVertex2f(0.25f, 0.2f);
    glVertex2f(0.0f, 0.55f);
    glEnd();

    // 3. MIDDLE LEAVES (Covers top of Bottom Leaves)
    glColor3f(0.15f, 0.6f, 0.25f); // Fill
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.0f, 0.75f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.0f, 0.75f);
    glEnd();

    // 4. TOP LEAVES
    glColor3f(0.2f, 0.7f, 0.3f); // Fill
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.0f, 0.9f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.0f, 0.9f);
    glEnd();
}



void riverSide()
{
    //
    //land
    //
    glColor3f(0.60f, 0.90f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-.25,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-.4);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black outline
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.25, .45);
    glVertex2f(-1.0, .45);
    glVertex2f(-1.0, -.4);
    glEnd();

    ornob_cropSet3();
    ornob_mosque();
    ornob_house1();
    ornob_house3();
    ornob_cropSet1();
    ornob_cropSet2();
    ornob_house4();
    ornob_house2();

    //tree2
    glPushMatrix();
    glTranslatef(-0.95f, -0.2f, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    ornob_PineTree();
    glPopMatrix();

    //tree3
    glPushMatrix();
    glTranslatef(-0.89f, -0.25f, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    ornob_PineTree();
    glPopMatrix();

    //tree1
    glPushMatrix();
    glTranslatef(-0.98f, -0.35f, 0.0f);
    glScalef(0.3f, 0.3f, 1.0f);
    ornob_PineTree();
    glPopMatrix();
}

void roadSide()
{
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



void ornob_shipTimer(int value) {
    if (ornob_isMoving) {
        // 1. Move Diagonally
        // We move Y slightly faster than X because the Y distance is greater
        ornob_shipX += 0.002f;
        ornob_shipY += 0.00316f;

        // 2. Rotate slightly
        ornob_shipAngle += 0.05f;

        // 3. Scale down (getting smaller as it moves away)
        if (ornob_shipScale > 0.4f) { // Don't let it disappear completely
            ornob_shipScale -= 0.0015f;
        }

        // 4. Reset Logic
        // If it reaches the target area (-0.1, 0.45), reset to start
        if (ornob_shipX >= 0.6f) {
            ornob_shipX = 0.0f;
            ornob_shipY = 0.0f;
            ornob_shipScale = 1.0f;
            ornob_shipAngle = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, ornob_shipTimer, 0);
}



void ornob_keyboardInput(unsigned char key, int x, int y) {
    if (key == '9') {
        ornob_isMoving = true;
    }
    else if (key == '0') {
        ornob_isMoving = false;
    }
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
void Airplane()
{

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

void Airplane2()
{
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


void road()
{
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





void keyboardS(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'a':
        tFlag = 1;
        break;
    case 's':
        tFlag = 0;
        break;


    }
    glutPostRedisplay();
}

void updateS(int value)
{

    if(tFlag == 1)
    {

        //car1
        tx1 -= 0.0002f;
        ty1 += 0.01f;
        scale1 = 0.70f - (ty1 * 0.57f);

        if(ty1 >= 0.70f)
        {
            tx1 = 0.0f;
            ty1 = -1.0f;
        }

        //car2
        tx2 = 0.004f;
        ty2 += 0.01f;
        scale2 = 0.33f - (ty2 * 0.5f);

        if(ty2 >= 0.14f)
        {
            tx2 = 0.0f;
            ty2 = -1.4f;
        }

        //car3
        ty3 += 0.01f;
        tx3 = 0.0f - (ty3 * 0.25f);
        //ty3 += 0.01f;
        scale3 = 0.50f - (ty3 * 0.57f);

        if(ty3 >= 0.40f)
        {
            //tx3 = 0.5f;
            ty3 = -1.0f;
        }





    }


    if(rFlag == 1)
    {
        angle += speed;
    }


    if(scale1 < 0.25f)
        scale1 = 0.25f;
    if(scale1 > 0.75f)
        scale1 = 0.75f;
    if(scale2 < 0.25f)
        scale2 = 0.25f;
    if(scale2 > 0.50f)
        scale2 = 0.50f;
    if(scale3 < 0.25f)
        scale3 = 0.25f;
    if(scale3 > 0.70f)
        scale3 = 0.70f;

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
void drawFlag()
{
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
    for(int i = 0; i <= triangleAmount; i++)
    {
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
void drawTwinTowers()
{
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
    for(float h = 0.30f; h < 0.75f; h += 0.12f)
    {
        // Left Tower Windows
        glVertex2f(0.86f, h);
        glVertex2f(0.90f, h);
        glVertex2f(0.90f, h + 0.08f);
        glVertex2f(0.86f, h + 0.08f);

        // Right Tower Windows
        glVertex2f(0.94f, h);
        glVertex2f(0.98f, h);
        glVertex2f(0.98f, h + 0.08f);
        glVertex2f(0.94f, h + 0.08f);
    }
    glEnd();

    // 3. Antennas (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.88f, 0.81f);
    glVertex2f(0.88f, 0.91f);
    glVertex2f(0.96f, 0.81f);
    glVertex2f(0.96f, 0.91f);
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
   // ship();
    roadSide();


    glPushMatrix();
glTranslatef(ornob_shipX, ornob_shipY, 0.0f);

        glRotatef(ornob_shipAngle, 0.0f, 0.0f, 1.0f);
        glScalef(ornob_shipScale, ornob_shipScale, 1.0f);
        ship();
    glPopMatrix();


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

    glutKeyboardFunc(ornob_keyboardInput);
    glutTimerFunc(16, ornob_shipTimer, 0);

    glClearColor(0.5f,0.8f,0.5f,1.0f);
    glutMainLoop();



    return 0;
}
