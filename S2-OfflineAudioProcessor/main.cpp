#include <stdio.h>
#include <stdlib.h>
#include "audio_processor.h"


int main( int argc, char *argv[]) {

    if (argc == 3) {
        printf("Processing audio file %s into %s.\n", argv[1], argv[2]);
    } else {
        printf("Arguments error. Usage: OfflineAudioProcessor INPUT OUTPUT.\n");
        return -1;
    }

    // try to open input file
    FILE* input_file_handler = fopen(argv[1],"rb");
    if (input_file_handler == nullptr) {
        printf("Failed to open input file.\n");
        return -1;
    }

    // try to create output file
    FILE* output_file_handler = fopen(argv[2],"wb");
    if (output_file_handler == nullptr) {
        printf("Failed to create output file.\n");
        return -1;
    }

    // prepare audio processor and processing buffer
    AudioProcessor * processor = new AudioProcessor{1.0f};
    unsigned int buffer_size = 4096;
    float * buffer = (float*)calloc(buffer_size, sizeof(float));

    // main processing loop
    size_t read_size = 0;
    size_t write_size = 0;
    while ((read_size = fread(buffer, sizeof(float), buffer_size, input_file_handler))) {
        printf("Processing %zu frames...\n", read_size);
        processor->Process(buffer, read_size);
        write_size = fwrite(buffer, sizeof(float), read_size, output_file_handler);
        if (write_size != read_size) {
            printf("Failed to write into output file. %zu, %zu\n", read_size, write_size);
            return -1;
        }
    }

    // clean up
    delete processor;
    free(buffer);

    // finish
    printf("Processing done. Output file : %s.\n", argv[2]);

    return 0;
}
