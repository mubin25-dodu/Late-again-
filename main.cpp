#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <cstdio>

#define PI 3.14159265358979323846
int a = 20;
int timer = a;
float x1, x2, x3, x4, y1_pos, y2_pos, y3_pos, y4_pos, colup;
int currentScreen = 0;
GLfloat playerX = 0.0f;
GLfloat playerY = -1.5f;
GLfloat move = 0.0f;
GLfloat screenmovement = 0.5f;
int l1 = 10;
int curentscreen = 0;
GLfloat playerSpeed = 0.4f;
bool isCountdownFinished = false;

void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    const char* c;
    glRasterPos3f(x, y, z);  // Position the text
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);  // Render each character
    }
}
void timeup() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // Light gray background
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the buffer

    glColor3f(0.8f, 0.8f, 0.8f);  // Light gray for the placeholder
    glBegin(GL_QUADS);
    glVertex2f(-3.0f, -3.5f);
    glVertex2f(3.0, -3.5f);
    glVertex2f(3.0f, 3.5f);
    glVertex2f(-3.0f, 3.5f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glColor3f(0.1f, 0.4f, 0.8f); // Blue color for title bar
    glBegin(GL_QUADS);
    glVertex2f(-2.5f, 2.2f); // Top-left corner
    glVertex2f(2.5f, 2.2f);  // Top-right corner
    glVertex2f(2.5f, 3.0f);  // Bottom-right corner
    glVertex2f(-2.5f, 3.0f); // Bottom-left corner
    glEnd();
    // Render title text
    glColor3f(1.0f, 1.0f, 1.0f); // Black color for text
    renderBitmapString(-1.0f, 2.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "YOU ARE LATE AGAIN!!");
    glPopMatrix();
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f); // Black color for text
    renderBitmapString(-0.4f, 1.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "TIME UP");

    // Render level texts
    glColor3f(0.0f, 0.0f, 0.0f);
    renderBitmapString(-0.8f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, " RETRY-PRESS R");
    renderBitmapString(-0.8f, -0.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, " HOME-PRESS H");

    glFlush();  // Render the objects now

}

void timerFunc(int value) {
    if (currentScreen == 1) {
        if (timer > 0) {
            timer--;
            glutPostRedisplay();  // Update display
            glutTimerFunc(1000, timerFunc, 0);  // Restart the timer
        } 
        else if(timer <=0) {
           currentScreen = 3;
            glutPostRedisplay();  // Update display to show timeup screen
        }
        else {
            isCountdownFinished = true;
            glutPostRedisplay();  // Update display to show timeup screen
        }
    }
}

void home() {

    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // Light gray background
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the buffer

    glColor3f(0.8f, 0.8f, 0.8f);  // Light gray for the placeholder
    glBegin(GL_QUADS);
    glVertex2f(-3.0f, -3.5f);
    glVertex2f(3.0, -3.5f);
    glVertex2f(3.0f, 3.5f);
    glVertex2f(-3.0f, 3.5f);
    glEnd();

    glColor3f(0.0f, 0.8f, 0.8f);// Light gray for the placeholder
    glBegin(GL_QUADS);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(-2.0f, -1.0f);
    glVertex2f(-2.0f, -2.0f);
    glVertex2f(2.0, -2.0f);

    glEnd();

    glColor3f(0.1f, 0.4f, 0.8f); // Blue color for title bar
    glBegin(GL_QUADS);
    glVertex2f(-2.5f, 2.2f); // Top-left corner
    glVertex2f(2.5f, 2.2f);  // Top-right corner
    glVertex2f(2.5f, 3.0f);  // Bottom-right corner
    glVertex2f(-2.5f, 3.0f); // Bottom-left corner
    glEnd();

    glColor3f(0.1f, 0.4f, 0.8f); // Blue color for title bar
    glBegin(GL_QUADS);
    glVertex2f(-2.0f, 0.35f); // Top-left corner
    glVertex2f(-1.0f, 0.35f);  // Top-right corner
    glVertex2f(-1.0f, -0.2f);  // Bottom-right corner
    glVertex2f(-2.0f, -0.2f); // Bottom-left corner
    glEnd();

    glColor3f(0.1f, 0.4f, 0.8f); // Blue color for title bar
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 0.35f); // Top-left corner
    glVertex2f(0.5f, 0.35f);  // Top-right corner
    glVertex2f(0.5f, -0.2f);  // Bottom-right corner
    glVertex2f(-0.5f, -0.2f); // Bottom-left corner
    glEnd();

    glColor3f(0.1f, 0.4f, 0.8f); // Blue color for title bar
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 0.35f); // Top-left corner
    glVertex2f(2.0f, 0.35f);  // Top-right corner
    glVertex2f(2.0f, -0.2f);  // Bottom-right corner
    glVertex2f(1.0f, -0.2f); // Bottom-left corner
    glEnd();

    // Render title text
    glColor3f(1.0f, 1.0f, 1.0f); // Black color for text
    renderBitmapString(-0.7f, 2.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "LATE AGAIN!!");

    // glColor3f(0.0f, 0.0f, 0.0f); // Black color for text
    // renderBitmapString(-0.4f, 1.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "LEVELS");

    // Render level texts
    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(-1.78f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "PRESS S TO START THE GAME");

    glFlush();  // Render the objects now

}

