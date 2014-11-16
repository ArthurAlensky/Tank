/*
 *  terrain.cpp
 *  cacti
 *
 *  Created by le van nghia on 10/31/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Terrain.h"

Terrain::Terrain(bool detail, int detailScale)
{
	this->detail = detail;
	this->detailScale = detailScale;
}

Terrain::~Terrain()
{
	if (sandTexture.texID)
		glDeleteTextures(1, &sandTexture.texID);
	if (treeTexture.texID) 
		glDeleteTextures(1, &treeTexture.texID);
}

void Terrain::loadTexture(char *filename, Texture &texture)
{
	glGenTextures(1, &texture.texID);
	glBindTexture(GL_TEXTURE_2D, texture.texID);
	
	texture.LoadTGA(filename);
	
	//set up the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0,texture.type , texture.width, texture.height, 0, texture.type, GL_UNSIGNED_BYTE, texture.imageData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, texture.type, texture.width, texture.height, texture.type, GL_UNSIGNED_BYTE, texture.imageData);
	
	free(texture.imageData);
	printf("width  %i  height %i\n",texture.width,texture.height);
	
}

void Terrain::initializeTerrain(char *sandFileName, char *treeFileName)  //initialize vertex array
{
	int index=0;
	int currentVertex;
	int x,z;
	
	//load texture to memory
	loadTexture(sandFileName, sandTexture);
	loadTexture(treeFileName, treeTexture);
	
	for (z=0; z<mapZ; z++) {
		for (x=0; x<mapX; x++) {
			
			terrain[x+z*mapX][0] = float(x)*mapScale;
			terrain[x+z*mapX][1] = 5.0 + FRAND *3.0;
			terrain[x+z*mapX][2] = -float(z)*mapScale;
			
			currentVertex = z*mapX +x;
			
			//printf(" %f   %f   %f\n",terrain[currentVertex][0],terrain[currentVertex][1],terrain[currentVertex][2]);
			
			colorArray[currentVertex][0] = colorArray[currentVertex][1]=colorArray[currentVertex][2]=terrain[x+z*mapX][1]/20.0 +0.5;
			
			texcoordArray[currentVertex][0]=(float)x;
			texcoordArray[currentVertex][1]=(float)z;
			
		}
	}
	
	//loop over all vertices in the terrain map
	for (z=0; z<mapZ-1; z++) {
		for (x=0; x<mapX; x++) {
			currentVertex=z*mapX +x;
			indexArray[index++] = currentVertex +mapX;
			indexArray[index++] = currentVertex;
		}
	}
}

void Terrain::drawSand()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, terrain);
	glColorPointer(3, GL_FLOAT, 0, colorArray);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoordArray);

	//select the sand texture
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, sandTexture.texID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// loop through all the triangle strips
	for (int z = 0; z < mapZ-1; z++)
	{
		// draw the triangles in this strip
		glDrawElements(GL_TRIANGLE_STRIP, mapX * 2, GL_UNSIGNED_INT, &indexArray[z * mapX * 2]);
	}

	glDisable(GL_TEXTURE_2D);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Terrain::drawTree()
{
	glEnable(GL_TEXTURE_2D);
	
	//make sure the random numbers we generate are the same every time
	srand(100);
	//make sure the transparent part of the texture isn't drawn
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	
	//get the modelview matrix
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	
	//get the right and up vectors
	TVector right(mat[0],mat[4],mat[8]);
	TVector up(mat[1],mat[5],mat[9]);
	
	
	//select the cactus texture
	glBindTexture(GL_TEXTURE_2D, treeTexture.texID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	//draw all cacti
	glBegin(GL_QUADS);
	for (int n=0; n<numTree; n++) {
		//randomly size the cactus
		float size = 20.0 + FRAND*5.0;
		
		//pick a random position on the map
		TVector pos(RAND_COORD((mapX-1)*mapScale),0.0,-RAND_COORD((mapZ-1)*mapScale));
		pos.setY(GetHeight(pos.X(), pos.Z()) + size -0.5);
		
		TVector tmp= pos + (right + up) * (-size);
		// bottom left corner
		glTexCoord2f(0.0, 0.0); glVertex3f(tmp.X(), tmp.Y(), tmp.Z());
		
		// bottom right corner
		tmp = pos + (right - up) * size;
		glTexCoord2f(1.0, 0.0); glVertex3f(tmp.X(), tmp.Y(), tmp.Z());
		
		// top right corner
		tmp = pos + (right + up) * size;
		glTexCoord2f(1.0, 1.0); glVertex3f(tmp.X(), tmp.Y(), tmp.Z());
		
		// top left corner
		tmp = pos + (up - right) * size;
		glTexCoord2f(0.0, 1.0); glVertex3f(tmp.X(), tmp.Y(), tmp.Z());
	}
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
}

void Terrain::drawTerrain()
{
	glPushMatrix();
		drawSand();
	glPopMatrix();

	/*glPushMatrix();
		drawTree();
	glPopMatrix();*/
}

