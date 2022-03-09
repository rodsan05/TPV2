// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/GameCtrl.h"
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
		mngr_(nullptr) {
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/asteroid.resources.json");

	// Create the manager
	mngr_ = new Manager();

	// create the PacMan entity
	//
	auto fighter = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_PACMAN, fighter);
	auto tr = fighter->addComponent<Transform>();
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	fighter->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighter->addComponent<FighterCtrl>();
	fighter->addComponent<ShowAtOppositeSide>();
	fighter->addComponent<DeAcceleration>();
	fighter->addComponent<Health>();
	fighter->addComponent<Gun>();

	// create the game info entity
	auto ginfo = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_GAMEINFO, ginfo);
	ginfo->addComponent<GameCtrl>();

	//asteroids manager
	auto astManager = new AsteroidsManager(mngr_);
	astManager->createAsteroids(10);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		checkCollisions();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() {

	// the PacMan's Transform
	//
	auto pTR = mngr_->getHandler(ecs::_hdlr_PACMAN)->getComponent<Transform>();

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &stars = mngr_->getEntities(ecs::_grp_STARS);
	auto n = stars.size();
	for (auto i = 0u; i < n; i++) {
		auto e = stars[i];
		if (e->isAlive()) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			//
			auto eTR = e->getComponent<Transform>();

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(pTR->getPos(), pTR->getWidth(),
					pTR->getHeight(), //
					eTR->getPos(), eTR->getWidth(), eTR->getHeight())) {
				e->setAlive(false);
				mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<GameCtrl>()->onStarEaten();

				// play sound on channel 1 (if there is something playing there
				// it will be cancelled
				//sdlutils().soundEffects().at("pacman_eat").play(0, 1);
			}
		}
	}
}
