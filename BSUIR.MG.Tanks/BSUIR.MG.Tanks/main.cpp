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

#include "Camera.h"
#include "Texture.h"
#include "Terrain.h"
#include "Tank.h"

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
static float gAngleTankDelta = 3.0;
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


Camera camera(gCenterPoint.X(), 30.0, gCenterPoint.Z(), gCenterPoint.X()+100.0, 10.0, gCenterPoint.Z(),0.0,1.0,0.0);


//prototype funciton
void draw();
void myReshape(int width, int height);
void mySetLight();
void quit();
void caculateCameraView(unsigned int viewMode);

//=======================================
void draw()
{
	glEnable(GL_DEPTH_TEST);
	
	//draw terrain
	glDisable(GL_LIGHTING);
	myTerrain.drawTerrain();
	glEnable(GL_LIGHTING);
	
	//draw tank
	myTank.draw(g_ViewMod);


	//collisionBoxArray.draw();

	glDisable(GL_DEPTH_TEST);
}

void myDisplay()
{	
	if(gViewMode == 2)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//viewport1
		glViewport(0, 0, 2*gWinWidth/3, gWinHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (double)(2*gWinWidth)/(double)(3*gWinHeight), 0.1, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		caculateCameraView(0);
		camera.view();
		draw();

		//viewport2
		glViewport(2*gWinWidth/3, gWinHeight/2, gWinWidth/3, gWinHeight/2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (double)(2*gWinWidth)/(double)(3*gWinHeight), 0.1, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		caculateCameraView(2);
		camera.view();
		draw();

		//viewport3
		glViewport(2*gWinWidth/3, 0, gWinWidth/3, gWinHeight/2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (double)(2*gWinWidth)/(double)(3*gWinHeight), 0.1, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		caculateCameraView(3);
		camera.view();
		draw();
	}
	else
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
	}

	glutSwapBuffers();
}

void myIdle()
{
	//caculateCameraView(gViewMode);
	glutPostRedisplay();
}

void myInit()
{
	//make the background look like the sky
	float blue[4] = {0.5,0.5,1.0,0.0};
	glClearColor(0.5, 0.5, 1.0, 0.0);
		
	glShadeModel(GL_SMOOTH);
	
	//mqoInit();

	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR,blue);
	glFogf(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_START, 200);
	glFogf(GL_FOG_END, 1000);
	glFogf(GL_FOG_DENSITY, gFogDensity);

	//initial terrain
	myTerrain.initializeTerrain("E:/My_Tank/Work/Tank/BSUIR.MG.Tanks/Data/Texture/Terrain/sand.tga", "E:/My_Tank/Work/Tank/BSUIR.MG.Tanks/Data/Texture/Terrain/cactus.tga");

	//initial ground collision square
	groundCollSquare.setParameters(TVector(0.0, 1.0, 0.0), gCenterPoint);
	

	//initial tank
	tankHeightPos = myTerrain.GetHeight(gCenterPoint.X()+100.0, gCenterPoint.Z());

	myTank.setParameters("T-90.3DS", "E:/My_Tank/Work/Tank/TANK-T90/T-90/",TVector(gCenterPoint.X()+100.0, tankHeightPos + 9.0, gCenterPoint.Z()), 0.0, &myTerrain, &collisionBoxArray);
	//myTank.setParameters("E:/My_Tank/Work/Tank/Tank-34/111.3DS", TVector(gCenterPoint.X()+100.0, tankHeightPos + 9.0, gCenterPoint.Z()), 0.0, &myTerrain, &collisionBoxArray);
	myTank.initTank();	

	/*gCameraPosition.setX(myTank.getPosition().X() + 150*cos(gRadViewAngle));
	gCameraPosition.setY(myTank.getPosition().Y() + 30);
	gCameraPosition.setZ(myTank.getPosition().Z() - 150*sin(gRadViewAngle));*/

	myTank.startFight();
	mySetLight();
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
}

void mouseMotion(int x, int y)
{
	angleWithX += gAngleTankDelta;
}

//============================================  OK =========================================================
int main (int argc, char ** const argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH |GLUT_DOUBLE);
	glutInitWindowSize(gWinWidth, gWinHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("MyGame");
	
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
	GLfloat position[]= {100.0, 200.0, 200.0, 0.0};
	
	glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
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

