// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

struct FighterCtrl: public ecs::Component {

	FighterCtrl();
	virtual ~FighterCtrl();

	float rotationSpeed_ = 5.0f;
	float thrust_ = 0.2f;
	float speedLimit_ = 3.0f;
};

