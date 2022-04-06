// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <cstdint>
#include <SDL_stdinc.h>

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
	void receive(const Message& m) override;
	void initSystem() override;

private:

	void onCollision_FighterAsteroid();

	void onAsteroidsExtinction();

	Uint8 winner_; // 0 - None, 1 - Asteroids, 2- Fighter
	Uint8 state_;  // El estado actual del juego (en lugar del componente State). 0 - start, 1 - playing, 2 - paused, 3 - round ended
};

