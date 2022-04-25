// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

struct FighterCtrl: public ecs::Component {

	__CMPID_DECL__(ecs::_FIGHTERCTRL)

	FighterCtrl() : up_(SDL_SCANCODE_UP), left_(SDL_SCANCODE_LEFT), right_(SDL_SCANCODE_RIGHT) {}
	virtual ~FighterCtrl() {}

	inline void setKeys(SDL_Scancode up, SDL_Scancode left, SDL_Scancode right) {
		up_ = up;
		left_ = left;
		right_ = right;
	}

	float rotationSpeed_ = 5.0f;
	float thrust_ = 0.2f;
	float speedLimit_ = 3.0f;

	SDL_Scancode up_;
	SDL_Scancode left_;
	SDL_Scancode right_;
};

