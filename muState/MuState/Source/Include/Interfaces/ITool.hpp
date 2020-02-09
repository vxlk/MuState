/*
  ==============================================================================

    ITool.hpp
    Created: 1 Feb 2020 11:36:01am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Interfaces/IObject.hpp>
#include <Interfaces/IState.hpp>
#include <vector>

// The Tool Interface

// A tool representing a sound generator
// A tool contains a state
// The state owned by the tool dictates how the object that
// the tool is wrapping (vst plugin for example) made the sound
// it made at that point in the audio buffer
// A tool can be a plugin (generator/effect), audio file etc

// \Brief: A tool creates/modifies sound in the sound buffer using States 
//		  (see IState)

class ITool : public IObject {
public:
	virtual const IState const* GetState() = 0;
	virtual bool CanUpdate() = 0;
	virtual bool Update() = 0;
	// virtual play function -> needs an audio buffer?
};
