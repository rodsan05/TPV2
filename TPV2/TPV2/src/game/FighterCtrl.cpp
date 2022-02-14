#include "FighterCtrl.h"

#include "../sdlutils/InputHandler.h"
#include "Container.h"

void FighterCtrl::handleInput(Container* o)
{
	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(SDLK_LEFT)) {
			o->setRotation(o->getRotation() - rotationSpeed_);
		}
		else if (ihdlr.isKeyDown(SDLK_RIGHT)) {
			o->setRotation(o->getRotation() + rotationSpeed_);
		}

		if (ihdlr.isKeyDown(SDLK_UP)) {
			Vector2D newVel = o->getVel() + Vector2D(0, -1).rotate(o->getRotation()) * thrust_;
			
			if (newVel.magnitude() > speedLimit_) newVel = newVel.normalize()*speedLimit_;
			
			o->getVel().set(newVel);
		}
	}
}
