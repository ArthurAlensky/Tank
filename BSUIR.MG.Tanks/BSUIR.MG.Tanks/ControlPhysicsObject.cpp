/*
 *  ControlWarObject.cpp
 *  cacti
 *
 *  Created by le van nghia on 12/15/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ControlPhysicsObject.h"

ControlPhysicsObject::ControlPhysicsObject()
{
	position = TVector(0.0, 0.0, 0.0);
	angleWithX = 0.0;
	collisionBoxArray = NULL;
}

ControlPhysicsObject::~ControlPhysicsObject()
{
}

void ControlPhysicsObject::setPosition(float x, float y, float z)
{
	position.setX(x);
	position.setY(y);
	position.setZ(z);
}

void ControlPhysicsObject::setParameters(TVector position, float angleWithX, CollisionBoxArray *collisionBoxArray)
{
	this->position = position;
	this->angleWithX = angleWithX;
	this->collisionBoxArray = collisionBoxArray;
}

void ControlPhysicsObject::plusPosition(float deltaX, float deltaY, float deltaZ)
{
	position += TVector(deltaX, deltaY, deltaZ);
}