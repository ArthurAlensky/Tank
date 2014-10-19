#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include "IncludeS.h"

// OpenGL Graphics includes
#include <GL\freeglut.h>

#include <iostream>
#include <cstdlib>
#include <time.h>



// Initial square position and size
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat height_track = 10;
GLfloat width_track = 60;

// Step size in x and y directions
// (number of pixels to move each time)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat wall_position = 60;
GLfloat wall_width = 20;
GLfloat wall_height = 40;

GLfloat break_x1 = 0;
GLfloat break_y1 = 0;

GLfloat break_x2 = 0;
GLfloat break_y2 = 0;

GLfloat break_x3 = 0;
GLfloat break_y3 = 0;

GLfloat barrel_height = 9;
GLfloat wheel_helt_width = 10;

// Keep track of windows changing width and height
GLfloat windowWidth;
GLfloat windowHeight;


void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

void drawFilledSun(float x, float y, float radius){
    double twicePi = 2.0 * 3.142;
    glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= 20; i++)   {
        glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
            );
    }
    glEnd(); //END
}

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	glColor3f(0.3f, 0.3f, 0.3f);

	glRectf(x + 10, y + 15, x + width_track * 0.5, y + 5); // tower

	glColor3f(0.3f, 0.5f, 0.5f);

	glRectf(x + 10, y + barrel_height + 3, x - width_track * 0.5, y + barrel_height); // barrel

	glColor3f(1.0f, 1.0f, 0.0f);

	glRectf(x, y + 5, x + width_track * 0.75, y - height_track); //body

	glBegin(GL_TRIANGLES); // body helt
		// Lower left vertex
		glVertex2f(x - 5.0f, y);
		// Lower right vertex
		glVertex2f( x, y);
		// Upper vertex
		glVertex2f( x, y + 5);

		// Lower left vertex
		glVertex2f(x + width_track * 0.75, y);
		// Lower right vertex
		glVertex2f( x + width_track * 0.75  + 3.0f, y);
		// Upper vertex
		glVertex2f( x + width_track * 0.75, y + 5);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);

	glRectf(x + width_track * 0.75 + 5, y + 1, x  + width_track * 0.75 + width_track * 0.3, y); // engine

	glColor3f(1.0f, 1.0f, 1.0f);

	glRectf(x, y, x + width_track, y - height_track); //wheels

	// Draw a triangle:
	glBegin(GL_TRIANGLES); // helt on wheels

		// Lower left vertex
		glVertex2f(x - wheel_helt_width, y);
		// Lower right vertex
		glVertex2f( x, y);
		// Upper vertex
		glVertex2f( x, y - height_track);

		// Lower left vertex
		glVertex2f(x + width_track, y);
		// Lower right vertex
		glVertex2f( x + width_track  + wheel_helt_width, y);
		// Upper vertex
		glVertex2f( x + width_track, y - height_track);

	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);

	DrawCircle(x - 1, y - 3, 3, 100);

	DrawCircle(x + 6, y - 5, 4, 100);

	DrawCircle(x + 16, y - 5, 4, 100);

	DrawCircle(x + 26, y - 5, 4, 100);

	DrawCircle(x + 36, y - 5, 4, 100);

	DrawCircle(x + 46, y - 5, 4, 100);

	DrawCircle(x + 56, y - 5, 4, 100);

	DrawCircle( x + 63, y - 3, 3, 100);

	drawFilledSun(x - 1, y - 3, 2);

	drawFilledSun(x + 6, y - 5, 3);

	drawFilledSun(x + 16, y - 5, 3);

	drawFilledSun(x + 26, y - 5, 3);

	drawFilledSun(x + 36, y - 5, 3);

	drawFilledSun(x + 46, y - 5, 3);

	drawFilledSun(x + 56, y - 5, 3);

	drawFilledSun( x + 63, y - 3, 2);

	glColor3f(0.50f, 0.50f, 0.0f);
	if( x - width_track * 0.5 <= -wall_position)
	{
		wall_height = barrel_height;

		glLoadIdentity();
		glPushMatrix();

		glTranslatef(break_x1--, break_y1++,0);
		glRotatef( -break_x1 * 2, 0, 0, 1);
			glBegin(GL_TRIANGLES); // helt on wheels
				// Lower left vertex
				glVertex2f(-wall_position - wall_width/2, 10);
				// Lower right vertex
				glVertex2f( -wall_position - wall_width/2, 20);
				// Upper vertex
				glVertex2f( -wall_position - wall_width/2 - 20, 0);
			glEnd();
		glPopMatrix();

		glLoadIdentity();
		glPushMatrix();

		glTranslatef(break_x2++, break_y2--,0);
		glRotatef( break_x2 * 2, 0, 0, 1); 
			glBegin(GL_TRIANGLES); // helt on wheels
				// Lower left vertex
				glVertex2f(-wall_position - wall_width/2, 5);
				// Lower right vertex
				glVertex2f( -wall_position - wall_width/2 + 5, 18);
				// Upper vertex
				glVertex2f( -wall_position - wall_width/2 - 10, 0);
			glEnd();
		glPopMatrix();

		glLoadIdentity();
		glPushMatrix();

		glTranslatef(-break_x3--, -break_y3++,0);
		glRotatef( break_x3 * 2, 0, 0, 1);
			glRectf(-wall_position - wall_width/2, 15, -wall_position - wall_width/2 - 10, 25); //body
		glPopMatrix();
	}

	if( x - wheel_helt_width <= -wall_position)
	{
		wall_height = -10;
	}

	glLoadIdentity();
		glPushMatrix();
			glColor3f(0.50f, 0.50f, 0.0f);
			glRectf(- wall_position - wall_width ,wall_height, -wall_position, -10); // wall
		glPopMatrix();

		glColor3f(0.50f, 0.90f, 0.0f);
		glRectf(-windowWidth,  - 10, windowWidth, -windowHeight); //body
	// Flush drawing commands and swap
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
{

	// Actually move the square
	   x -= xstep;
	// Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction, 1);
}


///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
{
	// Set clear color to blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}


///////////////////////////////////////////////////////////
// Called by GLUT library when the window has chanaged size
void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) 
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else 
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

///////////////////////////////////////////////////////////
// Main program entry point
int main_diabled(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);

	SetupRC();

	glutMainLoop();

	return 0;
}
