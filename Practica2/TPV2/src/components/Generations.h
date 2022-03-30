#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

struct Generations : public ecs::Component
{
	__CMPID_DECL__(ecs::_GENERATIONS)

	Generations() {
		generations_ = sdlutils().rand().nextInt(1, 4);
	}
	Generations(int n) {
		generations_ = n;
	}
	~Generations() {}

	int generations_;
};

