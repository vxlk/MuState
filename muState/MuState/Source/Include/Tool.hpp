/*
  ==============================================================================

    Tool.hpp
    Created: 1 Feb 2020 11:40:33am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Interfaces/ITool.hpp>
#include <ExecutiveController.hpp>

// implementation a tool, first goal - load a plugin with PluginTool

class Tool : public ITool {
public:
	Tool() = delete;
	Tool(IState* toolState);
	//IObject override
	virtual const std::string GetObjectName() const noexcept override { return "Generic Tool"; }
	virtual std::string GetLog() override { return ""; }

	// ITool override
	virtual const IState const* GetState() override { return m_pCurrentState.get(); }
	virtual bool CanUpdate() override				{ return m_bCanUpdate; }
	virtual bool Update() override					{ return m_bIsUpdating; }

protected:
	std::unique_ptr<IState> m_pCurrentState = nullptr;
	stateList_t m_listOfPreviousStates{};
	bool m_bCanUpdate =  false;
	bool m_bIsUpdating = false;
	
};