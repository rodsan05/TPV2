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

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawMsgs();
	drawScore();
	drawBullets();
	drawFighter();
}

void RenderSystem::drawMsgs() {
	auto state = mngr_->getSystem<GameCtrlSystem>()->getState();

	// message when game is not running
	if (state != 1) {

		// game over message
		if (state == 3) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
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

void RenderSystem::drawScore() {

	//auto leftScore = mngr_->getSystem<GameCtrlSystem>()->getScore(0);
	//auto rightScore = mngr_->getSystem<GameCtrlSystem>()->getScore(1);

	//Texture scoreMsg(
	//		sdlutils().renderer(), //
	//		std::to_string(leftScore) + " - " + std::to_string(rightScore),
	//		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	//scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}

void RenderSystem::drawBullets() {
	
	for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) {

		auto bulletTr_ = mngr_->getComponent<Transform>(b);

		SDL_Rect dest = build_sdlrect(bulletTr_->pos_, bulletTr_->width_, bulletTr_->height_);

		auto img = mngr_->getComponent<Image>(b);

		assert(img->tex_ != nullptr);
		img->tex_->render(dest, bulletTr_->rot_);
	}
}

void RenderSystem::drawFighter() {
	
	auto fighter_ = mngr_->getHandler(ecs::_hdlr_FIGHTER);

	auto fighterTr_ = mngr_->getComponent<Transform>(fighter_);

	SDL_Rect dest = build_sdlrect(fighterTr_->pos_, fighterTr_->width_, fighterTr_->height_);

	auto img = mngr_->getComponent<Image>(fighter_);

	assert(img->tex_ != nullptr);
	img->tex_->render(dest, fighterTr_->rot_);
}
