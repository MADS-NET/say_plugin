# say plugin for MADS

This is a Sink plugin for [MADS](https://github.com/MADS-NET/MADS). 

This is a sink agent that speaks any string received on in the `"tts"` field in the JSON input message. The plugin uses the `espeak` library to generate the speech.

*Required MADS version: 1.0.1.*


## Supported platforms

Currently, the supported platforms are:

* **Linux** 
* **MacOS**


## Dependencies

On **Linux**, the plugin requires the `espeak` library. To install it, run:

```bash
sudo apt-get install espeak libespeak-dev
```

On **MacOS**, the plugin requires the `espeak` library. To install it, run:

```bash
brew install espeak
```


## Installation

Linux and MacOS:

```bash
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$(mads -p)"
cmake --build build -j4
sudo cmake --install build
```


## Translation/I18N

The plugin supports translation of the spoken text. The translation is done using a dictionary file that maps the original text to the translated text. The dictionary file is a JSON file with the following format:

```json
{
    "original text": {
        "it": "testo tradotto",
        "fr": "texte traduit",
        "es": "texto traducido"
    }
}
```

If the translated text is not found in the dictionary, the original text is spoken.

This JSON file must be installed in the fordel `share/translate` under the MADS installation directory. 


## INI settings

The plugin supports the following settings in the INI file:

```ini
[say]
language = "europe/it" # Must be a valid espeak language code
locale = "it"          # Used for lanuage translation
dictionary = "translations.json" # Name of translation dictionary
```

All settings are optional; if omitted, the default values are used.


## Executable demo

The demo executable joins all its arguments as a single string and speaks them. 


---