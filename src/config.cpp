#include "config.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

Config::Config(std::filesystem::path path, uint64_t interval)
    : rootPath(std::move(path)), interval(interval) {
  loadExtensionsFromJson("config.json");
}

void Config::loadExtensionsFromJson(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Could not open config file: " << filename << std::endl;

    extensions = {{"audio", {".mp3", ".wav"}},
                  {"video", {".mp4", ".mkv"}},
                  {"images", {".jpg", ".png"}}};
    return;
  }

  try {
    nlohmann::json j;
    file >> j;

    if (j.contains("extensions")) {
      extensions = j.at("extensions")
                       .get<std::map<std::string, std::vector<std::string>>>();
    }
  } catch (const std::exception &e) {
    std::cerr << "Error parsing config.json: " << e.what() << std::endl;
  }
}
