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
#include "WaveformVoice.h"
#include "FrameSequenceParseErrors.h"
#include "EnvelopeParserTest.h"

//==============================================================================
Magical8bitPlug2AudioProcessor::Magical8bitPlug2AudioProcessor()
    : parameters (
          *this, nullptr, Identifier ("Params"),
{
        //
        // Meta
        //
        std::make_unique<AudioParameterBool> ("isAdvancedPanelOpen_raw", "Advanced", false),
        std::make_unique<AudioParameterChoice> ("colorScheme", "Color Scheme", StringArray ({"YMCK", "YMCK Dark", "Japan", "Worldwide", "Monotone", "Mono Dark"}), 0),
        //
        // Basic
        //
        std::make_unique<AudioParameterChoice> ("osc", "OSC Type", StringArray ({"Pulse/Square", "Triangle", "Noise", "Waveform"}), 0),
        std::make_unique<AudioParameterFloat> ("gain", "Gain", 0.0f, 1.0f, 0.5f),
        std::make_unique<AudioParameterFloat> ("maxPoly", "Max Poly", NormalisableRange<float> (1.0f,  //min
                                                                                                64.0f,   //max
                                                                                                1.0f, //step
                                                                                                1.0f),  //skew
                                                                                                8),
        //
        // ADSR
        //
        std::make_unique<AudioParameterFloat> ("attack", //ID
                                               "Attack", //name
                                               NormalisableRange<float> (0.0f,  //min
                                                                         5.0f,   //max
                                                                         0.001f, //step
                                                                         0.5f),  //skew
                                                                         0.0f), //default
        std::make_unique<AudioParameterFloat> ("decay", //ID
                                               "Decay", //name
                                               NormalisableRange<float> (0.0f,  //min
                                                                         5.0f,   //max
                                                                         0.001f, //step
                                                                         0.5f),  //skew
                                                                         0.0f), //default
        std::make_unique<AudioParameterFloat> ("suslevel", //ID
                                               "Sustain",  //name
                                               0.0f, //min
                                               1.0f, //max
                                               1.0f),//default
        std::make_unique<AudioParameterFloat> ("release", //ID
                                               "Release", //name
                                               NormalisableRange<float> (0.0f,  //min
                                                                         5.0f,   //max
                                                                         0.001f, //step
                                                                         0.5f),  //skew
                                                                         0.0f), //default
        //
        // Arpeggio
        //
        std::make_unique<AudioParameterBool> ("isArpeggioEnabled_raw", "Enabled", false),
        std::make_unique<AudioParameterFloat> ("arpeggioTime", "Time", 0.0f, 0.3f, 0.033f),
        std::make_unique<AudioParameterChoice> ("arpeggioDirection", "Direction", StringArray ({"up", "down"}), 0),
        //
        // Bend
        //
        std::make_unique<AudioParameterInt> ("bendRange", "Bend Range", 0, 24, 2),
        //
        // Vibrato
        //
        std::make_unique<AudioParameterFloat> ("vibratoRate", //ID
                                               "Rate", //name
                                               NormalisableRange<float> (0.01f, //min
                                                                         1.0f,   //max
                                                                         0.001f, //step
                                                                         0.5f),  //skew
                                                                         0.15f), //default
        std::make_unique<AudioParameterFloat> ("vibratoDepth", "Depth", 0.0f, 2.0f, 0.0f),
        std::make_unique<AudioParameterFloat> ("vibratoDelay", "Delay", 0.0f, 1.0f, 0.3f),
        std::make_unique<AudioParameterBool> ("vibratoIgnoresWheel_raw", "Ignores Wheel", true),
        //
        // Sweep
        //
        std::make_unique<AudioParameterInt> ("sweepInitialPitch", "Ini.Pitch", -24, 24, 0),
        std::make_unique<AudioParameterInt> ("sweepEndPitch", "End.Pitch", -24, 24, 0),
        std::make_unique<AudioParameterFloat> ("sweepTime", //ID
                                               "Time", //name
                                               NormalisableRange<float> (0.01f,  //min
                                                                         5.0f,   //max
                                                                         0.001f, //step
                                                                         0.5f),  //skew
                                                                         0.1f), //default
        //
        // For Pulse
        //
        std::make_unique<AudioParameterChoice> ("duty", "Duty", StringArray ({"12.5%", "25%", "50%"}), 0),
        //
        // For Noise
        //
        std::make_unique<AudioParameterChoice> ("noiseAlgorithm_raw", "Algorithm", StringArray ({"4bit Pure Random", "1bit Long Cycle", "1bit Short Cycle", "Nes Long Cycle", "Nes Short Cycle"}), 0),
        std::make_unique<AudioParameterBool> ("restrictsToNESFrequency_raw", "Restricts to NES frequency", false),
        //
        // Sequence
        //
        std::make_unique<AudioParameterBool> ("isVolumeSequenceEnabled_raw", "Enabled", false),
        std::make_unique<AudioParameterBool> ("isPitchSequenceEnabled_raw", "Enabled", false),
        std::make_unique<AudioParameterBool> ("isDutySequenceEnabled_raw", "Enabled", false),
        std::make_unique<AudioParameterChoice> ("pitchSequenceMode_raw", "Mode", StringArray ({"Coarse", "Fine8", "Fine16"}), 0),
        // waveform
        std::make_unique<AudioParameterChoice>("waveformX", "X", StringArray({ "16", "32", "64" }), 2),
        std::make_unique<AudioParameterChoice>("waveformY", "Y", StringArray({ "16", "32", "64" }), 2),
        std::make_unique<AudioParameterChoice>("waveformTemplate", "Template", StringArray({ "Custom", "Sine", "Triangle", "Sawtooth", "Square 6.25%", "Square 18.75%", "Square 31.25%", "Square 37.5%", "Square 43.75%" }), 0),
        std::make_unique<AudioParameterFloat>("waveformWave0", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave1", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave2", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave3", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave4", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave5", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave6", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave7", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave8", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave9", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave10", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave11", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave12", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave13", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave14", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave15", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave16", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave17", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave18", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave19", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave20", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave21", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave22", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave23", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave24", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave25", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave26", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave27", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave28", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave29", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave30", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave31", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave32", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave33", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave34", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave35", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave36", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave37", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave38", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave39", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave40", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave41", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave42", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave43", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave44", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave45", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave46", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave47", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave48", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave49", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave50", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave51", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave52", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave53", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave54", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave55", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave56", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave57", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave58", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave59", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave60", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave61", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave62", "wave", 0, 63, 0),
        std::make_unique<AudioParameterFloat>("waveformWave63", "wave", 0, 63, 0)

}
  )
