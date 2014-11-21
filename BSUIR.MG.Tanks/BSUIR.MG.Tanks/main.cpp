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

#include "GLTools.h"
#include "Global.h"
#include "common.h"
#include "Camera.h"
#include "Texture.h"
#include "Terrain.h"
#include "Tank.h"
#include "Brick.h"
#include "Wall.h"

#include "CollisionSquare.h"
#include "CollisionBox.h"
#include "CollisionBoxArray.h"

// This tells us if we want detail texturing turned on or off
bool g_bDetail;

// This holds the current tile scale value for our detail texture
int g_DetailScale;

int g_ViewMod = GL_TRIANGLES;					// We want the default drawing mode to be normal

int angleWithX = 1;

//global variables
static int gWinWidth = 1200;
static int gWinHeight = 600;
static unsigned int gViewMode = 0;
static float gTimeStep = 0.6;
static float gMoveDelta = 2.0;
static float gAngleTankDelta = 1.0;
static float gAngleGunDelta = 5.0;
static float gBombVelocityMagDelta = 0.4;
static float gBombVelocityMag = 2.0;
static float gAutoBombVelocityMag = 1.8;
static float gAirPlaneVelocityMag = 1.0;

static float gFogDensity = 0.0025;

static TVector gAcceleBomb(0.0, -0.02, 0.0);
static float gRadViewAngle;
static TVector gCameraPosition;
static TVector gCenterPoint(mapX*mapScale*0.5, 5.0,  -mapZ * mapScale*0.5);

static float tankHeightPos;

CollisionSquare groundCollSquare;
CollisionBoxArray collisionBoxArray;
Terrain myTerrain(true, 16);
Tank myTank;
Wall wall;

#define NUM_BRICKS 100

#define SLOWDOWN 0.3

Camera camera(gCenterPoint.X(), 30.0, gCenterPoint.Z(), gCenterPoint.X()+100.0, 10.0, gCenterPoint.Z(),0.0,1.0,0.0);
GLfloat lightPosition[]= {gCenterPoint.X() + 450, 450, gCenterPoint.Z() + 50, 1.0f };
GLint shadowSize = 512;


//prototype funciton
void draw();
void myReshape(int width, int height);
void mySetLight();
void quit();
void caculateCameraView(unsigned int viewMode);



//=======================================
void draw()
{
	glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);							// Enable texture mapping
	//glEnable(GL_DEPTH_TEST);							// Enables depth testing

	//draw terrain
	//glDisable(GL_LIGHTING);
	glPushMatrix();
		myTerrain.drawTerrain();
	glPopMatrix();
	//glEnable(GL_LIGHTING);

	glPushMatrix();
		wall.draw(SLOWDOWN);
	glPopMatrix();

	//draw tank
	glPushMatrix();
		myTank.draw(g_ViewMod);
	glPopMatrix();
	//collisionBoxArray.draw();

	//glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE1);
}

// Called to regenerate the shadow map
void RegenerateShadowMap(void)
{
	GLfloat lightModelview[16], lightProjection[16];

    glMatrixMode(GL_PROJECTION);
    glGetFloatv(GL_PROJECTION_MATRIX, lightProjection);

    // Switch to light's point of view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lightPosition[0], lightPosition[1], lightPosition[2], 
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, lightModelview);

    glViewport(0, 0, shadowSize, shadowSize);

    // Clear the window with current clearing color
    glClear(GL_DEPTH_BUFFER_BIT);

    // All we care about here is resulting depth values
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_NORMALIZE);
    glColorMask(0, 0, 0, 0);

    // Overcome imprecision
    glEnable(GL_POLYGON_OFFSET_FILL);

    // Draw objects in the scene
	draw();

    // Copy depth values into depth texture
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                     0, 0, shadowSize, shadowSize, 0);

    // Restore normal drawing state
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glColorMask(1, 1, 1, 1);
    glDisable(GL_POLYGON_OFFSET_FILL);

    // Set up texture matrix for shadow map projection
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glTranslatef(0.5f, 0.5f, 0.5f);
    glScalef(0.5f, 0.5f, 0.5f);

    glMultMatrixf(lightProjection);
    glMultMatrixf(lightModelview);
}

