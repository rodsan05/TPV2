// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;

class CollisionsSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_COLLISIONS)

	void receive(const Message& m) override;
	CollisionsSystem();
	virtual ~CollisionsSystem();
	void initSystem() override;
	void update() override;
private:
	Transform *fighterTr_;
	bool active_;
};

