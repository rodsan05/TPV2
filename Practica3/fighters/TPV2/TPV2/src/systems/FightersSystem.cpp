// This file is part of the course TPV2@UCM - Samir Genaim

#include "FightersSystem.h"

#include "../components/CtrlKeys.h"
#include "../components/FighterInfo.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "NetworkSystem.h"

using ecs::Entity;

FightersSystem::FightersSystem() :
		tr_(nullptr), trOther_(nullptr), side_(0), running_(false) {
}

FightersSystem::~FightersSystem() {
}

void FightersSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_GAME_START:
		handleGameStart(m);
		break;
	case _m_GAME_OVER:
		handleGameOver(m);
		break;
	case _m_BULLET_HIT_FIGHTER:
		handleBulletHitFighter(m);
		break;
	default:
		break;
	}
}

void FightersSystem::initSystem() {

	auto h = 50.0f;
	auto w = 50.0f;

	// Fighter 0
	//
	auto fighter0 = mngr_->addEntity(ecs::_grp_FIGHTERS);
	mngr_->setHandler(ecs::_hdlr_FIGHTER_0, fighter0);

	mngr_->addComponent<FighterInfo>(fighter0, 0);

	auto tr0 = mngr_->addComponent<Transform>(fighter0, //
			Vector2D(10.0f, (sdlutils().height() - h) / 2.0f), //
			Vector2D(), //
			w, //
			h, //
			90.0f);

	mngr_->addComponent<Image>(fighter0, //
			&sdlutils().images().at("airplanes"), //
			build_sdlrect(45.0f, 90.0f, 205.0f, 245.0f));

	mngr_->addComponent<CtrlKeys>(fighter0, //
			SDL_SCANCODE_UP, //
			SDL_SCANCODE_DOWN, //
			SDL_SCANCODE_LEFT, //
			SDL_SCANCODE_RIGHT, //
			SDL_SCANCODE_S);

	// Fighter 1
	//
	auto fighter1 = mngr_->addEntity(ecs::_grp_FIGHTERS);
	mngr_->setHandler(ecs::_hdlr_FIGHTER_1, fighter1);

	mngr_->addComponent<FighterInfo>(fighter1, 1);

	auto tr1 = mngr_->addComponent<Transform>(
			fighter1, //
			Vector2D(sdlutils().width() - w - 10.0f,
					(sdlutils().height() - h) / 2.0f), //
			Vector2D(), //
			w, //
			h, //
			-90.0f);

	mngr_->addComponent<Image>(fighter1, //
			&sdlutils().images().at("airplanes"), //
			build_sdlrect(805.0f, 125.0f, 310.0f, 165.0f)); //

	if (side_ == 0) 
	{
		tr_ = tr0;
		trOther_ = tr1;
	}

	else 
	{
		tr_ = tr1;
		trOther_ = tr0;
	}
}

void FightersSystem::update() {
	if (!running_)
		return;

	auto &ihdlr = ih();

	Entity* fighter;

	fighter = mngr_->getEntities(ecs::_grp_FIGHTERS)[side_];

	auto tr = mngr_->getComponent<Transform>(fighter);
	auto keys = mngr_->getComponent<CtrlKeys>(fighter);

	// handle input
	if (ihdlr.isKeyDown(keys->up_)) {
		auto thrust_ = 0.2f;
		if (tr->vel_.magnitude() < 5.0f)
			tr->vel_ = tr->vel_
			+ Vector2D(0, -1).rotate(tr->rot_) * thrust_;
	}
	else if (ihdlr.isKeyDown(keys->right_)) {
		tr->rot_ += 2.0f;
	}

	if (ihdlr.isKeyDown(keys->down_)) {
		tr->vel_ = tr->vel_ * 0.75f;
	}
	else if (ihdlr.isKeyDown(keys->left_)) {
		tr->rot_ -= 2.0f;
	}

	if (ihdlr.isKeyDown(keys->shoot_)) {
		auto fInfo = mngr_->getComponent<FighterInfo>(fighter);
		if (fInfo->lastShoot_ + fInfo->shootRate_
			< sdlutils().currRealTime()) {
			auto bPos = tr->pos_
				+ Vector2D(tr->width_ / 2.0f, tr->height_ / 2.0f)
				- Vector2D(0.0f, tr->height_ / 2.0f + 5.0f).rotate(
					tr->rot_);
			auto bVel = Vector2D(0.0f, -1.0f).rotate(tr->rot_)
				* (tr->vel_.magnitude() + 5.0f);
			Message m;
			m.id = _m_SHOOT;
			m.shoot.pos.x = bPos.getX();
			m.shoot.pos.y = bPos.getY();
			m.shoot.vel.x = bVel.getX();
			m.shoot.vel.y = bVel.getY();
			mngr_->send(m);
			fInfo->lastShoot_ = sdlutils().currRealTime();
		}
	}

	// move
	tr->move();

	// reduce velocity
	tr->vel_ = tr->vel_ * 0.99f;
	if (tr->vel_.magnitude() < 0.1f)
		tr->vel_ = Vector2D(0.0f, 0.0f);

	// show at opposite side
	if (tr->pos_.getX() < -tr->width_) {
		tr->pos_.setX(sdlutils().width());
	}
	else if (tr->pos_.getX() > sdlutils().width()) {
		tr->pos_.setX(-tr->width_);
	}

	if (tr->pos_.getY() < -tr->height_) {
		tr->pos_.setY(sdlutils().height());
	}
	else if (tr->pos_.getY() > sdlutils().height()) {
		tr->pos_.setY(-tr->height_);
	}

	auto netSys = mngr_->getSystem<NetworkSystem>();

	netSys->sendFighterPosition(tr);
}

void FightersSystem::setSide(int side)
{
	side_ = side;
}

void FightersSystem::setOtherFighterPos(float x, float y, float rot)
{
	trOther_->pos_.setX(x);
	trOther_->pos_.setY(y);

	trOther_->rot_ = rot;
}

void FightersSystem::setOtherFighterVel(float x, float y)
{
	trOther_->vel_.setX(x);
	trOther_->vel_.setY(y);
}

void FightersSystem::handleGameStart(const Message&) {
	running_ = true;
}

void FightersSystem::handleGameOver(const Message&) {
	
	int dir;
	if (side_ == 0) dir = 1;
	else dir = -1;

	running_ = false;
	tr_->pos_ = Vector2D(10.0f, (sdlutils().height() - tr_->height_) / 2.0f);
	tr_->vel_ = Vector2D();
	tr_->rot_ = 90.0f * dir;
}

void FightersSystem::handleBulletHitFighter(const Message&) {
	sdlutils().soundEffects().at("explosion").play();
}
