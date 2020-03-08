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
#include <vector>

//#include <tracktion_engine/project/tracktion_ProjectItemID.h>

// silence error, we dont care about adding to the global header
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED

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

using ID = int;

class IObject : public std::enable_shared_from_this<IObject> {
public:
	
	// for now we can't save projects so they all have id 0, this will change
	IObject() : m_id(std::rand() % 100) {
		//ExcController().RegisterObject(m_id);
	}

	virtual ~IObject() = default;

	virtual const std::string GetObjectName() const noexcept { return "Object"; }

	virtual IObject* CastToObject() noexcept { return dynamic_cast<IObject*>(this); }

	const ID GetID() const { return m_id; }

	virtual std::string GetLog() = 0;

protected:
	int m_id;
};

// syntactic sugar around common types of object wrappers

using objectPtr_t = std::shared_ptr<const IObject>;
using objectPtrMutable_t = std::shared_ptr<IObject>;

using objectList_t = std::vector<objectPtr_t>;
using objectListMutable_t = std::vector<objectPtrMutable_t>;