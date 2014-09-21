/*
 *  terrain.h
 *  myGame
 *
 *  Created by le van nghia on 10/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <iostream>
#include "IncludeS.h"
#include "Texture.h"
#include "Tvector.h"
#include "Global.h"

#define PI 3.14159
#define RAND_COORD(x)  ((float)rand()/RAND_MAX * (x))
#define MAP_SIZE		1024				// This is the size of our .raw height map
#define STEP_SIZE		16					// This is width and height of each triangle grid
#define HEIGHT_RATIO	1.5f				// This is the ratio that the Y is scaled according to the X and Z


class Terrain
{
private:
	//terrain data
	float terrain[mapX * mapZ][3];		    //heightfield terrain data (0-255)
	GLuint indexArray[mapX * mapZ *2];	    //vertex array
	float colorArray[mapX * mapZ][3];	    //color array
	float texcoordArray[mapX * mapZ][2];	//texcoord array
	UINT g_Texture[MAX_TEXTURES];						// This holds the texture info, referenced by an ID
	bool detail;							// This tells us if we want detail texturing turned on or off
	int detailScale;						// This holds the current tile scale value for our detail texture

public:
	
	Texture sandTexture;
	Texture treeTexture;
	
	Terrain(bool detail, int detailScale);
	~Terrain();
	
	void loadTexture(char *filename, Texture &texture);
	void initializeTerrain(char *sandFileName, char *treeFileName);   //initialize vertex array
	float GetHeight(float x, float z);
	
	void drawSand();
	void drawTree();
	void drawTerrain();

	// This returns the height (0 to 255) from a heightmap given an X and Y
	int Height(char *pHeightMap, int X, int Y);

	// This loads a .raw file of a certain size from the file
	void LoadRawFile(char* strName, int nSize, char *pHeightMap);

	// This turns heightmap data into primitives and draws them to the screen
	void RenderHeightMap(char *pHeightMap);


};

#endif