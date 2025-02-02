#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <cstdio>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <string>
#include<MMSystem.h>  // For PlaySound

#define PI 3.1416
int a = 60;
int timer = a;
GLfloat pspeed = 00.50; // playerx shift speed
int currentScreen = 0;
GLfloat playerX = 0.0f;
GLfloat playerY = -1.5f;
GLfloat move = 0.0f;
int level = 1;
float sm = 1.1; //movement
GLfloat screenmovement = sm;
GLfloat playerSpeed = pspeed;
int health = 100;
float truckLeft, truckRight, truckTop, truckBottom;
bool isCountdownFinished = false;
bool stop = true, jump = false;

std::string instructions[] = {
    "Objective: Reach the finish line before time runs out!",
    "Controls:",
    "    - Move Left: Press A",
    "    - Move Right: Press D",
    "    - Jump: Spacebar",
    "    - Restart: R",
    "    - Home Menu: H",
    "Press S to Start Game",
     "  ",
    "--------------------------------------------------",
    "Avoid cars, trucks, and rickshaws. Don't get hit!",
    "You will lose health if you crash, and distance will be increased.",
    "If you lose 100% of your health, you will die...",
    "and guess what? You'll never be LATE AGAIN!!",
   
    "--------------------------------------------------",
    "     ",
    "Successfully cross the finish line without running out of time.",
    "Good luck! Don't be LATE AGAIN!!"
    };
   
int currentChar = 0;
int currentLine = 0;
void renderBitmapString(float x, float y, void* font, const char* string, int length) {
    glRasterPos2f(x, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}
void renderBitmapString(float x, float y, float z, void* font, const char* string) {
    const char* c;
    glRasterPos3f(x, y, z);  // Position the text
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);  // Render each character
    }
}
bool showNotification = false;

void renderNotification() {
    if (showNotification) {
        glColor3f(1.0f, 1.0f, 1.0f);  // Red color for notification
        renderBitmapString(-1.80f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18,"Collision Detected! Health Decreased.");
    }

}

void clearNotification(int) {
    showNotification = false;
    glutPostRedisplay();
}

void colfeature() {
    if (health > 0) {
        health -= 25;
        playerSpeed = pspeed;
        if (move > -10) {
            while (move < 0) {
                move += 0.01f;
            }
            playerX = 0.0f;
            playerY = -1.5f;
        }
        else {
            health -= 15;
            playerSpeed = pspeed;
            move += 10.0f;
            playerX = 0.0f;
            playerY = -1.5f;
        }
    }
    if (health < 1) {
        currentScreen = 4;
        stop = true;
    }
  
    showNotification = true;
    glutTimerFunc(2000, clearNotification, 0);  // Clear notification after 2 seconds
    glutPostRedisplay();
}

void home() {

    // Background Color
    glColor3f(0.2f, 0.3f, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0f, -4.0f);
    glVertex2f(4.0f, -4.0f);
    glVertex2f(4.0f, 4.0f);
    glVertex2f(-4.0f, 4.0f);
    glEnd();
    
    // Title Typing Animation
    glColor3f(1.0f, 1.0f, 0.0f);
    renderBitmapString(-3.01f, 3.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, " LATE AGAIN!!");


    // Instructions Typing Animation
    glColor4f(1.0f, 1.0f, 1.0f,0.8f); 
    for (int i = 0; i <= currentLine; i++) {
        int length = (i == currentLine) ? currentChar : instructions[i].length();
        renderBitmapString(-3.5f, 2.5f - (i * 0.3f), GLUT_BITMAP_HELVETICA_18, instructions[i].c_str(), length);
    }
    
    glFlush();
}

void typing(int) {
    if (currentLine < 18 && stop==true) {
        if (currentChar < instructions[currentLine].length()) {
            currentChar++;
        }
        else {
            currentChar = 0;
            currentLine++;
        }
        glutPostRedisplay();
        glutTimerFunc(50, typing, 0);
    }
}


