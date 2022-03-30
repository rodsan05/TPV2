#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

struct Health : public ecs::Component
{
	__CMPID_DECL__(ecs::_HEALTH)

	Health() : lives(INI_LIVES) {

		text_ = &sdlutils().images().at("heart");
	}

	virtual ~Health() {}

	void resetLives() {

		lives = INI_LIVES;
	}

	void doDamage(int dmg) {

		lives -= dmg;
	}

	Texture* text_;
	const int INI_LIVES = 3;
	const int HEART_WIDTH = 50;
	const int HEART_HEIGHT = 50;

	int lives;
};

//void Health::render()
//{
//	float heartPos = 5;
//
//	assert(text_ != nullptr);
//
//	for (int i = 0; i < lives; i++) {
//
//		Vector2D* pos = new Vector2D(heartPos, 5);
//		SDL_Rect dest = build_sdlrect(*pos, HEART_WIDTH, HEART_HEIGHT);
//		text_->render(dest);
//
//		heartPos += HEART_WIDTH + 5;
//	}
//}

