#include<windows.h>
#include <GL/glut.h>
#define PI 3.141516
#include<math.h>

// ========== GLOBAL VARIABLES ==========
// Airplane
GLfloat txf = 0.0f;
GLfloat scalef = 1.0f;
int tFlagf = 0;

// Cars
GLfloat tx1 = 0, ty1 = 0;
GLfloat tx2 = 0, ty2 = 0;
GLfloat tx3 = 0, ty3 = 0;
GLfloat scale1 = 1, scale2 = 1, scale3 = 1;
GLfloat angle = 0;
GLfloat scale = 1;
GLfloat zoom = 1;
int tFlag = 0;
int rFlag = 0;
GLfloat speed = 1.0f;

// Ornob (ship)
float shipProgress = 0.0f;
float shipSpeed = 0.0015f;
bool isMoving = true;


// ========== DAY/NIGHT TRANSITION ==========
float dayFactor = 0.0f;
float nightFactor = 0.0f;      // 0 = full day, 1 = full night
float targetNight = 0.0f;
int transitioning = 0;
const float TRANSITION_SPEED = 0.008f;  // smooth 2‑second transition

// Helper: interpolate colors
void interpolateColor(float factor, float r1, float g1, float b1, float r2, float g2, float b2)
{
    float r = r1 * (1.0f - factor) + r2 * factor;
    float g = g1 * (1.0f - factor) + g2 * factor;
    float b = b1 * (1.0f - factor) + b2 * factor;
    glColor3f(r, g, b);
}

// Window colour: day = pale blue, night = bright yellow
void setWindowColor(float factor)
{
    interpolateColor(factor, 0.65f, 0.85f, 0.95f, 1.0f, 0.85f, 0.20f);
}

// Water colour: day = light blue, night = dark blue
void setWaterColor(float factor)
{
    interpolateColor(factor, 0.60f, 0.85f, 0.95f, 0.10f, 0.20f, 0.40f);
}

// Land / grass colour: day = bright green, night = dark green
void setLandColor(float factor)
{
    interpolateColor(factor, 0.60f, 0.90f, 0.55f, 0.20f, 0.40f, 0.15f);
}

// ========== EXISTING FUNCTIONS (unchanged except color adjustments) ==========
void Circle(GLfloat x, GLfloat y, GLfloat radius, int triangleAmount)
{
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),
                   y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

void drawCircle(GLfloat p1, GLfloat q1, GLfloat r1)
{
    int i, triangleAmount = 40;
    GLfloat twicePi = 2.0f * 3.1416f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(p1, q1);
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(p1 + (r1 * cos(i * twicePi / triangleAmount)),
                   q1 + (r1 * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

// ---------- Trees and bushes (unchanged) ----------
void treeType1(float x, float y, float s)
{
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.015f*s, y);
    glVertex2f(x + 0.015f*s, y);
    glVertex2f(x + 0.015f*s, y + 0.12f*s);
    glVertex2f(x - 0.015f*s, y + 0.12f*s);
    glEnd();
    glColor3f(0.1f, 0.6f, 0.05f);
    Circle(x - 0.04f*s, y + 0.12f*s, 0.05f*s, 100);
    Circle(x, y + 0.16f*s, 0.06f*s, 100);
    Circle(x + 0.04f*s, y + 0.12f*s, 0.05f*s, 100);
}
void treeType2(float x, float y, float s)
{
    glColor3f(0.40f, 0.22f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f*s, y);
    glVertex2f(x + 0.02f*s, y);
    glVertex2f(x + 0.02f*s, y + 0.14f*s);
    glVertex2f(x - 0.02f*s, y + 0.14f*s);
    glEnd();
    glColor3f(0.10f, 0.45f, 0.10f);
    Circle(x - 0.06f*s, y + 0.15f*s, 0.06f*s, 100);
    Circle(x - 0.02f*s, y + 0.18f*s, 0.07f*s, 100);
    Circle(x + 0.04f*s, y + 0.15f*s, 0.06f*s, 100);
    glColor3f(0.25f, 0.70f, 0.25f);
    Circle(x, y + 0.22f*s, 0.05f*s, 100);
}
void treeType3(float x, float y, float s)
{
    glColor3f(0.35f, 0.20f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.01f*s, y);
    glVertex2f(x + 0.01f*s, y);
    glVertex2f(x + 0.01f*s, y + 0.18f*s);
    glVertex2f(x - 0.01f*s, y + 0.18f*s);
    glEnd();
    glColor3f(0.20f, 0.70f, 0.20f);
    Circle(x, y + 0.18f*s, 0.04f*s, 100);
    Circle(x, y + 0.23f*s, 0.045f*s, 100);
    Circle(x, y + 0.28f*s, 0.04f*s, 100);
}
void bushType1(float x, float y, float s)
{
    glColor3f(0.12f, 0.50f, 0.12f);
    Circle(x - 0.04f*s, y, 0.05f*s, 100);
    Circle(x, y + 0.02f*s, 0.06f*s, 100);
    Circle(x + 0.04f*s, y, 0.05f*s, 100);
    glColor3f(0.20f, 0.65f, 0.20f);
    Circle(x, y + 0.05f*s, 0.045f*s, 100);
}
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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//ORNOB
// ---------- Water (dynamic colour) ----------
void water()
{
    setWaterColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-.1,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-1.0);
    glVertex2f(-.50,-1.0);
    glEnd();
}

// ---------- Ship (windows become yellow at night) ----------
void ship()
{
    glLineWidth(1.0f);
    //lower body- hull
    //1--background
    glColor3f(0.1f, 0.2f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();

    //upper body
    //1--main cabin front
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-.88, -.35);
    glVertex2f(-.75, -.35);
    glVertex2f(-.75, -.2);
    glVertex2f(-.88, -.2);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.88, -.35);
    glVertex2f(-.75, -.35);
    glVertex2f(-.75, -.2);
    glVertex2f(-.88, -.2);
    glEnd();

    //2--roof
    glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-.88, -.2);
    glVertex2f(-.75, -.2);
    glVertex2f(-.71, -.19);
    glVertex2f(-.83, -.19);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.88, -.2);
    glVertex2f(-.75, -.2);
    glVertex2f(-.71, -.19);
    glVertex2f(-.83, -.19);
    glEnd();

    //3--cabin side wall
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-.71, -.19);
    glVertex2f(-.75, -.2);
    glVertex2f(-.75, -.4);
    glVertex2f(-.71, -.4);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.71, -.19);
    glVertex2f(-.75, -.2);
    glVertex2f(-.75, -.4);
    glVertex2f(-.71, -.4);
    glEnd();

    //lower body
    //2--left side
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.90f, -0.35f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.35f);
    glEnd();
    //3--right side
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.37f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.48f, -0.30f);
    glEnd();
    //4--middle side
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, -0.35f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.37f);
    glEnd();
    //5--upper left side
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.875f, -0.43f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.43f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.875f, -0.43f);
    glVertex2f(-0.85f, -0.50f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.75f, -0.43f);
    glEnd();
    //6--upper right side
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.72f, -0.425f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.49f, -0.355f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.72f, -0.425f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.50f, -0.40f);
    glVertex2f(-0.49f, -0.355f);
    glEnd();
    //7--upper middle side
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.75f, -0.43f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.425f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.75f, -0.43f);
    glVertex2f(-0.75f, -0.50f);
    glVertex2f(-0.72f, -0.49f);
    glVertex2f(-0.72f, -0.425f);
    glEnd();


    //1--Container
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-.70, -.285);
    glVertex2f(-.70, -.365);
    glVertex2f(-.6, -.335);
    glVertex2f(-.6, -.26);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.70, -.285);
    glVertex2f(-.70, -.365);
    glVertex2f(-.6, -.335);
    glVertex2f(-.6, -.26);
    glEnd();
    //2--Container
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-.60, -.26);
    glVertex2f(-.60, -.335);
    glVertex2f(-.5, -.31);
    glVertex2f(-.5, -.235);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.60, -.26);
    glVertex2f(-.60, -.335);
    glVertex2f(-.5, -.31);
    glVertex2f(-.5, -.235);
    glEnd();


    // SHIP WINDOWS – dynamic colour
    //window1
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.87f, -0.30f);
    glVertex2f(-0.84f, -0.30f);
    glVertex2f(-0.84f, -0.26f);
    glVertex2f(-0.87f, -0.26f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.87f, -0.30f);
    glVertex2f(-0.84f, -0.30f);
    glVertex2f(-0.84f, -0.26f);
    glVertex2f(-0.87f, -0.26f);
    glEnd();
    //window2
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.83f, -0.30f);
    glVertex2f(-0.80f, -0.30f);
    glVertex2f(-0.80f, -0.26f);
    glVertex2f(-0.83f, -0.26f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.83f, -0.30f);
    glVertex2f(-0.80f, -0.30f);
    glVertex2f(-0.80f, -0.26f);
    glVertex2f(-0.83f, -0.26f);
    glEnd();
    //window3
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.79f, -0.30f);
    glVertex2f(-0.76f, -0.30f);
    glVertex2f(-0.76f, -0.26f);
    glVertex2f(-0.79f, -0.26f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.79f, -0.30f);
    glVertex2f(-0.76f, -0.30f);
    glVertex2f(-0.76f, -0.26f);
    glVertex2f(-0.79f, -0.26f);
    glEnd();
}

void ornob_house1()
{
    glLineWidth(.25f);
    // body1 (Front Wall)
    glColor3f(0.80f, 0.82f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.12f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.59f, 0.2f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.64f, 0.2f);
    glVertex2f(-0.64f, 0.12f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.59f, 0.2f);
    glEnd();
    // body2 (Side Wall)
    glColor3f(0.70f, 0.72f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.59f, 0.2f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.55f, 0.155f);
    glVertex2f(-0.55f, 0.23f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.59f, 0.2f);
    glVertex2f(-0.59f, 0.12f);
    glVertex2f(-0.55f, 0.155f);
    glVertex2f(-0.55f, 0.23f);
    glEnd();
    // roof1 (Side Roof)
    glColor3f(0.20f, 0.25f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(-0.575f, 0.28f);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.585f, 0.2f);
    glVertex2f(-0.54f, 0.23f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.575f, 0.28f);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.585f, 0.2f);
    glVertex2f(-0.54f, 0.23f);
    glEnd();
    // roof2 (Front Roof Triangle)
    glColor3f(0.15f, 0.20f, 0.25f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.65f, 0.2f);
    glVertex2f(-0.585f, 0.2f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.62f, 0.26f);
    glVertex2f(-0.65f, 0.2f);
    glVertex2f(-0.585f, 0.2f);
    glEnd();

    // Windows
    // Front Window 1 (Left)
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.633f, 0.175f);
    glVertex2f(-0.633f, 0.148f);
    glVertex2f(-0.619f, 0.148f);
    glVertex2f(-0.619f, 0.175f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.633f, 0.175f);
    glVertex2f(-0.633f, 0.148f);
    glVertex2f(-0.619f, 0.148f);
    glVertex2f(-0.619f, 0.175f);
    glEnd();
    // Front Window 2 (Right)
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.61f, 0.175f);
    glVertex2f(-0.61f, 0.148f);
    glVertex2f(-0.596f, 0.148f);
    glVertex2f(-0.596f, 0.175f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.61f, 0.175f);
    glVertex2f(-0.61f, 0.148f);
    glVertex2f(-0.596f, 0.148f);
    glVertex2f(-0.596f, 0.175f);
    glEnd();
    // Side Window 1 (Left)
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.585f, 0.179f);
    glVertex2f(-0.585f, 0.152f);
    glVertex2f(-0.578f, 0.158f);
    glVertex2f(-0.578f, 0.185f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.585f, 0.179f);
    glVertex2f(-0.585f, 0.152f);
    glVertex2f(-0.578f, 0.158f);
    glVertex2f(-0.578f, 0.185f);
    glEnd();
    // Side Door
    glColor3f(0.30f, 0.15f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.575f, 0.185f);
    glVertex2f(-0.575f, 0.135f);
    glVertex2f(-0.565f, 0.143f);
    glVertex2f(-0.565f, 0.1925f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.575f, 0.185f);
    glVertex2f(-0.575f, 0.135f);
    glVertex2f(-0.565f, 0.143f);
    glVertex2f(-0.565f, 0.1925f);
    glEnd();
    // Side Window 2 (Right)
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.562f, 0.195f);
    glVertex2f(-0.562f, 0.168f);
    glVertex2f(-0.554f, 0.176f);
    glVertex2f(-0.554f, 0.202f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.562f, 0.195f);
    glVertex2f(-0.562f, 0.168f);
    glVertex2f(-0.554f, 0.176f);
    glVertex2f(-0.554f, 0.202f);
    glEnd();
}

