#pragma once
#include "../ecs/Component.h"

class Transform;

class Follow : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_FOLLOW)

	Follow();
	~Follow();

	void initComponent() override;
	void update() override;

private:

	Transform* tr_;
	Transform* trPlayer_;
};

