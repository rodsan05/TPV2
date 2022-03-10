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

	bool hasPlayerWon();

private:

	const int TIME_BETWEEN_ASTEROIDS = 5000;

	Manager* mngr_;

	/**
	* Create an asteroid
	* 
	* @param type: Type of the asteroid (0 = type A, 1 = type B)
	* @param gens: Number of generations of the asteroid
	* @param x: coordinate x of the asteroid (if not specified is selected randomly)
	* @param y: coordinate y of the asteroid (if not specified is selected randomly)
	* @param vel: velocity of the asteroid (if not specified is selected randomly)
	*/
	void createAsteroid(int type, int gens, int x = -1, int y = -1, Vector2D vel = Vector2D(0, 0));

	int nAsteroids_;

	int lastTimeAsteroidCreated_;
};

