#pragma once
#include "IncludeS.h"
#include "Brick.h"
#include "Terrain.h"
#include <vector>

class Wall
{
	std::vector<Brick *> bricks;
	bool destroied;
	TVector position;
public:
	Wall();
	~Wall(void);

	void Init(float x, float y, float z, int numOfBricks, int brickTexture, Terrain * terrain);
	void draw(float slowdown);
	TVector GetPosition();
	void SetPosition(TVector vector );
};

