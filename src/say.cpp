/*
  ____  _       _            _             _       
 / ___|(_)_ __ | | __  _ __ | |_   _  __ _(_)_ __  
 \___ \| | '_ \| |/ / | '_ \| | | | |/ _` | | '_ \ 
  ___) | | | | |   <  | |_) | | |_| | (_| | | | | |
 |____/|_|_| |_|_|\_\ | .__/|_|\__,_|\__, |_|_| |_|
                      |_|            |___/         
# A Template for SayPlugin, a Sink Plugin
# Generated by the command: plugin -t sink -d say_plugin say
# Hostname: Fram-IV.homenet.telecomitalia.it
# Current working directory: /Users/p4010/Develop/MADS_plugins
# Creation date: 2024-08-01T21:05:16.990+0200
# NOTICE: MADS Version 1.0.1
*/

// Mandatory included headers
#include <sink.hpp>
#include <nlohmann/json.hpp>
#include <pugg/Kernel.h>
// other includes as needed here
#include <espeak/speak_lib.h>
#include <thread>

// Define the name of the plugin
#ifndef PLUGIN_NAME
#define PLUGIN_NAME "say"
#endif

// Load the namespaces
using namespace std;
using json = nlohmann::json;


// Plugin class. This shall be the only part that needs to be modified,
// implementing the actual functionality
class SayPlugin : public Sink<json> {

public:

  // Typically, no need to change this
  string kind() override { return PLUGIN_NAME; }

  ~SayPlugin() {
    espeak_Terminate();
  }

  // Implement the actual functionality here
  return_type load_data(json const &input, string topic = "") override {
    if (input.contains("tts")) {
      string tts = input["tts"].get<string>();
      if (!_silent)
        cerr << "Saying: " << tts << endl;
      espeak_ERROR rc = espeak_Synth(
        tts.c_str(), 
        tts.size() + 1, 
        0, 
        POS_CHARACTER, 
        tts.size(), 
        espeakCHARS_AUTO|espeakENDPAUSE, 
        NULL,
        NULL);

    if (rc != EE_OK && !_silent) {
      cerr << "Error synthesizing" << endl;
      return return_type::error;
    }
    return return_type::success;
    }
    return return_type::retry;
  }

  void set_params(void const *params) override { 
    Sink::set_params(params);
    _params["language"] = "europe/it";
    _params["silent"] = true;
    _params.merge_patch(*(json *)params);

    _silent = _params["silent"].get<bool>();

    int rate = espeak_Initialize(AUDIO_OUTPUT_SYNCH_PLAYBACK, 0, NULL, 0);
    if (rate < 0 && !_silent) {
      cerr << "Error initializing espeak" << endl;
    } else {
      if (!_silent)
        cerr << "Initialized espeak, rate: " << rate << " Hz" << endl;
    }
    if (espeak_SetVoiceByName(_params["language"].get<string>().c_str()) != EE_OK) {
      if (!_silent)
        cerr << "Error setting voice" << endl;
    }
    espeak_VOICE *voice = espeak_GetCurrentVoice();
    if (!_silent)
      cerr << "Voice: " << voice->name << ", " << voice->identifier << endl;
  }

  // Implement this method if you want to provide additional information
  map<string, string> info() override { 
    return {
      {"Language:", _params["language"].get<string>()}
    }; 
  };

private:
  // Define the fields that are used to store internal resources
  bool _silent;
};



/*
  ____  _             _             _      _                
 |  _ \| |_   _  __ _(_)_ __     __| |_ __(_)_   _____ _ __ 
 | |_) | | | | |/ _` | | '_ \   / _` | '__| \ \ / / _ \ '__|
 |  __/| | |_| | (_| | | | | | | (_| | |  | |\ V /  __/ |   
 |_|   |_|\__,_|\__, |_|_| |_|  \__,_|_|  |_| \_/ \___|_|   
                |___/                                      
Enable the class as plugin 
*/
INSTALL_SINK_DRIVER(SayPlugin, json)


/*
                  _
  _ __ ___   __ _(_)_ __
 | '_ ` _ \ / _` | | '_ \
 | | | | | | (_| | | | | |
 |_| |_| |_|\__,_|_|_| |_|

For testing purposes, when directly executing the plugin
*/
int main(int argc, char const *argv[]) {
  SayPlugin plugin;
  json input, params;
  string text = "Ciao, mondo!";

  if (argc > 1) {
    text.clear();
    for (int i = 1; i < argc; i++) {
      text += " ";
      text += argv[i];
    }
  }
  
  // Set example values to params
  params["language"] = "europe/it";

  // Set the parameters
  plugin.set_params(&params);

  input["tts"] = text;
  // Process data
  plugin.load_data(input);

  return 0;
}