float Terrain::GetHeight(float x, float z)
{
	// divide by the grid-spacing if it is not 1
	float projCameraX = x / mapScale;
	float projCameraZ = -z / mapScale;
	
	// compute the height field coordinates (hflCol0, hflRow0) and
	// (hflCol1, hflRow1) that identify the height field cell directly below the camera.
	int hflCol0 = int(projCameraX);
	int hflRow0 = int(projCameraZ);
	int hflCol1 = hflCol0 + 1;
	int hflRow1 = hflRow0 + 1;
	
	// get the four corner heights of the cell from the height field
	float h00 = terrain[hflCol0 + hflRow0*mapX][1];
	float h01 = terrain[hflCol1 + hflRow0*mapX][1];
	float h11 = terrain[hflCol1 + hflRow1*mapX][1];
	float h10 = terrain[hflCol0 + hflRow1*mapX][1];
	
	// calculate the position of the camera relative to the cell.
	// note, that 0 <= tx, ty <= 1.
	float tx = projCameraX - float(hflCol0);
	float ty = projCameraZ - float(hflRow0);
	
	// the next step is to perform a bilinear interpolation to compute the height
	// of the terrain directly below the object.
	float txty = tx * ty;
	
	return h00 * (1.0f - ty - tx + txty)
	+ h01 * (tx - txty)
	+ h11 * txty
	+ h10 * (ty - txty);
} // end GetHeight()


///////////////////////////////// HEIGHT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the height into the height map
/////
///////////////////////////////// HEIGHT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int Terrain::Height(char *pHeightMap, int X, int Y)
{
	// Make sure we don't go past our array size
	int x = X % MAP_SIZE;					// Error check our x value
	int y = Y % MAP_SIZE;					// Error check our y value

	if(!pHeightMap) return 0;				// Make sure our data is valid

	// Use the equation: index = (x + (y * arrayWidth) ) to find the current height
	return pHeightMap[x + (y * MAP_SIZE)];	// Index into our height array and return the height
}


///////////////////////////////// SET TEXTURE COORD \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This sets the current texture coordinate of the terrain, based on the X and Z
/////
///////////////////////////////// SET TEXTURE COORD \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void SetTextureCoord(float x, float z)
{
	// Find the (u, v) coordinate for the current vertex
	float u =  (float)x / (float)MAP_SIZE;
	float v = -(float)z / (float)MAP_SIZE;
	

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// Instead of using the normal API for assigning the current texture
	// coordinate, we want to use the glMultiTexCoord2fARB() function.
	// This will allow us to choose the (u, v) coordinate for every texture
	// map, since we are using multitexturing.  Due to the fact that we
	// are going to be using the texture matrix to set the tiling of our
	// detail texture, we just assign the same (u, v) coordinate for both
	// textures.  

	// Give OpenGL the current terrain texture coordinate for our height map
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);

	// Give OpenGL the current detail texture coordinate for our height map
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


}

