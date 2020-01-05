# Audio-Loop


This demo app is part of the student project [Real time audio processing on mobile platforms](https://gitlab.com/AudioScientist/real-time-audio-processing-on-mobile-platforms).

The app captures the audio input, process it with the class `AudioProcessor`, and send the results to the audio output.

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

## AudioProcessor integration

- An instance of `AudioProcessor` has been inserted inside the main audio render loop.
- Source files are located in [`AudioLoop/Classes/audio_processor.*`](AudioLoop/Classes).  
- If you need to change the call to `AudioProcessor` constructor, you can do so in [`AudioLoop/Classes/AUAudioProcessor.mm` line 79](AudioLoop/Classes/AUAudioProcessor.mm#L79).
- The two sliders are limited to the range `[0,1]` and values are sent continuously to the `AudioProcessor` with param IDs `0` and `1`.

---

## How to build and run

- You can run the app either on simulator or on a device.
- Check that your Apple developer account is registered in Xcode settings. If you don't have one, your can create one [here](https://developer.apple.com/account/).
- In the project properties, modify the Bundle ID with a new unique one (you can choose any string of alphanumeric characters).
- Build and run on a physical device or simulator.
- If needed, authorize the application on the device in Settings > General > Profiles or Profiles & Device Management.
