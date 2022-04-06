// This file is part of the course TPV2@UCM - Samir Genaim

#include "BulletSystem.h"

#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void BulletSystem::receive(const Message& m)
{
	if (m.id == _m_GAME_START) onRoundStart();
	else if (m.id == _m_GAME_OVER) onRoundOver();
}

BulletSystem::BulletSystem() : fighterTr_(), fighter_(), bulletTimer_(), active_(false){
}

BulletSystem::~BulletSystem() {
}

void BulletSystem::initSystem() {
	
	fighter_ = mngr_->getHandler(ecs::_hdlr_FIGHTER);
	fighterTr_ = mngr_->getComponent<Transform>(fighter_);

	assert(fighterTr_ != nullptr);
}

void BulletSystem::update() {

	if (active_) {

		for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) {

			auto tr = mngr_->getComponent<Transform>(b);
			tr->move();

			auto pos = tr->pos_;

			//disable on exit
			bool leftBorder = pos.getX() < 0;
			bool rightBorder = pos.getX() + tr->width_ > sdlutils().width();
			bool topBorder = pos.getY() < 0;
			bool bottomBorder = pos.getY() + tr->height_ > sdlutils().height();

			if (leftBorder || rightBorder || topBorder || bottomBorder)
				mngr_->setAlive(b, false);
		}

		checkShootInput();
	}
}

void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);

	auto tr = mngr_->addComponent<Transform>(bullet);

	auto posB = pos + Vector2D(width / 2.0f, height / 2.0f) - Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(fighterTr_->rot_) - Vector2D(2.0f, 10.0f);
	auto bVel = Vector2D(0.0f, -1.0f).rotate(fighterTr_->rot_) * (vel.magnitude() + 5.0f);
	
	tr->init(posB, bVel, BULLET_HEIGHT, BULLET_WIDTH, fighterTr_->rot_);

	mngr_->addComponent<Image>(bullet, &sdlutils().images().at("fire"));
}

void BulletSystem::onCollision_BulletAsteroid(ecs::Entity* b)
{
}

void BulletSystem::onRoundOver()
{
	active_ = false;
}

void BulletSystem::onRoundStart()
{
	active_ = true;
}

void BulletSystem::checkShootInput()
{
	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {

		if (ihdlr.isKeyDown(SDL_SCANCODE_S) && bulletTimer_.currTime() >= TIME_BETWEEN_SHOTS) {

			shoot(fighterTr_->pos_, fighterTr_->vel_, fighterTr_->width_, fighterTr_->height_);
			bulletTimer_.reset();
		}
	}
}