void ornob_house2()
{
    glLineWidth(.1f);
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7915f, 0.112f);
    glVertex2f(-0.7915f, 0.024f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.7365f, 0.112f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7915f, 0.112f);
    glVertex2f(-0.7915f, 0.024f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.7365f, 0.112f);
    glEnd();
    glColor3f(0.8f, 0.7f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7365f, 0.112f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.6925f, 0.0625f);
    glVertex2f(-0.6925f, 0.145f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7365f, 0.112f);
    glVertex2f(-0.7365f, 0.024f);
    glVertex2f(-0.6925f, 0.0625f);
    glVertex2f(-0.6925f, 0.145f);
    glEnd();
    glColor3f(0.8f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.720f, 0.200f);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.731f, 0.112f);
    glVertex2f(-0.6815f, 0.145f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.720f, 0.200f);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.731f, 0.112f);
    glVertex2f(-0.6815f, 0.145f);
    glEnd();
    glColor3f(0.6f, 0.2f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.8025f, 0.112f);
    glVertex2f(-0.731f, 0.112f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7695f, 0.178f);
    glVertex2f(-0.8025f, 0.112f);
    glVertex2f(-0.731f, 0.112f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.7838f, 0.0845f);
    glVertex2f(-0.7838f, 0.0548f);
    glVertex2f(-0.7684f, 0.0548f);
    glVertex2f(-0.7684f, 0.0845f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7838f, 0.0845f);
    glVertex2f(-0.7838f, 0.0548f);
    glVertex2f(-0.7684f, 0.0548f);
    glVertex2f(-0.7684f, 0.0845f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.7585f, 0.0845f);
    glVertex2f(-0.7585f, 0.0548f);
    glVertex2f(-0.7431f, 0.0548f);
    glVertex2f(-0.7431f, 0.0845f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7585f, 0.0845f);
    glVertex2f(-0.7585f, 0.0548f);
    glVertex2f(-0.7431f, 0.0548f);
    glVertex2f(-0.7431f, 0.0845f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.731f, 0.0889f);
    glVertex2f(-0.731f, 0.0592f);
    glVertex2f(-0.7233f, 0.0658f);
    glVertex2f(-0.7233f, 0.0955f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.731f, 0.0889f);
    glVertex2f(-0.731f, 0.0592f);
    glVertex2f(-0.7233f, 0.0658f);
    glVertex2f(-0.7233f, 0.0955f);
    glEnd();

    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-0.720f, 0.0955f);
    glVertex2f(-0.720f, 0.0405f);
    glVertex2f(-0.709f, 0.0493f);
    glVertex2f(-0.709f, 0.1038f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.720f, 0.0955f);
    glVertex2f(-0.720f, 0.0405f);
    glVertex2f(-0.709f, 0.0493f);
    glVertex2f(-0.709f, 0.1038f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.7057f, 0.1065f);
    glVertex2f(-0.7057f, 0.0768f);
    glVertex2f(-0.6969f, 0.0856f);
    glVertex2f(-0.6969f, 0.1142f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7057f, 0.1065f);
    glVertex2f(-0.7057f, 0.0768f);
    glVertex2f(-0.6969f, 0.0856f);
    glVertex2f(-0.6969f, 0.1142f);
    glEnd();
}

void ornob_house3()
{
    glLineWidth(.1f);
    glColor3f(0.60f, 0.75f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-0.935f, 0.113f);
    glVertex2f(-0.935f, 0.025f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.880f, 0.113f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.935f, 0.113f);
    glVertex2f(-0.935f, 0.025f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.880f, 0.113f);
    glEnd();
    glColor3f(0.50f, 0.65f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.880f, 0.113f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.836f, 0.0635f);
    glVertex2f(-0.836f, 0.146f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.880f, 0.113f);
    glVertex2f(-0.880f, 0.025f);
    glVertex2f(-0.836f, 0.0635f);
    glVertex2f(-0.836f, 0.146f);
    glEnd();
    glColor3f(0.25f, 0.30f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8635f, 0.201f);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.8745f, 0.113f);
    glVertex2f(-0.825f, 0.146f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8635f, 0.201f);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.8745f, 0.113f);
    glVertex2f(-0.825f, 0.146f);
    glEnd();
    glColor3f(0.20f, 0.25f, 0.30f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.946f, 0.113f);
    glVertex2f(-0.8745f, 0.113f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.913f, 0.179f);
    glVertex2f(-0.946f, 0.113f);
    glVertex2f(-0.8745f, 0.113f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.9273f, 0.0855f);
    glVertex2f(-0.9273f, 0.0558f);
    glVertex2f(-0.9119f, 0.0558f);
    glVertex2f(-0.9119f, 0.0855f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.9273f, 0.0855f);
    glVertex2f(-0.9273f, 0.0558f);
    glVertex2f(-0.9119f, 0.0558f);
    glVertex2f(-0.9119f, 0.0855f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.902f, 0.0855f);
    glVertex2f(-0.902f, 0.0558f);
    glVertex2f(-0.8866f, 0.0558f);
    glVertex2f(-0.8866f, 0.0855f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.902f, 0.0855f);
    glVertex2f(-0.902f, 0.0558f);
    glVertex2f(-0.8866f, 0.0558f);
    glVertex2f(-0.8866f, 0.0855f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.8745f, 0.0899f);
    glVertex2f(-0.8745f, 0.0602f);
    glVertex2f(-0.8668f, 0.0668f);
    glVertex2f(-0.8668f, 0.0965f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8745f, 0.0899f);
    glVertex2f(-0.8745f, 0.0602f);
    glVertex2f(-0.8668f, 0.0668f);
    glVertex2f(-0.8668f, 0.0965f);
    glEnd();

    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8635f, 0.0965f);
    glVertex2f(-0.8635f, 0.0415f);
    glVertex2f(-0.8525f, 0.0503f);
    glVertex2f(-0.8525f, 0.1048f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8635f, 0.0965f);
    glVertex2f(-0.8635f, 0.0415f);
    glVertex2f(-0.8525f, 0.0503f);
    glVertex2f(-0.8525f, 0.1048f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.8492f, 0.1075f);
    glVertex2f(-0.8492f, 0.0778f);
    glVertex2f(-0.8404f, 0.0866f);
    glVertex2f(-0.8404f, 0.1152f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8492f, 0.1075f);
    glVertex2f(-0.8492f, 0.0778f);
    glVertex2f(-0.8404f, 0.0866f);
    glVertex2f(-0.8404f, 0.1152f);
    glEnd();
}

void ornob_house4()
{
    glLineWidth(.1f);
    glColor3f(0.55f, 0.68f, 0.55f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7235f, 0.248f);
    glVertex2f(-0.7235f, 0.176f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6785f, 0.248f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7235f, 0.248f);
    glVertex2f(-0.7235f, 0.176f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6785f, 0.248f);
    glEnd();
    glColor3f(0.45f, 0.58f, 0.45f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6785f, 0.248f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6425f, 0.2075f);
    glVertex2f(-0.6425f, 0.275f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6785f, 0.248f);
    glVertex2f(-0.6785f, 0.176f);
    glVertex2f(-0.6425f, 0.2075f);
    glVertex2f(-0.6425f, 0.275f);
    glEnd();
    glColor3f(0.35f, 0.35f, 0.38f);
    glBegin(GL_QUADS);
    glVertex2f(-0.665f, 0.320f);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.674f, 0.248f);
    glVertex2f(-0.6335f, 0.275f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.665f, 0.320f);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.674f, 0.248f);
    glVertex2f(-0.6335f, 0.275f);
    glEnd();
    glColor3f(0.28f, 0.28f, 0.30f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.7325f, 0.248f);
    glVertex2f(-0.674f, 0.248f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7055f, 0.302f);
    glVertex2f(-0.7325f, 0.248f);
    glVertex2f(-0.674f, 0.248f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.7172f, 0.2255f);
    glVertex2f(-0.7172f, 0.2012f);
    glVertex2f(-0.7046f, 0.2012f);
    glVertex2f(-0.7046f, 0.2255f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7172f, 0.2255f);
    glVertex2f(-0.7172f, 0.2012f);
    glVertex2f(-0.7046f, 0.2012f);
    glVertex2f(-0.7046f, 0.2255f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.6965f, 0.2255f);
    glVertex2f(-0.6965f, 0.2012f);
    glVertex2f(-0.6839f, 0.2012f);
    glVertex2f(-0.6839f, 0.2255f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6965f, 0.2255f);
    glVertex2f(-0.6965f, 0.2012f);
    glVertex2f(-0.6839f, 0.2012f);
    glVertex2f(-0.6839f, 0.2255f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.674f, 0.2291f);
    glVertex2f(-0.674f, 0.2048f);
    glVertex2f(-0.6677f, 0.2102f);
    glVertex2f(-0.6677f, 0.2345f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.674f, 0.2291f);
    glVertex2f(-0.674f, 0.2048f);
    glVertex2f(-0.6677f, 0.2102f);
    glVertex2f(-0.6677f, 0.2345f);
    glEnd();

    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-0.665f, 0.2345f);
    glVertex2f(-0.665f, 0.1895f);
    glVertex2f(-0.656f, 0.1967f);
    glVertex2f(-0.656f, 0.24125f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.665f, 0.2345f);
    glVertex2f(-0.665f, 0.1895f);
    glVertex2f(-0.656f, 0.1967f);
    glVertex2f(-0.656f, 0.24125f);
    glEnd();

    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(-0.6533f, 0.2435f);
    glVertex2f(-0.6533f, 0.2192f);
    glVertex2f(-0.6461f, 0.2264f);
    glVertex2f(-0.6461f, 0.2498f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6533f, 0.2435f);
    glVertex2f(-0.6533f, 0.2192f);
    glVertex2f(-0.6461f, 0.2264f);
    glVertex2f(-0.6461f, 0.2498f);
    glEnd();
}

