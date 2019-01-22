
# Student project : Real time audio processing on mobile platforms

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

## Objectives

The goal of this project is to implement a real-time audio signal processing application on iOS and/or Android.  
You will follow the usual steps of such a project:  

- Preliminary step: choice of an audio effect and bibliography.
- S1. Prototyping the audio processing algorithm with `Matlab` or `Python`.
- S2. Platform-agnostic implementation of the audio processing module in `C++`, testing in a simple non-real-time command-line-interface (CLI) program.
- S3. Integration of the module in iOS and/or Android applications.

The main objective here is to work on real-time audio processing algorithms in `C++`. Therefore, other parts of the code (command line or graphical interface, plugging to the system's audio render loop etc.) is provided. However, it is possible to modify everything at will.


## What you'll need

### Hardware

- Steps S1 and S2 can be done on __any Linux, macOS or Windows computer__.
- The Android version of S3 requires also __an Android device (Android 8.1 or more recent) with audio input and output__, like a standard Android smartphone or tablet.
- The iOS version of S3 can be done on a __macOS computer__ only. Although it will be possible to run the application on a simulator, it is preferable to have __an iOS device (iOS 9.0 or more recent)__ (iPhone, iPad or iPod) at hand to test it.

### Softwares

- The Matlab version of S1 simply requires __Matlab__. No specific library is necessary, unless you need some for the implementation of your algorithm.
- The Python version of S1 requires __Python >=3.6, numpy and scipy__, and all the other libraries you may want to use for the implementation of your algorithm. You can use __whatever Python editor you'd like__ (IDLE, Spyder, VSCode, Atom, PyCharm etc.).
- S2 requires any __C++ compiler__ (__g++ or clang++__ for example), and any __code editor__. Use of a debugger -__gdb__ for example- is strongly recommended but not necessary. Feel free to use you favorite __C++ IDE__ (VSCode, Atom, Eclipse, Code::Blocks, Geany, CLion, Visual Studio, XCode, etc.).
- The Android version of S3 requires [__Android Studio__](https://developer.android.com/studio/) with __Android API 27, CMake 3.6, Android SDK Tools and Android NDK 18.1__ (stick to these specific versions).
- The iOS version of S3 requires [__Xcode__](https://developer.apple.com/xcode/) and an __[Apple Developer account](https://developer.apple.com/account/)__.


## Example audio files: `Sounds` folder

In order to simplify the platform-agnostic implementation and get rid of the WAV files decoding and encoding, you'll use "RAW audio" files. Unlike WAV files, which contain a header describing the audio and binary format, RAW audio files only contain series of numbers, and it is necessary to know the format in advance in order to read it correctly. In this project, all RAW audio files are encoded as PCM, mono, float-32 with a sample rate of 44100 Hz.

### Python scripts

Two python scripts are provided to convert between WAV and RAW audio files with the encoding described above.

You can convert `FILE.wav` to `FILE.pcm` with the following command:
```
python wavTOpcmf32.py FILE.wav FILE.pcm
```

You can convert `FILE.pcm` to `FILE.wav` with the following command:
```
python pcmf32TOwav.py FILE.pcm FILE.wav
```

### ffmpeg

Conversion between RAW and WAV audio formats is easily done with the CLI freeware `ffmpeg`, but you have to explicitly set the endianness of the RAW file.  
Let's suppose you have a RAW audio file `FILE.pcm`, encoded with the parameters described above, with a little-endian representation. You can convert it to a WAV file with the following command:
```
ffmpeg -f f32le -ar 44100 -ac 1 -i FILE.pcm FILE.wav
```
For a big-endian file, just replace `f32le` by `f32be`.

The reverse conversion is done with the following command:
```
ffmpeg -i FILE.wav -f f32le -acodec pcm_f32le FILE.pcm
```
Again, simply replace `f32le` by `f32be` for a big-endian representation.

To know your system's native endianness, run the following command:

- on Linux: `lscpu | grep "Byte Order"`
- on macOS: `sysctl hw | grep "byteorder"`
- on Windows: it should be little-endian, you can check with Python,
- with Python (any system): `python -c "import sys; print sys.byteorder"`


## Preliminary step: Choice of the audio effect and bibliography

This project can be carried out with any audio processing algorithm, as long as it is real-time compatible. Here is a list of suggestions, from the easiest to the most difficult:

- delay,
- tremolo -amplitude modulation-,
- vibrato -frequency modulation-,
- bitcrusher -low-resolution quantization-,
- dynamic compressor,
- distortion / overdrive,
- graphical or parametric equalizer,
- reverb,
- pitch-shifting -temporal or frequential methods-
- etc.

Before starting step 1, you need to choose an algorithm and study it by finding the necessary literature to fully understand it and be able to implement it. You'll need at least a graphical representation of your effect, with the corresponding time-domain and frequency-domain equations.


## S1. Prototyping : `S1-Matlab_AudioProcessor` / `S1-Python_AudioProcessor`

The goal of this first step if the try and test your algorithm. Both Matlab and Python let you implement and test algorithms quickly, with few lines of code. You can test several version until you obtain satisfying audio results.

Two scripts `audio_processor.m` and `audio_processor.py` are provided, as long as some audio files (see above).  
For the moment, the scripts simply copy the content of the input audio file to the output audio file without any modification.

What you have to do in this step is to add your processing algorithm in the script where indicated to modify the audio data.  
Check the results, and proceed to the next step when you are satisfied.


## S2. C++ Implementation: `S2-OfflineAudioProcessor`

During this second step, your goal is to translate the final algorithm of the previous step in platform-agnostic, real-time-compatible C++ code. In order to simplify this task, you will do this in the most simple context: a CLI program called `OfflineAudioProcessor`.  
The project structure is already established, and the provided program does the following:

- open a RAW audio file and read it,
- apply some audio processing to the data,
- write the modified data in a RAW audio file.

This program is not real-time, but the provided architecture is compatible with real-time constraints.

The proposed architecture contains a class named `AudioProcessor`, defined and implemented in the files `audio_processor.h` and `audio_processor.cpp`. This class is used in the main function - `main.cpp` - as follows:

- construction of an instance of `AudioProcessor` at the beginning of the program: `main.cpp` line 30,
- processing inside an audio process loop: `main.cpp` line 39,
- destruction of the instance at the end of the program: `main.cpp` line 48.

Details of how to build and run `OfflineAudioProcessor` are given in its `README.md` file.

As in step 1, the provided version of `OfflineAudioProcessor` does nothing more than copying input data into output data. Your objective for this step is to modify the `AudioProcessor` class in files `audio_processor.h` and `audio_processor.cpp`, so that it performs the audio processing algorithm you implemented in the previous step. What you need to do is:

- adapt the definition of the `AudioProcessor` class with all the needed member variables (memory buffer, parameters, etc.),
- adapt its constructor and destructor and, if needed, the call to the constructor in the main function,
- adapt its `Process` function's implementation (you shouldn't have to modify its declaration).

Once your modifications are completed and functional, you need to design and implement tests to check that the results are exactly the same as in the previous step.


## S3. Integration inside a mobile application: `S3-Android_AudioLoop` / `S3-iOS_AudioLoop`

The final step aims at integrate the algorithm in a mobile application. More precisely, you will directly integrate the `AudioProcessor` class, the one you modified in the previous step, in a simple application called `AudioLoop`.

`AudioLoop` is a simple example of audio real-time application: it captures the audio input of the device, apply a real-time process on the data, and send the modified audio data to the audio output. Two sample applications for iOS and Android are provided inside the directories `S3-Android_AudioLoop` et `S3-iOS_AudioLoop`.

The `AudioProcessor` model is a bit different in this step.

- The parameters that will be modified by the user (`gain` in the example provided) are atomic in order to avoid unexpected behavior when both the audio thread and the graphical thread are accessing (writing or reading) the variables.
- The different parameters are all set and get with the same functions `void set_param(int param_id, float value)`and `float get_param(int param_id)`. Each parameter is associated with an integer ID (in the example provided, the only parameter `gain` is associated to the parameter ID `0`), and internal getters and setters are called within them using a `switch` statement.

You can now modify the files `audio_processor.h` and `audio_processor.cpp` to replicate the modifications you did in the previous step. You can find them in the following directories:

- Android: `S3-Android_AudioLoop/app/src/main/cpp/`,
- iOS: `S3-iOS_AudioLoop/Classes`.

Then, if it is necessary, don't forget to modify the call of the `AudioProcessor` constructor:

- Android: `S3-Android_AudioLoop/app/src/main/cpp/audio_player.cpp` line 193,
- iOS: `S3-iOS_AudioLoop/AudioLoop/Classes/AUAudioProcessor.mm` line 79.

Instructions to build and run the apps are provided in each project's `README.md` file.
