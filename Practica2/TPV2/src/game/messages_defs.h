// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER, //
	_m_GAME_START, //
	_m_GAME_OVER, //
	_m_NEW_GAME, //
	_m_CONTINUE, //
	_m_BALL_HIT_PADDLE
};


struct Message {
	msgId_type id;

	union {

		struct {
			uint8_t winner_;
			uint8_t state_;
		} state_change_;

		struct {
			ecs::Entity *e;
		} ball_hit_paddle;

	};
};
