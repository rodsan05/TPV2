#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Entity.h"	

#include "../sdlutils/SDLUtils.h"

#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"


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

	void createAsteroid(int type, int gens);

	int nAsteroids_;
};

