// This file is part of the course TPV2@UCM - Samir Genaim

#include "DisableOnExit.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

DisableOnExit::DisableOnExit() :
		tr_() {
}

DisableOnExit::~DisableOnExit() {
}

void DisableOnExit::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DisableOnExit::update() {

	auto pos = tr_->getPos();

	bool leftBorder = pos.getX() < 0;
	bool rightBorder = pos.getX() + tr_->getWidth() > sdlutils().width();
	bool topBorder = pos.getY() < 0;
	bool bottomBorder = pos.getY() + tr_->getHeight() > sdlutils().height();
	
	if (leftBorder || rightBorder || topBorder || bottomBorder) 
		ent_->setAlive(false);
}
