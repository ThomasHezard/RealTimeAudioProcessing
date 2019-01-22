# Offline Audio Processor

## Make out-of-source with `CMake`

Type the following commands from project's root:
```
mkdir build
cd build
cmake ..
make
```

## Make out-of-source with `g++` or `clang++` (or any other C++ compiler)

Type the following commands from project's root (replace gcc++ with your compiler if needed)
```
mkdir build
cd build
g++ -std=c++11 ../main.cpp ../audio_processor.cpp -o OfflineAudioProcessor
```

## Usage

Once built, use the executable with the following command:
```
./OfflineAudioProcessor INPUT OUTPUT
```
`INPUT` must be a RAW audio file, mono and float-32. `OUTPUT` will be the same.  
See main documentation to convert files between WAV and RAW formats.
