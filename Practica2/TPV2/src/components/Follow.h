#pragma once
#include "../ecs/Component.h"

struct Follow : public ecs::Component
{
	__CMPID_DECL__(ecs::_FOLLOW)

	Follow() {}
	virtual ~Follow() {}
};

//void Follow::update()
//{
//	auto pos = tr_->getPos();
//	auto& vel = tr_->getVel();
//	auto playerPos = trPlayer_->getPos();
//
//	vel = vel.rotate(vel.angle(playerPos - pos) > 0 ? 1.0f : -1.0f);
//}

