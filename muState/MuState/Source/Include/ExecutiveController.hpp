/*
  ==============================================================================

    ExecutiveController.hpp
    Created: 25 Feb 2020 8:37:02pm
    Author:  small

  ==============================================================================
*/

#pragma once
#include <Interfaces/IState.hpp>
#include <Engine.hpp>

// engine manager paradigm
// this has a list of everything that could be and how they should be
// an engine has a list of how everything is
// this represents control of multiple engines (engines are systems of objects)

class ExecutiveController {
public:
	/// ehhhh this could be done better, todo
	Engine null_engine = {};

	// for now return initial state if not registered worry about
	// persistence later
	IState* GetState(ID id) { return FindEngineFromObjectID(id).DefaultState(id); }
	void RegisterObject(ID);
private:
	objectPtr_t FindObjectInOpenEngines();
	const Engine& FindEngineFromObjectID(ID id) {
		for (const auto& engine : m_OpenEngines)
			if (engine.FindObject(id))
				return engine;
		return null_engine;
	}

	std::vector<Engine> m_OpenEngines;
	objectList_t m_RegisteredObjects; //not necessarily in an engine
};

static ExecutiveController& ExcController() {
	ExecutiveController c;
	return c;
}

inline void ExecutiveController::RegisterObject(ID id) {
	// no no no, you need to make a type id system i dont want this to work like this
	if (std::find_if(m_RegisteredObjects.begin(), m_RegisteredObjects.end(),
		[&](objectPtr_t obj) { return obj->GetID() == id; }) != m_RegisteredObjects.end())
		return;
	//m_RegisteredObjects.emplace_back(some how get an object);

}