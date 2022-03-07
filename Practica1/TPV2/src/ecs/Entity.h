// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <bitset>
#include <cassert>
#include <vector>

#include "Component.h"
#include "ecs.h"

namespace ecs {

class Entity {
public:
	Entity(ecs::grpId_type gId) :
			mngr_(nullptr), //
			cmps_(), //
			currCmps_(), //
			alive_(),  //
			gId_(gId) //
	{
		// We reserve the a space for the maximum number of
		// components. This way we avoid resizing the vector.
		//
		currCmps_.reserve(ecs::maxComponentId);
	}

	// we delete the copy constructor/assignment because it is
	// not clear how to copy the components
	//
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	// Exercise: define move constructor/assignment for class Entity

	// Destroys the entity
	//
	virtual ~Entity() {

		// we delete all available components
		//
		for (auto c : currCmps_)
			delete c;
	}

	// Each entity knows to which manager it belongs, we use
	// this method to set the context
	//
	inline void setContext(Manager *mngr) {
		mngr_ = mngr;
	}

	// Setting the state of the entity (alive or dead)
	//
	inline void setAlive(bool alive) {
		alive_ = alive;
	}

	// Returns the state of the entity (alive o dead)
	//
	inline bool isAlive() {
		return alive_;
	}

	// Updating  an entity simply calls the update of all
	// components
	//
	void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}

	// Rendering an entity simply calls the render of all
	// components
	//
	void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}

	// Adds a component. It receives the type T (to be created), and the
	// list of arguments (if any) to be passed to the constructor.
	// The component identifier 'cId' is taken from T::id.
	//
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts &&... args) {

		constexpr cmpId_type cId = T::id;
		assert(cId < ecs::maxComponentId);

		// delete the current component, if any
		//
		removeComponent<T>();

		// create, initialise and install the new component
		//
		Component *c = new T(std::forward<Ts>(args)...);
		c->setContext(this, mngr_);
		c->initComponent();
		cmps_[cId] = c;
		currCmps_.push_back(c);

		// return it to the user so i can be initialised if needed
		return static_cast<T*>(c);
	}

	// Removes the components at position T::id.
	//
	template<typename T>
	inline void removeComponent() {

		constexpr cmpId_type cId = T::id;
		assert(cId < ecs::maxComponentId);

		if (cmps_[cId] != nullptr) {

			// find the element that is equal tocmps_[cId] (returns an iterator)
			//
			auto iter = std::find(currCmps_.begin(), currCmps_.end(),
					cmps_[cId]);

			// and then remove it
			currCmps_.erase(iter);

			// destroy it
			//
			delete cmps_[cId];

			// remove the pointer
			//
			cmps_[cId] = nullptr;
		}
	}

	// Returns the component that corresponds to position T::id, casting it
	// to T*. The casting is done just for ease of use, to avoid casting
	// outside.
	//
	template<typename T>
	inline T* getComponent() {

		constexpr cmpId_type cId = T::id;
		assert(cId < ecs::maxComponentId);

		return static_cast<T*>(cmps_[cId]);
	}

	// return true if there is a component with identifier T::id
	//
	template<typename T>
	inline bool hasComponent() {

		constexpr cmpId_type cId = T::id;
		assert(cId < ecs::maxComponentId);

		return cmps_[cId] != nullptr;
	}

	// returns the entity's group 'gId'
	//
	inline ecs::grpId_type groupId() {
		return gId_;
	}


private:

	Manager *mngr_;
	std::array<Component*, maxComponentId> cmps_;
	std::vector<Component*> currCmps_;
	bool alive_;
	ecs::grpId_type gId_;
};

} // end of name space
