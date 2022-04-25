// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

namespace ecs {
class Entity;
}
struct Transform;
struct PaddleCtrl;
class Vector2D;

class FighterSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_FIGHTER)

	FighterSystem();
	virtual ~FighterSystem();

	void receive(const Message& m) override;
	void update() override;
	void initSystem() override;

private:

	void moveFighter(ecs::Entity*);

	void returnToCenter();

	void onCollision_FighterAsteroid();

	void onRoundOver();
	void onRoundStart();
	void onGameOver();

	bool active_;

	Transform *fighterTr_;
	ecs::Entity* fighter_;
};

