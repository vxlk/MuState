/*
  ==============================================================================

    Engine.hpp
    Created: 1 Feb 2020 11:40:14am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Interfaces/ITool.hpp>
#include <Interfaces/IModulator.hpp>
#include <tracktion_engine.h>
#include <JuceHeader.h>

// The audio engine

class Engine {

	// eventually this will be contained in a repository
	// I want a transaction system to make sure multiple
	// objects dont modify other objects concurrently
	KnownPluginList m_KnownPluginList;
	KnownPluginList::SortMethod m_PluginSortMethod;
	Array<PluginDescription> m_PluginDescriptions;
	AudioPluginFormatManager m_PluginFormatManager;
	std::vector<std::pair<ID, IState*>> m_defaultStates;
	objectList_t m_ActiveObjects;
	AudioDeviceManager m_deviceManager;
	AudioPluginFormatManager m_formatManager;
	std::vector <std::shared_ptr<IModulator>> m_Modulators;
	unsigned int m_projectID = 0; //to be set from xml/preset file eventually
public:

	// expose tracktion functionality
	tracktion_engine::Engine& TracktionEngine() { return tracktion_engine::Engine::getInstance(); }

	objectPtr_t AddObject(IObject *);

	objectPtr_t FindObject(ID id) const;

	//objectPtr_t AddPlugin(const char *filePath);

	//objectPtr_t AddAudio(const char *filePath);

	IState* DefaultState(ID) const;

};

inline objectPtr_t Engine::AddObject(IObject* objectToAdd) {
	m_ActiveObjects.emplace_back(objectToAdd);
	return m_ActiveObjects.back();
}

inline IState* Engine::DefaultState(ID id) const {
	for (const auto& stateIdPair : m_defaultStates)
		if (stateIdPair.first == id)
			return stateIdPair.second;
	return nullptr;
}

inline objectPtr_t Engine::FindObject(ID id) const {
	for (const auto& object : m_ActiveObjects)
		if (object->GetID() == id)
			return object;
	return nullptr;
}