void ornob_mosque()
{
    glLineWidth(.5f);
    //concreate
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-0.88, 0.28f);
    glVertex2f(-0.94f, 0.2f);
    glVertex2f(-0.8f, 0.2f);
    glVertex2f(-0.7f, 0.28f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.88f, 0.28f);
    glVertex2f(-0.94f, 0.20f);
    glVertex2f(-0.80f, 0.20f);
    glVertex2f(-0.70f, 0.28f);
    glEnd();

    //walls

    // body1 (Main Hall Front Wall)
    glColor3f(0.95f, 0.93f, 0.88f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8912f, 0.222f);
    glVertex2f(-0.8087f, 0.222f);
    glVertex2f(-0.8087f, 0.310f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
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
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8087f, 0.222f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();

    // Minaret Shaft(Tall tower)
    glColor3f(0.90f, 0.87f, 0.82f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7537f, 0.4805f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7331f, 0.2646f);
    glVertex2f(-0.7331f, 0.4888f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7537f, 0.4805f);
    glVertex2f(-0.7537f, 0.2536f);
    glVertex2f(-0.7331f, 0.2646f);
    glVertex2f(-0.7331f, 0.4888f);
    glEnd();


    //roof
    //1--flat
    glColor3f(0.75f, 0.72f, 0.67f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8362f, 0.3416f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8087f, 0.310f);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.8362f, 0.3416f);
    glVertex2f(-0.7537f, 0.3416f);
    glEnd();

    //2--main golden dome
    glColor3f(1.0f, 0.84f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.9118f, 0.3361f);
    glVertex2f(-0.8843f, 0.3705f);
    glVertex2f(-0.8500f, 0.398f);
    glVertex2f(-0.8156f, 0.3705f);
    glVertex2f(-0.7881f, 0.3361f);
    glVertex2f(-0.8087f, 0.310f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8912f, 0.310f);
    glVertex2f(-0.9118f, 0.3361f);
    glVertex2f(-0.8843f, 0.3705f);
    glVertex2f(-0.8500f, 0.398f);
    glVertex2f(-0.8156f, 0.3705f);
    glVertex2f(-0.7881f, 0.3361f);
    glVertex2f(-0.8087f, 0.310f);
    glEnd();

    //3--tall tower Dome
    glColor3f(1.0f, 0.84f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7606f, 0.4668f);
    glVertex2f(-0.7427f, 0.5218f);
    glVertex2f(-0.7262f, 0.4668f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.7606f, 0.4668f);
    glVertex2f(-0.7427f, 0.5218f);
    glVertex2f(-0.7262f, 0.4668f);
    glEnd();

    // Mosque doors
    // Front Grand Entrance 1 (Left)
    interpolateColor(nightFactor, 0.0f, 0.4f, 0.2f, 1.0f, 0.85f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8775f, 0.2811f);
    glVertex2f(-0.8775f, 0.222f);
    glVertex2f(-0.8568f, 0.222f);
    glVertex2f(-0.8568f, 0.2811f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8775f, 0.2811f);
    glVertex2f(-0.8775f, 0.222f);
    glVertex2f(-0.8568f, 0.222f);
    glVertex2f(-0.8568f, 0.2811f);
    glEnd();
    // Front Grand Entrance 2 (Right)
    interpolateColor(nightFactor, 0.0f, 0.4f, 0.2f, 1.0f, 0.85f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8431f, 0.2811f);
    glVertex2f(-0.8431f, 0.222f);
    glVertex2f(-0.8225f, 0.222f);
    glVertex2f(-0.8225f, 0.2811f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.8431f, 0.2811f);
    glVertex2f(-0.8431f, 0.222f);
    glVertex2f(-0.8225f, 0.222f);
    glVertex2f(-0.8225f, 0.2811f);
    glEnd();

    // Side Door
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7881f, 0.2811f);
    glVertex2f(-0.7881f, 0.233f);
    glVertex2f(-0.7675f, 0.2454f);
    glVertex2f(-0.7675f, 0.2935f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
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
    interpolateColor(nightFactor, 0.85f, 0.75f, 0.25f, 0.40f, 0.35f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.43f, 0.43f);
    glVertex2f(-0.47f, 0.39f);
    glVertex2f(-0.33f, 0.39f);
    glVertex2f(-0.29f, 0.43f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.43f, 0.43f);
    glVertex2f(-0.47f, 0.39f);
    glVertex2f(-0.33f, 0.39f);
    glVertex2f(-0.29f, 0.43f);
    glEnd();
    // Crop Row 2 - Golden Wheat
    interpolateColor(nightFactor, 0.85f, 0.75f, 0.25f, 0.40f, 0.35f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.478f, 0.38f);
    glVertex2f(-0.518f, 0.34f);
    glVertex2f(-0.378f, 0.34f);
    glVertex2f(-0.338f, 0.38f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.478f, 0.38f);
    glVertex2f(-0.518f, 0.34f);
    glVertex2f(-0.378f, 0.34f);
    glVertex2f(-0.338f, 0.38f);
    glEnd();
    // Crop Row 3 - Golden Wheat
    interpolateColor(nightFactor, 0.85f, 0.75f, 0.25f, 0.40f, 0.35f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.526f, 0.33f);
    glVertex2f(-0.566f, 0.29f);
    glVertex2f(-0.426f, 0.29f);
    glVertex2f(-0.386f, 0.33f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
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
    interpolateColor(nightFactor, 0.45f, 0.75f, 0.30f, 0.20f, 0.40f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.6f, 0.43f);
    glVertex2f(-0.66f, 0.37f);
    glVertex2f(-0.5f, 0.37f);
    glVertex2f(-0.44f, 0.43f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.6f, 0.43f);
    glVertex2f(-0.66f, 0.37f);
    glVertex2f(-0.5f, 0.37f);
    glVertex2f(-0.44f, 0.43f);
    glEnd();
    // Crop Row 2 - Bright Paddy Green
    interpolateColor(nightFactor, 0.45f, 0.75f, 0.30f, 0.20f, 0.40f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.67f, 0.36f);
    glVertex2f(-0.73f, 0.3f);
    glVertex2f(-0.58f, 0.3f);
    glVertex2f(-0.51f, 0.36f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
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
    // Crop Row 1
    interpolateColor(nightFactor, 0.25f, 0.55f, 0.25f, 0.10f, 0.25f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-0.81f, 0.43f);
    glVertex2f(-0.94f, 0.3f);
    glVertex2f(-0.75f, 0.3f);
    glVertex2f(-0.62f, 0.43f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.81f, 0.43f);
    glVertex2f(-0.94f, 0.3f);
    glVertex2f(-0.75f, 0.3f);
    glVertex2f(-0.62f, 0.43f);
    glEnd();
    // Crop Row 2
    interpolateColor(nightFactor, 0.25f, 0.55f, 0.25f, 0.10f, 0.25f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-1.1f, 0.43f);
    glVertex2f(-1.5f, 0.3f);
    glVertex2f(-0.955f, 0.3f);
    glVertex2f(-0.83f, 0.43f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.1f, 0.43f);
    glVertex2f(-1.5f, 0.3f);
    glVertex2f(-0.955f, 0.3f);
    glVertex2f(-0.83f, 0.43f);
    glEnd();
}
void ornob_pineTree_model()
{
    glLineWidth(1.0f);
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.05f, 0.2f);
    glVertex2f(-0.05f, 0.2f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.05f, 0.2f);
    glVertex2f(-0.05f, 0.2f);
    glEnd();
    glColor3f(0.1f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25f, 0.2f);
    glVertex2f(0.25f, 0.2f);
    glVertex2f(0.0f, 0.55f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.25f, 0.2f);
    glVertex2f(0.25f, 0.2f);
    glVertex2f(0.0f, 0.55f);
    glEnd();
    glColor3f(0.15f, 0.6f, 0.25f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.0f, 0.75f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.0f, 0.75f);
    glEnd();
    glColor3f(0.2f, 0.7f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.0f, 0.9f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.15f, 0.6f);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.0f, 0.9f);
    glEnd();
}

