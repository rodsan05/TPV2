// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <cstdint>

#include "../ecs/System.h"

class GameCtrlSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_GAMECTRL)

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	inline Uint8 getState() {
		return state_;
	}

	void update() override;
	void recieve(const Message&) override;
	void initSystem() override;

private:

	void onCollision_FighterAsteroid();

	void onAsteroidsExtinction();

	Uint8 winner_;
	Uint8 state_;
};

