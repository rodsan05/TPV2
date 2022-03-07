// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cassert>

#include "Component.h"
#include "ecs.h"
#include "Entity.h"

namespace ecs {

class Manager {

public:
	Manager();
	virtual ~Manager();

	// Adding an entity simply creates an instance of Entity, adds
	// it to the list of entities and returns it to the caller.
	//
	inline Entity* addEntity(ecs::grpId gId = ecs::_grp_GENERAL) {

		// create and initialise the entity
		auto e = new Entity(gId);
		e->setAlive(true);
		e->setContext(this);

		// add the entity 'e' to list of entities
		//
		// IMPORTANT NOTE:
		//
		// Currently we immediately add the entity to the list of entities 'ents_',
		// so we will actually see them in this 'frame' if we traverse the list of
		// entities afterwards!
		//
		// A better solution would be to add them to an auxiliary list, and
		// define a method 'flush()' that moves them from the auxiliary list
		// to 'ents_'. We will have to call 'flush()' in each iteration of the
		// main loop. This way we guarantee that entities that are added in one
		// 'frame' they will appear only in the next 'frame' -- I leave it as an
		// exercise for you ...
		//
		entsByGroup_[gId].push_back(e);

		// return it to the caller
		//
		return e;
	}

	// returns the vector of all entities
	//
	inline const auto& getEntities(grpId_type gId = ecs::_grp_GENERAL) {
		return entsByGroup_[gId];;
	}

	// associates the entity 'e' to the handler 'hId'
	//
	inline void setHandler(hdlrId_type hId, Entity *e) {
		assert(hId < ecs::maxHdlrId);
		hdlrs_[hId] = e;
	}

	// returns the entity associated to the handler 'hId'
	//
	inline Entity* getHandler(hdlrId_type hId) {
		assert(hId < ecs::maxHdlrId);
		return hdlrs_[hId];
	}

	// call update of all entities
	//
	void update() {
		for (auto &ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->update();
		}
	}

	// call render of all entities
	//
	void render() {
		for (auto &ents : entsByGroup_) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->render();
		}
	}

	// eliminate dead entities (the implementation of this method
	// is in Manager.cpp, but we could also defined it here).
	//
	void refresh();

private:

	std::array<Entity*, maxHdlrId> hdlrs_;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
};

} // end of namespace