void ornob_trees()
{
    //tree5
    glPushMatrix();
    glTranslatef(-0.985f, -0.18f, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    ornob_pineTree_model();
    glPopMatrix();


    //tree4
    glPushMatrix();
    glTranslatef(-0.9f, -0.178f, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    ornob_pineTree_model();
    glPopMatrix();


    //tree2
    glPushMatrix();
    glTranslatef(-0.95f, -0.2f, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    ornob_pineTree_model();
    glPopMatrix();

    //tree3
    glPushMatrix();
    glTranslatef(-0.89f, -0.26f, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    ornob_pineTree_model();
    glPopMatrix();

    //tree1
    glPushMatrix();
    glTranslatef(-0.972f, -0.35f, 0.0f);
    glScalef(0.3f, 0.3f, 1.0f);
    ornob_pineTree_model();
    glPopMatrix();
}

void ornob_road()
{
    glLineWidth(.5f);

    // 1
    glColor3f(0.65f, 0.52f, 0.38f);
    glBegin(GL_QUADS);
    glVertex2f(-0.265f, 0.45f);
    glVertex2f(-0.455f, 0.255f);
    glVertex2f(-0.419f, 0.255f);
    glVertex2f(-0.245f, 0.45f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.265f, 0.45f);
    glVertex2f(-0.455f, 0.255f);
    glVertex2f(-0.419f, 0.255f);
    glVertex2f(-0.245f, 0.45f);
    glEnd();

    //2
    glColor3f(0.65f, 0.52f, 0.38f);
    glBegin(GL_QUADS);
    glVertex2f(-0.705f, 0.286f);
    glVertex2f(-0.730f, 0.255f);
    glVertex2f(-0.430f, 0.255f);
    glVertex2f(-0.400f, 0.286f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.424f, 0.286f);
    glVertex2f(-0.705f, 0.286f);
    glVertex2f(-0.730f, 0.255f);
    glVertex2f(-0.42f, 0.255f);
    glEnd();

    //3
    glColor3f(0.65f, 0.52f, 0.38f);
    glBegin(GL_QUADS);
    glVertex2f(-1.000f, 0.050f);
    glVertex2f(-1.000f, -0.020f);
    glVertex2f(-0.642f, 0.286f);
    glVertex2f(-0.692f, 0.286f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.692f, 0.286f);
    glVertex2f(-1.000f, 0.050f);
    glVertex2f(-1.000f, -0.020f);
    glVertex2f(-0.642f, 0.286f);
    glEnd();
}

void riverSide()
{
    setLandColor(nightFactor);
    //land
    glBegin(GL_TRIANGLES);
    glVertex2f(-.24,.45);
    glVertex2f(-1.0,.45);
    glVertex2f(-1.0,-.42);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-.24, .45);
    glVertex2f(-1.0, .45);
    glVertex2f(-1.0, -.42);
    glEnd();

    ornob_cropSet3();
    ornob_mosque();
    ornob_road();
    ornob_house3();
    ornob_cropSet1();
    ornob_cropSet2();
    ornob_house4();
    ornob_house2();
    ornob_house1();
    ornob_trees();

}

void roadSide()
{
    glColor3f(0.20f, 0.50f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, 0.45f);
    glVertex2f(-0.12f, 0.45f);
    glVertex2f(-0.60f, -1.0f);
    glVertex2f(-0.50f, -1.0f);
    glEnd();
}


void updateShip(int value){
if (isMoving) {
        shipProgress += shipSpeed;
        if (shipProgress > 1.0f) {
            shipProgress = 0.0f;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(8, updateShip, 0);
}


void ship_transition()
{
    float currentX = -0.7f + shipProgress * (-0.04f - (-0.7f));
    float currentY = -.9f + shipProgress * (0.5f - (-.9f));
    float currentScale = 1.6f + shipProgress * (0.2f - 1.6f);

    glPushMatrix();
    glTranslatef(currentX, currentY, 0.0f);
    glScalef(currentScale, currentScale, 1.0f);

    ship();

    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// ========== FAHIM (sky, clouds, mountains, forest, airplane) ==========
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
    Circle(-0.68f, 0.75f, 0.020f, 100);
    Circle(-0.84f, 0.78f, 0.027f, 100);
    Circle(-0.80f, 0.78f, 0.030f, 100);
    Circle(-0.76f, 0.77f, 0.030f, 100);
    Circle(-0.72f, 0.78f, 0.030f, 100);
    Circle(-0.78f, 0.81f, 0.035f, 100);
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
    interpolateColor(nightFactor, 1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.4f);
    glPushMatrix();
    drawOneCloud();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5f, 0.13f, 0.0f);
    drawCloud2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5f, 0.15f, 0.0f);
    drawOneCloud();
    glPopMatrix();
}

void drawMountain()
{
    interpolateColor(nightFactor, 0.78f, 0.50f, 0.28f, 0.30f, 0.20f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-1.0f, 0.64f);
    glVertex2f(-0.96f,0.635f);
    glVertex2f(-0.92f,0.625f);
    glVertex2f(-0.88f,0.605f);
    glVertex2f(-0.84f,0.590f);
    glVertex2f(-0.80f,0.605f);
    glVertex2f(-0.76f,0.610f);
    glVertex2f(-0.72f,0.605f);
    glVertex2f(-0.68f,0.590f);
    glVertex2f(-0.64f,0.590f);
    glVertex2f(-0.60f,0.600f);
    glVertex2f(-0.56f,0.605f);
    glVertex2f(-0.52f,0.595f);
    glVertex2f(-0.48f,0.585f);
    glVertex2f(-0.44f,0.570f);
    glVertex2f(-0.40f,0.555f);
    glVertex2f(-0.36f,0.545f);
    glVertex2f(-0.30f,0.565f);
    glVertex2f(-0.26f,0.540f);
    glVertex2f(-0.22f,0.525f);
    glVertex2f(-0.18f,0.515f);
    glVertex2f(-0.10f,0.550f);
    glVertex2f(-0.08f,0.535f);
    glVertex2f(-0.04f,0.525f);
    glVertex2f(-0.03f,0.515f);
    glVertex2f(0.0f,0.510f);
    glVertex2f(0.0f,0.45f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.0f,0.45f);
    glVertex2f(0.0f,0.510f);
    glVertex2f(0.03f,0.515f);
    glVertex2f(0.04f,0.525f);
    glVertex2f(0.08f,0.535f);
    glVertex2f(0.10f,0.550f);
    glVertex2f(0.18f,0.515f);
    glVertex2f(0.22f,0.525f);
    glVertex2f(0.26f,0.540f);
    glVertex2f(0.30f,0.565f);
    glVertex2f(0.36f,0.545f);
    glVertex2f(0.40f,0.555f);
    glVertex2f(0.44f,0.570f);
    glVertex2f(0.48f,0.585f);
    glVertex2f(0.52f,0.595f);
    glVertex2f(0.56f,0.605f);
    glVertex2f(0.60f,0.600f);
    glVertex2f(0.64f,0.590f);
    glVertex2f(0.68f,0.590f);
    glVertex2f(0.72f,0.605f);
    glVertex2f(0.76f,0.615f);
    glVertex2f(0.80f,0.605f);
    glVertex2f(0.84f,0.496f);
    glVertex2f(0.88f,0.605f);
    glVertex2f(0.92f,0.625f);
    glVertex2f(0.96f,0.635f);
    glVertex2f(1.0f,0.64f);
    glVertex2f(1.0f,0.45f);
    glEnd();
}

void drawForest()
{
    interpolateColor(nightFactor, 0.12f, 0.42f, 0.26f, 0.05f, 0.20f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-1.0f, 0.55f);
    glVertex2f(-0.99f,0.555f);
    glVertex2f(-0.98f,0.560f);
    glVertex2f(-0.97f,0.550f);
    glVertex2f(-0.96f,0.540f);
    glVertex2f(-0.95f,0.530f);
    glVertex2f(-0.94f,0.540f);
    glVertex2f(-0.92f,0.552f);
    glVertex2f(-0.90f,0.554f);
    glVertex2f(-0.88f,0.560f);
    glVertex2f(-0.86f,0.558f);
    glVertex2f(-0.84f,0.555f);
    glVertex2f(-0.82f,0.550f);
    glVertex2f(-0.80f,0.560f);
    glVertex2f(-0.78f,0.560f);
    glVertex2f(-0.76f,0.540f);
    glVertex2f(-0.74f,0.550f);
    glVertex2f(-0.72f,0.530f);
    glVertex2f(-0.70f,0.535f);
    glVertex2f(-0.68f,0.550f);
    glVertex2f(-0.66f,0.555f);
    glVertex2f(-0.64f,0.535f);
    glVertex2f(-0.62f,0.545f);
    glVertex2f(-0.60f,0.550f);
    glVertex2f(-0.58f,0.530f);
    glVertex2f(-0.52f,0.520f);
    glVertex2f(-0.50f,0.525f);
    glVertex2f(-0.48f,0.530f);
    glVertex2f(-0.46f,0.535f);
    glVertex2f(-0.40f,0.520f);
    glVertex2f(-0.34f,0.520f);
    glVertex2f(-0.30f,0.525f);
    glVertex2f(-0.28f,0.515f);
    glVertex2f(-0.20f,0.495f);
    glVertex2f(-0.17f,0.505f);
    glVertex2f(-0.14f,0.515f);
    glVertex2f(-0.12f,0.490f);
    glVertex2f(-0.09f,0.485f);
    glVertex2f(-0.06f,0.500f);
    glVertex2f(-0.04f,0.493f);
    glVertex2f(0.00f,0.480f);
    glVertex2f(0.00f,0.45f);
    glEnd();
    glBegin(GL_POLYGON);
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
    glVertex2f(1.0f,0.55f);
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
    glBegin(GL_POLYGON);
    glVertex2f(-0.64f,0.855f);
    glVertex2f(-0.59f,0.855f);
    glVertex2f(-0.54f,0.79f);
    glVertex2f(-0.61f,0.79f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.60f,0.73f);
    glVertex2f(-0.52f,0.73f);
    glVertex2f(-0.59f,0.64f);
    glVertex2f(-0.64f,0.64);
    glEnd();
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
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f,0.760f);
    glVertex2f(-0.45f,0.760f);
    glVertex2f(-0.43f,0.740f);
    glVertex2f(-0.5f,0.740f);
    glEnd();
    glColor3f(0.1f, 0.2f, 0.4f);
    Circle(-0.72f,0.75f,0.008f,100);
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
    glScalef(0.7f, 0.7f, 1.0f);
    Airplane();
    glColor3f(0.05f, 0.10f, 0.30f);
    drawText(-0.7f, 0.737f, "F&F Airlines");
    glPopMatrix();
}

void updatef(int value)
{
    if(tFlagf == 1)
    {
        txf = txf + 0.006f;
        scalef = scalef - 0.001f;
        if(txf >= 2.0f)
        {
            txf = 0.0f;
            scalef = 1.0f;
            tFlagf = 0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, updatef, 0);
}

// ========== SHOHAG (road, cars, traffic lights, etc.) ==========
void road()
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.10f, 0.45f);
    glVertex2f(-0.50f, -1.0f);
    glVertex2f(-0.41f, -1.0f);
    glVertex2f(-0.090f, 0.447f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.090f, 0.447f);
    glVertex2f(-0.41f, -1.0f);
    glVertex2f(-0.38f, -1.0f);
    glVertex2f(-0.087f, 0.447f);
    glEnd();
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.087f, 0.447f);
    glVertex2f(-0.38f, -1.0f);
    glVertex2f(-0.30f, -1.0f);
    glVertex2f(-0.080f, 0.447f);
    glEnd();
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.080f, 0.447f);
    glVertex2f(-0.30f, -1.0f);
    glVertex2f(-0.275f, -1.0f);
    glVertex2f(-0.077f, 0.447f);
    glEnd();
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.077f, 0.447f);
    glVertex2f(-0.275f, -1.0f);
    glVertex2f(0.0187, -1.0f);
    glVertex2f(-0.033f, 0.447f);
    glEnd();
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.033f, 0.447f);
    glVertex2f(0.017f, -1.0f);
    glVertex2f(0.045f, -1.0f);
    glVertex2f(0.015f, 0.425f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.447f);
    glVertex2f(0.45f, -1.0f);
    glVertex2f(0.55f, -1.0f);
    glVertex2f(0.04f, 0.45f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.030f, 0.447f);
    glVertex2f(0.026f, 0.447f);
    glVertex2f(0.42f, -1.0f);
    glVertex2f(0.45f, -1.0f);
    glEnd();
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(0.026f, 0.447f);
    glVertex2f(0.018f, 0.447f);
    glVertex2f(0.35f, -1.0f);
    glVertex2f(0.42f, -1.0f);
    glEnd();
    glColor3f(0.98f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(0.015f, 0.447f);
    glVertex2f(0.018f, 0.447f);
    glVertex2f(0.325f, -1.0f);
    glVertex2f(0.35f, -1.0f);
    glEnd();
    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.029f, 0.447f);
    glVertex2f(0.045f, -1.0f);
    glVertex2f(0.325f, -1.0f);
    glVertex2f(0.015f, 0.447f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.55f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.09f, 0.45f);
    glVertex2f(-0.09f, 0.447f);
    glVertex2f(0.02f, 0.447f);
    glVertex2f(0.03f, 0.45f);
    glEnd();

    glColor3f(0.31f, 0.31f, 0.31f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.65f);
    glVertex2f(-0.02f, -0.80);
    glVertex2f(0.04f, -0.80f);
    glVertex2f(0.04f, -0.65f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.35f);
    glVertex2f(-0.02f, -0.47);
    glVertex2f(0.02f, -0.47f);
    glVertex2f(0.02f, -0.35f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.12f);
    glVertex2f(-0.02f, -0.220);
    glVertex2f(0.02f, -0.22f);
    glVertex2f(0.02f, -0.12f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, 0.06f);
    glVertex2f(-0.02f, -0.02);
    glVertex2f(0.02f, -0.02f);
    glVertex2f(0.02f, 0.06f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f, 0.21f);
    glVertex2f(-0.03f, 0.14f);
    glVertex2f(0.01f, 0.14f);
    glVertex2f(0.01f, 0.21f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.04f, 0.325f);
    glVertex2f(-0.04f, 0.275f);
    glVertex2f(0.01f, 0.275f);
    glVertex2f(0.01f, 0.325f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.04f, 0.4f);
    glVertex2f(-0.04f, 0.365f);
    glVertex2f(0.0f, 0.365f);
    glVertex2f(0.0f, 0.4f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.06f, 0.447f);
    glVertex2f(-0.06f, 0.43f);
    glVertex2f(-0.01f, 0.43f);
    glVertex2f(-0.01f, 0.447f);
    glEnd();
}

