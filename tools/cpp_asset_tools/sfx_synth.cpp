#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <cstdint>

void write_wav(const std::string& outPath, const std::vector<int16_t>& samples, int sampleRate) {
    std::ofstream out(outPath, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outPath << std::endl;
        return;
    }
    int dataSize = samples.size() * 2;
    int fmtChunkSize = 16;
    int wavSize = 4 + (8 + fmtChunkSize) + (8 + dataSize);
    // RIFF header
    out.write("RIFF", 4);
    uint32_t chunkSize = wavSize;
    out.write(reinterpret_cast<const char*>(&chunkSize), 4);
    out.write("WAVE", 4);
    // fmt chunk
    out.write("fmt ", 4);
    uint32_t fmtSize = fmtChunkSize;
    out.write(reinterpret_cast<const char*>(&fmtSize), 4);
    uint16_t audioFormat = 1; // PCM
    uint16_t numChannels = 1;
    uint32_t sr = sampleRate;
    uint32_t byteRate = sr * numChannels * 2;
    uint16_t blockAlign = numChannels * 2;
    uint16_t bitsPerSample = 16;
    out.write(reinterpret_cast<const char*>(&audioFormat), 2);
    out.write(reinterpret_cast<const char*>(&numChannels), 2);
    out.write(reinterpret_cast<const char*>(&sr), 4);
    out.write(reinterpret_cast<const char*>(&byteRate), 4);
    out.write(reinterpret_cast<const char*>(&blockAlign), 2);
    out.write(reinterpret_cast<const char*>(&bitsPerSample), 2);
    // data chunk
    out.write("data", 4);
    uint32_t dataSz = dataSize;
    out.write(reinterpret_cast<const char*>(&dataSz), 4);
    out.write(reinterpret_cast<const char*>(samples.data()), dataSize);
    out.close();
}
// SFX Synth (stub)
// Dev Credit: Stephen Deline Jr
#include <iostream>
int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout << "Usage: sfx_synth <output_wav> <waveform> <duration_ms>\n";
        std::cout << "Waveform: square | triangle | noise\n";
        return 1;
    }
    std::string outPath = argv[1];
    std::string waveform = argv[2];
    int durationMs = std::stoi(argv[3]);
    std::cout << "Generating WAV: " << outPath << " waveform: " << waveform << " duration: " << durationMs << "ms\n";
    // Generate WAV SFX (square, triangle, noise)
    int sampleRate = 44100;
    int numSamples = sampleRate * durationMs / 1000;
    std::vector<int16_t> samples(numSamples);
    if (waveform == "square") {
        for (int i = 0; i < numSamples; ++i) {
            double t = double(i) / sampleRate;
            samples[i] = (i % (sampleRate / 440) < (sampleRate / 880)) ? 16000 : -16000;
        }
    } else if (waveform == "triangle") {
        for (int i = 0; i < numSamples; ++i) {
            double t = double(i) / sampleRate;
            double phase = fmod(t * 440, 1.0);
            samples[i] = int16_t(32000 * (2 * fabs(phase - 0.5) - 1));
        }
    } else if (waveform == "noise") {
        std::mt19937 rng(12345);
        std::uniform_int_distribution<int16_t> dist(-16000, 16000);
        for (int i = 0; i < numSamples; ++i) {
            samples[i] = dist(rng);
        }
    } else {
        std::cerr << "Unknown waveform: " << waveform << std::endl;
        return 1;
    }
    write_wav(outPath, samples, sampleRate);
    std::cout << "WAV generated: " << outPath << std::endl;
    return 0;
}
