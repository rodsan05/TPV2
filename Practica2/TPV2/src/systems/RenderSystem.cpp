// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include <SDL_rect.h>
#include "../components/Image.h"
#include "../components/RectangleViewer.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "../components/FramedImage.h"
#include "../components/Health.h"

RenderSystem::RenderSystem() : winner_(0), state_(0){
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawMsgs();

	if (state_ != 3) {
		drawLives();
		drawBullets();
		drawFighter();
		drawAsteroids();
	}
}

void RenderSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_GAME_START: onGameStart();
		break;
	case _m_GAME_OVER: onGameOver(m.game_over_info.winner_);
		break;
	case _m_ROUND_START: onRoundStart();
		break;
	case _m_ROUND_OVER: onRoundOver();
		break;
	case _m_NEW_GAME: onNewGame();
		break;
	default:
		break;
	}
}

void RenderSystem::drawMsgs() {
	auto state = mngr_->getSystem<GameCtrlSystem>()->getState();

	// message when game is not running
	if (state != 1) {

		// game over message
		if (state == 3) {

			if (winner_ == 2) {

				auto& t = sdlutils().msgs().at("victory");

				t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
			}

			else {
			
				auto& t = sdlutils().msgs().at("gameover");

				t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
			}
		}

		// new game message
		if (state == 0) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}
}

void RenderSystem::drawBullets() {
	
	for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) {

		auto bulletTr_ = mngr_->getComponent<Transform>(b);
		auto img_ = mngr_->getComponent<Image>(b);

		renderImage(bulletTr_, img_);
	}
}

void RenderSystem::drawFighter() {
	
	auto fighter_ = mngr_->getHandler(ecs::_hdlr_FIGHTER);

	auto tr_ = mngr_->getComponent<Transform>(fighter_);
	auto img_ = mngr_->getComponent<Image>(fighter_);

	renderImage(tr_, img_);
}

void RenderSystem::drawLives()
{
	float heartPos = 5;

	auto fighter_ = mngr_->getHandler(ecs::_hdlr_FIGHTER);
	auto health = mngr_->getComponent<Health>(fighter_);

	assert(health->text_ != nullptr);

	for (int i = 0; i < health->lives; i++) {

		Vector2D* pos = new Vector2D(heartPos, 5);
		SDL_Rect dest = build_sdlrect(*pos, health->HEART_WIDTH, health->HEART_HEIGHT);
		health->text_->render(dest);

		heartPos += health->HEART_WIDTH + 5;
	}
}

void RenderSystem::drawAsteroids()
{
	for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {

		auto framedImg_ = mngr_->getComponent<FramedImage>(a);
		auto tr_ = mngr_->getComponent<Transform>(a);

		changeFrame(framedImg_);

		renderFrame(framedImg_, tr_);
	}
}


void RenderSystem::renderImage(Transform* tr_, Image* img_)
{
	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);

	assert(img_->tex_ != nullptr);
	img_->tex_->render(dest, tr_->rot_);
}

void RenderSystem::renderFrame(FramedImage* framedImg_, Transform* tr_)
{
	int column = framedImg_->currentFrame_ % framedImg_->columns_;
	int row = framedImg_->currentFrame_ / framedImg_->columns_;

	Vector2D* posSrc = new Vector2D(column * framedImg_->frameWidth_, row * framedImg_->frameHeight_);

	SDL_Rect src = build_sdlrect(*posSrc, framedImg_->frameWidth_, framedImg_->frameHeight_);
	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);

	assert(framedImg_->text_ != nullptr);
	framedImg_->text_->render(src, dest, tr_->rot_);
}

void RenderSystem::changeFrame(FramedImage* framedImg_)
{
	int time = sdlutils().currRealTime();

	//si ha pasado el tiempo entre frames
	if (time - framedImg_->lastTimeFrameChanged_ >= framedImg_->timeBetweenFrames_) {

		//si ha llegado al ultimo frame pone currentFrame_ a 0
		if (framedImg_->currentFrame_ >= framedImg_->nFrames_ - 1) framedImg_->currentFrame_ = 0;

		else framedImg_->currentFrame_++;

		framedImg_->lastTimeFrameChanged_ = time;
	}
}

void RenderSystem::onRoundStart()
{
	state_ = 1;
}

void RenderSystem::onRoundOver()
{
	state_ = 2;
}

void RenderSystem::onGameStart()
{
	state_ = 1;
}

void RenderSystem::onGameOver(Uint8 w)
{
	state_ = 3;

	winner_ = w;
}

void RenderSystem::onNewGame()
{
	state_ = 0;
}
