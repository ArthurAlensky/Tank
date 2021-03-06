#include "Tank.h"

Tank::Tank()
{
	radius = 14.0;
}

Tank::~Tank()
{
}

void Tank::setParameters(const char *bodyFile, const char *rootFolder,TVector position, float angleWithX, Terrain *terrain, CollisionBoxArray *collisionBoxArray, Wall *wall)
{
	GameModel3Ds::setParameters(bodyFile, 0.2, rootFolder);
	this->position = position;
	this->angleWithX = angleWithX;
	this->terrain = terrain;
	this->collisionBoxArray = collisionBoxArray;
	this->wall = wall;
}

void Tank::plusAngleWithX(float deltaAngle)
{
	angleWithX += deltaAngle;
	if(angleWithX>= 360)
		angleWithX = 0;
	if(angleWithX < 0)
		angleWithX = 360;
	collisionBox.updateCollisionBoxAngle(angleWithX);
}

void Tank::move(float deltaTranslate)
{
	if(Collision())
	{
		wall->Destroy();
	}

	radTankAngle = M_PI*angleWithX/180.0;

	position += TVector(deltaTranslate*cos(radTankAngle), 0.0, -deltaTranslate*sin(radTankAngle));	// realitive moving
	position.setY(terrain->GetHeight((float)position.X(), (float)position.Z()) +9.0);
	collisionBox.updateCollisionBoxPos(TVector(position.X()-2.2*cos(radTankAngle), position.Y()-2.1, position.Z()));
}

bool Tank::Collision()
{
	TVector wallPosition = wall->GetPosition();
	return position.X() + 35 >= wallPosition.X();
}

void Tank::initTank()
{
	this->initModel();

	radTankAngle = M_PI*angleWithX/180.0;
	collisionBox.setParameters(TVector(position.X()-2.5*cos(radTankAngle), position.Y()-2.1, position.Z()), angleWithX, 17.0, 4.5, 8.0);

	collisionBoxArray->addCollisionBox(&collisionBox);
}

void Tank::draw(int viewMode)
{
	glPushMatrix();
	glTranslatef(position.X(), position.Y() - 10, position.Z());
	glRotatef(angleWithX - 90, 0.0, 1.0, 0.0);

	glScalef(10,10,10);
	this->display(viewMode);
	
	glPopMatrix();

	if(!collisionBox.isLife())
	{
		printf("player's Tank die\n");
	}
}