void div()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.305f, -0.8f);
    glVertex2f(-0.33f, -0.95f);
    glVertex2f(-0.31f, -0.95f);
    glVertex2f(-0.285f, -0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.232f, -0.8f);
    glVertex2f(-0.253f, -0.95f);
    glVertex2f(-0.233f, -0.95f);
    glVertex2f(-0.212f, -0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.192f, -0.8f);
    glVertex2f(-0.211f, -0.95f);
    glVertex2f(-0.191f, -0.95f);
    glVertex2f(-0.172f, -0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.152f, -0.8f);
    glVertex2f(-0.169f, -0.95f);
    glVertex2f(-0.147f, -0.95f);
    glVertex2f(-0.132f, -0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.112f, -0.8f);
    glVertex2f(-0.126f, -0.95f);
    glVertex2f(-0.104f, -0.95f);
    glVertex2f(-0.092f, -0.8f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.072f, -0.798f);
    glVertex2f(-0.082f, -0.948f);
    glVertex2f(-0.060f, -0.948f);
    glVertex2f(-0.052f, -0.798f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.032f, -0.796f);
    glVertex2f(-0.039f, -0.946f);
    glVertex2f(-0.016f, -0.946f);
    glVertex2f(-0.012f, -0.796f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.008f, -0.794f);
    glVertex2f(0.005f, -0.944f);
    glVertex2f(0.0130f, -0.944f);
    glVertex2f(0.028f, -0.794f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.048f, -0.792f);
    glVertex2f(0.046f, -0.942f);
    glVertex2f(0.068f, -0.942f);
    glVertex2f(0.068f, -0.792f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.088f, -0.790f);
    glVertex2f(0.092f, -0.940f);
    glVertex2f(0.116f, -0.940f);
    glVertex2f(0.108f, -0.790f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.128f, -0.788f);
    glVertex2f(0.135f, -0.938f);
    glVertex2f(0.154f, -0.938f);
    glVertex2f(0.148f, -0.788f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.168f, -0.786f);
    glVertex2f(0.174f, -0.936f);
    glVertex2f(0.195f, -0.936f);
    glVertex2f(0.188f, -0.786f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.208f, -0.784f);
    glVertex2f(0.215f, -0.934f);
    glVertex2f(0.238f, -0.934f);
    glVertex2f(0.228f, -0.784f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.248f, -0.782f);
    glVertex2f(0.262f, -0.932f);
    glVertex2f(0.284f, -0.932f);
    glVertex2f(0.268f, -0.782f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.288f, -0.78f);
    glVertex2f(0.309f, -0.93f);
    glVertex2f(0.334f, -0.93f);
    glVertex2f(0.308f, -0.78f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.328f, -0.778f);
    glVertex2f(0.356f, -0.928f);
    glVertex2f(0.378f, -0.928f);
    glVertex2f(0.348f, -0.778f);
    glEnd();
}

void drawCar1(float tx1, float ty1, float scale1, float angle)
{
    glPushMatrix();
    glTranslatef(tx1, ty1, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale1, scale1, 1);
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.33f, -0.240f);
    glVertex2f(-0.335f, -0.295f);
    glVertex2f(-0.335f, -0.335f);
    glVertex2f(-0.105f, -0.335f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.11f, -0.240f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.325f, -0.246f);
    glVertex2f(-0.325f, -0.276f);
    glVertex2f(-0.285f, -0.276f);
    glVertex2f(-0.285f, -0.246f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.155f, -0.246f);
    glVertex2f(-0.155f, -0.276f);
    glVertex2f(-0.115f, -0.276f);
    glVertex2f(-0.115f, -0.246f);
    glEnd();
    glColor3f(1.0f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.335f, -0.295f);
    glVertex2f(-0.285f, -0.297f);
    glVertex2f(-0.155f, -0.297f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.155f, -0.285f);
    glVertex2f(-0.285f, -0.285f);
    glEnd();
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
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.30f, -0.21f);
    glVertex2f(-0.33f, -0.24f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.12f, -0.215f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.28f, -0.14f);
    glVertex2f(-0.30f, -0.21f);
    glVertex2f(-0.12f, -0.215f);
    glVertex2f(-0.14f, -0.15f);
    glEnd();
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.27f, -0.155f);
    glVertex2f(-0.29f, -0.205f);
    glVertex2f(-0.13f, -0.205f);
    glVertex2f(-0.15f, -0.158f);
    glEnd();
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.26f, -0.125f);
    glVertex2f(-0.28f, -0.14f);
    glVertex2f(-0.14f, -0.15f);
    glVertex2f(-0.13f, -0.130f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.13f, -0.130f);
    glVertex2f(-0.14f, -0.15f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.090f, -0.17f);
    glEnd();
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.127f, -0.140f);
    glVertex2f(-0.135f, -0.160f);
    glVertex2f(-0.104f, -0.230f);
    glVertex2f(-0.095f, -0.175f);
    glEnd();
    glColor3f(1.0f, 0.27f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.090f, -0.17f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.105f, -0.335f);
    glVertex2f(-0.09f, -0.23f);
    glVertex2f(-0.09f, -0.17f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.10f, -0.285f);
    glVertex2f(-0.11f, -0.330f);
    glVertex2f(-0.11f, -0.335f);
    glVertex2f(-0.10f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.140f, -0.335f);
    glVertex2f(-0.145f, -0.385f);
    glVertex2f(-0.140f, -0.391f);
    glVertex2f(-0.11f, -0.390f);
    glVertex2f(-0.105f, -0.375f);
    glVertex2f(-0.105f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.330f, -0.335f);
    glVertex2f(-0.330f, -0.380f);
    glVertex2f(-0.325f, -0.390f);
    glVertex2f(-0.295f, -0.390f);
    glVertex2f(-0.290f, -0.375f);
    glVertex2f(-0.290f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.295f, -0.335f);
    glVertex2f(-0.295f, -0.360f);
    glVertex2f(-0.140f, -0.360f);
    glVertex2f(-0.140f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.09f, -0.23f);
    glVertex2f(-0.105f, -0.30f);
    glVertex2f(-0.095f, -0.30f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.095f, -0.158f);
    glVertex2f(-0.095f, -0.182f);
    glVertex2f(-0.077f, -0.187f);
    glVertex2f(-0.077f, -0.165f);
    glEnd();
    glPopMatrix();
}
void drawCar2(float tx2, float ty2, float scale2, float angle)
{
    glPushMatrix();
    glTranslatef(tx2, ty2, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale2, scale2, 1);
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.33f, -0.240f);
    glVertex2f(-0.335f, -0.295f);
    glVertex2f(-0.335f, -0.335f);
    glVertex2f(-0.105f, -0.335f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.11f, -0.240f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.325f, -0.246f);
    glVertex2f(-0.325f, -0.276f);
    glVertex2f(-0.285f, -0.276f);
    glVertex2f(-0.285f, -0.246f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.155f, -0.246f);
    glVertex2f(-0.155f, -0.276f);
    glVertex2f(-0.115f, -0.276f);
    glVertex2f(-0.115f, -0.246f);
    glEnd();
    glColor3f(1.0f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.335f, -0.295f);
    glVertex2f(-0.285f, -0.297f);
    glVertex2f(-0.155f, -0.297f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.155f, -0.285f);
    glVertex2f(-0.285f, -0.285f);
    glEnd();
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
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.30f, -0.21f);
    glVertex2f(-0.33f, -0.24f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.12f, -0.215f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.28f, -0.14f);
    glVertex2f(-0.30f, -0.21f);
    glVertex2f(-0.12f, -0.215f);
    glVertex2f(-0.14f, -0.15f);
    glEnd();
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.27f, -0.155f);
    glVertex2f(-0.29f, -0.205f);
    glVertex2f(-0.13f, -0.205f);
    glVertex2f(-0.15f, -0.158f);
    glEnd();
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.26f, -0.125f);
    glVertex2f(-0.28f, -0.14f);
    glVertex2f(-0.14f, -0.15f);
    glVertex2f(-0.13f, -0.130f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.13f, -0.130f);
    glVertex2f(-0.14f, -0.15f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.090f, -0.17f);
    glEnd();
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.127f, -0.140f);
    glVertex2f(-0.135f, -0.160f);
    glVertex2f(-0.104f, -0.230f);
    glVertex2f(-0.095f, -0.175f);
    glEnd();
    glColor3f(0.1f, 0.2f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.090f, -0.17f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.105f, -0.335f);
    glVertex2f(-0.09f, -0.23f);
    glVertex2f(-0.09f, -0.17f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.10f, -0.285f);
    glVertex2f(-0.11f, -0.330f);
    glVertex2f(-0.11f, -0.335f);
    glVertex2f(-0.10f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.140f, -0.335f);
    glVertex2f(-0.145f, -0.385f);
    glVertex2f(-0.140f, -0.391f);
    glVertex2f(-0.11f, -0.390f);
    glVertex2f(-0.105f, -0.375f);
    glVertex2f(-0.105f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.330f, -0.335f);
    glVertex2f(-0.330f, -0.380f);
    glVertex2f(-0.325f, -0.390f);
    glVertex2f(-0.295f, -0.390f);
    glVertex2f(-0.290f, -0.375f);
    glVertex2f(-0.290f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.295f, -0.335f);
    glVertex2f(-0.295f, -0.360f);
    glVertex2f(-0.140f, -0.360f);
    glVertex2f(-0.140f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.09f, -0.23f);
    glVertex2f(-0.105f, -0.30f);
    glVertex2f(-0.095f, -0.30f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.095f, -0.158f);
    glVertex2f(-0.095f, -0.182f);
    glVertex2f(-0.077f, -0.187f);
    glVertex2f(-0.077f, -0.165f);
    glEnd();
    glPopMatrix();
}
void drawCar3(float tx3, float ty3, float scale3, float angle)
{
    glPushMatrix();
    glTranslatef(tx3, ty3, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale3, scale3, 1);
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.33f, -0.240f);
    glVertex2f(-0.335f, -0.295f);
    glVertex2f(-0.335f, -0.335f);
    glVertex2f(-0.105f, -0.335f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.11f, -0.240f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.325f, -0.246f);
    glVertex2f(-0.325f, -0.276f);
    glVertex2f(-0.285f, -0.276f);
    glVertex2f(-0.285f, -0.246f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.155f, -0.246f);
    glVertex2f(-0.155f, -0.276f);
    glVertex2f(-0.115f, -0.276f);
    glVertex2f(-0.115f, -0.246f);
    glEnd();
    glColor3f(1.0f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.335f, -0.295f);
    glVertex2f(-0.285f, -0.297f);
    glVertex2f(-0.155f, -0.297f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.155f, -0.285f);
    glVertex2f(-0.285f, -0.285f);
    glEnd();
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
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.30f, -0.21f);
    glVertex2f(-0.33f, -0.24f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.12f, -0.215f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.28f, -0.14f);
    glVertex2f(-0.30f, -0.21f);
    glVertex2f(-0.12f, -0.215f);
    glVertex2f(-0.14f, -0.15f);
    glEnd();
    glColor3f(0.35f, 0.45f, 0.55f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.27f, -0.155f);
    glVertex2f(-0.29f, -0.205f);
    glVertex2f(-0.13f, -0.205f);
    glVertex2f(-0.15f, -0.158f);
    glEnd();
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.26f, -0.125f);
    glVertex2f(-0.28f, -0.14f);
    glVertex2f(-0.14f, -0.15f);
    glVertex2f(-0.13f, -0.130f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.13f, -0.130f);
    glVertex2f(-0.14f, -0.15f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.090f, -0.17f);
    glEnd();
    glColor3f(0.35f, 0.45f, 0.55f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.127f, -0.140f);
    glVertex2f(-0.135f, -0.160f);
    glVertex2f(-0.104f, -0.230f);
    glVertex2f(-0.095f, -0.175f);
    glEnd();
    glColor3f(1.0f, 0.85f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.090f, -0.17f);
    glVertex2f(-0.11f, -0.24f);
    glVertex2f(-0.105f, -0.295f);
    glVertex2f(-0.105f, -0.335f);
    glVertex2f(-0.09f, -0.23f);
    glVertex2f(-0.09f, -0.17f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.10f, -0.285f);
    glVertex2f(-0.11f, -0.330f);
    glVertex2f(-0.11f, -0.335f);
    glVertex2f(-0.10f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.140f, -0.335f);
    glVertex2f(-0.145f, -0.385f);
    glVertex2f(-0.140f, -0.391f);
    glVertex2f(-0.11f, -0.390f);
    glVertex2f(-0.105f, -0.375f);
    glVertex2f(-0.105f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.330f, -0.335f);
    glVertex2f(-0.330f, -0.380f);
    glVertex2f(-0.325f, -0.390f);
    glVertex2f(-0.295f, -0.390f);
    glVertex2f(-0.290f, -0.375f);
    glVertex2f(-0.290f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.295f, -0.335f);
    glVertex2f(-0.295f, -0.360f);
    glVertex2f(-0.140f, -0.360f);
    glVertex2f(-0.140f, -0.335f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.09f, -0.23f);
    glVertex2f(-0.105f, -0.30f);
    glVertex2f(-0.095f, -0.30f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.095f, -0.158f);
    glVertex2f(-0.095f, -0.182f);
    glVertex2f(-0.077f, -0.187f);
    glVertex2f(-0.077f, -0.165f);
    glEnd();
    glPopMatrix();
}

