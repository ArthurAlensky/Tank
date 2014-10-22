#include "Wall.h"


Wall::Wall(){}

TVector Wall::GetPosition()
{
	return position;
}
void Wall::SetPosition(TVector vector )
{
	position = vector;
}

void Wall::Init(float x, float y, float z, int numOfBricks, int brickTexture, Terrain * terrain)
{
	SetPosition(TVector(x,y,z));

	for(int j = 0; j < sqrt(numOfBricks); j++ )
	{
		for(int i = 0; i < sqrt(numOfBricks); i++)
		{
			Brick *brick = new Brick();
			bricks.push_back(brick);

			brick->setTexture(brickTexture);
			brick->setTerrain(terrain);

			brick->setPosition(TVector(x, y + brick->height * j, z + brick->length * i ));

			brick->setDirection(TVector(
				float((rand()%50)-26.0f)*10.0f,	// Random Speed On X Axis
				float((rand()%50)-25.0f)*10.0f,	// Random Speed On Y Axis
				float((rand()%50)-25.0f)*10.0f	// Random Speed On Z Axis
				));   

			brick->setGravity(TVector(
				0.0f,	// Set Horizontal Pull To Zero
				-0.8f,	// Set Vertical Pull Downward
				0.0f	// Set Pull On Z Axis To Zero
				));              
		}
	}
}

void Wall::draw(float slowdown)
{
	for(int i = 0; i < 100; i++)
	{
		Brick *brick = bricks[i];

		if(destroied)
			brick->moveWhenCrash(slowdown);

		brick->draw();
	}
}

Wall::~Wall(void)
{
}
