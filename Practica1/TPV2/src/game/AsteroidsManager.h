#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Entity.h"	
#include "../components/Transform.h"


using namespace ecs;

class AsteroidsManager
{
public:

	AsteroidsManager(Manager* manager);
	~AsteroidsManager();

	void createAsteroids(int n);

	void addAsteroidFrequently();
	void destroyAllAsteroids();

	void onCollision(Entity* a);

private:

	Manager* mngr_;

	void createAsteroid();

	int nAsteroids_;
};