void timeup() {
      // Background Color
    glColor4f(1.0f, 0.1f, 0.1f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0f, -4.0f);
    glVertex2f(4.0f, -4.0f);
    glVertex2f(4.0f, 4.0f);
    glVertex2f(-4.0f, 4.0f);
    glEnd();

    glColor3f(0.15f, 0.25f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-3.950f, -3.95f);
    glVertex2f(3.95f, -3.95f);
    glVertex2f(3.95f, 3.95f);
    glVertex2f(-3.95f, 3.95f);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 0.0f); // White color for text
    renderBitmapString(-3.5f, 3.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "YOU ARE LATE AGAIN!!...");
    glColor3f(1.0f, 1.0f, 0.0f); // White color for text
    renderBitmapString(-3.5f, 3.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "------------------------------");
    glColor3f(1.0f, 0.0f, 0.0f); 
    renderBitmapString(-3.5f, 2.7f, 0.0f, GLUT_BITMAP_HELVETICA_18,"Looks like you took the scenic route... to FAILURE");
    renderBitmapString(-3.5f, 2.2f, 0.0f, GLUT_BITMAP_HELVETICA_18,  "Press  R to Restart Game");
    renderBitmapString(-3.5f, 1.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press H to Home");
     renderBitmapString(-3.5f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Life saving tips...");
     renderBitmapString(-3.5f, 0.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "   Next time, try teleportation. It's still in beta testing, though");
    glPopMatrix();
}
void finish() {
      // Background Color
    glColor4f(1.0f, 0.1f, 0.1f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0f, -4.0f);
    glVertex2f(4.0f, -4.0f);
    glVertex2f(4.0f, 4.0f);
    glVertex2f(-4.0f, 4.0f);
    glEnd();

    glColor3f(0.15f, 0.25f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-3.950f, -3.95f);
    glVertex2f(3.95f, -3.95f);
    glVertex2f(3.95f, 3.95f);
    glVertex2f(-3.95f, 3.95f);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 0.0f); // White color for text
    renderBitmapString(-3.5f, 3.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "CONGRATULATION   SO,  YOU ARE !!LATE AGAIN  THIS  TIME...");
    glColor3f(1.0f, 1.0f, 0.0f); // White color for text
    renderBitmapString(-3.5f, 3.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "------------------------------");
    glColor4f(1.0f, 1.0f, 1.0f,0.8f); 
    renderBitmapString(-3.5f, 2.7f, 0.0f, GLUT_BITMAP_HELVETICA_18,"You did it! ");
    renderBitmapString(-3.5f, 2.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press  R to Restart Game");
    renderBitmapString(-3.5f, 1.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press H to Home");
     renderBitmapString(-3.5f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Life saving tips...");
     renderBitmapString(-3.5f, 0.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "   Now don't get too confident… tomorrow is another battle!");
     glPopMatrix();
     
}
void colpage() {
//      std::string collition[] = {
//     "THIS TIME... THIS TIME YOU ARE !LATE AGAIN.. YOU ARE LATE..",
//     "-",
//     "Press S or R to Start Game",
//     "     oh wait, you're dead. Unless you're a ghost, then go ahead!",
//     "Press H to Home",
//     "Close the window and forget about being late—time is just a suggestion anyway!"
    
// };
    // Background Color
    glColor4f(1.0f, 0.1f, 0.1f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0f, -4.0f);
    glVertex2f(4.0f, -4.0f);
    glVertex2f(4.0f, 4.0f);
    glVertex2f(-4.0f, 4.0f);
    glEnd();

    glColor3f(0.15f, 0.25f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-3.950f, -3.95f);
    glVertex2f(3.95f, -3.95f);
    glVertex2f(3.95f, 3.95f);
    glVertex2f(-3.95f, 3.95f);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 0.0f); // White color for text
    renderBitmapString(-3.5f, 3.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "THIS TIME YOU ARE !LATE AGAIN... YOU ARE LATE...");
    glColor3f(1.0f, 1.0f, 0.0f); // White color for text
    renderBitmapString(-3.5f, 3.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "-------------------------------------------------");
    glColor3f(1.0f, 0.0f, 0.0f); 
    renderBitmapString(-3.5f, 2.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press  R to Restart Game");
    renderBitmapString(-3.5f, 2.2f, 0.0f, GLUT_BITMAP_HELVETICA_18, "     oh wait, you're dead. Unless you're a ghost, then go ahead!");
    renderBitmapString(-3.5f, 1.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Press H to Home");
     renderBitmapString(-3.5f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Life saving tips...");
     renderBitmapString(-3.5f, 0.7f, 0.0f, GLUT_BITMAP_HELVETICA_18, "    Close the window and forget about being late...");
    renderBitmapString(-3.5f, 0.4f, 0.0f, GLUT_BITMAP_HELVETICA_18, "     time is just a suggestion anyway!!");
    glPopMatrix();

//    glColor3f(1.0f, 1.0f, 1.0f);
//     for (int i = 0; i <= currentLine; i++) {
//         int length = (i == currentLine) ? currentChar : collition[i].length();
//         renderBitmapString(-3.5f, 2.5f - (i * 0.5f), GLUT_BITMAP_HELVETICA_18, collition[i].c_str(), length);
//     }
    
    glFlush();
}
    void timerFunc(int value) {
    if (timer > 0) {
        timer--;
          if (health < 30) {
        health+=1;
    }
        glutPostRedisplay();  // Update display
        glutTimerFunc(1000, timerFunc, 0);  // Restart the timer
    }
  
    else {
        currentScreen = 3;
        glutPostRedisplay();  // Ensure "Time Up" message is displayed
    }

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
    return !(obj1Left > obj2Right || obj1Right < obj2Left ||
        obj1Top < obj2Bottom || obj1Bottom > obj2Top);
}
void drawBoundingBox(float left, float right, float top, float bottom, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, top);
    glVertex2f(right, top);
    glVertex2f(right, bottom);
    glVertex2f(left, bottom);
    glEnd();
}
void checkCollisions() {
    // Player bounding box
    float playerLeft = playerX;
    float playerRight = playerX;
    float playerTop = playerY;
    float playerBottom = playerY;

    // Van bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.6f, 2.4f, -1.0f + move, -2.1f + move)) {
        colfeature();
    }

    // Van1 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.3f, 2.1f, 12.0f + move, 10.9f + move)) {
         colfeature();
    }

    // Van2 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.6f, 2.2f, -0.8f + move + 48, -1.8f + move + 48)) {
          colfeature();

    }
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.0f, 1.75f, -2.95f + move + 8, -5.05f + move + 8)) {
        // Car2 collision
      colfeature();
    }

    // Car2 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.0f, 1.35f, -2.95f + move + 48, -5.05f + move + 48)) {
        // Car2 collision
          colfeature();
    }

    // Car2 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.0f, 1.35f, -2.95f + move + 64, -5.05f + move + 64)) {
          colfeature();
    }

    // Truck bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.34f, 2.5f, -0.6f + move + 32, -3.4f + move + 32)) {
         colfeature();
    }
    // Truck1 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.34f, 2.5f, -0.6f + move + 40, -3.4f + move + 40)) {
      colfeature();
    }

    // Truck2 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.34f, 2.5f, -0.6f + move + 56, -3.4f + move + 56)) {
         colfeature();
    }

    // Truck3 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.34f, 2.5f, -0.6f + move + 72, -3.4f + move + 72)) {
      colfeature();
    }

    // Truck4 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.34f + 0.35f, 2.5f + 0.35f, -0.6f + move + 80, -3.4f + move + 80)) {
       colfeature();
    }

    // Truck5 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.34f, 2.5f, -0.6f + move + 88, -3.4f + move + 88)) {
     colfeature();
    }

    // Rickshaw1 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.85f, 2.7f, 1.35f + move + 24, 1.7f - 0.5f + move + 24)) {
      colfeature();
    }

    // Rickshaw2 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.85f, 2.5f, 1.35f + move + 40, 0.7f - 0.5f + move + 40)) {
        colfeature();
    }
   
    // Rickshaw3 bounding box
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 0.85f, 2.7f, 1.35f + move + 16, 0.7f - 0.5f + move + 16)) {
       colfeature();
    }

    //   car 1
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 1.25f, 2.7f, -.70f + move + 16, -3.0f + move + 16)) {
       colfeature();
    }
    // car 2
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, 1.25f, 2.7f, -.70f + move + 24, -3.0f + move + 24)) {
        colfeature();
    }
    // left truck