void RenderScene1()
{
	glViewport(0, 0, gWinWidth, gWinHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (double)gWinWidth/(double)gWinHeight, 0.1, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		caculateCameraView(gViewMode);
		camera.view();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw();
		glutSwapBuffers();
}

//*********************************************************
GLfloat sPlane[4] = {1.0f, 0.0f, 0.0f, 0.0f};
GLfloat tPlane[4] = {0.0f, 1.0f, 0.0f, 0.0f};
GLfloat rPlane[4] = {0.0f, 0.0f, 1.0f, 0.0f};
GLfloat qPlane[4] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat ambientLight[] = { 0.7f, 0.7f, 0.7f, 1.0f};
GLfloat diffuseLight[] = { 0.4f, 0.4f, 0.4f, 1.0f};

GLfloat lowAmbient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat lowDiffuse[4] = {0.1f, 0.1f, 0.1f, 1.0f};
//*********************************************************

void myDisplay()
{
	RegenerateShadowMap();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (double)gWinWidth/(double)gWinHeight, 0.1, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		caculateCameraView(gViewMode);
		camera.view();
		glViewport(0, 0, gWinWidth, gWinHeight);
	glPushMatrix();
		glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
		glColor3ub(255, 255, 40);
		gluSphere(gluNewQuadric(), 1.0, 60, 60);
	glPopMatrix();

	//------------------------------------------------------------------

	// Track light position
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Because there is no support for an "ambient"
	// shadow compare fail value, we'll have to
	// draw an ambient pass first...
	glLightfv(GL_LIGHT0, GL_AMBIENT, lowAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lowDiffuse);

	// Draw objects in the scene
	draw();

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	// Set up shadow comparison
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	// Enable alpha test so that shadowed fragments are discarded
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_ALPHA_TEST);	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set up the eye plane for projecting the shadow map on the scene
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);
	glTexGenfv(GL_S, GL_EYE_PLANE, sPlane);
	glTexGenfv(GL_T, GL_EYE_PLANE, tPlane);
	glTexGenfv(GL_R, GL_EYE_PLANE, rPlane);
	glTexGenfv(GL_Q, GL_EYE_PLANE, qPlane);

	// Draw objects in the scene
	draw();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
	// Flush drawing commands

	glutSwapBuffers();
}

void myIdle()
{
	//caculateCameraView(gViewMode);
	glutPostRedisplay();
}

void initGL()
{
	glewInit();
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)gltGetExtensionPointer("glActiveTexture");
	
	// Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Hidden surface removal
	glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glPolygonOffset(4.0f, 0.0f);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

    // Set up some lighting state that never changes
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	GLuint shadowTextureID;

    // Set up some texture state that never changes
	glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &shadowTextureID);
    glBindTexture(GL_TEXTURE_2D, shadowTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
}

void myInit()
{

	glActiveTexture(GL_TEXTURE0);
	//make the background look like the sky
	float blue[4] = {0.5,0.5,1.0,0.0};
	glClearColor(0.5, 0.5, 1.0, 0.0);

	glShadeModel(GL_SMOOTH);

	
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR,blue);
	glFogf(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_START, 200);
	glFogf(GL_FOG_END, 1000);
	glFogf(GL_FOG_DENSITY, gFogDensity);

	//initial terrain
	myTerrain.initializeTerrain("../Data/Texture/Terrain/sand.tga", "../Data/Texture/Terrain/cactus.tga");

	//initial ground collision square
	groundCollSquare.setParameters(TVector(0.0, 1.0, 0.0), gCenterPoint);


	//initial tank
	tankHeightPos = myTerrain.GetHeight(gCenterPoint.X()+100.0, gCenterPoint.Z());

	myTank.setParameters("T-90.3DS", "../T-90/",TVector(gCenterPoint.X()-600.0, tankHeightPos + 9.0, gCenterPoint.Z()-20), 0.0, &myTerrain, &collisionBoxArray, &wall);
	myTank.initTank();	

	unsigned int brickTexture;

	createTexture("../Data/Texture/Brick/brick.bmp", brickTexture);

	wall.Init(myTank.getPosition().X() + 50, myTank.getPosition().Y(), myTank.getPosition().Z() + 20, NUM_BRICKS, brickTexture, &myTerrain);

	myTank.startFight();
}



