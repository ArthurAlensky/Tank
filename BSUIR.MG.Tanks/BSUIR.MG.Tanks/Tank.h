/*
 *  tank.h
 *  GlMetaseq
 *
 *  Created by le van nghia on 12/5/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _TANK_H_
#define _TANK_H_
#include "GameModel3Ds.h"
#include "ControlWarObject.h"
#include "Terrain.h"
#include "TVector.h"

class Tank: public ControlWarObject
{
private:
	GameModel3Ds bodyModel;
	float radTankAngle;
	Terrain *terrain;
	
public:
	Tank();
	~Tank();
	
	void setParameters(const char *bodyFile, const char *rootFolder,TVector position, float angleWithX, Terrain *terrain, CollisionBoxArray *collisionBoxArray);
	void plusAngleWithX(float deltaAngle);
	void move(float deltaTranslate);
	void initTank();
	void startFight();
	void draw(int viewMode);
};

#endif