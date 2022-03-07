#include "DeAcceleration.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

DeAcceleration::DeAcceleration() : tr_(), deaccelValue_(0.955f)
{
}

DeAcceleration::DeAcceleration(float deacceleration) : tr_()
{
}

DeAcceleration::~DeAcceleration()
{
}

void DeAcceleration::initComponent()
{
	tr_ = ent_->getComponent<Transform>();

	bool comps = tr_ != nullptr;
	assert(comps);
}

void DeAcceleration::update()
{
	if (tr_->getVel().magnitude() > 0.05f) tr_->getVel().set(tr_->getVel() * deaccelValue_);
	else tr_->getVel().set(Vector2D(0, 0));
}
