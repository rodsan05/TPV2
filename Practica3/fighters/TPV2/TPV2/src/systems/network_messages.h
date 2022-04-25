// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../sdlutils/SDLNetUtils.h"

namespace net {

enum MsgId : Uint8 {
	_CONNECTION_REQUEST, //
	_REQUEST_ACCEPTED, //
	_REQUEST_REFUSED, //
	_FIGHTER_POS, //
	_FIGHTER_VEL, //
	_BULLET_POS, //
	_BULLETS_VEL, //
	_START_GAME_REQUEST, //
	_START_THE_GAME, //
	_GAME_OVER_REQUEST, //
	_GAME_OVER, //
	_BULLET_HIT_FIGHTER, //
	_DISCONNECTING
};

struct Message {
	Uint8 id;

	//
	_IMPL_SERIALIAZION_(id)
};

struct ReqAccMsg: Message {

	Uint8 side;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side)
};

struct FighterPosMsg: Message {

	Uint8 side;
	float x;
	float y;
	float rot;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y,rot)
};

struct BulletPosMsg: Message {

	Uint8 side;
	float x;
	float y;
	float rot;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y)
};

struct BulletVelMsg: Message {

	Uint8 side;
	float x;
	float y;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side,x,y)
};

struct StartRequestMsg: Message {

	Uint8 side;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,side)
};

struct BulletHitFighterMsg: Message {

	Uint8 winner;

	//
	_IMPL_SERIALIAZION_WITH_BASE_(Message,winner)
};

}

