// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"
#include <SDL_stdinc.h>

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER, //
	_m_GAME_START, //
	_m_GAME_OVER, //
	_m_NEW_GAME, //
	_m_BULLET_HIT_ASTEROID, //
	_m_ASTEROID_HIT_FIGHTER
};


struct Message {
	msgId_type id;

	union {

		struct {
			ecs::Entity* asteroid;
			ecs::Entity* bullet;
		} collision_bullet_fighter;

		struct {
			Uint8 winner_;
		} game_over_info;

	};
};
