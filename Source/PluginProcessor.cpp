/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PulseVoice.h"
#include "TriangleVoice.h"
#include "NoiseVoice.h"
#include "FrameSequenceParseErrors.h"
#include "EnvelopeParserTest.h"

//==============================================================================
Magical8bitPlug2AudioProcessor::Magical8bitPlug2AudioProcessor()
    : parameters(
          *this, nullptr, Identifier("Params"),
          {//
           // Meta
           //
           std::make_unique<AudioParameterBool>(ParameterID{"isAdvancedPanelOpen_raw", 1},
                                                "Advanced",
                                                false),
           std::make_unique<AudioParameterChoice>(ParameterID{"colorScheme", 1}, 
                                                  "Color Scheme",
                                                  StringArray({"YMCK", "YMCK Dark", "Japan", "Worldwide", "Monotone", "Mono Dark"}),
                                                  0),
           //
           // Basic
           //
           std::make_unique<AudioParameterChoice>(ParameterID{"osc", 1}, 
                                                  "OSC Type",
                                                  StringArray({"Pulse/Square", "Triangle", "Noise"}),
                                                  0),
           std::make_unique<AudioParameterFloat>(ParameterID{"gain", 1}, 
                                                 "Gain",
                                                 0.0f,
                                                 1.0f,
                                                 0.5f),
           std::make_unique<AudioParameterFloat>(ParameterID{"maxPoly", 1}, 
                                                 "Max Poly",
                                                 NormalisableRange<float>(1.0f,  // min
                                                                          64.0f, // max
                                                                          1.0f,  // step
                                                                          1.0f), // skew
                                                 8),
           //
           // ADSR
           //
           std::make_unique<AudioParameterFloat>(ParameterID{"attack", 1},
                                                 "Attack",                        // name
                                                 NormalisableRange<float>(0.0f,   // min
                                                                          5.0f,   // max
                                                                          0.001f, // step
                                                                          0.5f),  // skew
                                                 0.0f),                           // default
           std::make_unique<AudioParameterFloat>(ParameterID{"decay", 1},
                                                 "Decay",                         // name
                                                 NormalisableRange<float>(0.0f,   // min
                                                                          5.0f,   // max
                                                                          0.001f, // step
                                                                          0.5f),  // skew
                                                 0.0f),                           // default
           std::make_unique<AudioParameterFloat>(ParameterID{"suslevel", 1},
                                                 "Sustain",  // name
                                                 0.0f,       // min
                                                 1.0f,       // max
                                                 1.0f),      // default
           std::make_unique<AudioParameterFloat>(ParameterID{"release", 1},
                                                 "Release",                       // name
                                                 NormalisableRange<float>(0.0f,   // min
                                                                          5.0f,   // max
                                                                          0.001f, // step
                                                                          0.5f),  // skew
                                                 0.0f),                           // default
           //
           //  Monophonic
           //
           std::make_unique<AudioParameterChoice>(ParameterID{"monophonicBehavior_raw", 1},
                                                  "Behavior",
                                                  StringArray({"Legato", "Arpeggio Up", "Arpeggio Down", "Non-legato"}),
                                                  0),
           std::make_unique<AudioParameterChoice>(ParameterID{"arpeggioIntervalType_raw", 1},
                                                  "Interval",
                                                  StringArray({"1 frame", "2 frames", "3 frames", "96th", "64th", "48th", "32nd", "24th", "Slider"}),
                                                  0),
           std::make_unique<AudioParameterFloat>(ParameterID{"arpeggioIntervalSliderValue", 1},
                                                 "Interval", // name
                                                 NormalisableRange<float>(0.001f, // min
                                                                          0.3f,   // max
                                                                          0.001f, // step
                                                                          0.5f),  // skew
                                                 0.001f), // default
           std::make_unique<AudioParameterFloat>(ParameterID{"portamentoTime", 1},
                                                 "Portamento Time",
                                                 0.0f,
                                                 1.0f,
                                                 0.0f),
           //
           // Bend
           //
           std::make_unique<AudioParameterInt>(ParameterID{"bendRange", 1}, 
                                               "Bend Range",
                                               0,
                                               24,
                                               2),
           //
           // Vibrato
           //
           std::make_unique<AudioParameterFloat>(ParameterID{"vibratoRate", 1},
                                                 "Rate",                          // name
                                                 NormalisableRange<float>(0.01f,  // min
                                                                          1.0f,   // max
                                                                          0.001f, // step
                                                                          0.5f),  // skew
                                                 0.15f),                          // default
           std::make_unique<AudioParameterFloat>(ParameterID{"vibratoDepth", 1}, 
                                                 "Depth",
                                                 0.0f,
                                                 2.0f,
                                                 0.0f),
           std::make_unique<AudioParameterFloat>(ParameterID{"vibratoDelay", 1}, 
                                                 "Delay",
                                                 0.0f,
                                                 1.0f,
                                                 0.3f),
           std::make_unique<AudioParameterBool>(ParameterID{"vibratoIgnoresWheel_raw", 1},
                                                "Ignores Wheel",
                                                true),
           //
           // Sweep
           //
           std::make_unique<AudioParameterInt>(ParameterID{"sweepInitialPitch", 1}, 
                                               "Ini.Pitch",
                                               -24,
                                               24,
                                               0),
           std::make_unique<AudioParameterFloat>(ParameterID{"sweepTime", 1},
                                                 "Time",                          // name
                                                 NormalisableRange<float>(0.01f,  // min
                                                                          5.0f,   // max
                                                                          0.001f, // step
                                                                          0.5f),  // skew
                                                 0.1f),                           // default
           //
           //  For Pulse
           //
           std::make_unique<AudioParameterChoice>(ParameterID{"duty", 1}, 
                                                  "Duty",
                                                  StringArray({"12.5%", "25%", "50%"}),
                                                  0),
           //
           // For Noise
           //
           std::make_unique<AudioParameterChoice>(ParameterID{"noiseAlgorithm_raw", 1},
                                                  "Algorithm", StringArray({"4bit Pure Random", "1bit Long Cycle", "1bit Short Cycle"}),
                                                  0),
           std::make_unique<AudioParameterBool>(ParameterID{"restrictsToNESFrequency_raw", 1},
                                                "Restricts to NES frequency",
                                                false),
           //
           // Sequence
           //
           std::make_unique<AudioParameterBool>(ParameterID{"isVolumeSequenceEnabled_raw", 1},
                                                "Enabled",
                                                false),
           std::make_unique<AudioParameterBool>(ParameterID{"isPitchSequenceEnabled_raw", 1},
                                                "Enabled",
                                                false),
           std::make_unique<AudioParameterBool>(ParameterID{"isDutySequenceEnabled_raw", 1},
                                                "Enabled",
                                                false),
           std::make_unique<AudioParameterChoice>(ParameterID{"pitchSequenceMode_raw", 1},
                                                  "Mode",
                                                  StringArray({"Coarse", "Fine"}),
                                                  0)
          }),
      settingRefs(&parameters), synth(*this)
