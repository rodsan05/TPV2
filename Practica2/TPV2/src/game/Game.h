// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

namespace ecs {
class Manager;
}

class FighterSystem;
class GameCtrlSystem;
class CollisionsSystem;
class RenderSystem;
class BulletSystem;
class AsteroidsSystem;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	ecs::Manager *mngr_;

	FighterSystem *fighterSys_;
	GameCtrlSystem *gameCtrlSys_;
	CollisionsSystem *collisionsSys_;
	RenderSystem *renderSys_;
	BulletSystem* bulletSys_;
	AsteroidsSystem* asteroidsSys_;
};