// Calculate m
    float m = -move * 0.20f;
    // Check collisions for the first call
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.25f, -0.34f, 2.7f + m, 0.0f + m)) {
       colfeature();
    }

    // Check collisions for the second call
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.25f + 0.6f, -0.34f + 0.6f, 3.0f - move * 0.20f - 13, 0.1f - move * 0.20f - 13)) {
        colfeature();
    }
    // Check collisions for the left 2nd truck
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.8f, -0.85f, -6.75f + m, -9.42f + m)) {
        colfeature();
    }

    // left car
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.35f, -0.34f, -.4f + m, -2.5f + m)) {
        colfeature();
    }

    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.35f - .6, -0.34f - .7, -.4f + m - 13, -2.5f + m - 13)) {
        colfeature();
    }
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, +.4-2.35f - .6, -0.34f+4 - .7, -.4f + m - 13-7, -2.5f + m - 13-7)) {
        colfeature();
    }
    // left van

    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.00f, 0.0f, -3.5f + m, -4.8f + m)) {
          colfeature();
    }
   // Finish line bounding box
    float finishLineY = 50.0f + move / 2;
    if (isCollision(playerLeft, playerRight, playerTop, playerBottom, -2.4f, 2.4f, finishLineY + 0.1f, finishLineY - 0.1f)) {
        currentScreen = 5;
    }

    if (playerX > 2.75) {
        playerX = 2.75;
    }
    if (playerX < -2.75) {
        playerX = -2.75;
    }
}