void trafficLight()
{
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.40f, -0.1f);
    glVertex2f(-0.40f, -0.8f);
    glVertex2f(-0.38f, -0.8f);
    glVertex2f(-0.38f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.403f, -0.1f);
    glVertex2f(-0.403f, -0.2f);
    glVertex2f(-0.377f, -0.2f);
    glVertex2f(-0.377f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.377f, -0.13f);
    glVertex2f(-0.377f, -0.18f);
    glVertex2f(-0.36f, -0.18f);
    glVertex2f(-0.36f, -0.13f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.36f, -0.144f);
    glVertex2f(-0.36f, -0.159f);
    glVertex2f(-0.23f, -0.159f);
    glVertex2f(-0.23f, -0.144f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.23f, -0.090f);
    glVertex2f(-0.23f, -0.213f);
    glVertex2f(-0.205f, -0.213f);
    glVertex2f(-0.205f, -0.090f);
    glEnd();
    glColor3f(0.8f, 0.0f, 0.0f);
    drawCircle(-0.2175f,-0.11f,0.01f);
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(-0.2175f,-0.15f,0.01f);
    glColor3f(0.0f, 0.8f, 0.0f);
    drawCircle(-0.2175f,-0.19f,0.01f);
}
void speedLimit()
{
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.43f, -0.65f);
    glVertex2f(-0.43f, -0.9f);
    glVertex2f(-0.42f, -0.9f);
    glVertex2f(-0.42f, -0.65f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.425f,-0.62f,0.04f);
    glColor3f(0.8f, 0.0f, 0.0f);
    drawCircle(-0.425f,-0.62f,0.036f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.425f,-0.62f,0.028f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.435f,-0.61f,0.010f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.435f,-0.61f,0.005f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.435f,-0.63f,0.010f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.435f,-0.63f,0.005f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.413f,-0.62f,0.013f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.413f,-0.62f,0.007f);
}
void light()
{
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_POLYGON);
    glVertex2f(0.41f, -0.1f);
    glVertex2f(0.41f, -0.8f);
    glVertex2f(0.425f, -0.8f);
    glVertex2f(0.425f, -0.1f);
    glEnd();
    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_POLYGON);
    glVertex2f(0.408f, -0.1f);
    glVertex2f(0.408f, -0.2f);
    glVertex2f(0.427f, -0.2f);
    glVertex2f(0.427f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.330f, -0.08f);
    glVertex2f(0.330f, -0.10f);
    glVertex2f(0.430f, -0.17f);
    glVertex2f(0.430f, -0.15f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.295f, -0.07f);
    glVertex2f(0.290f, -0.08f);
    glVertex2f(0.330f, -0.10f);
    glVertex2f(0.330f, -0.08f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(0.290f, -0.08f);
    glVertex2f(0.288f, -0.085f);
    glVertex2f(0.315f, -0.097f);
    glVertex2f(0.320f, -0.091f);
    glEnd();
}
void signBoard()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.45f, -0.65f);
    glVertex2f(0.45f, -0.9f);
    glVertex2f(0.46f, -0.9f);
    glVertex2f(0.46f, -0.65f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.42f, -0.55f);
    glVertex2f(0.42f, -0.65f);
    glVertex2f(0.49f, -0.65f);
    glVertex2f(0.49f, -0.55f);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.425f, -0.555f);
    glVertex2f(0.425f, -0.643f);
    glVertex2f(0.485f, -0.643f);
    glVertex2f(0.485f, -0.555f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.455f, -0.560f);
    glVertex2f(0.430f, -0.635f);
    glVertex2f(0.480f, -0.635f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.455f,-0.580f,0.007f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.454f, -0.585f);
    glVertex2f(0.454f, -0.615f);
    glVertex2f(0.456f, -0.615f);
    glVertex2f(0.456f, -0.585f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.454f, -0.615f);
    glVertex2f(0.444f, -0.627f);
    glVertex2f(0.447f, -0.627f);
    glVertex2f(0.457f, -0.617f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.454f, -0.617f);
    glVertex2f(0.463f, -0.627f);
    glVertex2f(0.463f, -0.625f);
    glVertex2f(0.456f, -0.615f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.454f, -0.592f);
    glVertex2f(0.445f, -0.605f);
    glVertex2f(0.445f, -0.607f);
    glVertex2f(0.454f, -0.594f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.454f, -0.594f);
    glVertex2f(0.464f, -0.607f);
    glVertex2f(0.464f, -0.605f);
    glVertex2f(0.454, -0.592f);
    glEnd();
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
        tFlagf = 0;
        break;
    case 'f':
        tFlagf = 1;
        break;
    case 'o':
        isMoving = true;
        break;
    case 'p':
        isMoving = false;
        break;
    case ']':
        shipSpeed *= 1.1f;
        break;
    case '[':
        shipSpeed *= 0.9f;
        break;

    case '3':
        if (!transitioning && nightFactor !=1)
        {
            transitioning = 1;
            targetNight = 1.0f;
        }
        break;
    }
    glutPostRedisplay();
}


