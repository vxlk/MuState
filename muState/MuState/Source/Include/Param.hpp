/*
  ==============================================================================

    Param.hpp
    Created: 25 Feb 2020 8:37:12pm
    Author:  small

  ==============================================================================
*/

#pragma once
#include <Interfaces/IObject.hpp>
struct Param {
	std::string name = "Param";
	double val = 0.0;
};

using paramList_t = std::vector<Param>; //states have a varying amount of params
										//based on the tool that constructs them