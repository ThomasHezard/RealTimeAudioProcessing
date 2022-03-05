# Offline Audio Processor

This project is the step 2 of the main project [Real-time audio processing](https://github.com/ThomasHezard/RealTimeAudioProcessing). Please refer to the README of main project for more information.

---

## Author

Thomas Hézard - Audio scientist and developer  
www.thomashezard.com  
thomas.hezard [at] thz.fr

---

## License

This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).  
[![Licence Creative Commons](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-nc-sa/4.0/)

---

## 🎯  Objectives

Your goal is to translate the final algorithm of the previous step into platform-agnostic, real-time-compatible C++ code. In order to simplify this task, you will do this in the most simple context: a CLI program called `OfflineAudioProcessor`.  

The project structure is already established, and the provided program does the following:

- open a WAV audio file and read it (using the external library `AudioFile`),
- apply some audio processing to the data,
- write the modified data in a WAV audio file (using the external library `AudioFile`).

This program is not real-time, but the provided architecture is compatible with real-time constraints.  

The proposed architecture contains a class named `AudioProcessor`, defined and implemented in the files [`audio_processor.h`](sources/audio_processor.h) and [`audio_processor.cpp`](sources/audio_processor.cpp). This class is used in the main function - [`main.cpp`](sources/main.cpp) - as follows:

- construction of an instance of `AudioProcessor` at the beginning of the program: [`main.cpp` line 35](sources/main.cpp#L35),
- preparation of the `AudioProcessor`: [`main.cpp` line 36](sources/main.cpp#L36),
- processing inside an audio process loop: [`main.cpp` line 52](sources/main.cpp#L52),
- destruction of the instance at the end of the program: [`main.cpp` line 67](sources/main.cpp#L67).

All header and source files are located in the [`sources`](sources) directory.

As in step 1, the provided version of `OfflineAudioProcessor` does nothing more than copying input data into output data. Your objective for this step is to modify the `AudioProcessor` class in files `audio_processor.h` and `audio_processor.cpp`, so that it performs the audio processing algorithm you implemented in the previous step. What you need to do is:

- adapt the definition of the `AudioProcessor` class with all the needed member variables (memory buffer, parameters, etc.),
- if your `AudioProcessor` needs some prior information before starting the rendering loop, like sample rate or parameter values, these information should be passed in the `Prepare` function, it is recommended to keep a constructor as simple as possible,
- adapt its `Prepare` function and destructor and, if needed, the call to the `Prepare` function in the main function,
- adapt its `Process` function's implementation (you shouldn't have to modify its declaration).

Once your modifications are completed and functional, you need to design and implement tests to check that the results are exactly the same as in the previous step.


---

## ⚙️  Compilation and run instructions

### Compile and run on replit

This project can be compiled and run in a pre-configured environment on replit: [Run on replit](https://replit.com/@ThomasHezard/RealTimeAudioProcessing-Step2OfflineCPP).  
Clicking the `Run` button will compile the project, and run it to read the audio file `Marimba.wav`, process its audio data, and write the resulting audio data in the audio file `output.wav`.  

### Compile out-of-source with `CMake` and `make`

Type the following commands from project's root:
```
mkdir build
cd build
cmake ..
make
```

### Compile out-of-source with `g++` or `clang++` (or any other C++ compiler)

Type the following commands from project's root (replace `gcc++`` with your compiler if needed)
```
mkdir build
cd build
g++ -std=c++11 ../sources/main.cpp ../sources/audio_processor.cpp -o OfflineAudioProcessor
```

### Running the compiled program

Once built, run the executable with the following command:
```
./OfflineAudioProcessor INPUT OUTPUT
```
`INPUT` must be the path to a WAV mono audio file. You can use the provided file `Marimba.wav`.  
`OUTPUT` must be the path to a non-existing WAV audio file.  
For example, after building with cmake, while still inside the `build` folder: 
```
./OfflineAudioProcessor ../Marimba.wav ../output.wav
```

--- 

## Credits

Thanks to Adam Stark for [AudioFile C++ library](https://github.com/adamstark/AudioFile), copyright (c) 2017 Adam Stark.