void updateS(int value)
{
    if(tFlag == 1)
    {
        tx1 -= 0.0002f;
        ty1 += 0.01f;
        float t1 = (ty1 + 1.0f) / (0.7f + 1.0f);
        scale1 = 0.90f - t1 * (0.90f - 0.25f);
        if(ty1 >= 0.70f)
        {
            tx1 = 0.0f;
            ty1 = -1.0f;
        }
        tx2 = -0.030f;
        ty2 += 0.01f;
        float t2 = (ty2 + 1.9f) / (0.14f + 1.9f);
        scale2 = 0.80f - t2 * (0.80f - 0.25f);
        if(ty2 >= 0.14f)
        {
            tx2 = -0.12f;
            ty2 = -1.9f;
        }
        ty3 += 0.01f;
        tx3 = -0.01f - (ty3 * 0.25f);
        float t3 = (ty3 + 1.2f) / (0.4f + 1.2f);
        scale3 = 0.70f - t3 * (0.70f - 0.25f);
        if(ty3 >= 0.40f)
        {
            ty3 = -1.2f;
        }
    }
    if(rFlag == 1)
        angle += speed;
    if(scale1 < 0.25f)
        scale1 = 0.25f;
    if(scale1 > 0.80f)
        scale1 = 0.80f;
    if(scale2 < 0.25f)
        scale2 = 0.25f;
    if(scale2 > 0.60f)
        scale2 = 0.60f;
    if(scale3 < 0.25f)
        scale3 = 0.25f;
    if(scale3 > 0.70f)
        scale3 = 0.70f;

    // Day/Night transition
    if (transitioning)
    {
        if (nightFactor < targetNight)
        {
            nightFactor += TRANSITION_SPEED;
            if (nightFactor >= targetNight)
            {
                nightFactor = targetNight;
                transitioning = 0;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, updateS, 0);
}

// ========== SAFIUL (buildings, hospital, school, etc.) ==========




void drawBushes(float x, float y)
{
    glColor3f(0.35f, 0.50f, 0.15f);
    float r = 0.035f;
    for(float i=0; i<0.08f; i+=0.025f)
    {
        glBegin(GL_POLYGON);
        for(int j=0; j<360; j+=30)
            glVertex2f(x+i + r*cos(j*3.14/180), y + r*sin(j*3.14/180));
        glEnd();
    }
}
void drawHome()
{
    glColor3f(0.0f, 0.70f, 0.80f);
    glBegin(GL_QUADS);
    glVertex2f(0.75f, -0.71f);
    glVertex2f(0.98f, -0.71f);
    glVertex2f(0.98f, -0.67f);
    glVertex2f(0.75f, -0.67f);
    glEnd();
    glColor3f(0.82f, 0.92f, 0.97f);
    glBegin(GL_QUADS);
    glVertex2f(0.75f, -0.67f);
    glVertex2f(0.98f, -0.67f);
    glVertex2f(0.98f, -0.38f);
    glVertex2f(0.75f, -0.38f);
    glEnd();
    glColor3f(0.35f, 0.20f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.71f, -0.39f);
    glVertex2f(1.02f, -0.39f);
    glVertex2f(0.865f, -0.28f);
    glEnd();
    glColor3f(0.45f, 0.30f, 0.25f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.74f, -0.38f);
    glVertex2f(1.00f, -0.38f);
    glVertex2f(0.865f, -0.30f);
    glEnd();
    glColor3f(0.35f, 0.20f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(0.87f, -0.67f);
    glVertex2f(0.95f, -0.67f);
    glVertex2f(0.95f, -0.43f);
    glVertex2f(0.87f, -0.43f);
    glEnd();
    glColor3f(0.95f, 0.75f, 0.20f);
    float kX = 0.935f, kY = -0.55f, kR = 0.009f;
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=20)
        glVertex2f(kX + kR*cos(i*3.14/180), kY + kR*sin(i*3.14/180));
    glEnd();
    float wX = 0.77f, wY = -0.58f;
    glColor3f(0.35f, 0.20f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(wX, wY);
    glVertex2f(wX+0.07f, wY);
    glVertex2f(wX+0.07f, wY+0.09f);
    glVertex2f(wX, wY+0.09f);
    glEnd();
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(wX+0.006f, wY+0.006f);
    glVertex2f(wX+0.064f, wY+0.006f);
    glVertex2f(wX+0.064f, wY+0.084f);
    glVertex2f(wX+0.006f, wY+0.084f);
    glEnd();
    glColor3f(0.35f, 0.20f, 0.15f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(wX+0.035f, wY);
    glVertex2f(wX+0.035f, wY+0.09f);
    glVertex2f(wX, wY+0.045f);
    glVertex2f(wX+0.07f, wY+0.045f);
    glEnd();
    drawBushes(0.75f, -0.73f);
    drawBushes(0.95f, -0.73f);
}
void drawApartmentWindow(float x, float y)
{
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.005f, y - 0.01f);
    glVertex2f(x + 0.065f, y - 0.01f);
    glVertex2f(x + 0.065f, y);
    glVertex2f(x - 0.005f, y);
    glEnd();
    glColor3f(0.85f, 0.20f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 0.06f, y);
    glVertex2f(x + 0.06f, y + 0.07f);
    glVertex2f(x, y + 0.07f);
    glEnd();
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.005f, y + 0.005f);
    glVertex2f(x + 0.025f, y + 0.005f);
    glVertex2f(x + 0.025f, y + 0.065f);
    glVertex2f(x + 0.005f, y + 0.065f);
    glVertex2f(x + 0.035f, y + 0.005f);
    glVertex2f(x + 0.055f, y + 0.005f);
    glVertex2f(x + 0.055f, y + 0.065f);
    glVertex2f(x + 0.035f, y + 0.065f);
    glEnd();
}
void drawNeighborApartment()
{
    glColor3f(0.93f, 0.88f, 0.78f);
    glBegin(GL_QUADS);
    glVertex2f(0.52f, -0.71f);
    glVertex2f(0.72f, -0.71f);
    glVertex2f(0.72f, -0.32f);
    glVertex2f(0.52f, -0.32f);
    glEnd();
    glColor3f(0.85f, 0.20f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.48f, -0.32f);
    glVertex2f(0.76f, -0.32f);
    glVertex2f(0.62f, -0.15f);
    glEnd();
    drawApartmentWindow(0.55f, -0.44f);
    drawApartmentWindow(0.64f, -0.44f);
    drawApartmentWindow(0.55f, -0.56f);
    drawApartmentWindow(0.64f, -0.56f);
    drawApartmentWindow(0.55f, -0.68f);
    glColor3f(0.85f, 0.20f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.63f, -0.60f);
    glVertex2f(0.71f, -0.60f);
    glVertex2f(0.67f, -0.56f);
    glEnd();
    glColor3f(0.55f, 0.40f, 0.30f);
    glBegin(GL_QUADS);
    glVertex2f(0.64f, -0.71f);
    glVertex2f(0.70f, -0.71f);
    glVertex2f(0.70f, -0.60f);
    glVertex2f(0.64f, -0.60f);
    glEnd();
    glColor3f(0.7f, 0.7f, 0.7f);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(0.65f, -0.66f);
    glEnd();
    glColor3f(0.85f, 0.20f, 0.15f);
    for(float wx = 0.655f; wx <= 0.675f; wx += 0.012f)
    {
        for(float wy = -0.65f; wy <= -0.62f; wy += 0.012f)
        {
            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx+0.008f, wy);
            glVertex2f(wx+0.008f, wy+0.008f);
            glVertex2f(wx, wy+0.008f);
            glEnd();
        }
    }
}
void drawText(const char* text, float x, float y, float r, float g, float b)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}
void drawSchool()
{
    float bodyOrange[] = {1.0f, 0.65f, 0.35f};
    float roofGrey[] = {0.25f, 0.30f, 0.35f};
    float bannerWhite[] = {0.95f, 0.95f, 0.95f};
    float glassBlue[] = {0.60f, 0.85f, 0.95f};
    float doorBrown[] = {0.45f, 0.25f, 0.15f};
    glColor3fv(bodyOrange);
    glBegin(GL_QUADS);
    glVertex2f(0.38f, 0.00f);
    glVertex2f(0.47f, 0.00f);
    glVertex2f(0.47f, 0.28f);
    glVertex2f(0.38f, 0.28f);
    glVertex2f(0.63f, 0.00f);
    glVertex2f(0.72f, 0.00f);
    glVertex2f(0.72f, 0.28f);
    glVertex2f(0.63f, 0.28f);
    glVertex2f(0.47f, 0.00f);
    glVertex2f(0.63f, 0.00f);
    glVertex2f(0.63f, 0.33f);
    glVertex2f(0.47f, 0.33f);
    glEnd();
    glColor3fv(roofGrey);
    glBegin(GL_QUADS);
    glVertex2f(0.37f, 0.28f);
    glVertex2f(0.47f, 0.28f);
    glVertex2f(0.47f, 0.31f);
    glVertex2f(0.37f, 0.31f);
    glVertex2f(0.63f, 0.28f);
    glVertex2f(0.73f, 0.28f);
    glVertex2f(0.73f, 0.31f);
    glVertex2f(0.63f, 0.31f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.46f, 0.33f);
    glVertex2f(0.64f, 0.33f);
    glVertex2f(0.55f, 0.43f);
    glEnd();
    glColor3fv(bannerWhite);
    glBegin(GL_QUADS);
    glVertex2f(0.48f, 0.27f);
    glVertex2f(0.62f, 0.27f);
    glVertex2f(0.62f, 0.32f);
    glVertex2f(0.48f, 0.32f);
    glEnd();
    float cx = 0.55f, cy = 0.37f, r = 0.028f;
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=15)
        glVertex2f(cx + r*cos(i*3.1415/180), cy + r*sin(i*3.1415/180));
    glEnd();
    glColor3fv(roofGrey);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.50f, 0.13f);
    glVertex2f(0.60f, 0.13f);
    glVertex2f(0.55f, 0.18f);
    glEnd();
    glColor3fv(doorBrown);
    glBegin(GL_QUADS);
    glVertex2f(0.52f, 0.02f);
    glVertex2f(0.58f, 0.02f);
    glVertex2f(0.58f, 0.13f);
    glVertex2f(0.52f, 0.13f);
    glEnd();
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(0.49f, 0.20f);
    glVertex2f(0.52f, 0.20f);
    glVertex2f(0.52f, 0.25f);
    glVertex2f(0.49f, 0.25f);
    glVertex2f(0.535f, 0.20f);
    glVertex2f(0.565f, 0.20f);
    glVertex2f(0.565f, 0.25f);
    glVertex2f(0.535f, 0.25f);
    glVertex2f(0.58f, 0.20f);
    glVertex2f(0.61f, 0.20f);
    glVertex2f(0.61f, 0.25f);
    glVertex2f(0.58f, 0.25f);

    for(float xPos = 0.39f; xPos <= 0.43f; xPos += 0.04f)
    {
        for(float yPos = 0.06f; yPos <= 0.18f; yPos += 0.10f)
        {
            glVertex2f(xPos, yPos);
            glVertex2f(xPos+0.03f, yPos);
            glVertex2f(xPos+0.03f, yPos+0.06f);
            glVertex2f(xPos, yPos+0.06f);
        }
    }
    for(float xPos = 0.65f; xPos <= 0.69f; xPos += 0.04f)
    {
        for(float yPos = 0.06f; yPos <= 0.18f; yPos += 0.10f)
        {
            glVertex2f(xPos, yPos);
            glVertex2f(xPos+0.03f, yPos);
            glVertex2f(xPos+0.03f, yPos+0.06f);
            glVertex2f(xPos, yPos+0.06f);
        }
    }
    glEnd();
    drawText("SCHOOL", 0.515f, 0.285f, 0.1f, 0.1f, 0.1f);
}
void drawFlag()
{
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(0.300f, -0.05f);
    glVertex2f(0.305f, -0.05f);
    glVertex2f(0.305f,  0.22f);
    glVertex2f(0.300f,  0.22f);
    glEnd();
    glColor3f(0.0f, 0.42f, 0.31f);
    glBegin(GL_QUADS);
    glVertex2f(0.305f, 0.14f);
    glVertex2f(0.380f, 0.14f);
    glVertex2f(0.380f, 0.20f);
    glVertex2f(0.305f, 0.20f);
    glEnd();
    glColor3f(0.95f, 0.18f, 0.13f);
    float circleX = 0.335f, circleY = 0.170f, radius = 0.015f;
    int triangleAmount = 40;
    GLfloat twicePi = 2.0f * 3.14159f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circleX, circleY);
    for(int i = 0; i <= triangleAmount; i++)
        glVertex2f(circleX + (radius * cos(i * twicePi / triangleAmount)),
                   circleY + (radius * sin(i * twicePi / triangleAmount)));
    glEnd();
}
void drawHospital()
{
    float wingGrey[] = {0.88f, 0.94f, 0.96f};
    float centerGrey[] = {0.62f, 0.74f, 0.80f};
    float glassBlue[] = {0.0f, 0.72f, 0.92f};
    float signBlue[] = {0.0f, 0.30f, 0.70f};
    float hospitalRed[] = {0.95f, 0.15f, 0.10f};
    float pureWhite[] = {1.0f, 1.0f, 1.0f};
    glColor3f(0.5f, 0.5f, 0.55f);
    glBegin(GL_QUADS);
    glVertex2f(0.70f, -0.22f);
    glVertex2f(1.00f, -0.22f);
    glVertex2f(1.00f, -0.18f);
    glVertex2f(0.70f, -0.18f);
    glEnd();
    glColor3fv(wingGrey);
    glBegin(GL_QUADS);
    glVertex2f(0.73f, -0.18f);
    glVertex2f(0.84f, -0.18f);
    glVertex2f(0.84f,  0.15f);
    glVertex2f(0.73f,  0.15f);
    glVertex2f(0.96f, -0.18f);
    glVertex2f(1.00f, -0.18f);
    glVertex2f(1.00f,  0.15f);
    glVertex2f(0.96f,  0.15f);
    glEnd();
    glColor3fv(centerGrey);
    glBegin(GL_QUADS);
    glVertex2f(0.84f, -0.18f);
    glVertex2f(0.96f, -0.18f);
    glVertex2f(0.96f,  0.18f);
    glVertex2f(0.84f,  0.18f);
    glEnd();
    glColor3fv(signBlue);
    glBegin(GL_QUADS);
    glVertex2f(0.85f, -0.05f);
    glVertex2f(0.95f, -0.05f);
    glVertex2f(0.95f,  0.01f);
    glVertex2f(0.85f,  0.01f);
    glEnd();
    glColor3fv(pureWhite);
    glBegin(GL_QUADS);
    glVertex2f(0.865f, -0.18f);
    glVertex2f(0.875f, -0.18f);
    glVertex2f(0.875f, -0.08f);
    glVertex2f(0.865f, -0.08f);
    glVertex2f(0.930f, -0.18f);
    glVertex2f(0.940f, -0.18f);
    glVertex2f(0.940f, -0.08f);
    glVertex2f(0.930f, -0.08f);
    glVertex2f(0.865f, -0.08f);
    glVertex2f(0.940f, -0.08f);
    glVertex2f(0.940f, -0.06f);
    glVertex2f(0.865f, -0.06f);
    glEnd();
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    glVertex2f(0.88f, -0.18f);
    glVertex2f(0.92f, -0.18f);
    glVertex2f(0.92f, -0.08f);
    glVertex2f(0.88f, -0.08f);
    glEnd();
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    for(float rowY = -0.15f; rowY <= 0.05f; rowY += 0.08f)
    {
        glVertex2f(0.74f, rowY);
        glVertex2f(0.76f, rowY);
        glVertex2f(0.76f, rowY+0.04f);
        glVertex2f(0.74f, rowY+0.04f);
        glVertex2f(0.78f, rowY);
        glVertex2f(0.80f, rowY);
        glVertex2f(0.80f, rowY+0.04f);
        glVertex2f(0.78f, rowY+0.04f);
        glVertex2f(0.81f, rowY);
        glVertex2f(0.83f, rowY);
        glVertex2f(0.83f, rowY+0.04f);
        glVertex2f(0.81f, rowY+0.04f);
        if(rowY > 0.02f)
        {
            glVertex2f(0.86f, rowY);
            glVertex2f(0.90f, rowY);
            glVertex2f(0.90f, rowY+0.05f);
            glVertex2f(0.86f, rowY+0.05f);
            glVertex2f(0.91f, rowY);
            glVertex2f(0.95f, rowY);
            glVertex2f(0.95f, rowY+0.05f);
            glVertex2f(0.91f, rowY+0.05f);
        }
        glVertex2f(0.97f, rowY);
        glVertex2f(0.99f, rowY);
        glVertex2f(0.99f, rowY+0.04f);
        glVertex2f(0.97f, rowY+0.04f);
    }
    glEnd();
    float cxH = 0.90f, cyH = 0.07f, rH = 0.03f;
    glColor3fv(hospitalRed);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=10)
        glVertex2f(cxH + rH*cos(i*3.14159/180), cyH + rH*sin(i*3.14159/180));
    glEnd();
    glColor3fv(pureWhite);
    glBegin(GL_QUADS);
    glVertex2f(cxH-0.005f, cyH-0.02f);
    glVertex2f(cxH+0.005f, cyH-0.02f);
    glVertex2f(cxH+0.005f, cyH+0.02f);
    glVertex2f(cxH-0.005f, cyH+0.02f);
    glVertex2f(cxH-0.02f, cyH-0.005f);
    glVertex2f(cxH+0.02f, cyH-0.005f);
    glVertex2f(cxH+0.02f, cyH+0.005f);
    glVertex2f(cxH-0.02f, cyH+0.005f);
    glEnd();
    drawText("HOSPITAL", 0.862f, -0.03f, 1.0f, 1.0f, 1.0f);
}
void drawBuilding()
{
    float startX = 0.20f, bWidth = 0.15f, startY = 0.215f;
    float floorH = 0.22f;
    int totalFloors = 3;
    float wallBrown[] = {0.50f, 0.40f, 0.35f};
    float trimGold[] = {0.85f, 0.75f, 0.50f};
    if (nightFactor > 0.5f)
        glColor3f(0.2f, 0.2f, 0.3f);   // same as Twin Towers
    else
        glColor3fv(wallBrown);
    glBegin(GL_QUADS);
    glVertex2f(startX, startY);
    glVertex2f(startX + bWidth, startY);
    glVertex2f(startX + bWidth, startY + (floorH * totalFloors));
    glVertex2f(startX, startY + (floorH * totalFloors));
    glEnd();
    for (int i = 0; i < totalFloors; i++)
    {
        float currentY = startY + (i * floorH);
        glColor3fv(trimGold);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2f(startX, currentY);
        glVertex2f(startX + bWidth, currentY);
        glEnd();
        setWindowColor(nightFactor);
        glBegin(GL_QUADS);
        for (float winX = startX + 0.02f; winX < startX + bWidth - 0.02f; winX += 0.045f)
        {
            glVertex2f(winX, currentY + 0.06f);
            glVertex2f(winX + 0.03f, currentY + 0.06f);
            glVertex2f(winX + 0.03f, currentY + 0.18f);
            glVertex2f(winX, currentY + 0.18f);
        }
        glEnd();
        glColor3fv(trimGold);
        glBegin(GL_LINES);
        glVertex2f(startX + 0.01f, currentY + 0.06f);
        glVertex2f(startX + bWidth - 0.01f, currentY + 0.06f);
        glEnd();
    }
}
void drawTwinTowers()
{
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(0.85f, 0.25f);
    glVertex2f(0.91f, 0.25f);
    glVertex2f(0.91f, 0.81f);
    glVertex2f(0.85f, 0.81f);
    glVertex2f(0.93f, 0.25f);
    glVertex2f(0.99f, 0.25f);
    glVertex2f(0.99f, 0.81f);
    glVertex2f(0.93f, 0.81f);
    glEnd();
    setWindowColor(nightFactor);
    glBegin(GL_QUADS);
    for(float h = 0.30f; h < 0.75f; h += 0.12f)
    {
        glVertex2f(0.86f, h);
        glVertex2f(0.90f, h);
        glVertex2f(0.90f, h + 0.08f);
        glVertex2f(0.86f, h + 0.08f);
        glVertex2f(0.94f, h);
        glVertex2f(0.98f, h);
        glVertex2f(0.98f, h + 0.08f);
        glVertex2f(0.94f, h + 0.08f);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.88f, 0.81f);
    glVertex2f(0.88f, 0.91f);
    glVertex2f(0.96f, 0.81f);
    glVertex2f(0.96f, 0.91f);
    glEnd();
}

