/*
  ==============================================================================

    IModulator.hpp
    Created: 15 Feb 2020 12:28:29am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Interfaces/IState.hpp>

// A modulator is an algorithm that dictates state changes

class IModulator {
public:

	IState *Modulate(IState *);



};