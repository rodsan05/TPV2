#include "AsteroidsManager.h"

AsteroidsManager::AsteroidsManager(ecs::Manager* manager) : mngr_(manager), nAsteroids_(0)
{
}

AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::createAsteroids(int n)
{
}

void AsteroidsManager::addAsteroidFrequently()
{
}

void AsteroidsManager::destroyAllAsteroids()
{
}

void AsteroidsManager::onCollision(Entity* a)
{
}

void AsteroidsManager::createAsteroid()
{
	Entity* asteroid = mngr_->addEntity();

	asteroid->addComponent<Transform>();
}
