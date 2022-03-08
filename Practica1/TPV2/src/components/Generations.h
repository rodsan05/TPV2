#pragma once
#include "../ecs/Component.h"
class Generations : public ecs::Component
{
public:

	__CMPID_DECL__(ecs::_GENERATIONS)

	Generations();
	Generations(int n);
	~Generations();

	int nGenerations();
	void setGenerations(int n);

private:

	int generations_;
};

