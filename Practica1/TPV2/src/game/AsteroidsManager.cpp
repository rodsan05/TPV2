#include "AsteroidsManager.h"
#include "../components/Follow.h"

AsteroidsManager::AsteroidsManager(ecs::Manager* manager) : mngr_(manager), nAsteroids_(0), lastTimeAsteroidCreated_(0)
{
}

AsteroidsManager::~AsteroidsManager()
{
	destroyAllAsteroids();
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
	int time = sdlutils().currRealTime();

	if (time - lastTimeAsteroidCreated_ >= TIME_BETWEEN_ASTEROIDS && nAsteroids_ < 30) {
		
		createAsteroids(1);

		lastTimeAsteroidCreated_ = time;
	}
}

void AsteroidsManager::destroyAllAsteroids()
{
	for (auto ast : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
	
		ast->setAlive(false);
	}
}

void AsteroidsManager::onCollision(Entity* a)
{
	a->setAlive(false);

	auto tr = a->getComponent<Transform>();
	auto gensA = a->getComponent<Generations>();

	assert(a != nullptr && gensA != nullptr);

	if (gensA->nGenerations() > 0) {

		auto p = tr->getPos();
		auto v = tr->getVel();

		float w = 10.0f + 5.0f * (gensA->nGenerations() - 1);
		float h = w;

		for (int i = 0; i < 2; i++) {

			if (nAsteroids_ < 30) {
				auto r = sdlutils().rand().nextInt(0, 360);
				auto pos = p + v.rotate(r) * 2 * std::max(w, h);
				auto vel = v.rotate(r) * 1.1f;

				int type;
				if (a->getComponent<Follow>() == nullptr)
					type = 0;

				else type = 1;

				createAsteroid(type, gensA->nGenerations() - 1, pos.getX(), pos.getY(), vel);
			}
		}
	}
}

bool AsteroidsManager::hasPlayerWon()
{
	return nAsteroids_ == 0;
}

void AsteroidsManager::createAsteroid(int type, int gens, int x, int y, Vector2D vel)
{
	int width = sdlutils().width();
	int height = sdlutils().height();
	
	Entity* asteroid = mngr_->addEntity(_grp_ASTEROIDS);

	auto g = asteroid->addComponent<Generations>(gens);

	auto tr_ = asteroid->addComponent<Transform>();
	
	int border = sdlutils().rand().nextInt(0, 4);

	//height and width
	float w = 10.0f + 5.0f * g->nGenerations();

	//position
	Vector2D pos;

	if (x == -1) {

		if (border == 0) pos = Vector2D(sdlutils().rand().nextInt(0, width - w), 0);
		else if (border == 1) pos = Vector2D(sdlutils().rand().nextInt(0, width - w), height - w);
		else if (border == 2) pos = Vector2D(0, sdlutils().rand().nextInt(0, height - w));
		else if (border == 3) pos = Vector2D(width - w, sdlutils().rand().nextInt(0, height - w));
	}

	else pos = Vector2D(x, y);

	//velocity
	auto c = Vector2D(width / 2, height / 2);
	auto rx = sdlutils().rand().nextInt(-100, 100);
	auto ry = sdlutils().rand().nextInt(-100, 100);

	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
	Vector2D v;

	if (vel.magnitude() == 0) v = (c - pos).normalize() * speed;
	else v = vel;

	tr_->init(pos, v, w, w, 0);

	asteroid->addComponent<ShowAtOppositeSide>();

	if (type == 0) {
	
		asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 50, 30);
	}

	else {
	
		asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"), 5, 6, 50, 30);
		asteroid->addComponent<Follow>();
	}
}
