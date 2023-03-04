#include <iostream>
#include <cstring>
#include "audio_processor.h"
#include "../external/AudioFile.h"


int main( int argc, char *argv[]) {

    if (argc == 3) {
        std::cout << "Processing audio file " << argv[1] << " into file " << argv[2] << ".\n";
    } else {
        std::cout << "ERROR: Argument error. Usage: OfflineAudioProcessor INPUT OUTPUT.\n";
        return -1;
    }

    // try to open input file
    std::string input_file_name{argv[1]};
    auto input_file = new AudioFile<float>();
    bool success = input_file->load(input_file_name);
    if (!success) {
        std::cout << "ERROR: Input file reading error.\n";
        return -1;
    }
    if (input_file->getNumChannels() != 1) {
        std::cout << "ERROR: Input file must be mono.\n";
        return -1;
    }
    
    // prepare output file
    std::string output_file_name{argv[2]};
    auto output_file = new AudioFile<float>();
    output_file->setAudioBufferSize(input_file->getNumChannels(), input_file->getNumSamplesPerChannel());

    // prepare audio processor and processing buffers
    AudioProcessor* processor = new_audio_processor();
    prepare_audio_processor(processor);
    unsigned int buffer_size = 4096;
    float * input_buffer = (float*)calloc(buffer_size, sizeof(float));
    float * output_buffer = (float*)calloc(buffer_size, sizeof(float));

    // main processing loop
    int number_processed_frames = 0;
    int batch_size = buffer_size;
    int remaining_frames = input_file->getNumSamplesPerChannel() - number_processed_frames;
    while (remaining_frames > 0) {
        if (remaining_frames < batch_size) {
            batch_size = remaining_frames;
        }
        std::cout << "Processing " << batch_size << " frames...\n";
        memcpy(input_buffer, input_file->samples[0].data() + number_processed_frames, batch_size*sizeof(float));

        ap_process(processor, input_buffer, output_buffer, batch_size);
        
        memcpy(output_file->samples[0].data() + number_processed_frames, output_buffer, batch_size*sizeof(float));
        number_processed_frames += batch_size;
        remaining_frames = input_file->getNumSamplesPerChannel() - number_processed_frames;
    }
    
    // write output file
    success = output_file->save(output_file_name);
    if (!success) {
        std::cout << "ERROR: Output file writing error.\n";
        return -1;
    }

    // clean up
    destroy_audio_processor(processor);
    delete output_file;
    delete input_file;

    // finish
    std::cout << "Processing done. Output file : " << output_file_name << ".\n";

    return 0;
}
