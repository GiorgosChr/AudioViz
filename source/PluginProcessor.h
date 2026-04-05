#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)

    // FFT information
    static constexpr int fftOrder = 11;
    static constexpr int fftSize  = 1 << fftOrder; // 2^fftOrder

    juce::dsp::FFT forwardFFT {fftOrder};
    juce::dsp::WindowingFunction<float> window {(size_t) fftSize, juce::dsp::WindowingFunction<float>::hann};

    std::array<float, fftSize * 2> fftBuffer {};
    std::array<float, fftSize> fifo {};
    std::array<float, fftSize> fftData {};
    
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;

    // Helper functions to fill FIFO (First In First Out)
    // and to process the input.
    void pushInFifo(const float& sample);
    void computeFFT();
};
