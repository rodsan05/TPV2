// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include <SDL_stdinc.h>

struct Transform;
struct Image;
struct FramedImage;

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_RENDER)

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
	void receive(const Message& m) override;

private:
	void drawMsgs();
	void drawBullets();
	void drawFighter();
	void drawLives();
	void renderImage(Transform* tr_, Image* img_);
	void drawAsteroids();
	void renderFrame(FramedImage* framedImg_, Transform* tr_);
	void changeFrame(FramedImage* framedImg_);

	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver(Uint8 w);
	void onNewGame();
	
	Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)

};

