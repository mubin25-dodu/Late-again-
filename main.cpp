#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <cstdio>

#define PI 3.14159265358979323846
int timer = 60;
bool isCountdownFinished = false;

GLfloat playerX = 0.0f;
GLfloat playerY = -1.5f;
GLfloat move = 0.0f;
GLfloat playerSpeed = 0.1f;

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':  // Move up
        move -= playerSpeed;
        break;
    case 's':  // Move down
        move += playerSpeed;
        break;
    case 'a':  // Move leftw
        playerX -= playerSpeed;
        break;
    case 'd':  // Move right
        playerX += playerSpeed;
        break;
    }
    glutPostRedisplay();  // Update display
}


void Road() {
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

}

void timerFunc(int value) {
    if (timer > 0) {
        timer--;
        glutPostRedisplay();  // Update display
        glutTimerFunc(1000, timerFunc, 0);  // Restart the timer
    }
    else {
        isCountdownFinished = true;
        glutPostRedisplay();  // Ensure "Time Up" message is displayed
    }
}
void renderText(float x, float y, void* font, const char* text) {
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color
    glRasterPos2f(x, y);          // Position the text
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void van() {
    // Back
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.52f, 0.37f, 0.26f, 0.9f);
    glVertex2f(1.9f, -0.8f);  // top-left vertex
    glVertex2f(0.6f, -0.8f);  // top-right vertex 
    glVertex2f(0.6f, -1.8f); // bottom-left vertex 
    glVertex2f(1.9f, -1.8f);  // bottom-right vertex 
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

    glFlush(); // Render now 

}
void Rickshaw() {

    glPushMatrix();
    glScalef(1.3f, 1.3f, 1.3f);
    glTranslatef(0.4f, 0.4f, 0.0f);

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
void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glPushMatrix();
    glTranslatef(0.0f, move + -4.0f, 0.0f);
    Road();
    truck();
    Rickshaw();
    van();
    glPopMatrix();
  

    glPushMatrix();
    glTranslatef(0.0f, move + 4.0f, 0.0f);
    Road();
    truck();
    Rickshaw();
    van();
    glPopMatrix();
    
    player();

    if (!isCountdownFinished) {
        char timerText[10];
        sprintf(timerText, "Time: %d", timer);  // Convert timer value to string
        renderText(-2.4f, 3.7f, GLUT_BITMAP_HELVETICA_18, timerText);  // Adjust position and font
    }
    else {
        renderText(-0.5f, 3.5f, GLUT_BITMAP_HELVETICA_18, "Time Up!");  // Message after countdown ends
    }

    glFlush();  // Render now
}



// Initialization function
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black
    glOrtho(-4, 4, -4, 4, -4, 4);          // Set up orthogonal projection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutTimerFunc(1000, timerFunc, 0);
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