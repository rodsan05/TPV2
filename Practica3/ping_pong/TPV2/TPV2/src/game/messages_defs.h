// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER, //
	_m_GAME_OVER, //
	_m_NEW_GAME, //
	_m_BALL_EXIT
};


struct Message {
	msgId_type id;

	union {

		// _m_CREATE_STARS
		struct {
			uint8_t side;
		} ball_exit;

	};
};
