/*
  ___ _  ___  _   _
 |_ _/ |( _ )| \ | |
  | || |/ _ \|  \| |
  | || | (_) | |\  |
 |___|_|\___/|_| \_|

Internationalization class
Author: Paolo Bosetti, Aug. 2024
*/

#ifndef I18N_HPP
#define I18N_HPP
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

class I18n {
public:
  I18n() { _locale = "en"; }

  I18n(string path, string locale = "en") {
    set_translations(path);
    _locale = locale;
  }

  void set_locale(string locale) { _locale = locale; }
  
  void set_translations(json translations) { _translations = translations; }
  
  void set_translations(char const *path) { set_translations(string(path)); }
  
  void set_translations(string path) {
    try {
      ifstream ifs(path);
      _translations = json::parse(ifs);
    } catch (exception e) {
      cerr << "Error parsing translation file at: " << path << ", " << e.what()
           << endl;
    }
  }
  
  string t(string key) {
    if (_translations.empty()) {
      return key;
    }
    if (_translations.contains(key)) {
      if (_translations[key].contains(_locale)) {
        return _translations[key][_locale].get<string>();
      }
    }
    return key;
  }

private:
  string _locale;
  json _translations;
};

#endif // I18N_HPP