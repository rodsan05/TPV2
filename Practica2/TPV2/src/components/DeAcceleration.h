#pragma once
#include "../ecs/Component.h"

struct DeAcceleration : public ecs::Component
{
	__CMPID_DECL__(ecs::_DEACCELERATION)

	DeAcceleration() : deaccelValue_(0.955f) {}
	DeAcceleration(float deacceleration) : deaccelValue_(deacceleration) {}
	virtual ~DeAcceleration() {}

	float deaccelValue_;
};