#ifndef JucePlugin_PreferredChannelConfigurations
      ,
      AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
    synth.setCurrentPlaybackSampleRate(44100); // Temporary setup, just in case. The actual sample rate is set in prepareToPlay func.

    setupVoice();
    synth.addSound(new GenericSound());

#if JUCE_DEBUG
    EnvelopeParserTest test;
    UnitTestRunner runner;
    runner.runAllTests();
#endif
}

Magical8bitPlug2AudioProcessor::~Magical8bitPlug2AudioProcessor()
{
}
//==============================================================================
void Magical8bitPlug2AudioProcessor::setupVoice()
{
    int poly = synth.getNumVoices();

    for (auto i = 0; i < poly; i++)
    {
        synth.removeVoice(0);
    }

    int type = roundToInt(*settingRefs.osc);

    for (auto i = 0; i < (int)(*settingRefs.maxPoly); ++i)
    {
        switch (type)
        {
        case kVoiceTypePulse:
            synth.addVoice(new PulseVoice(&settingRefs));
            break;

        case kVoiceTypeTriangle:
            synth.addVoice(new TriangleVoice(&settingRefs));
            break;

        case kVoiceTypeNoise:
            synth.addVoice(new NoiseVoice(&settingRefs));
            break;
        }
    }
}

double Magical8bitPlug2AudioProcessor::getCurrentBPM()
{
    auto ph = getPlayHead();
    if (ph == NULL)
    {
        return 120.0;
    }
    juce::AudioPlayHead::CurrentPositionInfo result;
    ph->getCurrentPosition(result);

    return result.bpm > 0 ? result.bpm : 120.0;
}

//==============================================================================
const String Magical8bitPlug2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Magical8bitPlug2AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Magical8bitPlug2AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Magical8bitPlug2AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double Magical8bitPlug2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Magical8bitPlug2AudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Magical8bitPlug2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Magical8bitPlug2AudioProcessor::setCurrentProgram(int index)
{
}

const String Magical8bitPlug2AudioProcessor::getProgramName(int index)
{
    return {};
}

