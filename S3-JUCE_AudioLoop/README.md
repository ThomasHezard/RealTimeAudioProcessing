# AudioLoop


This demo app is part of the student project [Real-time audio processing](https://github.com/ThomasHezard/RealTimeAudioProcessing).

The app captures the audio input, process it with the class `AudioProcessor`, and send the results to the audio output.

⚠️ It is highly recommended to work on this project with headphones, to avoid a Larsen effect between the audio input and output.

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

## Presentation of the AudioLoop project

This application is developped using the [JUCE framework](https://juce.com), and can be built for macOS, Linux, Windows, iOS or Android.  

The app is already fully functionnal with the following features:
- An audio processing loop where the audio input is captured, process with the class `AudioProcessor`, and and then senbt to the audio output. 
- The audio rendering loop automatically starts when the program starts.
- If you build and run the app in a desktop environement, some audio hardware controls are available in the interface.
- Two controllers are available in the interface. In the current state of the project, they are not linked to the `AudioProcessor`, but you'll be able to use them to control your processor's parameters in real time if you want.

All the files you will have to modify are located inthe [`sources/audio_engine`](sources/audio_engine) directory. You should not modify the other files or the [`AudioLoop.jucer`](AudioLoop.jucer) project.

---

## How to build and run

- Make sure [JUCE](https://juce.com) is installed on your computer with the `Projucer` app available and the global paths properly set.
- Depending on the platform you are working on and the platform on which you want to run the app, be sure you have all the tools needed installed on your system. See the main README of the project for more information.
- Open the [`AudioLoop.jucer`](AudioLoop.jucer) with `Projucer`.
- Choose your exporter and export the project.
- You can now build the app with the build system corresponding to your exporter (Xcode, make, Visual Studio, Code::Block or Android Studio), and edit the sources in your favourite IDE.

---

## AudioProcessor integration

An instance of `AudioProcessor` has been inserted inside the main audio render loop.  
Source files are located in [`sources/audio_processor/audio_processor.*`](sources/audio_processor).  
`AudioProcessor` is used the following way:
  - Instanciation of the `AudioProcessor` inside the `audio_processor_` variable of `AudioEngine` in [`sources/audio_engine.cpp` line 15](sources/audio_engine.cpp#L15).
  - Call of the `Prepare` function in [`sources/audio_engine.cpp` line 22](sources/audio_engine.cpp#L22).
  - Call of the `Process` function in [`sources/audio_engine.cpp` line 36](sources/audio_engine.cpp#L36).

For the moment, `AudioProcessor` do not have any parameters, and the controllers from UI are linked to two variables from `AudioEngine`: `parameter_a_` and `parameter_b_`.   
If you want to link these paramaters to your `AudioProcessor`, you have to modify the following code:
  - Setters and getters for the parameters in [`sources/audio_engine.cpp` lines 42](sources/audio_engine.cpp#L42), [47](sources/audio_engine.cpp#L47), [52](sources/audio_engine.cpp#L52) and [57](sources/audio_engine.cpp#L57).
  - The controllers have a range of `[0,1]` with a mid value of `0.5`. You can either
    - change these values in [`main_screen.cpp` lines 18-19](main_screen.cpp#L18) and [37-38](main_screen.cpp#L37)
