# say plugin for MADS

This is a Sink plugin for [MADS](https://github.com/MADS-NET/MADS). 

This is a sink agent that speaks any string received on in the `"tts"` field in the JSON input message. The plugin uses the `espeak` library to generate the speech.

*Required MADS version: 1.0.1.*


## Supported platforms

Currently, the supported platforms are:

* **Linux** 
* **MacOS**


## Installation

Linux and MacOS:

```bash
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$(mads -p)"
cmake --build build -j4
sudo cmake --install build
```

Windows:

```powershell
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$(mads -p)"
cmake --build build --config Release
cmake --install build --config Release
```


## INI settings

The plugin supports the following settings in the INI file:

```ini
[say]
language = "europe/it" # Must be a valid espeak language code
```

All settings are optional; if omitted, the default values are used.


## Executable demo

The demo executable joins all its arguments as a single string and speaks them. 


---