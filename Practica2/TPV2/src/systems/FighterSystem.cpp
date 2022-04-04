// This file is part of the course TPV2@UCM - Samir Genaim

#include "FighterSystem.h"

#include "../components/PaddleCtrl.h"
#include "../components/RectangleViewer.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../components/Gun.h"

FighterSystem::FighterSystem() :
		fighterTr_(nullptr) {
}

FighterSystem::~FighterSystem() {
}

void FighterSystem::initSystem() {
	
	// create the left paddle
	fighter_ = mngr_->addEntity();

	fighterTr_ = mngr_->addComponent<Transform>(fighter_);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	fighterTr_->init(Vector2D(x, y), Vector2D(),
			s, s, 0.0f);

	mngr_->addComponent<Image>(fighter_, sdlutils().images().at("fighter"));
	mngr_->addComponent<FighterCtrl>(fighter_);
	mngr_->addComponent<DeAcceleration>(fighter_);
	mngr_->addComponent<Health>(fighter_);
	mngr_->addComponent<Gun>(fighter_);
}

void FighterSystem::recieve(const Message& m)
{
}

void FighterSystem::update() {
	
	if (active_) {

		moveFighter(fighter_);
	}
}

void FighterSystem::moveFighter(ecs::Entity *fighter) {
	
	auto fighterCtrl = mngr_->getComponent<FighterCtrl>(fighter);

	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(fighterCtrl->left_)) {
			fighterTr_->rot_ = fighterTr_->rot_ - fighterCtrl->rotationSpeed_;
		}
		else if (ihdlr.isKeyDown(fighterCtrl->right_)) {
			fighterTr_->rot_ = fighterTr_->rot_ + fighterCtrl->rotationSpeed_;
		}

		if (ihdlr.isKeyDown(fighterCtrl->up_)) {
			Vector2D newVel = fighterTr_->vel_ + Vector2D(0, -1).rotate(fighterTr_->rot_) * fighterCtrl->thrust_;

			if (newVel.magnitude() > fighterCtrl->speedLimit_) newVel = newVel.normalize() * fighterCtrl->speedLimit_;

			fighterTr_->vel_ = newVel;;
		}
	}

	fighterTr_->move();

	//show at opposite border
	auto& pos = fighterTr_->pos_;
	int width = sdlutils().width();
	int height = sdlutils().height();
	
	if (pos.getX() > sdlutils().width()) pos.set(Vector2D(0, pos.getY()));
	else if (pos.getX() + fighterTr_->width_ < 0) pos.set(Vector2D(width, pos.getY()));
	
	if (pos.getY() > sdlutils().height()) pos.set(Vector2D(pos.getX(), 0));
	else if (pos.getY() + fighterTr_->height_ < 0) pos.set(Vector2D(pos.getX(), height));
}

void FighterSystem::onCollision_FighterAsteroid()
{
}

void FighterSystem::onRoundOver()
{
	active_ = false;
}

void FighterSystem::onRoundStart()
{
	active_ = true;
}

