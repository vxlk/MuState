/*
  ==============================================================================

    IObject.hpp
    Created: 1 Feb 2020 11:35:51am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <string>
#include <memory>

// The Object Interface

// Interface to the object class
// The object class is the highest level super class
// in the library.  It represents a unit in the code
// that carries self identifying features such as name
// this is also the generic class for tying the data model
// to the ui code

// object (data) -> controller (signals/slots) -> ui (widgets)

// \Brief: The super class of all physical objects in the 
//		   MuState codebase

///todo: it will become more clear to me when i start implementing what all this needs to hold
/// the idea right now is to be able to up-cast to a common base

class IObject {
public:
	
	virtual const std::string& GetName() const noexcept { return "Object"; }

	virtual IObject* CastToObject() noexcept			{ return dynamic_cast<IObject*>(this); }

	virtual std::string GetLog() = 0;
};

// syntactic sugar around common types of object wrappers

using objectPtr_t = std::shared_ptr<const IObject>;
using objectPtrMutable_t = std::shared_ptr<IObject>;

using objectList_t = std::vector<objectPtr_t>;
using objectListMutable_t = std::vector<objectPtrMutable_t>;