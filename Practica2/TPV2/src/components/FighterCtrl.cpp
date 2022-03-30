// This file is part of the course TPV2@UCM - Samir Genaim

#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
		tr_(nullptr) {
}

FighterCtrl::~FighterCtrl() {
}

//void FighterCtrl::update() {
//
//	auto& ihdlr = ih();
//
//	if (ihdlr.keyDownEvent()) {
//		if (ihdlr.isKeyDown(SDLK_LEFT)) {
//			tr_->setRot(tr_->getRot() - rotationSpeed_);
//		}
//		else if (ihdlr.isKeyDown(SDLK_RIGHT)) {
//			tr_->setRot(tr_->getRot() + rotationSpeed_);
//		}
//
//		if (ihdlr.isKeyDown(SDLK_UP)) {
//			Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * thrust_;
//
//			if (newVel.magnitude() > speedLimit_) newVel = newVel.normalize() * speedLimit_;
//
//			tr_->getVel().set(newVel);
//		}
//	}
//}
