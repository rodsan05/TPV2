#include "Follow.h"

#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"

Follow::Follow() : tr_(), trPlayer_()
{
}

Follow::~Follow()
{
}

void Follow::initComponent()
{
	tr_ = ent_->getComponent<Transform>();

	trPlayer_ = mngr_->getHandler(ecs::_hdlr_FIGHTER)->getComponent<Transform>();

	bool correct = tr_ != nullptr && trPlayer_ != nullptr;
	assert(correct);
}

void Follow::update()
{
	auto pos = tr_->getPos();
	auto& vel = tr_->getVel();
	auto playerPos = trPlayer_->getPos();

	vel = vel.rotate(vel.angle(playerPos - pos) > 0 ? 1.0f : -1.0f);
}
