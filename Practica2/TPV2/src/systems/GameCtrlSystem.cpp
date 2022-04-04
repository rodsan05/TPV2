// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

GameCtrlSystem::GameCtrlSystem() {
}

GameCtrlSystem::~GameCtrlSystem() {
}


void GameCtrlSystem::update() {
	
	if (state_ != 1) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			
			if (state_ == 0) {
				
				Message m;
				m.id = _m_GAME_START;
				mngr_->send(m);
			}
			else if (state_ == 2) {

				Message m;
				m.id = _m_CONTINUE;
				mngr_->send(m);
			}
			else if (state_ == 3) {
			
				Message m;
				m.id = _m_ROUND_START;
				mngr_->send(m);
			}
		}
	}
}

void GameCtrlSystem::recieve(const Message&)
{
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
