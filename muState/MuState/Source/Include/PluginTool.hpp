#pragma once

#include <Tool.hpp>
// set include path to include tracktion, include plugin.h
// get rid of this garbage you cant use it
#include <../JuceLibraryCode/JuceHeader.h>

// Implementation of a tool - specifically wrapping a plugin instance
// this plugin can be of type generator or effect, the engine does not care

class PluginTool : public Tool {
public:
	//==============================================================================
	PluginTool() = delete;
	// I want this behavior, send it a file path and load the tool as 
	// a plugin - it should be able to figure all of the micro details out
	// itself
	PluginTool(std::string filePath);
	~PluginTool() override = default;

	// IObject override
	// rename to GetObjectName to avoid ambiguity
	// get rid of reference for performance
	virtual const std::string GetObjectName() const noexcept override
	{
		return "Plugin Tool";
	}
	virtual std::string GetLog() override { return ""; }

	//==============================================================================

private:
	void PrivateSetup();
	// somehow manage its own format..
};

/*
class PluginTool : public Tool, public juce::AudioProcessor {
public:
	//==============================================================================
	PluginTool() = default;
	~PluginTool() override = default;

	// IObject override
	virtual const std::string& GetName() const noexcept override 
							   { return static_cast<const char *>(plugin->getName().toUTF8()); }
	virtual std::string GetLog() override { return ""; }

	PluginTool(AudioPluginInstance* processorToUse)
		: AudioProcessor(getBusesPropertiesFromProcessor(processorToUse)),
		plugin(processorToUse)
	{}

	//==============================================================================
	const String getName() const override					{ return plugin->getName(); }
	bool canAddBus(bool inputBus) const override			{ return plugin->canAddBus(inputBus); }
	bool canRemoveBus(bool inputBus) const override			{ return plugin->canRemoveBus(inputBus); }
	bool supportsDoublePrecisionProcessing() const override { return plugin->supportsDoublePrecisionProcessing(); }
	double getTailLengthSeconds() const override			{ return plugin->getTailLengthSeconds(); }
	bool acceptsMidi() const override						{ return plugin->acceptsMidi(); }
	bool producesMidi() const override						{ return plugin->producesMidi(); }
	bool supportsMPE() const override						{ return plugin->supportsMPE(); }
	bool isMidiEffect() const override						{ return plugin->isMidiEffect(); }
	void reset() override									{ plugin->reset(); }
	AudioProcessorEditor* createEditor() override			{ return plugin->createEditor(); }
	bool hasEditor() const override							{ return plugin->hasEditor(); }
	int getNumParameters() override							{ return plugin->getNumParameters(); }
	const String getParameterName(int parameterIndex) override { return plugin->getParameterName(parameterIndex); }
	String getParameterID(int index) override { return plugin->getParameterID(index); }
	float getParameter(int parameterIndex) override { return plugin->getParameter(parameterIndex); }
	String getParameterName(int parameterIndex, int maximumStringLength) override { return plugin->getParameterName(parameterIndex, maximumStringLength); }
	const String getParameterText(int parameterIndex) override { return plugin->getParameterText(parameterIndex); }
	String getParameterText(int parameterIndex, int maximumStringLength) override { return plugin->getParameterText(parameterIndex, maximumStringLength); }
	int getParameterNumSteps(int parameterIndex) override { return plugin->getParameterNumSteps(parameterIndex); }
	float getParameterDefaultValue(int parameterIndex) override { return plugin->getParameterDefaultValue(parameterIndex); }
	String getParameterLabel(int index) const override { return plugin->getParameterLabel(index); }
	bool isParameterOrientationInverted(int index) const override { return plugin->isParameterOrientationInverted(index); }
	void setParameter(int parameterIndex, float newValue) override { plugin->setParameter(parameterIndex, newValue); }
	bool isParameterAutomatable(int parameterIndex) const override { return plugin->isParameterAutomatable(parameterIndex); }
	bool isMetaParameter(int parameterIndex) const override { return plugin->isMetaParameter(parameterIndex); }
	int getNumPrograms() override { return plugin->getNumPrograms(); }
	int getCurrentProgram() override { return plugin->getCurrentProgram(); }
	void setCurrentProgram(int index) override { plugin->setCurrentProgram(index); }
	const String getProgramName(int index) override { return plugin->getProgramName(index); }
	void changeProgramName(int index, const String& newName) override { plugin->changeProgramName(index, newName); }
	void getStateInformation(juce::MemoryBlock& destData) override { plugin->getStateInformation(destData); }
	void getCurrentProgramStateInformation(juce::MemoryBlock& destData) override { plugin->getCurrentProgramStateInformation(destData); }
	void setStateInformation(const void* data, int sizeInBytes) override { plugin->setStateInformation(data, sizeInBytes); }
	void setCurrentProgramStateInformation(const void* data, int bytes) override { plugin->setCurrentProgramStateInformation(data, bytes); }

	//==============================================================================
	void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override
	{
		plugin->releaseResources();

		plugin->setRateAndBufferSizeDetails(sampleRate, maximumExpectedSamplesPerBlock);

		// sync number of buses
		for (int dir = 0; dir < 2; ++dir)
		{
			const bool isInput = (dir == 0);
			int expectedNumBuses = getBusCount(isInput);
			int requiredNumBuses = plugin->getBusCount(isInput);

			for (; expectedNumBuses < requiredNumBuses; expectedNumBuses++)
				plugin->addBus(isInput);

			for (; requiredNumBuses < expectedNumBuses; requiredNumBuses++)
				plugin->removeBus(isInput);
		}

		plugin->setBusesLayout(getBusesLayout());
		plugin->prepareToPlay(sampleRate, maximumExpectedSamplesPerBlock);
	}

	void releaseResources() override { return plugin->releaseResources(); }

	//==============================================================================
	void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override { plugin->processBlock(buffer, midiMessages); }
	void processBlock(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override { plugin->processBlock(buffer, midiMessages); }
	void processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override { plugin->processBlockBypassed(buffer, midiMessages); }
	void processBlockBypassed(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override { plugin->processBlockBypassed(buffer, midiMessages); }

protected:

	//==============================================================================
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override { return plugin->checkBusesLayoutSupported(layouts); }
	bool canApplyBusesLayout(const BusesLayout& layouts) const override { return plugin->setBusesLayout(layouts); }
	bool canApplyBusCountChange(bool isInput, bool isAddingBuses,
		BusProperties& outNewBusProperties) override
	{
		if (isAddingBuses)
		{
			int busIdx = plugin->getBusCount(isInput);

			if (!plugin->addBus(isInput))
				return false;

			if (Bus* bus = plugin->getBus(isInput, busIdx))
			{
				outNewBusProperties.busName = bus->getName();
				outNewBusProperties.defaultLayout = bus->getDefaultLayout();
				outNewBusProperties.isActivatedByDefault = bus->isEnabledByDefault();

				return true;
			}
			else
			{
				jassertfalse;
				return false;
			}
		}
		else
			return plugin->removeBus(isInput);
	}
private:
	//==============================================================================
	static BusesProperties getBusesPropertiesFromProcessor(AudioProcessor* processor)
	{
		BusesProperties retval;

		for (int dir = 0; dir < 2; ++dir)
		{
			const bool isInput = (dir == 0);
			const int n = processor->getBusCount(isInput);

			for (int i = 0; i < n; ++i)
				if (AudioProcessor::Bus* bus = processor->getBus(isInput, i))
					retval.addBus(isInput, bus->getName(), bus->getDefaultLayout(), bus->isEnabledByDefault());
		}

		return retval;
	}

	ScopedPointer<AudioProcessor> plugin;
};

//==============================================================================
static String osTypeToString(uint32 osCode)
{
	union osCodeConvertHelper
	{
		uint32 osCode;
		char code[4];
	};

	osCodeConvertHelper helper;

	helper.osCode = ByteOrder::swapIfLittleEndian(osCode);
	return String(helper.code, 4);
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
		return nullptr;
}
*/