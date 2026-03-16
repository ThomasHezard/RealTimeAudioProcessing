# Offline Audio Processor

This project is the step 1 of the main project [Real-time audio processing](https://github.com/ThomasHezard/RealTimeAudioProcessing). Please refer to the README of main project for more information.

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

This directory contains a self-sufficient Python script `audio_processor.py`, and a notebook version of the same script `audio_processor.ipynb`. The present version of the code does nothing but copying audio data from an input audio file into an output audio file.

Your goal is to implement modify this script to replace the data copy with the audio processing algorithm you chose. All you have to do is to __replace [line 42](audio_processor.py#L35) with your code__.

--- 

## ⚙️  How to run

### Run on Google Colab (recommended)

The notebook can be run on Google Colab: [Run on Google Colab](https://colab.research.google.com/github/ThomasHezard/RealTimeAudioProcessing/blob/google-colab/S1-Python_AudioProcessor/audio_processor.ipynb).  

### Run on Github Codespace

This project can be run in a pre-configured environment on Github Codespace:
1. [Fork this repository](https://github.com/ThomasHezard/RealTimeAudioProcessing/fork) to your own Github account,
2. On your fork's page, click the green **Code** button → **Codespaces** tab → **Create codespace**.

Once in the Codespace, open a terminal and follow the instructions below to run the Python script.

### Run the script

This project has been written for `Python >= 3.7`, necessary packages are detailed in `requirements.txt`.
After having installed and setup `Python`, you can install all necessary packages and run the script with `uv`:
```bash
uv run audio_processor.py
```
or install the packages manually with `pip`:
```bash
pip install -r requirements.txt
```
or `conda`:
```bash
conda install --file requirements.txt
```

Once your environment is ready, you can execute the Python script with the command
```bash
python audio_processor.py
```

Alternatively, you can open this directory in your favourite Python IDE and work from there.
