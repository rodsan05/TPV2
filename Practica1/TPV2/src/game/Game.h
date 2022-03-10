// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include <string>

class AsteroidsManager;

namespace ecs {
class Manager;
class Entity;
}

enum State { START, PLAYING, CONTINUE, GAMEOVER };

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	void checkCollisions();

	void renderMessage(std::string name);

	void renderGameOver();

	ecs::Manager *mngr_;

	AsteroidsManager* astManager_;

	ecs::Entity* fighter_;

	State game_state;

	bool victory_;
};

