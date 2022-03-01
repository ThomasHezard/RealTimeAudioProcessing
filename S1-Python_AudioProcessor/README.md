# Offline Audio Processor

## Introduction

This project is the step 1 of the main project [Real-time audio processing on mobile platforms](https://gitlab.com/AudioScientist/real-time-audio-processing-on-mobile-platforms) written for Python. Please refer to the README of main project for more information.

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

This folder contains a self-sufficient Python script `audio_processor.py`. The present version of the code does nothing but copying audio data from an input audio file into an output audio file.  
Your goal is to implement modify this script to replace the data copy with the audio processing algorithm you chose. All you have to do is to __replace [line 35](audio_processor.py#L35) with your code__.

--- 

## Python environment

### Run it on replit

This project can be run in a pre-configured environment on replit: [Run on replit](https://replit.com/@ThomasHezard/RealTimeAudioProcessing-Step1Python).  
Clicking the `Run` button will run the script `audio_processor.py`, which reads the audio file `Marimba.wav`, processes its audio data, and writes the resulting audio data in the audio file `output.wav`.  

### Setup your environment

This project has been written for Python 3.7, necessary packages are detailed in `requirements.txt`.  
For example, you can install all necessary packages with `conda` : 
```
conda install --file requirements.txt
```
or `pip` : 
```
pip install -r requirements.txt
```