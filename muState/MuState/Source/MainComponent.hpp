/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <Engine.hpp>

/*
class TestButton : public juce::TextButton {
public:
	TestButton(const String& propertyName,
			   bool triggerOnMouseDown) 
			   : juce::ButtonPropertyComponent(propertyName, triggerOnMouseDown) {}
	
	void buttonClicked() override {}
	String getButtonText() const override { return "blah"; }
};
*/

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
	std::unique_ptr<TextButton> loadPluginButton;

	// eventually this will be wrapped by a controller
	Engine m_pEngine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
