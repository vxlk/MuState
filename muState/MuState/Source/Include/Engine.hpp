/*
  ==============================================================================

    Engine.hpp
    Created: 1 Feb 2020 11:40:14am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Interfaces/ITool.hpp>

// The audio engine

class Engine {

	// eventually this will be contained in a repository
	// I want a transaction system to make sure multiple
	// objects dont modify other objects concurrently
	objectList_t m_ActiveObjects;
	AudioDeviceManager m_deviceManager;
	AudioPluginFormatManager m_formatManager;

public:

	objectPtr_t AddObject(IObject *);

	objectPtr_t AddPlugin(const char *filePath);

	objectPtr_t AddAudio(const char *filePath);

};
