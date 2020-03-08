/*
  ==============================================================================

    PluginTool.cpp
    Created: 27 Feb 2020 5:08:20pm
    Author:  small

  ==============================================================================
*/

#include "PluginTool.hpp"

PluginTool::PluginTool(std::string filePath) : 
	// Get the initial state of this object id from the executive controller
	Tool(ExcController().GetState(this->GetID())) 
{
	KnownPluginList listOfPlugins{}; // this gets added to

	PluginDirectoryScanner scanner(/*fill this in*/);
	// Grab scanner 
	// scan paths
	// build plugin description
	// execute plugin
	// show gui? (don't know yet how to handle this..)
}