void Magical8bitPlug2AudioProcessor::changeProgramName(int index, const String &newName)
{
}

//==============================================================================
void Magical8bitPlug2AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void Magical8bitPlug2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Magical8bitPlug2AudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else

    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

#endif

    return true;
#endif
}
#endif

void Magical8bitPlug2AudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Magical8bitPlug2AudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor *Magical8bitPlug2AudioProcessor::createEditor()
{
    return new Magical8bitPlug2AudioProcessorEditor(*this);
}

//==============================================================================
void Magical8bitPlug2AudioProcessor::getStateInformation(MemoryBlock &destData)
{
    auto state = parameters.copyState();

    XmlElement *rootElement = new XmlElement("root");

    std::unique_ptr<XmlElement> stateElement = std::unique_ptr<XmlElement>(state.createXml());
    rootElement->addChildElement(stateElement.get());
    stateElement.release(); // give up the ownership already because xml object will delete it

    XmlElement *volEnvElement = new XmlElement("volumeEnv");
    XmlElement *pitEnvElement = new XmlElement("pitchEnv");
    XmlElement *dutEnvElement = new XmlElement("dutyEnv");
    volEnvElement->addTextElement(settingRefs.volumeSequenceString);
    pitEnvElement->addTextElement(settingRefs.pitchSequenceString);
    dutEnvElement->addTextElement(settingRefs.dutySequenceString);
    rootElement->addChildElement(volEnvElement);
    rootElement->addChildElement(pitEnvElement);
    rootElement->addChildElement(dutEnvElement);

    std::unique_ptr<XmlElement> xml(rootElement);

    copyXmlToBinary(*xml, destData);
}

void Magical8bitPlug2AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName("root"))
        {
            // ValueTree
            XmlElement *valueTreeXml = xmlState->getChildByName(parameters.state.getType());

            if (valueTreeXml != nullptr)
            {
                parameters.replaceState(ValueTree::fromXml(*valueTreeXml));
            }
            else
            {
                printf("Saved plugin parameters are incompatible");
            }

            // Custom Env
            XmlElement *volumeEnvXml = xmlState->getChildByName("volumeEnv");
            XmlElement *pitchEnvXml = xmlState->getChildByName("pitchEnv");
            XmlElement *dutyEnvXml = xmlState->getChildByName("dutyEnv");

            if (volumeEnvXml != nullptr)
            {
                XmlElement *volElem = volumeEnvXml->getFirstChildElement();

                if (volElem != nullptr && volElem->isTextElement())
                {
                    String volStr = volElem->getText();

                    ParseError err = kParseErrorNone;
                    settingRefs.setSequenceWithString("volume", volStr, &err);

                    if (settingRefs.volumeSequenceListener != nullptr)
                    {
                        settingRefs.volumeSequenceListener->sequenceChanged(volStr);
                    }

                    Logger::writeToLog("volume seq = " + volStr);
                }
                else
                {
                    Logger::writeToLog("volumeEnv entry found, but seems not like a text element.");
                }
            }

            if (pitchEnvXml != nullptr)
            {
                XmlElement *pitElem = pitchEnvXml->getFirstChildElement();

                if (pitElem != nullptr && pitElem->isTextElement())
                {
                    String pitStr = pitElem->getText();
                    ParseError err = kParseErrorNone;
                    settingRefs.setSequenceWithString("pitch", pitStr, &err);

                    if (settingRefs.pitchSequenceListener != nullptr)
                    {
                        settingRefs.pitchSequenceListener->sequenceChanged(pitStr);
                    }

                    Logger::writeToLog("pitch seq = " + pitStr);
                }
                else
                {
                    Logger::writeToLog("pitchEnv entry found, but seems not like a text element.");
                }
            }

            if (dutyEnvXml != nullptr)
            {
                XmlElement *dutElem = dutyEnvXml->getFirstChildElement();

                if (dutElem != nullptr && dutElem->isTextElement())
                {
                    String dutStr = dutElem->getText();
                    ParseError err = kParseErrorNone;
                    settingRefs.setSequenceWithString("duty", dutStr, &err);

                    if (settingRefs.dutySequenceListener != nullptr)
                    {
                        settingRefs.dutySequenceListener->sequenceChanged(dutStr);
                    }

                    Logger::writeToLog("duty seq = " + dutStr);
                }
                else
                {
                    Logger::writeToLog("dutyEnv entry found, but seems not like a text element.");
                }
            }
        }
    }

    setupVoice();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new Magical8bitPlug2AudioProcessor();
}
