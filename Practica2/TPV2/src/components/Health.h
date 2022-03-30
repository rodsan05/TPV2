#pragma once
#include "../ecs/Component.h"

class Texture;

class Health : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_HEALTH)

	Health();
	~Health();

	int actualLives();
	void resetLives();

	void doDamage(int dmg);

	void render() override;

private:

	Texture* text_;
	const int INI_LIVES = 3;
	const int HEART_WIDTH = 50;
	const int HEART_HEIGHT = 50;

	int lives;
};

