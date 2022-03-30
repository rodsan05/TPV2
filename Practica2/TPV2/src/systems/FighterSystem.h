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

	__SYSID_DECL__(ecs::_sys_PADDLES)

	FighterSystem();
	virtual ~FighterSystem();
	void update() override;
	void initSystem() override;

private:
	void movePaddle(ecs::Entity*);
	void moveWithKeyboard(PaddleCtrl*, Transform*);
	void moveWithMouse(PaddleCtrl*, Transform*);
	void moveWithAI(PaddleCtrl*, Transform*);
	bool ballComingTowardsPaddle(const Vector2D&);

	Transform *fighterTr_;
	ecs::Entity* fighter_;
};

