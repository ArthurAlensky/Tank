#pragma once

#include "3ds.h"
#include "Global.h"
#include "Terrain.h"
#include <string.h>

class Brick
{

	unsigned int texture;
	Terrain *terrain;
	TVector position;
	TVector direction;
	TVector gravity;

public:

	float width;
	float height;
	float length;

	Brick(void);
	~Brick(void);

	void draw();
	void setTexture(unsigned int texture);
	void setTerrain(Terrain *terrain);

	void setPosition(TVector position);
	void setDirection(TVector direction);
	void setGravity(TVector gravity);

	void moveWhenCrash(float slowdown);
};

