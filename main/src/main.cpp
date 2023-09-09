#include <iostream>

#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>

class SineWaveGenerator : public juce::AudioIODeviceCallback
{
public:
    SineWaveGenerator()
    {
        sampleRate = 44100.0;  // Sample rate in Hz
        frequency = 440.0;     // Frequency of the sine wave in Hz
        amplitude = 0.5;       // Amplitude (volume) of the sine wave

        angularFrequency = 2.0 * juce::MathConstants<double>::pi * frequency;
        currentAngle = 0.0;
    }

    void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
                                          int numInputChannels,
                                          float* const* outputChannelData,
                                          int numOutputChannels,
                                          int numSamples,
                                          const juce::AudioIODeviceCallbackContext& context) override
    {
        for (int channel = 0; channel < numOutputChannels; ++channel)
        {
            float* channelData = outputChannelData[channel];

            for (int sample = 0; sample < numSamples; ++sample)
            {
                channelData[sample] = static_cast<float>(amplitude * std::sin(currentAngle));
                currentAngle += angularFrequency / sampleRate;

                if (currentAngle >= 2.0 * juce::MathConstants<double>::pi)
                    currentAngle -= 2.0 * juce::MathConstants<double>::pi;
            }
        }
        std::cout << numOutputChannels << std::endl;
    }

    void audioDeviceAboutToStart(juce::AudioIODevice* device) override
    {
        sampleRate = device->getCurrentSampleRate();
    }

    void audioDeviceStopped() override
    {
        sampleRate = 0.0;
    }

private:
    double sampleRate;
    double frequency;
    double amplitude;
    double angularFrequency;
    double currentAngle;
};

int main()
{
    juce::AudioDeviceManager audioDeviceManager;

    SineWaveGenerator sineWaveGenerator;

    //juce::String error = audioDeviceManager.initialise(0, 2, nullptr, true);
    juce::String error = audioDeviceManager.initialiseWithDefaultDevices(0, 2);
    audioDeviceManager.addAudioCallback(&sineWaveGenerator);

    std::cout << "Error(?): " << error << std::endl;

    juce::AudioDeviceManager::AudioDeviceSetup setup = audioDeviceManager.getAudioDeviceSetup();
    // Configure the audio device setup here, e.g., setup.inputDeviceName and setup.outputDeviceName
    std::cout << setup.bufferSize << std::endl;
    setup.bufferSize = 8192;
    audioDeviceManager.setAudioDeviceSetup(setup, false);


    // error = audioDeviceManager.setAudioDeviceSetup(setup, true);
    // std::cout << "Error(?): " << error << std::endl;
    audioDeviceManager.restartLastAudioDevice();

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    audioDeviceManager.removeAudioCallback(&sineWaveGenerator);
    audioDeviceManager.closeAudioDevice();

    return 0;
}
