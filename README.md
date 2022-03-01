
# Real time audio processing

#### An introductory project to the wonderful world of real-time audio programming.

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

The goal of this project is to implement a real-time audio signal processing application.  
You will follow the usual steps of such a project:  
- Preliminary step: choice of an audio effect and bibliography.
- S1. Prototyping the audio processing algorithm with `Python`.
- S2. Platform-agnostic implementation of the audio processing module in `C++`, testing in a simple non-real-time command-line-interface (CLI) program.
- S3. Integration of the module in real-time audio processing applications coded in `C++`.

The main objective here is to work on real-time audio processing algorithms in `C++`. Therefore, other parts of the code (command line or graphical interface, plugging to the system's audio render loop etc.) is provided. However, it is possible to modify everything at will.


## What you'll need

### Hardware

- Steps S1 and S2 can be done on __any Linux, macOS or Windows computer__.
- Step S3 can also be done on __any Linux, macOS or Windows computer__, but additionnal hardware may be needed depending on the platform on which you want to build your application:
  - You can run the application on __the same computer__ you are working on, but you will need at least __a mono audio input and a stereo audio output__.
  - You can run the application on an __Android device__, smartphone or tablet, with at least __a mono audio input and a stereo audio output__. 
  - You can run the application on an __iOS device__, smartphone or tablet, with at least __a mono audio input and a stereo audio output__, but you will need to work on __macOS computer__ in that case.

### Softwares

- For step 1, a pre-configured online environment is available on __[replit](https://replit.com)__ and only requires a web browser. If you prefer to work on your own environment, you can use __whatever Python editor you'd like__ (IDLE, Spyder, VSCode, Atom, PyCharm etc.), with __Python >=3.7, numpy and scipy__, and all the other libraries you may want to use for the implementation of your algorithm. 
- For step 2, a pre-configured online environment is available on __[replit](https://replit.com)__ and only requires a web browser. If you prefer to work on your own environment, S2 requires either __cmake__ and __make__ or any __C++ compiler__ (__g++ or clang++__ for example), and any __code editor__. Use of a debugger -__gdb__ for example- is strongly recommended but not necessary. Feel free to use you favorite __C++ IDE__ (VSCode, Atom, Eclipse, Code::Blocks, Geany, CLion, Visual Studio, XCode, etc.).
- Step 3 requires the [__JUCE framework__](https://juce.com), which you can get for free for eductional purpose. Depending on the platform you want to build on, you will need specific software:
  - For Windows, you'll need [__Visual Studio 2015, 2017, 2019 or 2022__](https://visualstudio.microsoft.com).
  - For macOS and iOS, you'll need [__Xcode__](https://developer.apple.com/xcode/) and an __[Apple Developer account](https://developer.apple.com/account/)__.
  - For Linux, you'll need [__make__](https://www.gnu.org/software/make/), or [__Code::Blocks__](https://www.codeblocks.org).
  - For Android, you'll need [__Android Studio__](https://developer.android.com/studio/).


## Example audio files

In order to simplify the platform-agnostic implementation and get rid of the audio decoding and encoding, you'll use WAV audio files throughout this project.  
Some audio file examples are provided in the [`Sounds`](Sounds) directory. All WAV files are mono with a sample rate of 44100 Hz.  
Feel free to use these or your own audio files to test your code.


## Preliminary step: Choice of the audio effect and bibliography

This project can be carried out with any audio processing algorithm, as long as it is real-time compatible. Here is a list of suggestions, from the easiest to the most difficult:

- delay,
- tremolo -amplitude modulation-,
- vibrato -frequency modulation-,
- wah-wah,
- phaser,
- bitcrusher -low-resolution quantization-,
- dynamic compressor,
- distortion / overdrive,
- graphical or parametric equalizer,
- reverb,
- pitch-shifting -temporal or frequential methods-
- etc.

Before starting step 1, you need to choose an algorithm and study it by finding the necessary literature to fully understand it and be able to implement it. You'll need at least a graphical representation of your effect, with the corresponding time-domain and frequency-domain equations.     

Here is a selected bibliography on audio effects:
- [DAFX - Digital Audio Effects](http://dafx.de/DAFX_Book_Page/index.html)
- [Julius Orion Smith III website](https://ccrma.stanford.edu/~jos/)


## S1. Prototyping : [`S1-Python_AudioProcessor`](S1-Python_AudioProcessor)

The goal of this first step if the try and test your algorithm. Python let you implement and test audio processing algorithms quickly, with very few lines of code. You can test and improve your algorithm until you obtain satisfying audio results.

A script `audio_processor.py` is provided, as long as some audio files (see above).  
For the moment, the script simply copies the content of the input audio file to the output audio file without any modification.

What you have to do in this step is to add your processing algorithm in the script where indicated to modify the audio data.  
Check the results, and proceed to the next step when you are satisfied.  

Please refer to the [README.md file](S1-Python_AudioProcessor/README.md) file of the [`S1-Python_AudioProcessor`](S1-Python_AudioProcessor) directory.  


## S2. C++ Implementation: [`S2-CPP_OfflineAudioProcessor`](S2-CPP_OfflineAudioProcessor)

During this second step, your goal is to translate the final algorithm of the previous step in platform-agnostic, real-time-compatible C++ code. In order to simplify this task, you will do this in the most simple context: a CLI program called `OfflineAudioProcessor`.  

Please refer to the [README.md file](S2-CPP_OfflineAudioProcessor/README.md) inside the [`S2-CPP_OfflineAudioProcessor`](S2-CPP_OfflineAudioProcessor) directory for detailed explanation.

## S3. Integration inside a real-time application: [`S3-JUCE_AudioLoop`](S3-JUCE_AudioLoop)

The final step aims at integrate the algorithm in a real-time application. More precisely, you will directly integrate the `AudioProcessor` class, the one you modified in the previous step, in a simple application called `AudioLoop`.

`AudioLoop` is a simple example of audio real-time application: it captures the audio input of the device, apply a real-time process on the data, and send the modified audio data to the audio output. This application is developped using the [JUCE framework](https://juce.com), and can be built for macOS, Linux, Windows, iOS or Android.

The project is located inside the directory [`S3-JUCE_AudioLoop`](S3-JUCE_AudioLoop).

Please refer to the [README.md file](S3-JUCE_AudioLoop/README.md) inside the [`S3-JUCE_AudioLoop`](S3-JUCE_AudioLoop) directory for detailed explanation.