void Road() {
    //bottom tin shade
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.0f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.5f, -1.5f);  // top-left vertex
    glVertex2f(3.3f, -2.3f);  // top-right vertex
    glVertex2f(4.2f, -2.3f); // bottom-right vertex
    glVertex2f(5.0f, -1.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();       //left

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.6f, 0.2f, 0.2f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.5f, -1.5f);  // top-left vertex
    glVertex2f(3.3f, -2.3f);  // top-right vertex
    glVertex2f(3.3f, -3.2f); // bottom-right vertex
    glVertex2f(2.5f, -4.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.5f, 0.0f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.5f, -4.0f);  // top-left vertex
    glVertex2f(3.3f, -3.2f);  // top-right vertex
    glVertex2f(4.2f, -3.2f); // bottom-right vertex
    glVertex2f(5.0f, -4.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.4f, 0.0f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(3.3f, -2.3f);  // top-left vertex
    glVertex2f(3.3f, -3.2f);  // top-right vertex
    glVertex2f(4.2f, -3.2f); // bottom-right vertex
    glVertex2f(4.2f, -2.3f);  // bottom-left vertex
    glEnd();
    glPopMatrix();


    //TOP TIN SHADE
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.0f, 0.75f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.5f, 4.0f);  // top-left vertex
    glVertex2f(3.5f, 3.4f);  // top-right vertex
    glVertex2f(3.5f, 2.1f); // bottom-right vertex
    glVertex2f(2.5f, 1.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//LEFT

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.0f, 0.5f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(4.5f, 4.0f);  // top-left vertex
    glVertex2f(3.5f, 3.4f);  // top-right vertex
    glVertex2f(3.5f, 2.1f); // bottom-right vertex
    glVertex2f(4.5f, 1.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//RIGHT

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(0.13f, 0.55f, 0.13f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.5f, 4.0f);  // top-left vertex
    glVertex2f(3.5f, 3.4f);  // top-right vertex
    glVertex2f(4.5f, 4.0f); // bottom-right vertex
    glEnd();
    glPopMatrix();//TOP

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(0.13f, 0.55f, 0.13f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(3.5f, 2.1f);  // top-left vertex
    glVertex2f(2.5f, 1.5f);  // top-right vertex
    glVertex2f(4.5f, 1.5f); // bottom-right vertex
    glEnd();
    glPopMatrix();//BOTTOM


    //BUILDING
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.8f, 0.6f, 0.4f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.5f, -1.5f);  // top-left vertex
    glVertex2f(5.0f, -1.5f);  // top-right vertex
    glVertex2f(5.0f, 1.5f); // bottom-right vertex
    glVertex2f(2.5f, 1.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//OUTER BORDER

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.8f, 0.8f, 0.8f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(2.6f, 1.4f);  // top-left vertex
    glVertex2f(2.6f, -1.4f);  // top-right vertex
    glVertex2f(4.9f, -1.4f); // bottom-right vertex
    glVertex2f(4.9f, 1.4f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//INNER BORDER

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.55f, 0.27f, 0.07f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(3.7f, 1.0f);  // top-left vertex
    glVertex2f(4.5f, 1.0f);  // top-right vertex
    glVertex2f(4.5f, -0.2f); // bottom-right vertex
    glVertex2f(3.7f, -0.2f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//RIGHT BOX OUTER BORDER


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.82f, 0.71f, 0.55f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(3.8f, 0.9f);  // top-left vertex
    glVertex2f(4.4f, 0.9f);  // top-right vertex
    glVertex2f(4.4f, -0.1f); // bottom-right vertex
    glVertex2f(3.8f, -0.1f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//RIGHT BOX INNER BORDER

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.55f, 0.27f, 0.07f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(3.0f, 1.0f);  // top-left vertex
    glVertex2f(3.5f, 1.0f);  // top-right vertex
    glVertex2f(3.5f, 0.5f); // bottom-right vertex
    glVertex2f(3.0f, 0.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//TOP LEFT BOX

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.55f, 0.27f, 0.07f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(3.0f, -0.5f);  // top-left vertex
    glVertex2f(3.5f, -0.5f);  // top-right vertex
    glVertex2f(3.5f, -1.0f); // bottom-right vertex
    glVertex2f(3.0f, -1.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//BOTTOM LEFT BOX


    //left side of the road
    //top tin shade
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(0.6f, 0.0f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-2.5f, 4.0f);  // top-left vertex
    glVertex2f(-5.0f, 4.0f);  // top-right vertex
    glVertex2f(-3.2f, 3.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//top rectangle

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(0.6f, 0.0f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-3.2f, 3.0f);  // top-left vertex
    glVertex2f(-5.0f, 2.0f); // bottom-right vertex
    glVertex2f(-2.5f, 2.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//bottom rectangle


    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(0.7f, 0.2f, 0.2f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-4.0f, 4.0f);  // top-left vertex
    glVertex2f(-4.0f, 2.0f);  // top-right vertex
    glVertex2f(-3.2f, 3.0f); // bottom-right vertex
    glEnd();
    glPopMatrix();//Left

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(0.5f, 0.0f, 0.0f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-2.5f, 4.0f);  // top-left vertex
    glVertex2f(-2.5f, 2.0f);  // top-right vertex
    glVertex2f(-3.2f, 3.0f); // bottom-right vertex
    glEnd();
    glPopMatrix();  //Right


    //Bottom Building

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-5.0f, -2.0f);  // top-left vertex
    glVertex2f(-2.5f, -2.0f);  // top-right vertex
    glVertex2f(-2.5f, -4.0f); // bottom-right vertex
    glVertex2f(-5.0f, -4.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//Outer border


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.8f, 0.8f, 0.8f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-4.9f, -2.1f);  // top-left vertex
    glVertex2f(-2.6f, -2.1f);  // top-right vertex
    glVertex2f(-2.6f, -3.9f); // bottom-right vertex
    glVertex2f(-4.9f, -3.9f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//Inner border



    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-3.5f, -2.5f);  // top-left vertex
    glVertex2f(-3.0f, -2.5f);  // top-right vertex
    glVertex2f(-3.0f, -3.0f); // bottom-right vertex
    glVertex2f(-3.5f, -3.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//right box


    //Middle Building

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.27f, 0.51f, 0.71f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-2.5f, 2.0f);  // top-left vertex
    glVertex2f(-6.0f, 2.0f);  // top-right vertex
    glVertex2f(-6.0f, -2.0f); // bottom-right vertex
    glVertex2f(-2.5f, -2.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//outer border


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.74f, 0.85f, 0.91f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-2.6f, 1.9f);  // top-left vertex
    glVertex2f(-5.9f, 1.9f);  // top-right vertex
    glVertex2f(-5.9f, -1.9f); // bottom-right vertex
    glVertex2f(-2.6f, -1.9f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//Inner border


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.27f, 0.51f, 0.71f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-3.9f, 1.5f);  // top-left vertex
    glVertex2f(-3.0f, 1.5f);  // top-right vertex
    glVertex2f(-3.0f, 0.2f); // bottom-right vertex
    glVertex2f(-3.9f, 0.2f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//Top box outer border


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.7f, 0.86f, 0.96f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-3.8f, 1.4f);  // top-left vertex
    glVertex2f(-3.1f, 1.4f);  // top-right vertex
    glVertex2f(-3.1f, 0.3f); // bottom-right vertex
    glVertex2f(-3.8f, 0.3f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//top box Inner border


    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.27f, 0.51f, 0.71f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-3.9f, -0.6f);  // top-left vertex
    glVertex2f(-3.0f, -0.6f);  // top-right vertex
    glVertex2f(-3.0f, -1.5f); // bottom-right vertex
    glVertex2f(-3.9f, -1.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();//bottom box


    glPushMatrix();
    // glLineWidth(2);
    glBegin(GL_QUADS);
    glColor4f(0.52f, 0.52f, 0.52f, 0.95f);  //  color gray with 95% transparency

    glVertex2f(-2.5f, 4.0f);
    glVertex2f(-2.5f, -4.0f);
    glVertex2f(2.5f, -4.0f);
    glVertex2f(2.5f, 4.0f);
    glEnd();
    glPopMatrix();

    // top line
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.95f);  //  color white with 95% transparency

    glVertex2f(-0.08f, 4.0f);
    glVertex2f(-0.08f, 3.0f);
    glVertex2f(0.08f, 3.0f);
    glVertex2f(0.08f, 4.0f);
    glEnd();
    glPopMatrix();

    // mid line
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.95f);  //  color white with 95% transparency

    glVertex2f(-0.08f, 1.0f);
    glVertex2f(-0.08f, -1.0f);
    glVertex2f(0.08f, -1.0f);
    glVertex2f(0.08f, 1.0f);
    glEnd();
    glPopMatrix();
    // bottom line
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.95f);  //  color white with 95% transparency

    glVertex2f(-0.08f, -4.0f);
    glVertex2f(-0.08f, -3.0f);
    glVertex2f(0.08f, -3.0f);
    glVertex2f(0.08f, -4.0f);
    glEnd();
    glPopMatrix();

    // road side left

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.4f);  // color #F6F4F0 in OpenGL
    glVertex2f(-2.4f, 4.0f);  // top-left vertex
    glVertex2f(-2.5f, 4.0f);  // top-right vertex
    glVertex2f(-2.5f, -4.0f); // bottom-right vertex
    glVertex2f(-2.4f, -4.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // road side right
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.4f);  // color #F6F4F0 in OpenGL
    glVertex2f(2.4f, 4.0f);  // top-left vertex
    glVertex2f(2.5f, 4.0f);  // top-right vertex
    glVertex2f(2.5f, -4.0f); // bottom-right vertex
    glVertex2f(2.4f, -4.0f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

}

void renderText(float x, float y, void* font, const char* text) {
    glColor3f(1.0f, 1.0f, 1.0f);  //  color
    glRasterPos2f(x, y);          // Position the text
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
}
bool isCollision(float obj1Left, float obj1Right, float obj1Top, float obj1Bottom,
    float obj2Left, float obj2Right, float obj2Top, float obj2Bottom) {
    // Check if the rectangles overlap
    return !(obj1Left > obj2Right || obj1Right < obj2Left ||
        obj1Top < obj2Bottom || obj1Bottom > obj2Top);
}
void checkCollisions() {
    // Player bounding box
    float playerLeft = playerX - 0.1f;
    float playerRight = playerX + 0.1f;
    float playerTop = playerY + 0.1f;
    float playerBottom = playerY - 0.1f;

    // Van bounding box
    float vanLeft = x1;
    float vanRight = x2;
    float vanTop = y1_pos + move;
    float vanBottom = y3_pos + move;

    // Road bounding boxes
    float roadLeft = -4.0f;
    float roadRight = -2.7f;
    float roadTop = 4.0f;
    float roadBottom = -4.0f;

    float roadLeft2 = 2.7f;
    float roadRight2 = 4.0f;
    float roadTop2 = 4.0f;
    float roadBottom2 = -4.0f;

    // Car bounding boxes
    float carLeft = 0.5f;
    float carRight = 3.0f;
    float carTop = 5.0f + move;
    float carBottom = 2.0f + move;

    float car2Left = -0.0f;
    float car2Right = 3.0f;
    float car2Top = -3.5f + move;
    float car2Bottom = -6.5f + move;

    // Rickshaw bounding box
    float rickshawLeft = -2.3f;
    float rickshawRight = -1.05f;
    float rickshawTop = -1.6f + move;
    float rickshawBottom = -1.85f + move;

    // Truck bounding box
    float truckLeft = -2.0f;
    float truckRight = -0.4f;
    float truckTop = 3.2f + move;
    float truckBottom = 0.5f + move;

    if (isCollision(playerLeft, playerRight, playerTop, playerBottom,
        vanLeft, vanRight, vanTop, vanBottom) ||
        isCollision(playerLeft, playerRight, playerTop, playerBottom,
            roadLeft, roadRight, roadTop, roadBottom) ||
        isCollision(playerLeft, playerRight, playerTop, playerBottom,
            roadLeft2, roadRight2, roadTop2, roadBottom2) ||
        isCollision(playerLeft, playerRight, playerTop, playerBottom,
            carLeft, carRight, carTop, carBottom) ||
        isCollision(playerLeft, playerRight, playerTop, playerBottom,
            car2Left, car2Right, car2Top, car2Bottom) ||
        isCollision(playerLeft, playerRight, playerTop, playerBottom,
            rickshawLeft, rickshawRight, rickshawTop, rickshawBottom) ||
        isCollision(playerLeft, playerRight, playerTop, playerBottom,
            truckLeft, truckRight, truckTop, truckBottom)) {
        // Handle collision (e.g., reset player position)
        playerX = 0.0;
        move = 0.0f;
        glColor3f(1.0f, 0.0f, 0.0f);
        renderBitmapString(-0.5f, 3.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Collision Detected");
    }
}

void car() {
    glPushMatrix();
    glTranslated(0.5, 0.5, 0.0f);  // Translate to the position
    glScalef(0.45f, 0.35f, 1.0f);  // Scale down the car

    // Car body (main part)
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color
    glRectd(0, 2, 3, 5);  // Main body of the car

    // Car windows (white color)
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectd(0.75, 2.75, 2.25, 4.25);

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2d(0.75, 3.25);
    glVertex2d(2.25, 3.25);
    glVertex2d(2.5, 3.25);
    glEnd();

    // Roof (red color)
    glColor3f(1.0f, 0.0f, 0.0f);  // Red roof
    glBegin(GL_QUADS);
    glVertex2d(0.25, 5.5);
    glVertex2d(2.75, 5.5);
    glVertex2d(3, 5);
    glVertex2d(0, 5);
    glEnd();

    // Car bottom (green color)
    glColor3f(1.0f, 0.0f, 0.0f);  // Green bottom
    glBegin(GL_QUADS);
    glVertex2d(0, 2);
    glVertex2d(3, 2);
    glVertex2d(2.6, 0);
    glVertex2d(0.4, 0);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRectd(.85, 2.8, 2.0, 3.1);
    glRectd(1.5, 2.8, 2.2, 3.1);

    glRectd(.7, 3.5, 1.8, 4.2);
    glRectd(1.5, 3.5, 2.3, 4.2);
    glPopMatrix();

}

void car2() {
    glPushMatrix();
    glTranslatef(-0.0f, -5.5f, 0.0f);  // Translate to the position
    glScalef(0.45f, 0.35f, 1.0f);  // Scale down the car

    // Car body (main part)
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    glRectd(0, 2, 3, 5);  // Main body of the car

    // Car windows (light blue color)
    glColor3f(0.68f, 0.85f, 0.90f);
    glRectd(0.75, 2.75, 2.25, 4.25);

    glBegin(GL_LINES);
    glColor3f(0.68f, 0.85f, 0.90f);
    glVertex2d(0.75, 3.25);
    glVertex2d(2.25, 3.25);
    glVertex2d(2.5, 3.25);
    glEnd();

    // Roof (red color)
    glColor3f(1.0f, 0.0f, 0.0f);  // Red roof
    glBegin(GL_QUADS);
    glVertex2d(0.25, 5.5);
    glVertex2d(2.75, 5.5);
    glVertex2d(3, 5);
    glVertex2d(0, 5);
    glEnd();

    // Car bottom (green color)
    glColor3f(0.0f, 1.0f, 0.0f);  // Green bottom
    glBegin(GL_QUADS);
    glVertex2d(0, 2);
    glVertex2d(3, 2);
    glVertex2d(2.6, 0);
    glVertex2d(0.4, 0);
    glEnd();

    // Additional details (black color)
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectd(0.85, 2.8, 2.0, 3.1);
    glRectd(1.5, 2.8, 2.2, 3.1);

    glRectd(0.7, 3.5, 1.8, 4.2);
    glRectd(1.5, 3.5, 2.3, 4.2);
    glPopMatrix();
}
void van() {
    // Back
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.1f, 0.1f);
    glVertex2f(x2 = 1.9f, y1_pos = -0.8f);  // top-left vertex
    glVertex2f(x1 = 0.6f, y2_pos = -0.8f);  // top-right vertex
    glVertex2f(x3 = 0.6f, y3_pos = -1.8f);  // bottom-right vertex
    glVertex2f(x4 = 1.9f, y4_pos = -1.8f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // right connector
    glPushMatrix();
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor4f(0.0, 0.0f, 0.0f, 0.5f);  // color #black
    glVertex2f(1.9f, -1.8f);
    glVertex2f(1.25f, -2.0f);
    glEnd();
    glPopMatrix();

    // left connector
    glPushMatrix();
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor4f(0.0, 0.0f, 0.0f, 0.5f);  // color #black
    glVertex2f(0.6f, -1.8f);
    glVertex2f(1.25f, -2.0f);
    glEnd();
    glPopMatrix();

    // front 
    glPushMatrix();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor4f(0.0, 0.0f, 0.0f, 0.5f);  // color #black
    glVertex2f(1.25f, -1.8f);
    glVertex2f(1.25f, -2.35f);
    glEnd();
    glPopMatrix();

    // handle 
    glPushMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4f(0.0, 0.0f, 0.0f, 0.5f);  // color #black
    glVertex2f(1.0f, -2.25f);
    glVertex2f(1.5f, -2.25f);
    glEnd();
    glPopMatrix();

    //seat
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(1.15f, -1.75f);
    glVertex2f(1.15f, -1.85f);
    glVertex2f(1.35f, -1.85f);
    glVertex2f(1.35f, -1.75f);

    glEnd();
    glPopMatrix();
}
void player() {

    glPushMatrix();
    glScalef(0.8f, 0.8f, 1.0f);
    GLfloat x = playerX;
    GLfloat y = -1.5f; // Center position of the semicircle
    GLfloat radius = 0.17f;
    int i;
    int lineAmount = 100; //# of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    // Draw the lower semicircle
    glColor3f(0.0f, 0.0f, 0.0f); // Cyan color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for (i = lineAmount / 2; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();

    // Draw the Bézier curve (upper side)
    glColor3f(0.0f, 0.0f, 0.0f); // Red color for the curve
    GLfloat startX = x - radius;
    GLfloat startY = y;
    GLfloat endX = x + radius;
    GLfloat endY = y;

    // Two control points for the cubic Bézier curve
    GLfloat controlPoint1X = x - radius / 1.5;
    GLfloat controlPoint1Y = y + radius / .85;
    GLfloat controlPoint2X = x + radius / 1.5;
    GLfloat controlPoint2Y = y + radius / .85;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Starting point for the triangle fan
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        GLfloat bezX = pow(1 - t, 3) * startX +
            3 * pow(1 - t, 2) * t * controlPoint1X +
            3 * (1 - t) * pow(t, 2) * controlPoint2X +
            pow(t, 3) * endX;

        GLfloat bezY = pow(1 - t, 3) * startY +
            3 * pow(1 - t, 2) * t * controlPoint1Y +
            3 * (1 - t) * pow(t, 2) * controlPoint2Y +
            pow(t, 3) * endY;

        glVertex2f(bezX, bezY);
    }

    glEnd();


    // Draw triangles at the ends of the lines
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Left triangle (based on semicircle and Bézier control points)
    glVertex2f(x - radius + 0.2, y);   // Left base of the semicircle
    glVertex2f(controlPoint1X - 0.1, controlPoint1Y - 0.15); // Left control point of Bézier
    glVertex2f(x - (radius + .2) / 2, y - 0.06);  // Top of the left triangle

    // Right triangle (based on semicircle and Bézier control points)
    glVertex2f(x + radius - .15, y);    // Right base of the semicircle
    glVertex2f(controlPoint2X + 0.1, controlPoint2Y - 0.16); // Right control point of Bézier
    glVertex2f(x + (radius + .2) / 2, y - 0.06);   // Top of the right triangle
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glFlush(); // Render now 

}
void Rickshaw() {

    glPushMatrix();
    glScalef(1.3f, 1.3f, 1.3f);
    glTranslatef(0.6f, 0.7f, 0.0f);

    // Top rickshaw
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-2.3f, -1.6f); // top left
    glVertex2f(-2.3f, -1.85f); // bottom left
    glVertex2f(-1.05f, -1.85f); // bottom right
    glVertex2f(-1.05f, -1.6f); // top right   
    glEnd();
    glPopMatrix();

    // Leg area
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-2.25f, -1.5f); // top left
    glVertex2f(-2.25f, -1.6f); // bottom left
    glVertex2f(-1.1f, -1.6f); // bottom right
    glVertex2f(-1.1f, -1.5f); // top right   
    glEnd();
    glPopMatrix();

    // Mid connector
    glPushMatrix();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-1.67f, -1.5f);
    glVertex2f(-1.67f, -1.3f);
    glEnd();
    glPopMatrix();

    // Left connector
    glPushMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-1.87f, -1.5f);
    glVertex2f(-1.67f, -1.3f);
    glEnd();
    glPopMatrix();

    // Right connector
    glPushMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-1.47f, -1.5f);
    glVertex2f(-1.67f, -1.3f);
    glEnd();
    glPopMatrix();

    // Mid connector 
    glPushMatrix();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-1.67f, -1.5f);
    glVertex2f(-1.67f, -0.9f);
    glEnd();
    glPopMatrix();

    // Mid connector 
    glPushMatrix();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor4f(1.0, 1.0f, 1.0f, .95f);  // color #white
    glVertex2f(-1.85f, -1.0f);
    glVertex2f(-1.45f, -1.0f);
    glEnd();
    glPopMatrix();

    //seat 
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.93f, 0.76f, 0.56f, 1.0f);
    glVertex2f(-1.77f, -1.25f);
    glVertex2f(-1.57f, -1.25f);
    glVertex2f(-1.57f, -1.35f);
    glVertex2f(-1.77f, -1.35f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void truck() {
    // front glass frames
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.97f, 0.94f, 0.90f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-1.9f, 3.2f);  // top-left vertex
    glVertex2f(-0.5f, 3.2f);  // top-right vertex
    glVertex2f(-0.4f, 3.1f); // bottom-right vertex
    glVertex2f(-2.0f, 3.1f);  // bottom-left vertex
    glEnd();
    glPopMatrix();


    //  glass
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.86f, 0.91f, 0.98f, 1.0f);  // color #D9EAFD in OpenGL

    glVertex2f(-1.85f, 3.17f);  // top-left vertex
    glVertex2f(-0.6f, 3.17f);  // top-right vertex
    glVertex2f(-0.55f, 3.12f); // bottom-right vertex
    glVertex2f(-1.9f, 3.12f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // 1st box top
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.97f, 0.94f, 0.90f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-2.0f, 3.1f);  // top-left vertex
    glVertex2f(-0.4f, 3.1f);  // top-right vertex
    glVertex2f(-0.4f, 2.9f); // bottom-right vertex
    glVertex2f(-2.0f, 2.9f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // 2nd box top 
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.93f, 0.76f, 0.56f, 1.0f);
    glVertex2f(-2.04f, 2.9f);  // top-left vertex
    glVertex2f(-0.34f, 2.9f);  // top-right vertex
    glVertex2f(-0.34f, 2.55f); // bottom-right vertex
    glVertex2f(-2.05f, 2.55f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // 3rd box top
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.97f, 0.94f, 0.90f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-2.05f, 2.55f);  // top-left vertex
    glVertex2f(-0.34f, 2.55f);  // top-right vertex
    glVertex2f(-0.4f, 2.5f); // bottom-right vertex
    glVertex2f(-2.0f, 2.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // back box 
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.97f, 0.94f, 0.90f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-1.95f, 2.5f);  // top-left vertexF
    glVertex2f(-0.45f, 2.5f); // top-right vertex
    glVertex2f(-0.45f, 0.5f); // bottom-right vertex
    glVertex2f(-1.95f, 0.5f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    //back box inside box
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.39f, 0.38f, 0.38f, 1.0f);  // color #636262 in OpenGL

    glVertex2f(-1.9f, 2.45f);  // top-left vertex
    glVertex2f(-0.5f, 2.45f); // top-right vertex
    glVertex2f(-0.5f, 0.55f); // bottom-right vertex
    glVertex2f(-1.9f, 0.55f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    //back box inside inside box
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.97f, 0.94f, 0.90f, 1.0f);  // color #F6F4F0 in OpenGL

    glVertex2f(-1.87f, 2.42f);  // top-left vertex
    glVertex2f(-0.53f, 2.42f); // top-right vertex
    glVertex2f(-0.53f, 0.6f); // bottom-right vertex
    glVertex2f(-1.87f, 0.6f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

}
void levelinfobox() {
    // timer
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);  // color #F6F4F0 in OpenGL
    glVertex2f(-4.0f, 4.0f);  // top-left vertex
    glVertex2f(4.0f, 4.0f);  // top-right vertex
    glVertex2f(4.0f, 3.75f); // bottom-right vertex
    glVertex2f(-4.0f, 3.75f);  // bottom-left vertex
    glEnd();
    glPopMatrix();

    // Render level texts
    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(-1.51f, 3.82f, 0.0f, GLUT_BITMAP_HELVETICA_18, " Press R to restart");
    renderBitmapString(1.31f, 3.82f, 0.0f, GLUT_BITMAP_HELVETICA_18, " Press H to quit to menu");

    if (isCountdownFinished == 0) {
        char timerText[10];
        sprintf(timerText, "Time: %d", timer);  // Convert timer value to string
        renderText(-3.0f, 3.82f, GLUT_BITMAP_HELVETICA_18, timerText);  // Adjust position and font
    }

}
void gamescreen() {
    // frame 1
    glPushMatrix();
    glTranslatef(0.0f, move, 0.0f);  // Apply move variable
    Road();
    truck();
    Rickshaw();
    car();
    car2();
    van();
    glPopMatrix();

    // frame 2
    glPushMatrix();
    glTranslatef(0.0f, move + 8.0f, 0.0f);  // Apply move variable
    Road();
    truck();
    van();
    glTranslatef(0.6f, -3.0f, 0.0f);
    truck();
    glPopMatrix();

    // frame 3
    glPushMatrix();
    glTranslatef(0.0f, move + 16.0f, 0.0f);  // Apply move variable
    glRotatef(180, 0.0, 0.0, 0.0);
    Road();
    car();
    van();
    car2();
    glTranslatef(0.6f, -3.0f, 0.0f);
    truck();
    glPopMatrix();

    levelinfobox();
    player();
    checkCollisions();
    // Render now
}
void keyboard(unsigned char key, int x, int y) {
        switch (key) {
            // case 'w':  // Move up
            //     move -= playerSpeed;
            //     break;
            // case 's':  // Move down
            //     move += playerSpeed;
            //     break;
        case 'a':  // Move left
            playerX -= playerSpeed * 0.3f;  // Smaller increment for smoother transition
            break;
        case 'd':  // Move right
            playerX += playerSpeed * 0.3f;  // Smaller increment for smoother transition
            break;
        case 's':
            currentScreen=1;
            break;
    }

    switch (key) {

    case 'h':
        home();
        currentScreen = 0;
        break;

    case 'r':
        timer = a;  // Reset the timer
        isCountdownFinished = false;
        playerX = 0.0f;  // Reset player position
        playerY = -1.5f;
        move = 0.0f;
        // Restart the timer
       
        // else if (currentScreen == 2) {
        //     level2();
        // }
        // else if (currentScreen == 3) {
        //     level3();
        // }
        // break;
    }

    glutPostRedisplay();  // Update display
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (currentScreen == 0) {
        home(); // Render home 
    }
    else if (currentScreen == 1) {
        gamescreen();
      
    }
    else if (currentScreen == 3) {
        timeup();  // Display time up screen if countdown is finished
    }

    glutSwapBuffers(); // Double buffering

    glFlush();
}