, settingRefs (&parameters)
#ifndef JucePlugin_PreferredChannelConfigurations
, AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
    #if ! JucePlugin_IsSynth
        .withInput  ("Input",  AudioChannelSet::stereo(), true)
    #endif
    .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                 )
#endif
{
    // waveform
    //parameters.createAndAddParameter(std::make_unique<AudioParameterChoice>("waveformX", "X", StringArray({ "16", "32", "64" }), 2));
    //parameters.createAndAddParameter(std::make_unique<AudioParameterChoice>("waveformY", "Y", StringArray({ "16", "32", "64" }), 2));
    //parameters.createAndAddParameter(std::make_unique<AudioParameterChoice>("waveformTemplate", "Template", StringArray({ "Custom", "Sine", "Triangle", "Sawtooth", "Square 6.25%", "Square 18.75%", "Square 31.25%", "Square 37.5%", "Square 43.75%" }), 0));
    //for (int i = 0; i < 64; i++)
    //{
    //    parameters.createAndAddParameter(std::make_unique<AudioParameterInt>("waveformWave" + String(i), "wave" + String(i), 0, 63, 0));
    //}
    //settingRefs.setWaveform(&parameters);

    synth.setCurrentPlaybackSampleRate (44100); // Temporary setup, just in case. The actual sample rate is set in prepareToPlay func.

    setupVoice();
    synth.addSound (new GenericSound());
    
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
        synth.removeVoice (0);
    }

    int type = roundToInt (*settingRefs.osc);

    for (auto i = 0; i < (int) (*settingRefs.maxPoly); ++i)
    {
        switch (type)
        {
            case kVoiceTypePulse:
                synth.addVoice (new PulseVoice (&settingRefs));
                break;

            case kVoiceTypeTriangle:
                synth.addVoice (new TriangleVoice (&settingRefs));
                break;

            case kVoiceTypeNoise:
                synth.addVoice (new NoiseVoice (&settingRefs));
                break;

            case kVoiceTypeWaveform:
                synth.addVoice(new WaveformVoice(&settingRefs));
                break;
        }
    }
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
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Magical8bitPlug2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Magical8bitPlug2AudioProcessor::setCurrentProgram (int index)
{
}

const String Magical8bitPlug2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Magical8bitPlug2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Magical8bitPlug2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate (sampleRate);
}

void Magical8bitPlug2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Magical8bitPlug2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else

    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

#endif

    return true;
#endif
}
#endif

void Magical8bitPlug2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples()); // [5]

    /*
        buffer.clear();
        MidiBuffer processedMidi;
        int time;
        MidiMessage m;
        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
        {
            if (m.isNoteOn())
            {
                uint8 newVel = (uint8)noteOnVel;
                m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
            }
            else if (m.isNoteOff())
            {
            }
            else if (m.isAftertouch())
            {
            }
            else if (m.isPitchWheel())
            {
            }
            processedMidi.addEvent (m, time);
        }
        midiMessages.swapWith (processedMidi);


        ScopedNoDenormals noDenormals;
        auto totalNumInputChannels  = getTotalNumInputChannels();
        auto totalNumOutputChannels = getTotalNumOutputChannels();

        // In case we have more outputs than inputs, this code clears any output
        // channels that didn't contain input data, (because these aren't
        // guaranteed to be empty - they may contain garbage).
        // This is here to avoid people getting screaming feedback
        // when they first compile a plugin, but obviously you don't need to keep
        // this code if your algorithm always overwrites all the output channels.
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());

        // This is the place where you'd normally do the guts of your plugin's
        // audio processing...
        // Make sure to reset the state if your inner loop is processing
        // the samples and the outer loop is handling the channels.
        // Alternatively, you can process the samples with the channels
        // interleaved by keeping the same state.
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer (channel);

            // ..do something to the data...
        }
        */
}

