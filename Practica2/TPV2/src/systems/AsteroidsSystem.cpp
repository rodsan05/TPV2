// This file is part of the course TPV2@UCM - Samir Genaim

#include "AsteroidsSystem.h"

#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../components/Generations.h"

void AsteroidsSystem::receive(const Message& m)
{
	if (m.id == _m_GAME_START || m.id == _m_ROUND_START) onRoundStart();
	else if (m.id == _m_GAME_OVER || m.id == _m_ROUND_OVER) onRoundOver();
	else if (m.id == _m_BULLET_HIT_ASTEROID) onCollision_AsteroidBullet(m.collision_bullet_fighter.asteroid);
}

AsteroidsSystem::AsteroidsSystem() : asteroidsTimer_(), active_(false), numOfAsteroids_(0), fighterTr_(nullptr){
}

AsteroidsSystem::~AsteroidsSystem() {
}

void AsteroidsSystem::initSystem() {
	
	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);

	fighterTr_ = mngr_->getComponent<Transform>(fighter);

	assert(fighterTr_ != nullptr);
}

void AsteroidsSystem::update() {

	if (active_) {

		for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {

			auto tr = mngr_->getComponent<Transform>(a);

			auto& pos = tr->pos_;

			if (mngr_->getComponent<Follow>(a) != nullptr) {
			
				auto& vel = tr->vel_;
				auto playerPos = fighterTr_->pos_;
				
				vel = vel.rotate(vel.angle(playerPos - pos) > 0 ? 1.0f : -1.0f);
			}

			tr->move();

			//show at opposite border
			int width = sdlutils().width();
			int height = sdlutils().height();

			if (pos.getX() > sdlutils().width()) pos.set(Vector2D(0, pos.getY()));
			else if (pos.getX() + tr->width_ < 0) pos.set(Vector2D(width, pos.getY()));

			if (pos.getY() > sdlutils().height()) pos.set(Vector2D(pos.getX(), 0));
			else if (pos.getY() + tr->height_ < 0) pos.set(Vector2D(pos.getX(), height));
		}

		addAsteroidFrequently();
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(ecs::Entity* a)
{
	mngr_->setAlive(a, false);

	numOfAsteroids_--;

	auto gensA = mngr_->getComponent<Generations>(a);
	auto tr = mngr_->getComponent<Transform>(a);

	if (gensA->generations_ > 0) {

		auto p = tr->pos_;
		auto v = tr->vel_;

		float w = 10.0f + 5.0f * (gensA->generations_ - 1);
		float h = w;

		for (int i = 0; i < 2; i++) {

			if (numOfAsteroids_ < 30) {
				auto r = sdlutils().rand().nextInt(0, 360);
				auto pos = p + v.rotate(r) * 2 * std::max(w, h);
				auto vel = v.rotate(r) * 1.1f;

				int type;
				if (mngr_->getComponent<Follow>(a) == nullptr)
					type = 0;

				else type = 1;

				createAsteroid(type, gensA->generations_ - 1, pos.getX(), pos.getY(), vel);
			}
		}
	}

	else if (numOfAsteroids_ <= 0) {
	
		Message m;
		m.game_over_info.winner_ = 2;
		m.id = _m_GAME_OVER;
		mngr_->send(m);
	}
}

void AsteroidsSystem::onRoundOver()
{
	active_ = false;

	destroyAllAsteroids();
}

void AsteroidsSystem::onRoundStart()
{
	active_ = true;

	createAsteroids(10);
}

void AsteroidsSystem::createAsteroids(int n)
{
	if (n + numOfAsteroids_ > 30) n = 30 - numOfAsteroids_;

	for (int i = 0; i < n; i++) {

		int generations = sdlutils().rand().nextInt(0, 4);

		int type;

		if (sdlutils().rand().nextInt(0, 10) < 3) type = 1;
		else type = 0;

		createAsteroid(type, generations);
	}
}

void AsteroidsSystem::createAsteroid(int type, int gens, int x, int y, Vector2D vel)
{
	int width = sdlutils().width();
	int height = sdlutils().height();

	ecs::Entity* asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);

	auto g = mngr_->addComponent<Generations>(asteroid, gens);

	auto tr_ = mngr_->addComponent<Transform>(asteroid);

	int border = sdlutils().rand().nextInt(0, 4);

	//height and width
	float w = 10.0f + 5.0f * g->generations_;

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

	if (type == 0) {

		mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid"), 5, 6, 50, 30);
	}

	else {

		mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid_gold"), 5, 6, 50, 30);
		mngr_->addComponent<Follow>(asteroid);
	}

	numOfAsteroids_++;
}

void AsteroidsSystem::addAsteroidFrequently()
{
	if (asteroidsTimer_.currTime() >= TIME_BETWEEN_ASTEROIDS && numOfAsteroids_ < 30) {

		createAsteroids(1);

		asteroidsTimer_.reset();
	}
}

void AsteroidsSystem::destroyAllAsteroids()
{
	for (auto ast : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {

		mngr_->setAlive(ast, false);
	}

	numOfAsteroids_ = 0;
}
