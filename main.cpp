#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

// Function to draw the X and Y axes in the top-left section
void Road() {
    glPushMatrix();
    // glLineWidth(2);
    glBegin(GL_QUADS);
    glColor4f(0.52f, 0.52f, 0.52f, 0.5f);  //  color gray with 50% transparency

    glVertex2f(-2.5f, 4.0f);
    glVertex2f(-2.5f, -4.0f);
    glVertex2f(2.5f, -4.0f);
    glVertex2f(2.5f, 4.0f);
    glEnd();
    glPopMatrix();

    // top line
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //  color white with 50% transparency

    glVertex2f(-0.08f, 4.0f);
    glVertex2f(-0.08f, 3.0f);
    glVertex2f(0.08f, 3.0f);
    glVertex2f(0.08f, 4.0f);
    glEnd();
    glPopMatrix();

    // mid line
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //  color white with 50% transparency

    glVertex2f(-0.08f, 1.0f);
    glVertex2f(-0.08f, -1.0f);
    glVertex2f(0.08f, -1.0f);
    glVertex2f(0.08f, 1.0f);
    glEnd();
    glPopMatrix();
    // bottom line
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //  color white with 50% transparency

    glVertex2f(-0.08f, -4.0f);
    glVertex2f(-0.08f, -3.0f);
    glVertex2f(0.08f, -3.0f);
    glVertex2f(0.08f, -4.0f);
    glEnd();
    glPopMatrix();

}



void player() {

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

    // 2nd box top (with a different color)
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0.93f, 0.76f, 0.56f, 1.0f);  // color (Brown) - A warm, earthy color that complements the truck's design

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
    Road();
    truck();
    // Draw each shape in a separate section

    glFlush();  // Render now
}


// Initialization function
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black
    glOrtho(-4, 4, -4, 4, -4, 4);          // Set up orthogonal projection
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowSize(700, 1000);          // Set the window's initial width & height
    glutInitWindowPosition(500, 0);        // Set the window's initial position
    glutCreateWindow("OpenGL Separate Shapes");  // Create window with the given title
    glutDisplayFunc(display);              // Register display callback handler for window re-paint
    initGL();                              // Initialize OpenGL settings
    glutMainLoop();                        // Enter the event-processing loop
    return 0;
}