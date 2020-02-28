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

// abstract engine
// this has a list of everything that could be and how they should be
// an engine has a list of how everything is
// this and the engine should ping back and forth about changes

class ExecutiveController {
public:
	// for now return initial state if not registered worry about
	// persistence later
	IState* GetState(ID id) { return FindEngineFromObjectID(id).DefaultState(id); }
	void RegisterObject(ID) {}
private:
	objectPtr_t FindObjectInOpenEngines();
	Engine& FindEngineFromObjectID(ID);

	std::vector<Engine> m_OpenEngines;
	objectList_t m_RegisteredObjects; //not necessarily in the engine
};

static ExecutiveController& ExcController() {
	ExecutiveController c;
	return c;
}