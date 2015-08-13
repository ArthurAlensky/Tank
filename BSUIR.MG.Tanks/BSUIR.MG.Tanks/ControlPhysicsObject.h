/*
 *  ControlPhysicsObject.h
 *  myGame
 *
 *  Created by le van nghia on 12/15/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _CONTROLPHYSICSOBJECT_H_
#define _CONTROLPHYSICSOBJECT_H_

#include "IncludeS.h"
#include "Tvector.h"
#include "CollisionBox.h"
#include "CollisionBoxArray.h"

class ControlPhysicsObject
{
protected:
	TVector	position;
	float angleWithX;
	CollisionBox collisionBox;
	CollisionBoxArray *collisionBoxArray;
	float radius;
	
public:
	ControlPhysicsObject();
	~ControlPhysicsObject();
	
	void setParameters(TVector position, float angleWithX, CollisionBoxArray *collisionBoxArray);
	void setPosition(float x, float y, float z);
	float getRadius(){return radius;}
	TVector getPosition(){ return position;}
	float getAngleWithX(){return angleWithX;}
	void plusPosition(float deltaX, float deltaY, float deltaZ);
	virtual void draw(){}
};

#endif