#pragma once
#include "Entity.h"

class EntityDemo : public Entity
{

	virtual void UpdateEntity();
	virtual void OnCollision(Entity* collidedWith);

public :

	Entity* target;
};