void car() {
    glPushMatrix();
    glTranslated(-1.0, 2.5, 0.0f);  // Translate to the position
    glRotated(180.0, 0.0, 0.0, 1.0);
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

    // Car body (main part)
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    glRectd(0, -3.925, 1.35, -2.95);  // Adjusted main body of the car

    // Car windows (light blue color)
    glColor3f(0.68f, 0.85f, 0.90f);
    glRectd(0.3375, -3.7375, 1.0125, -3.2625);

    glBegin(GL_LINES);
    glColor3f(0.68f, 0.85f, 0.90f);
    glVertex2d(0.3375, -3.5875);
    glVertex2d(1.0125, -3.5875);
    glEnd();

    // Roof (red color)
    glColor3f(1.0f, 0.0f, 0.0f);  // Red roof
    glBegin(GL_QUADS);
    glVertex2d(0.1125, -2.825);
    glVertex2d(1.2375, -2.825);
    glVertex2d(1.35, -2.95);
    glVertex2d(0, -2.95);
    glEnd();

    // Car bottom (green color)
    glColor3f(0.0f, 1.0f, 0.0f);  // Green bottom
    glBegin(GL_QUADS);
    glVertex2d(0, -3.925);
    glVertex2d(1.35, -3.925);
    glVertex2d(1.17, -4.7);
    glVertex2d(0.18, -4.7);
    glEnd();

    // Additional details (black color)
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectd(0.3825, -3.71, 0.9, -3.605);
    glRectd(0.675, -3.71, 0.99, -3.605);
    glRectd(0.315, -3.425, 0.81, -3.145);
    glRectd(0.675, -3.425, 1.035, -3.145);

    glPopMatrix();
}

void van() {
    // Back
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.1f, 0.1f);
    glVertex2f(1.9f, -0.8f);  // top-left vertex
    glVertex2f(0.6f, -0.8f);  // top-right vertex
    glVertex2f(0.6f, -1.8f);  // bottom-right vertex
    glVertex2f(1.9f, -1.8f);  // bottom-left vertex
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