///////////////////////////////// RENDER HEIGHT MAP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This renders the height map as QUADS
/////
///////////////////////////////// RENDER HEIGHT MAP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
void Terrain::RenderHeightMap(char pHeightMap[])
{
	int X = 0, Y = 0;						// Create some variables to walk the array with.
	int x, y, z;							// Create some variables for readability
	bool bSwitchSides = false;

	// Make sure our height data is valid
	if(!pHeightMap) return;		
	

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// Now comes the juice of our detail texture.  We want to combine the
	// terrain texture and the detail texture together.  To blend the two
	// textures nicely, we will want to use some ARB extension defines
	// for our texture properties.  The first one, GL_COMBINE_ARB, allows
	// us to use combine texture properties, which brings us to our second
	// one: GL_RGB_SCALE_ARB.  With this texture property, we can now 
	// increase the gamma of our second texture so that it does not darken
	// the texture beneath it.  This works great for lightmaps and detail 
	// textures.  I believe that the GL_RGB_SCALE_ARB property only accepts
	// 1, 2 or 4 as a valid scale value.  2 works just fine, where 4 is
	// too bright.  
	// 
	// To tile the detail texture appropriately, the texture matrix is
	// effected.  When we enter into the texture matrix mode, it allows us
	// to effect the current position of the selected texture.  This isn't
	// necessary to use, since we could just calculate the detail texture
	// coordinates on our own, but I thought it would be nice to introduce
	// this functionality.  All we do is just scale the texture by a certain
	// amount, which can provide different levels of detail.  By hitting the
	// SPACE bar on the keyboard, you are able to cycle through different
	// scale values to see the one that works best for you.  It is good to
	// add a third texture on top that is the same detail texture, but with
	// a different scale value.

	// Activate the first texture ID and bind the tree background to it
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_Texture[0]);

	// If we want detail texturing on, let's render the second texture
	if(detail)
	{
		// Activate the second texture ID and bind the fog texture to it
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		
		// Here we turn on the COMBINE properties and increase our RGB
		// gamma for the detail texture.  2 seems to work just right.
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
		
		// Bind the detail texture
		glBindTexture(GL_TEXTURE_2D, g_Texture[1]);
	
		// Now we want to enter the texture matrix.  This will allow us
		// to change the tiling of the detail texture.
		glMatrixMode(GL_TEXTURE);

			// Reset the current matrix and apply our chosen scale value
			glLoadIdentity();
			glScalef((float)detailScale, (float)detailScale, 1);

		// Leave the texture matrix and set us back in the model view matrix
		glMatrixMode(GL_MODELVIEW);
	}

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


	// We want to render triangle strips
	glBegin( GL_TRIANGLE_STRIP );			

	// Go through all of the rows of the height map
	for ( X = 0; X <= MAP_SIZE; X += STEP_SIZE )
	{
		// Check if we need to render the opposite way for this column
		if(bSwitchSides)
		{	
			// Render a column of the terrain, for this current X.
			// We start at MAP_SIZE and render down to 0.
			for ( Y = MAP_SIZE; Y >= 0; Y -= STEP_SIZE )
			{
				// Get the (X, Y, Z) value for the bottom left vertex		
				x = X;							
				y = Height(pHeightMap, X, Y );	
				z = Y;							

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				glVertex3i(x, y, z);		

				// Get the (X, Y, Z) value for the bottom right vertex		
				x = X + STEP_SIZE; 
				y = Height(pHeightMap, X + STEP_SIZE, Y ); 
				z = Y;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				glVertex3i(x, y, z);			
			}
		}
		else
		{	
			// Render a column of the terrain, for this current X.
			// We start at 0 and render down up to MAP_SIZE.
			for ( Y = 0; Y <= MAP_SIZE; Y += STEP_SIZE )
			{
				// Get the (X, Y, Z) value for the bottom right vertex		
				x = X + STEP_SIZE; 
				y = Height(pHeightMap, X + STEP_SIZE, Y ); 
				z = Y;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				glVertex3i(x, y, z);

				// Get the (X, Y, Z) value for the bottom left vertex		
				x = X;							
				y = Height(pHeightMap, X, Y );	
				z = Y;							

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				glVertex3i(x, y, z);		
			}
		}

		// Switch the direction the column renders to allow the fluid tri strips
		bSwitchSides = !bSwitchSides;
	}

	// Stop rendering triangle strips
	glEnd();


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// Now let's clean up our multitexturing so it doesn't effect anything else

	// Turn the second multitexture pass off
	glActiveTextureARB(GL_TEXTURE1_ARB);
    glDisable(GL_TEXTURE_2D);

	// Turn the first multitexture pass off
	glActiveTextureARB(GL_TEXTURE0_ARB);		
    glDisable(GL_TEXTURE_2D);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


}

///////////////////////////////// LOAD RAW FILE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This loads a .raw file into an array of bytes.  Each value is a height value.
/////
///////////////////////////////// LOAD RAW FILE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Terrain::LoadRawFile(char *strName, int nSize, char *pHeightMap)
{
	FILE *pFile = NULL;

	// Let's open the file in Read/Binary mode.
	pFile = fopen( strName, "rb" );

	// Check to see if we found the file and could open it
	if ( pFile == NULL )	
	{
		return;
	}

	// Here we load the .raw file into our pHeightMap data array.
	// We are only reading in '1', and the size is the (width * height)
	fread( pHeightMap, 1, nSize, pFile );

	// After we read the data, it's a good idea to check if everything read fine.
	int result = ferror( pFile );

	// Close the file.
	fclose(pFile);
}