void caculateCameraView(unsigned int viewMode)
{
	switch(viewMode)
	{
	case 0:
		//gRadViewAngle = M_PI*myTank.getAngleWithX()/180.0 - M_PI; //Depricated
		gRadViewAngle = M_PI*angleWithX/180.0 - M_PI;


		gCameraPosition.setX(myTank.getPosition().X() + 150*cos(gRadViewAngle));
		gCameraPosition.setY(myTank.getPosition().Y() + 30);
		gCameraPosition.setZ(myTank.getPosition().Z() - 150*sin(gRadViewAngle));

		camera.changePosition(gCameraPosition);
		camera.changeTarget(gCameraPosition.X() - 150.0*cos(gRadViewAngle), gCameraPosition.Y(), gCameraPosition.Z() + 150.0*sin(gRadViewAngle));
		break;
	case 1:
		gRadViewAngle = M_PI*myTank.getAngleWithX()/180.0  - M_PI;
		gCameraPosition.setX(myTank.getPosition().X() + 250*cos(gRadViewAngle));
		gCameraPosition.setY(myTank.getPosition().Y() + 50.0);
		gCameraPosition.setZ(myTank.getPosition().Z() - 250*sin(gRadViewAngle));

		camera.changePosition(gCameraPosition);
		camera.changeTarget(gCameraPosition.X() - 150.0*cos(gRadViewAngle), gCameraPosition.Y(), gCameraPosition.Z() + 150.0*sin(gRadViewAngle));
		break;
	case 2:
		gRadViewAngle = M_PI*myTank.getAngleWithX()/180.0  - M_PI*0.5;
		gCameraPosition.setX(myTank.getPosition().X() + 250*cos(gRadViewAngle));
		gCameraPosition.setY(myTank.getPosition().Y() + 50.0);
		gCameraPosition.setZ(myTank.getPosition().Z() - 250*sin(gRadViewAngle));

		camera.changePosition(gCameraPosition);
		camera.changeTarget(gCameraPosition.X() - 150.0*cos(gRadViewAngle), gCameraPosition.Y(), gCameraPosition.Z() + 150.0*sin(gRadViewAngle));
		break;
	case 3:
		gRadViewAngle = M_PI*myTank.getAngleWithX()/180.0;
		gCameraPosition.setX(myTank.getPosition().X() + 250*cos(gRadViewAngle));
		gCameraPosition.setY(myTank.getPosition().Y() + 50.0);
		gCameraPosition.setZ(myTank.getPosition().Z() - 250*sin(gRadViewAngle));

		camera.changePosition(gCameraPosition);
		camera.changeTarget(gCameraPosition.X() - 150.0*cos(gRadViewAngle), gCameraPosition.Y(), gCameraPosition.Z() + 150.0*sin(gRadViewAngle));
		break;
	}
}


void myKeyboard(unsigned char key,int x,int y)
{
	switch (key)
	{
	case 'g':					//decrease gun angle
		//myTank.plusGunAngle(-gAngleGunDelta);
		break;
	case 'G':					//increase gun angle
		//myTank.plusGunAngle(gAngleGunDelta);
		break;

	case 's':					//shot generally bomb
		//myTank.shot();
		break;
	case 'm':					//shot auto bomb
		break;
	case 'v':					//decrease generally bomb velocity
		//myTank.plusBombVelocityMag(-gBombVelocityMagDelta);
		break;
	case 'V':					//increase generally bomb velocity
		//myTank.plusBombVelocityMag(gBombVelocityMagDelta);
		break;

	case 'f':					//decrease fog density
		if(gFogDensity > 0.0005)
		{
			gFogDensity -= 0.0005;
			glFogf(GL_FOG_DENSITY, gFogDensity);
		}		
		break;
	case 'F':					//increase fog density
		if(gFogDensity < 0.99)
		{
			gFogDensity += 0.001;
			glFogf(GL_FOG_DENSITY, gFogDensity);
		}
		break;

	case 'r':					//reset game
		myTank.startFight();
		break;
	case 27:					//exit game
		exit(0);
		break;

	default:
		break;
	}
}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:				//move to left
		myTank.plusAngleWithX(gAngleTankDelta);
		break;
	case GLUT_KEY_RIGHT:			//move to right
		myTank.plusAngleWithX(-gAngleTankDelta);
		break;
	case GLUT_KEY_UP:				//move to up
		myTank.move(gMoveDelta);
		break;
	case GLUT_KEY_DOWN:				//move to right
		myTank.move(-gMoveDelta);
		break;
	case GLUT_KEY_F1:				//view 1
		gViewMode = 0;
		break;
	case GLUT_KEY_F2:				//view 2
		gViewMode = 1;
		break;
	case GLUT_KEY_F3:				//view 3
		gViewMode = 2;
		break;
	}

	printf("==============================");
	printf("x=%f\n", myTank.getPosition().X());
	printf("y=%f\n", myTank.getPosition().Y());
	printf("z=%f\n", myTank.getPosition().Z());
}

void mouseMotion(int x, int y)
{
	static float lastX = 0.0;
	static float lastY = 0.0;

	angleWithX += (lastX - x) * gAngleTankDelta / 2;
	if(angleWithX>= 360)
		angleWithX = 0;
	if(angleWithX < 0)
		angleWithX = 360;

	lastX = x;
}

//============================================  OK =========================================================
int main (int argc, char ** const argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH |GLUT_DOUBLE);
	glutInitWindowSize(gWinWidth, gWinHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("MyGame");

	initGL();
	myInit();

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutPassiveMotionFunc(mouseMotion);
	glutMainLoop();

	quit();
	return 0;	
}

void mySetLight()
{
	GLfloat diffuse[]={0.9, 0.9, 0.9, 1.0};
	GLfloat specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat ambient[]={0.3, 0.3, 0.3, 0.1};
	

	glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void quit()
{
	//mqoCleanup();
}

void myReshape(int width, int height)
{
	gWinWidth=width;
	gWinHeight=height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}