void truck()  {
    // front glass frames 
    glPushMatrix();
   
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


    // Render level textsFFF
    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(-1.01f, 3.82f, 0.0f, GLUT_BITMAP_HELVETICA_18, "             Press R to restart");
    renderBitmapString(1.31f, 3.82f, 0.0f, GLUT_BITMAP_HELVETICA_18, "      Press H to quit to menu");
    char levelText[10];
    sprintf(levelText, "Level %d", level);
    renderBitmapString(-3.90f, 3.82f, 0.0f, GLUT_BITMAP_HELVETICA_18, levelText);
    if (health < 50) {
       
       char healtht[10]; glColor3f(1.0f, 0.0f, 0.0f);
        sprintf(healtht, "Health: %d", health);  // Convert timer value to string
        renderText(-1.5f, 3.82f, GLUT_BITMAP_HELVETICA_18, healtht);
    }
    else {
         char healtht[10];glColor3f(1.0f, 1.0f, 1.0f);
        sprintf(healtht, "Health: %d", health);  // Convert timer value to string
        renderText(-1.5f, 3.82f, GLUT_BITMAP_HELVETICA_18, healtht);
    } 

    if (!isCountdownFinished) {
        if (timer < 50) {
          
            char timerText[10];  glColor3f(1.0f, 0.0f, 0.0f);
            sprintf(timerText, "Time: %d", timer);  
            renderText(-2.8f, 3.82f, GLUT_BITMAP_HELVETICA_18, timerText); 
        }
        else {
           
            char timerText[10]; glColor3f(1.0f, 0.0f, 0.0f);
            sprintf(timerText, "Time: %d", timer);  
            renderText(-2.8f, 3.82f, GLUT_BITMAP_HELVETICA_18, timerText);  
        }

    }
}


void manhole() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark gray color

    // Draw the outer circle
    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    GLfloat radius = 0.05f;
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);  // Center of the circle
    for (int i = 0; i <= numSegments; i++) {
        GLfloat angle = 2.0f * PI * i / numSegments;
        glVertex2f(x + (radius * cos(angle)), y + (radius * sin(angle)));
    }
    glEnd();

    // Draw the inner circle (manhole cover)
    glColor3f(0.4f, 0.4f, 0.4f);  // Lighter gray color
    radius = 0.25f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);  // Center of the circle
    for (int i = 0; i <= numSegments; i++) {
        GLfloat angle = 2.0f * PI * i / numSegments;
        glVertex2f(x + (radius * cos(angle)), y + (radius * sin(angle)));
    }
    glEnd();

    // Draw the lines on the manhole cover
    glColor3f(0.2f, 0.2f, 0.2f);  // Darker gray color
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < numSegments; i += 10) {
        GLfloat angle = 2.0f * PI * i / numSegments;
        glVertex2f(x + (radius * cos(angle)), y + (radius * sin(angle)));
        glVertex2f(x - (radius * cos(angle)), y - (radius * sin(angle)));
    }
    glEnd();

    glPopMatrix();
}
void FinishLine() {
    int numStripes = 30; // Number of black and white stripes
    float xEnd = 2.4f; // Y-coordinate of the finish line
    float xStart = -2.4f;
    float y = 50 + move / 2; // Y-coordinate of the finish line

    float stripeWidth = (xEnd - xStart) / numStripes;

    for (int i = 0; i < numStripes; i++) {
        float x1 = xStart + i * stripeWidth;
        float x2 = x1 + stripeWidth;

        // Alternate black and white stripes
        if (i % 2 == 0) {
            glColor4f(0.0f, 0.0f, 0.0f, 0.7); // Black
        } else {
            glColor4f(1.0f, 1.0f, 1.0f, 0.7); // White
        }
        glBegin(GL_QUADS);
        glVertex2f(x1, y - 0.1f); // Bottom-left
        glVertex2f(x2, y - 0.1f); // Bottom-right
        glVertex2f(x2, y + 0.1f); // Top-right
        glVertex2f(x1, y + 0.1f); // Top-left
        glEnd();
    }

    // Draw the bounding box for the finish line
    drawBoundingBox(xStart, xEnd, y + 0.1f, y - 0.1f, 1.0f, 1.0f, 1.0f); // Yellow color

  

}
void level1() {
    // frame 1
    glPushMatrix();
    glTranslatef(0.0f, move, 0.0f);
    car2();
    van();
    glPopMatrix();

    // frame 2
    glPushMatrix();
    glTranslatef(0.0f, move + 8.0f, 0.0f);
    car2();
    glTranslatef(-0.3f, 5.0f, 0.0f);
    van();
    glPopMatrix();

    // frame 3
    glPushMatrix();
    glTranslatef(0.0f, move + 16.0f, 0.0f);
    glScalef(-1.0f, -1.0f, 0.0f);
    Rickshaw();
    car();
    glPopMatrix();

    // frame 4
    glPushMatrix();
    glTranslatef(0.0f, move + 24.0f, 0.0f);
    glScalef(-1.0f, -1.0f, 0.0f);
    Rickshaw();
    car();
    glPopMatrix();
}

