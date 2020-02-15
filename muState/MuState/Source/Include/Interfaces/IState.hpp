/*
  ==============================================================================

    IState.hpp
    Created: 1 Feb 2020 11:35:12am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Frame.hpp>
#include <Interfaces/IObject.hpp>

#include <unordered_map>

// The State Interface

// A State is a representation of parameter
// configuration of an object in order to
// replicate a sound played at any point in the buffer

// An output from the MuState engine is a sequence of states
// from a number of tools

// VST Plugin
// state0, state1, state2...   = sound
// params, params, params...
// --- time axis -----

// If you wanted to replicate a sound at any point
// in the audio buffer, you could simply grab the state
// data, and the tool that contained the state and reproduce
// the audio

// Note a song usually has many tools active at the same time

// States can also contain automation
// This means states are further broken down
// into frames.  So, an automation state will contain
// multiple frames (which are essentially sub-states)
// on a time axis within the single state

// \Brief: States are the building blocks of generative music.
//		   They are a simple view of configuration at a point
//		   in time, and an object's state may dictate how it will
//		   transition into the next state

class IState : public IObject {
public:
	virtual bool   CanTransition()  = 0;
	virtual void   Transition()		= 0;
};

// should move these to an implementation file

// the different ways a state can be compared to one another
class StateTimeComparators {
	// states are compared
	time_t m_timeOfCreation;
};

class StateLikenessComparators {
	Frame m_frameToCompareAgainst;
};

class State : public IState {
protected:
	bool m_bInTransition;
	std::vector<Frame> m_Frames;
public:

	friend class StateOperators;

	virtual bool   CanTransition() override;
	virtual void   Transition()    override;

	constexpr bool IsInTransition() noexcept { return m_bInTransition; }
};

using stateList_t = std::vector<std::shared_ptr<const IState>>;
using stateMap_t = std::unordered_map<std::shared_ptr<const IState>>;