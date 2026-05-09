#include "config.hpp"
#include <fstream>
#include <iostream>

namespace app {
Config::Config(Path path, Seconds interval, File configFile)
    : rootPath(std::move(path)), interval(interval) {
  loadExtensions(configFile);
}

void Config::loadExtensions(const File &configFile) {
  std::ifstream file(configFile);

  if (file.is_open()) {
    try {
      Json j;
      file >> j;

      for (auto &&[category, exts] : j.items()) {
        if (!exts.is_array()) {
          std::cerr << "Category " << category << " isn't category. Skipping"
                    << std::endl;
          continue;
        }

        extensions[category] = exts.get<FileList>();
      }
    } catch (std::exception &err) {

      setDefaultExtensions();
    }
  } else {
    setDefaultExtensions();
  }
}

void Config::setDefaultExtensions() {
  extensions["audio"] = {".mp3", ".wav", ".flac"};
  extensions["video"] = {".mp4", ".mkv", ".avi"};
  extensions["images"] = {".jpg", ".png", ".gif"};
}

Path Config::getRootPath() const { return rootPath; }

Seconds Config::getInterval() const { return interval; }

const MediaFiles &Config::getExtensions() const { return extensions; }
} // namespace app