// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

GameCtrlSystem::GameCtrlSystem() : state_(0), winner_(0) {
}

GameCtrlSystem::~GameCtrlSystem() {
}


void GameCtrlSystem::update() {
	
	if (state_ != 1) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			
			Message m;

			if (state_ == 0) {
			
				m.id = _m_GAME_START;
				state_ = 1;
			}

			else if (state_ == 2) {

				m.id = _m_ROUND_START;
				state_ = 1;
			}
			else {

				m.id = _m_NEW_GAME;
				state_ = 0;
			}

			mngr_->send(m);
		}
	}
}

void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_OVER:
		state_ = 2;
		break;
	case _m_GAME_OVER:
		state_ = 3;
		winner_ = m.game_over_info.winner_;
		break;
	default:
		break;
	}
}

void GameCtrlSystem::initSystem()
{
}

void GameCtrlSystem::onCollision_FighterAsteroid()
{
}

void GameCtrlSystem::onAsteroidsExtinction()
{
}
