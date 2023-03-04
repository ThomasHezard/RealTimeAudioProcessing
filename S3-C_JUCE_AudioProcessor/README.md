# AudioProcessor


This project is the step 3 of the main project [Real-time audio processing](https://github.com/ThomasHezard/RealTimeAudioProcessing). Please refer to the README of main project for more information.

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

## 📋  Presentation of the AudioLoop project

The application `AudioProcessor` provided is developped using the [JUCE framework](https://juce.com), and can be built for macOS, Linux or Windows.  

The app is already fully functionnal with the following features:
- The audio processing loop reads an audio file little by little, processes it with the class `AudioProcessor` (the same class as in step 2 of the project), and sends teh result to the audio output. 
- The audio processing loop automatically starts when the program starts.
- Buttons are available to browse for an audio file to play (wav and mp3 only), and start/stop the file playing.
- Two controllers are available in the interface. In the current state of the project, they are not linked to the `AudioProcessor`, but you'll be able to use them to control your processor's parameters in real time if you want.

All the files you will have to modify are located in the [`sources/audio_engine`](sources/audio_engine) directory. You should not modify the other files or the [`AudioProcessor.jucer`](AudioProcessor.jucer) project.

---

## 🎯  Objectives: `AudioProcessor` integration

An instance of the class `AudioProcessor`, the same you worked on in step 2, is used inside the main audio render loop.  
Source files are located in [`sources/audio_engine/audio_processor.*`](sources/audio_processor).  
`AudioProcessor` is used the following way:
  - Instanciation of the `AudioProcessor` inside the `audio_processor_` variable of `AudioEngine` in [`sources/audio_engine/audio_engine.cpp` line 23](sources/audio_engine/audio_engine.cpp#L23).
  - Call of the `prepare_audio_processor` function in [`sources/audio_engine/audio_engine.cpp` line 38](sources/audio_engine/audio_engine.cpp#L38).
  - Call of the `ap_process` function in [`sources/audio_engine/audio_engine.cpp` line 54](sources/audio_engine/audio_engine.cpp#L54).

For the moment, `AudioProcessor` does not have any parameters, and the controllers from UI are linked to two internal variables from `AudioEngine`: `parameter_a_` and `parameter_b_`.   

In order to link these paramaters to your `AudioProcessor`, you have to modify the following code:
  - Setters and getters for the parameters in [`sources/audio_engine/audio_engine.cpp` lines 75](sources/audio_engine/audio_engine.cpp#L75), [80](sources/audio_engine/audio_engine.cpp#L80), [85](sources/audio_engine/audio_engine.cpp#L85) and [88](sources/audio_engine/audio_engine.cpp#L88) (you can remove `parameter_a_` and `parameter_b_` if they are not needed anymore).
  - The controllers have a range of `[0,1]` with a mid value of `0.5`. You can either
    - change these values in [`main_screen.cpp` lines 44-45](sources/main_screen.cpp#L44) and [63-64](sources/main_screen.cpp#L63),
    - or transform this `[0,1]` range into usefull values within your `AudioProcessor` class (recommended).

---

## ⚙️  How to build and run

- Make sure [JUCE](https://juce.com) is installed on your computer with the `Projucer` app available and the global paths properly set. The project has been tested with JUCE 7.0.5, it is recommended to use the exact same version.
- Depending on the platform you are working on and the platform you want to build the app for, be sure you have all the tools needed installed on your system. See the main README of the project for more information.
- Open the [`AudioProcessor.jucer`](AudioProcessor.jucer) with `Projucer`.
- Click `File -> Save Project` to export the project.
- You can now build the app with the build system corresponding to your exporter (Xcode, make, Visual Studio or Code::Block), and edit the sources in your favourite IDE by either:
  - launching the IDE from JUCE directly with the dedicated button at the top,
  - opening the project in the [`Builds`](Builds) directory.