void level2() {

    // frame 1
    glPushMatrix();
    glTranslatef(0.0f, move + 32.0f, 0.0f);
    glScalef(-1.0f, -1.0f, 0.0f);
    truck();
    glPopMatrix();

    // frame 2
    glPushMatrix();
    glTranslatef(0.0f, move + 40.0f, 0.0f);
    glScalef(-1.0f, -1.0f, 0.0f);
    truck();
    Rickshaw();
    glPopMatrix();

    // frame 3
    glPushMatrix();
    glTranslatef(0.0f, move + 48, 0.0f);
    car2();
    glPopMatrix();

    //  frame 4 
    glPushMatrix();
    glTranslatef(0.0f, move + 56.0f, 0.0f);
    glScalef(-1.0f, -1.0f, 0.0f);
    truck();
    glPopMatrix();

    // New frame 5
    glPushMatrix();
    glTranslatef(0.0f, move + 64.0f, 0.0f);
    car2();
    glPopMatrix();
}

void level3() {
    // frame 1
    glPushMatrix();
    glTranslatef(0.0f, move + 72, 0.0f);  // Apply move variable
    glScalef(-1.0f, -1.0f, 0.0f);
    truck();
    glPopMatrix();

    // frame 3
    glPushMatrix();
    glTranslatef(0.0f, move + 80.0f, 0.0f);
    glScalef(-1.0f, -1.0f, 0.0f);
    glTranslatef(-0.3f, -0.0f, 0.0f);
    truck();
    glPopMatrix();

    // frame 2
    glPushMatrix();
    glTranslatef(0.0f, move + 88.0f, 0.0f);  
    glScalef(-1.0f, -1.0f, 0.0f);
    truck();
    Rickshaw();
    glPopMatrix();

}

void roadmove() {
    for (int b = 0; b < 100; b += 8) {
        glPushMatrix();
        glTranslatef(0.0f, move / 2 + b, 0.0f);
        Road();
        if (level == 3) {
            manhole();
            if (!jump) {
                if (isCollision(
                    playerX - 0.1f, playerX + 0.1f,  
                    playerY + 0.1f, playerY - 0.1f,  
                    -0.25f, 0.25f,                     
                    -0.2f + move / 2 + b,              
                    -0.5f + move / 2 + b            
                )) {
                    stop = true;
                    currentScreen = 4;
                }
            }
        }
        glPopMatrix();
    }
}

void leftmovement() {
    float m = -move * 0.20f;
    glPushMatrix();
    glTranslatef(0.0f, m, 0.0f);  // Apply move variable
    truck();
    glTranslatef(0.6f, -2.7f, 0.0f);
    car();
    glTranslatef(-1.0f, -7.0f, 0.0f);
    truck();
    glScalef(-1.0f, -1.0f, 0.0f);
    glTranslatef(-1.0f, -4.5f, 0.0f);
    van();
    checkCollisions();
    glPopMatrix();

    if (m >= 4) {
        glPushMatrix();
        glTranslatef(0.6f, -move * 0.20f - 13, 0.0f);
        truck();  
        glTranslatef(-0.6f, -2.7f, 0.0f);
        car();
        glTranslatef(1.0f, -7.0f, 0.0f);
        car();
        glPopMatrix();
    }
}

