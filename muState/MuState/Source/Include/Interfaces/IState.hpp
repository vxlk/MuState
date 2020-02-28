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
#include <Param.hpp>
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
	objectPtrMutable_t       GetStateMutable() { return shared_from_this(); }
	objectPtr_t				 GetState()		   { return shared_from_this(); }
	virtual bool			 CanTransition() = 0;
	virtual void			 Transition()	 = 0;

	//IObject override
	virtual const std::string GetObjectName() const noexcept override { return "State"; }
	virtual std::string GetLog() override { return ""; }
};

using stateList_t = std::vector<std::shared_ptr<const IState>>;
// should move these to an implementation file

// the different ways a state can be compared to one another
class StateTimeComparators {
	// states are compared
	time_t m_timeOfCreation;
};

class StateLikenessComparators {
	Frame m_frameToCompareAgainst;
};

// move this out of istate you slop bag
class State : public IState {
protected:
	bool m_bInTransition;
	// a state knows about its previous states
	stateList_t m_listOfPreviousStates{};
	paramList_t m_listOfParams{};
	std::vector<Frame> m_Frames;

public:

	friend class StateOperators;

	// Executive Controller Updates state with an alloted edit
	State() 
			: m_bInTransition(false),
			  m_Frames{}
			  {}

	virtual bool   CanTransition() override;
	virtual void   Transition()    override;
	// return the juce value tree of this state
	//virtual const ValueTree& GetTree() const override { return m_StateTree; }
	constexpr bool IsInTransition() noexcept { return m_bInTransition; }
};

//using stateMap_t = std::unordered_map<std::shared_ptr<const IState>>;