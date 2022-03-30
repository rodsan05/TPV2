// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;

class DisableOnExit : public ecs::Component {

	__CMPID_DECL__(ecs::_ONBORDER)

	DisableOnExit() {}
	virtual ~DisableOnExit() {}
};

//void DisableOnExit::update() {
//
//	auto pos = tr_->getPos();
//
//	bool leftBorder = pos.getX() < 0;
//	bool rightBorder = pos.getX() + tr_->getWidth() > sdlutils().width();
//	bool topBorder = pos.getY() < 0;
//	bool bottomBorder = pos.getY() + tr_->getHeight() > sdlutils().height();
//	
//	if (leftBorder || rightBorder || topBorder || bottomBorder) 
//		ent_->setAlive(false);
//}
