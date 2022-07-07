#pragma once

class Collider; //forward declaration to avoid circular dependency
class CollisionListener {

public:
	virtual ~CollisionListener() {}

	virtual void applyPhysics(Collider* coll) = 0;

protected:
	CollisionListener() {}
};
