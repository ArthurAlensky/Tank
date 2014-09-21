/*
 *  GameModel3Ds.h
 *  
 *
 *  Created by le van nghia on 12/5/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include "3ds.h"
#include "Global.h"
#include <string.h>

class GameModel3Ds
{
private:
	char fileName[100];
	float scale;
	CLoad3DS g_Load3ds;										// This is 3DS class.  This should go in a good model class.
	t3DModel g_3DModel;										// This holds the 3D Model info that we load in
	UINT g_Texture[MAX_TEXTURES];						// This holds the texture info, referenced by an ID


	bool createTexture(LPTSTR szFileName, GLuint &textureID);

public:
	GameModel3Ds();
	GameModel3Ds(const char *filename, float scale);
	~GameModel3Ds();
	
	void setParameters(const char *filename, float scale);
	void initModel();
	void display(int viewMode);
	void deleteModel();
};

