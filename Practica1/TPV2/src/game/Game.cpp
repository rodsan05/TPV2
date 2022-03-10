// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/StopOnBorders.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../components/Gun.h"
#include "../game/AsteroidsManager.h"

using ecs::Entity;
using ecs::Manager;

Game::Game() :
		mngr_(nullptr), astManager_(nullptr), game_state(START), victory_(true){
}

Game::~Game() {
	delete mngr_;
	delete astManager_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/asteroid.resources.json");

	// Create the manager
	mngr_ = new Manager();

	// create the PacMan entity
	//
	fighter_ = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_FIGHTER, fighter_);
	auto tr = fighter_->addComponent<Transform>();
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	fighter_->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighter_->addComponent<FighterCtrl>();
	fighter_->addComponent<ShowAtOppositeSide>();
	fighter_->addComponent<DeAcceleration>();
	fighter_->addComponent<Health>();
	fighter_->addComponent<Gun>();

	//asteroids manager
	astManager_ = new AsteroidsManager(mngr_);
	astManager_->createAsteroids(10);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		if (game_state == START) {
		
			if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {

				game_state = PLAYING;
			}

			renderMessage("start");
		}

		else if (game_state == PLAYING) {

			Uint32 startTime = sdlutils().currRealTime();

			mngr_->update();
			mngr_->refresh();

			astManager_->addAsteroidFrequently();

			checkCollisions();

			if (astManager_->hasPlayerWon()) game_state == GAMEOVER;

			sdlutils().clearRenderer();
			mngr_->render();
			sdlutils().presentRenderer();

			Uint32 frameTime = sdlutils().currRealTime() - startTime;

			if (frameTime < 10)
				SDL_Delay(10 - frameTime);
		}

		else if (game_state == CONTINUE) {

			if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {

				game_state = PLAYING;
				astManager_->createAsteroids(10);
			}

			renderMessage("continue");
		}

		else if (game_state == GAMEOVER) {

			if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {

				game_state = START;
				astManager_->createAsteroids(10);

				fighter_->getComponent<Health>()->resetLives();
			}

			renderGameOver();
		}
	}

}

void Game::checkCollisions() {

	auto player = mngr_->getHandler(ecs::_hdlr_FIGHTER);
	auto pTr = player->getComponent<Transform>();
	auto pHealth = player->getComponent<Health>();

	auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	auto n = asteroids.size();
	auto p = bullets.size();

	for (auto i = 0u; i < n; i++) {

		auto a = asteroids[i];
		if (a->isAlive()) {

			//collision bullets
			auto aTr = a->getComponent<Transform>();

			for (auto j = 0u; j < p; j++) {

				auto b = bullets[j];
				if (b->isAlive()) {

					auto bTr = b->getComponent<Transform>();

					if (Collisions::collidesWithRotation(aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot(),
						bTr->getPos(), bTr->getWidth(), bTr->getHeight(), bTr->getRot())) {

						a->setAlive(false);
						astManager_->onCollision(a);
					}
				}
			}

			//collision player

			if (Collisions::collidesWithRotation(aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot(),
				pTr->getPos(), pTr->getWidth(), pTr->getHeight(), pTr->getRot())) {

				//destroy asteroid
				astManager_->destroyAllAsteroids();

				//destroy bullets
				for (auto j = 0u; j < p; j++) {

					auto b = bullets[j];
					if (b->isAlive()) {

						b->setAlive(false);
					}
				}

				auto cx = sdlutils().width() / 2 - pTr->getWidth() / 2;
				auto cy = sdlutils().height() / 2 - pTr->getHeight() / 2;

				pTr->getPos().set(cx, cy);
				pTr->getVel().set(Vector2D(0.0f, 0.0f));
				pTr->setRot(0.0f);

				pHealth->doDamage(1);

				if (pHealth->actualLives() > 0) game_state = CONTINUE;

				else {

					game_state = GAMEOVER;
					victory_ = false;
				}
			}
		}
	}
}

void Game::renderGameOver()
{
	int width = sdlutils().width();
	int height = sdlutils().height();

	Texture* text = &sdlutils().msgs().at("continue");
	
	Texture* gameOverText;
	if (!victory_) gameOverText = &sdlutils().msgs().at("gameover");
	else gameOverText = &sdlutils().msgs().at("victory");

	int cx = sdlutils().width() / 2 - text->width() / 2;
	int cy = sdlutils().height() / 2 - text->height() / 2;

	sdlutils().clearRenderer();
	text->render(cx, cy + 50);

	cx = sdlutils().width() / 2 - gameOverText->width() / 2;
	cy = sdlutils().height() / 2 - gameOverText->height() / 2;
	gameOverText->render(cx, cy - 100);

	fighter_->getComponent<Image>()->render();
	fighter_->getComponent<Health>()->render();
	sdlutils().presentRenderer();
}

void Game::renderMessage(std::string name)
{
	int width = sdlutils().width();
	int height = sdlutils().height();

	Texture* text = &sdlutils().msgs().at(name);

	int cx = sdlutils().width() / 2 - text->width() / 2;
	int cy = sdlutils().height() / 2 - text->height() / 2;

	sdlutils().clearRenderer();
	text->render(cx, cy + 50);
	fighter_->getComponent<Image>()->render();
	fighter_->getComponent<Health>()->render();
	sdlutils().presentRenderer();
}