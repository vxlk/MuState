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
	objectList_t m_ActiveObjects;
	AudioDeviceManager m_deviceManager;
	AudioPluginFormatManager m_formatManager;
	std::vector <std::shared_ptr<IModulator>> m_Modulators;
	unsigned int m_projectID = 0; //to be set from xml/preset file eventually
public:

	// expose tracktion functionality
	tracktion_engine::Engine& TracktionEngine() { return tracktion_engine::Engine::getInstance(); }

	objectPtr_t AddObject(IObject *);

	objectPtr_t AddPlugin(const char *filePath);

	objectPtr_t AddAudio(const char *filePath);

	IState* DefaultState(ID);

};

inline objectPtr_t Engine::AddObject(IObject* objectToAdd) {
	m_ActiveObjects.emplace_back(objectToAdd);
	return m_ActiveObjects.back();
}