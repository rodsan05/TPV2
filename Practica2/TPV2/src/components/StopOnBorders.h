// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

struct StopOnBorders: public ecs::Component {

	__CMPID_DECL__(ecs::_ONBORDER)

	StopOnBorders() {}
	virtual ~StopOnBorders() {}
};

//void StopOnBorders::update() {
//	auto& pos = tr_->getPos();
//	auto& vel = tr_->getVel();
//
//	// check left/right borders
//	if (pos.getX() < 0) {
//		pos.setX(0.0f);
//		vel.set(0.0f, 0.0f);
//	}
//	else if (pos.getX() + tr_->getWidth() > sdlutils().width()) {
//		pos.setX(sdlutils().width() - tr_->getWidth());
//		vel.set(0.0f, 0.0f);
//	}
//
//	// check upper/lower borders
//	if (pos.getY() < 0) {
//		pos.setY(0.0f);
//		vel.set(0.0f, 0.0f);
//	}
//	else if (pos.getY() + tr_->getHeight() > sdlutils().height()) {
//		pos.setY(sdlutils().height() - tr_->getHeight());
//		vel.set(0.0f, 0.0f);
//	}
//}

