#include "Global.h"
// GLTools.h
// OpenGL SuperBible
// Copyright 1998 - 2003 Richard S. Wright Jr..
// Code by Richard S. Wright Jr.
// All Macros prefixed with GLT_, all functions prefixed with glt... This
// should avoid most namespace problems
// Some of these functions allocate memory. Use CRT functions to free
// Report bugs to rwright@starstonesoftware.com

//#ifndef __GLTOOLS__LIBRARY
//#define __GLTOOLS__LIBRARY



///////////////////////////////////////////////////////
// Useful constants
#define GLT_PI	3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229

///////////////////////////////////////////////////////////////////////////////
// Useful shortcuts and macros
// Radians are king... but we need a way to swap back and forth
#define gltDegToRad(x)	((x)*GLT_PI_DIV_180)
#define gltRadToDeg(x)	((x)*GLT_INV_PI_DIV_180)


///////////////////////////////////////////////////////
// Some data types
typedef GLfloat GLTVector2[2];      // Two component floating point vector
typedef GLfloat GLTVector3[3];      // Three component floating point vector
typedef GLfloat GLTVector4[4];      // Four component floating point vector
typedef GLfloat GLTMatrix[16];      // A column major 4x4 matrix of type GLfloat

typedef struct{                     // The Frame of reference container
	GLTVector3 vLocation;
	GLTVector3 vUp;
	GLTVector3 vForward;
} GLTFrame;

typedef struct 			    // High resolution timer
{
#ifdef WIN32
	LARGE_INTEGER m_LastCount;
#else
	struct timeval last;
#endif
} GLTStopwatch;


///////////////////////////////////////////////////////
// Macros for big/little endian happiness
#define BYTE_SWAP(x)    x = ((x) >> 8) + ((x) << 8)


///////////////////////////////////////////////////////////////////////////////
//         THE LIBRARY....
///////////////////////////////////////////////////////////////////////////////

// vector functions in VectorMath.c 
void gltAddVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);
void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);
void gltScaleVector(GLTVector3 vVector, const GLfloat fScale);
GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector);
GLfloat gltGetVectorLength(const GLTVector3 vVector);
void gltNormalizeVector(GLTVector3 vNormal);
void gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2, const GLTVector3 vP3, GLTVector3 vNormal);
void gltCopyVector(const GLTVector3 vSource, GLTVector3 vDest);
GLfloat gltVectorDotProduct(const GLTVector3 u, const GLTVector3 v);
void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult);
void gltTransformPoint(const GLTVector3 vSrcPoint, const GLTMatrix mMatrix, GLTVector3 vPointOut);
void gltRotateVector(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vPointOut);
void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane);
GLfloat gltDistanceToPlane(GLTVector3 vPoint, GLTVector4 vPlane);


//////////////////////////////////////////
// Other matrix functions in matrixmath.c
void gltLoadIdentityMatrix(GLTMatrix m);
void gltMultiplyMatrix(const GLTMatrix m1, const GLTMatrix m2, GLTMatrix mProduct );
void gltRotationMatrix(float angle, float x, float y, float z, GLTMatrix mMatrix);
void gltTranslationMatrix(GLfloat x, GLfloat y, GLfloat z, GLTMatrix mTranslate);
void gltScalingMatrix(GLfloat x, GLfloat y, GLfloat z, GLTMatrix mScale);
void gltMakeShadowMatrix(GLTVector3 vPoints[3], GLTVector4 vLightPos, GLTMatrix destMat);
void gltTransposeMatrix(GLTMatrix mTranspose);
void gltInvertMatrix(const GLTMatrix m, GLTMatrix mInverse);


//////////////////////////////////////////////////////////////
void *gltGetExtensionPointer(const char *szExtensionName);