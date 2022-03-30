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
			
		}
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