//==============================================================================
bool Magical8bitPlug2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Magical8bitPlug2AudioProcessor::createEditor()
{
    return new Magical8bitPlug2AudioProcessorEditor (*this);
}

//==============================================================================
void Magical8bitPlug2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = parameters.copyState();

    XmlElement* rootElement = new XmlElement ("root");

    std::unique_ptr<XmlElement> stateElement = std::unique_ptr<XmlElement> (state.createXml());
    rootElement->addChildElement (stateElement.get());
    stateElement.release(); // give up the ownership already because xml object will delete it

    XmlElement* volEnvElement = new XmlElement ("volumeEnv");
    XmlElement* pitEnvElement = new XmlElement ("pitchEnv");
    XmlElement* dutEnvElement = new XmlElement ("dutyEnv");
    volEnvElement->addTextElement (settingRefs.volumeSequenceString);
    pitEnvElement->addTextElement (settingRefs.pitchSequenceString);
    dutEnvElement->addTextElement (settingRefs.dutySequenceString);
    rootElement->addChildElement (volEnvElement);
    rootElement->addChildElement (pitEnvElement);
    rootElement->addChildElement (dutEnvElement);

    std::unique_ptr<XmlElement> xml (rootElement);

    copyXmlToBinary (*xml, destData);
}

void Magical8bitPlug2AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    //if (Magical8bitPlug2AudioProcessorEditor* activeEditor = (Magical8bitPlug2AudioProcessorEditor*)getActiveEditor())
    //{
    //    activeEditor->waveformInit();
    //}

    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName ("root"))
        {
            // ValueTree
            XmlElement* valueTreeXml = xmlState->getChildByName (parameters.state.getType());

            if (valueTreeXml != nullptr)
            {
                parameters.replaceState (ValueTree::fromXml (*valueTreeXml));
            }
            else
            {
                printf ("Saved plugin parameters are incompatible");
            }

            // Custom Env
            XmlElement* volumeEnvXml = xmlState->getChildByName ("volumeEnv");
            XmlElement* pitchEnvXml = xmlState->getChildByName ("pitchEnv");
            XmlElement* dutyEnvXml = xmlState->getChildByName ("dutyEnv");

            if (volumeEnvXml != nullptr)
            {
                XmlElement* volElem = volumeEnvXml->getFirstChildElement();

                if (volElem != nullptr && volElem->isTextElement())
                {
                    String volStr = volElem->getText();

                    ParseError err = kParseErrorNone;
                    settingRefs.setSequenceWithString ("volume", volStr, &err);

                    if (settingRefs.volumeSequenceListener != nullptr)
                    {
                        settingRefs.volumeSequenceListener->sequenceChanged (volStr);
                    }

                    Logger::writeToLog ("volume seq = " + volStr);
                }
                else
                {
                    Logger::writeToLog ("volumeEnv entry found, but seems not like a text element.");
                }
            }

            if (pitchEnvXml != nullptr)
            {
                XmlElement* pitElem = pitchEnvXml->getFirstChildElement();

                if (pitElem != nullptr && pitElem->isTextElement())
                {
                    String pitStr = pitElem->getText();
                    ParseError err = kParseErrorNone;
                    settingRefs.setSequenceWithString ("pitch", pitStr, &err);

                    if (settingRefs.pitchSequenceListener != nullptr)
                    {
                        settingRefs.pitchSequenceListener->sequenceChanged (pitStr);
                    }

                    Logger::writeToLog ("pitch seq = " + pitStr);
                }
                else
                {
                    Logger::writeToLog ("pitchEnv entry found, but seems not like a text element.");
                }
            }

            if (dutyEnvXml != nullptr)
            {
                XmlElement* dutElem = dutyEnvXml->getFirstChildElement();

                if (dutElem != nullptr && dutElem->isTextElement())
                {
                    String dutStr = dutElem->getText();
                    ParseError err = kParseErrorNone;
                    settingRefs.setSequenceWithString ("duty", dutStr, &err);

                    if (settingRefs.dutySequenceListener != nullptr)
                    {
                        settingRefs.dutySequenceListener->sequenceChanged (dutStr);
                    }

                    Logger::writeToLog ("duty seq = " + dutStr);
                }
                else
                {
                    Logger::writeToLog ("dutyEnv entry found, but seems not like a text element.");
                }
            }
        }
    }

    setupVoice();

    if (Magical8bitPlug2AudioProcessorEditor* activeEditor = (Magical8bitPlug2AudioProcessorEditor*)getActiveEditor())
    {
        activeEditor->resized();
        activeEditor->resizeWholePanel();
        activeEditor->waveformUpdate();
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Magical8bitPlug2AudioProcessor();
}