void gamescreen() {
    roadmove();
    if (move <= -32.0f && move >= -72.0f) {
        level = 2;
    }
    else if (move <= -72.0f) {
        level = 3;
    }
    else {
        level = 1;
    }

    if (level == 1) {
        level1();
        level2();
    }
    else if (level == 2) {
        level2();
        level3();
    }
    else if (level == 3) {
        level3();
    }
    leftmovement();
    FinishLine();
    player();
    
    checkCollisions(); // Ensure collisions are checked after rendering all frames
}

void movement(int value) {
    if (!stop) { 
        if (level == 1) {
            move -= screenmovement * 0.02f;  // Smaller increment for smoother transition
            glutPostRedisplay();  // Update display
            glutTimerFunc(16, movement, 0);  // Restart the timer with shorter interval
        }
        if (level == 2 || level == 3) {
            move -= screenmovement * 0.04f;
            playerSpeed=pspeed/2;// Smaller increment for smoother transition
            glutPostRedisplay();  // Update display
            glutTimerFunc(16, movement, 0);  // Restart the timer with shorter interval
        }
    }
}
void reset() {
    timer = a;  // Reset the timer
    isCountdownFinished = false;
    playerSpeed = pspeed;
    move = 0.0f;
    screenmovement = sm;
    playerX = 0.0f;
    playerY = -1.5f;
    health = 100;
    stop = false; // Stop
    movement(stop);

}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // case 'q':  // Move left
        //     move -= .2;
        //     ll = -2.3;
        //     break;
        // case 'e':  // Move right
        //     move += .2;
        //     ll = 2.3;
        //     break;
    case ' ':  // Jump forward
        if (level == 3 && !jump) {
            jump = true;
            playerY -= 0.2f;  
            glutTimerFunc(1000, [](int) { jump = false; playerY += 0.2f; glutPostRedisplay(); }, 0);  // Reset jump 
        }
        break;
    case 'a':  // Move left
        if (currentScreen != 0) {
            playerX -= playerSpeed;
        }
        break;
    case 'd':  // Move right
        if (currentScreen != 0) {
            playerX += playerSpeed;
        }
        break;

    case 's':
        if (currentScreen == 0 && currentLine >17 ) {
            reset();
            currentScreen = 1;
        }
        break;

    case 'h':
        home();
        stop = true;
        reset();
        currentScreen = 0;
        break;

    case 'r':
        if (currentScreen != 0) {
            reset();
            currentScreen = 1;
        }
        break;
    }

    glutPostRedisplay();  // Update display
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    
    if (currentScreen == 0) {
        home(); // Render home 
        timer = 100000;
        isCountdownFinished = true;
        showNotification = false;   
    }
    else if (currentScreen == 1) {
        gamescreen();
        levelinfobox();
    }
    else if (currentScreen == 3) {
        timeup();
        isCountdownFinished = true;    
        showNotification = false;   
    }
    else if (currentScreen == 4) {
        colpage();
        isCountdownFinished = true;   
        showNotification = false;   
    }
        else if (currentScreen == 5) {
        finish();
        isCountdownFinished = true;   
        showNotification = false;   
    }
    renderNotification();  // Render notification if needed
    checkCollisions(); // Check collision
    glutSwapBuffers(); // Double buffering
}

// Initialization function
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black
    glOrtho(-4, 4, -4, 4, -4, 4);          // Set up orthogonal projection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutTimerFunc(1000, timerFunc, 0);
    glutTimerFunc(16, movement, 0);  // Increase frequency of movement function calls
    glutTimerFunc(100, typing, 0);   // Start the typing animation timer
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffering
    glutInitWindowSize(700, 1000);          // Set the window's initial width & height
    glutInitWindowPosition(500, 0);        // Set the window's initial position
    glutCreateWindow("Late Again!!");  // Create window with the given title
    glutDisplayFunc(display);              // Register display callback handler for window re-paint
    glutKeyboardFunc(keyboard);            // Register keyboard callback
    initGL();                              // Initialize OpenGL settings
    glutMainLoop();                        // Enter the event-processing loop
    return 0;
}
