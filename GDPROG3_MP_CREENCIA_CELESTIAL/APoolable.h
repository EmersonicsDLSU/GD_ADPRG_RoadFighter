#pragma once
#include "AGameObject.h"
class APoolable : public AGameObject
{
public:
	APoolable(string name);
	//initializes the property of this object.
	virtual void initialize() = 0; 

	//throws this event when this object has been released back to the pool.
	virtual void onRelease() = 0; 

	//throws this event when this object has been activated from the pool.
	virtual void onActivate() = 0; 

	//provides a copy of the poolable instance. must be implemented per specific class
	virtual APoolable* clone() = 0;
};
