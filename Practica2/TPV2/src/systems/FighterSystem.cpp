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
		fighterTr_(nullptr), fighter_(), active_(false) {
}

FighterSystem::~FighterSystem() {
}

void FighterSystem::initSystem() {
	
	fighter_ = mngr_->addEntity();

	mngr_->setHandler(ecs::_hdlr_FIGHTER, fighter_);

	fighterTr_ = mngr_->addComponent<Transform>(fighter_);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	fighterTr_->init(Vector2D(x, y), Vector2D(),
			s, s, 0.0f);

	mngr_->addComponent<Image>(fighter_, &sdlutils().images().at("fighter"));
	auto ctrl = mngr_->addComponent<FighterCtrl>(fighter_);
	mngr_->addComponent<DeAcceleration>(fighter_);
	mngr_->addComponent<Health>(fighter_);
	mngr_->addComponent<Gun>(fighter_);
}

void FighterSystem::receive(const Message& m)
{
	if (m.id == _m_GAME_START || m.id == _m_ROUND_START) onRoundStart();
	else if (m.id == _m_ROUND_OVER) onRoundOver();
	else if (m.id == _m_GAME_OVER) onGameOver();
	else if (m.id == _m_ASTEROID_HIT_FIGHTER) onCollision_FighterAsteroid();
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

			sdlutils().soundEffects().at("thrust").play();
			sdlutils().soundEffects().at("thrust").setVolume(10);
		}
	}

	fighterTr_->move();

	//deacceleration
	auto deaccel = mngr_->getComponent<DeAcceleration>(fighter);
	if (fighterTr_->vel_.magnitude() > 0.05f) fighterTr_->vel_.set(fighterTr_->vel_ * deaccel->deaccelValue_);
	else fighterTr_->vel_.set(Vector2D(0, 0));

	//show at opposite border
	auto& pos = fighterTr_->pos_;
	int width = sdlutils().width();
	int height = sdlutils().height();
	
	if (pos.getX() > sdlutils().width()) pos.set(Vector2D(0, pos.getY()));
	else if (pos.getX() + fighterTr_->width_ < 0) pos.set(Vector2D(width, pos.getY()));
	
	if (pos.getY() > sdlutils().height()) pos.set(Vector2D(pos.getX(), 0));
	else if (pos.getY() + fighterTr_->height_ < 0) pos.set(Vector2D(pos.getX(), height));
}

void FighterSystem::returnToCenter()
{
	auto s = fighterTr_->width_;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	fighterTr_->pos_ = Vector2D(x, y);
	fighterTr_->rot_ = 0;
	fighterTr_->vel_ = Vector2D(0, 0);
}

void FighterSystem::onCollision_FighterAsteroid()
{
	auto health = mngr_->getComponent<Health>(fighter_);

	health->doDamage(1);

	sdlutils().soundEffects().at("explosion").play();
	sdlutils().soundEffects().at("explosion").setVolume(10);

	if (health->lives > 0) {
	
		Message m;
		m.id = _m_ROUND_OVER;
		mngr_->send(m);
	}

	else {
	
		Message m;
		m.id = _m_GAME_OVER;
		mngr_->send(m);
	}
}

void FighterSystem::onRoundOver()
{
	active_ = false;

	returnToCenter();
}

void FighterSystem::onRoundStart()
{
	active_ = true;
}

void FighterSystem::onGameOver()
{
	active_ = false;

	auto health = mngr_->getComponent<Health>(fighter_);
	health->resetLives();

	returnToCenter();
}

