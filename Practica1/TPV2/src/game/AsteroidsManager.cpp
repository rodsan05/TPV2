#include "AsteroidsManager.h"


AsteroidsManager::AsteroidsManager(ecs::Manager* manager) : mngr_(manager), nAsteroids_(0)
{
}

AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::createAsteroids(int n)
{
	if (n + nAsteroids_ > 30) n = 30 - nAsteroids_;

	for (int i = 0; i < n; i++) {
	
		int generations = sdlutils().rand().nextInt(0, 4);

		int type;

		if (sdlutils().rand().nextInt(0, 10) < 3) type = 1;
		else type = 0;

		createAsteroid(type, generations);
	}
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

void AsteroidsManager::createAsteroid(int type, int gens)
{
	int width = sdlutils().width();
	int height = sdlutils().height();
	
	Entity* asteroid = mngr_->addEntity(_grp_ASTEROIDS);

	auto g = asteroid->addComponent<Generations>(gens);

	auto tr_ = asteroid->addComponent<Transform>();
	
	int axis = sdlutils().rand().nextInt(0, 2);

	//position
	Vector2D pos;
	if (axis == 0) pos = Vector2D(sdlutils().rand().nextInt(0, width), 0);
	else pos = Vector2D(0, sdlutils().rand().nextInt(0, height));

	//velocity
	auto c = Vector2D(width / 2, height / 2);
	auto rx = sdlutils().rand().nextInt(-100, 100);
	auto ry = sdlutils().rand().nextInt(-100, 100);

	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
	Vector2D vel = (c - pos).normalize() * speed;

	//height and width
	float w = 10.0f + 5.0f * g->nGenerations();
	tr_->init(pos, vel, w, w, 0);

	asteroid->addComponent<ShowAtOppositeSide>();

	if (type == 0) {
	
		asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 50, 30);
	}

	else {
	
		asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"), 5, 6, 50, 30);
	}
}