void movement(int value) {
    if (move < 1 && move > -l1) {
        move -= screenmovement * 0.02f;  // Smaller increment for smoother transition
        glutPostRedisplay();  // Update display
        glutTimerFunc(16, movement, 0);  // Restart the timer with shorter interval
    }
    if (move < -l1 && move > -l1*2) {
        move -= screenmovement * 0.02f;  // Smaller increment for smoother transition
        glutPostRedisplay();  // Update display
        glutTimerFunc(16, movement, 0);  // Restart the timer with shorter interval
    }
    if (move < -l1*2 && move > -l1*4) {
        move -= screenmovement * 0.02f;  // Smaller increment for smoother transition
        glutPostRedisplay();  // Update display
        glutTimerFunc(16, movement, 0);  // Restart the timer with shorter interval
    }
    checkCollisions();  // Check collisions after movement
}

// Initialization function
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black
    glOrtho(-4, 4, -4, 4, -4, 4);          // Set up orthogonal projection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutTimerFunc(1000, timerFunc, 0);
    glutTimerFunc(16, movement, 0);  // Increase frequency of movement function calls
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowSize(700, 1000);          // Set the window's initial width & height
    glutInitWindowPosition(500, 0);        // Set the window's initial position
    glutCreateWindow("Late Again!!");  // Create window with the given title
    glutDisplayFunc(display);              // Register display callback handler for window re-paint
    glutKeyboardFunc(keyboard);            // Register keyboard callback
    initGL();                              // Initialize OpenGL settings
    glutMainLoop();                        // Enter the event-processing loop
    return 0;
}