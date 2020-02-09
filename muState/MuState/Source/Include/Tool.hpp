/*
  ==============================================================================

    Tool.hpp
    Created: 1 Feb 2020 11:40:33am
    Author:  small

  ==============================================================================
*/

#pragma once

#include <Interfaces/ITool.hpp>

// implementation a tool, first goal - load a plugin with PluginTool

class Tool : public ITool {
public:

	//IObject override
	virtual const std::string& GetName() const noexcept override { return "Generic Tool"; }
	virtual std::string GetLog() override;

	// ITool override
	virtual const IState const* GetState() override { return m_pState.get(); }
	virtual bool CanUpdate() override				{ return m_bCanUpdate; }
	virtual bool Update() override					{ return m_bIsUpdating; }

protected:
	std::unique_ptr<IState> m_pState = nullptr;
	bool m_bCanUpdate =  false;
	bool m_bIsUpdating = false;
};