// ========== STREET LAMPS (only appear at night) ==========
void drawStreetLamps()
{
    if (nightFactor < 0.2f)
        return; // invisible during day
    // positions along the road (x, y) – approximate center line
    float lampPositions[][2] =
    {
        {-0.07f, 0.35f}, {-0.03f, 0.10f}, {0.01f, -0.15f},
        {0.05f, -0.40f}, {0.09f, -0.65f}, {0.13f, -0.90f}
    };
    for (int i = 0; i < 6; i++)
    {
        float x = lampPositions[i][0];
        float y = lampPositions[i][1];
        // pole
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(x - 0.008f, y - 0.02f);
        glVertex2f(x + 0.008f, y - 0.02f);
        glVertex2f(x + 0.008f, y + 0.08f);
        glVertex2f(x - 0.008f, y + 0.08f);
        glEnd();
        // lamp head
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_QUADS);
        glVertex2f(x - 0.015f, y + 0.08f);
        glVertex2f(x + 0.015f, y + 0.08f);
        glVertex2f(x + 0.015f, y + 0.10f);
        glVertex2f(x - 0.015f, y + 0.10f);
        glEnd();
        // light glow: radius and brightness increase with nightFactor
        float glowSize = 0.025f + nightFactor * 0.025f;
        glColor3f(1.0f, 0.9f, 0.5f);
        drawCircle(x, y + 0.09f, glowSize);
    }
}

// ========== SUN & MOON ==========
void drawSun()
{
    if (nightFactor >= 0.99f)
        return;
    float size = 0.075f * (1.0f - nightFactor);
    if (size <= 0.001f)
        return;
    // sun fades to sky colour
    float r = 1.0f * (1.0f - nightFactor) + 0.05f * nightFactor;
    float g = 0.9f * (1.0f - nightFactor) + 0.05f * nightFactor;
    float b = 0.5f * (1.0f - nightFactor) + 0.3f * nightFactor;
    glColor3f(r, g, b);
    drawCircle(0.0f, 0.55f - nightFactor * 0.3f, size);
}
void drawMoon()
{
    if (nightFactor <= 0.1f)
        return;
    float size = 0.07f * (nightFactor - 0.1f) / 0.9f;
    if (size <= 0.001f)
        return;
    glColor3f(1.0f, 1.0f, 0.85f);
    drawCircle(-0.4f, 0.75f, size);
}
void drawRightGround()
{
    if (nightFactor > 0.5f)
        glColor3f(0.12f, 0.28f, 0.12f);   // light dark green
    else
        interpolateColor(nightFactor, 0.60f, 0.90f, 0.55f, 0.12f, 0.28f, 0.12f);

    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.45f);   // top left (just below horizon)
    glVertex2f(1.00f, 0.45f);   // top right
    glVertex2f(1.00f, -1.00f);  // bottom right
    glVertex2f(0.20f, -1.00f);  // bottom left
    glEnd();
}

// ========== DISPLAY ==========
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky (interpolated)
    interpolateColor(nightFactor, 0.55f, 0.75f, 0.80f, 0.05f, 0.08f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(1.0f,1.0f);
    glVertex2f(1.0f,0.45f);
    glVertex2f(-1.0f,0.45f);
    glEnd();

    drawSun();
    drawMoon();
    drawMountain();
    drawForest();
    drawCloud();
    drawRightGround();

    glPushMatrix();
    glTranslatef(txf, 0.0f, 0.0f);
    glScalef(scalef, scalef, 1.0f);
    Airplane2();
    glPopMatrix();

    road();
    div();
    drawCar1(0.02f + tx1, -0.2f + ty1, scale1, 7.0f);
    drawCar2(0.02f + tx2, 0.35f + ty2, scale2, 7.0f);
    drawCar3(0.15f + tx3, 0.1f + ty3, scale3, 05.0f);
    light();
    signBoard();

    drawHome();
    drawSchool();
    drawHospital();
    drawBuilding();
    drawTwinTowers();
    drawFlag();
    drawNeighborApartment();

//////////////////////////
////ORNOB/////
    water();
    riverSide();
    roadSide();
    ship_transition();
//////////////////////

    trafficLight();
    speedLimit();


    glFlush();
}

// ========== MAIN ==========
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(960,540);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Day & Night Scenario");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardS);
    glutTimerFunc(16, updatef, 0);
    glutTimerFunc(16, updateS, 0);
    glutTimerFunc(0, updateShip, 0);

    glClearColor(1.0f,1.0f,1.0f,1.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutMainLoop();
    return 0;
}
