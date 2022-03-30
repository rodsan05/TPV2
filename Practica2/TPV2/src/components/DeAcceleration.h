#pragma once
#include "../ecs/Component.h"

struct DeAcceleration : public ecs::Component
{
	__CMPID_DECL__(ecs::_FOLLOW)

	DeAcceleration() : deaccelValue_(0.955f) {}
	DeAcceleration(float deacceleration) : deaccelValue_(deacceleration) {}
	virtual ~DeAcceleration() {}

	float deaccelValue_;
};

//void DeAcceleration::update()
//{
//	if (tr_->getVel().magnitude() > 0.05f) tr_->getVel().set(tr_->getVel() * deaccelValue_);
//	else tr_->getVel().set(Vector2D(0, 0));
//}

