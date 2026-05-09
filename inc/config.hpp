#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

class Config final {
private:
    using fs = std::filesystem;
private:
  fs::path rootPath;
  uint64_t interval;
  std::map<std::string, std::vector<std::string>> extensions;

  void loadExtensionsFromJson(const std::string &filename);

public:
  Config(fs::path path, uint64_t interval);

  fs::path getRootPath() const { return rootPath; }
  uint64_t getInterval() const { return interval; }
  const std::map<std::string, std::vector<std::string>> &getExtensions() const {
    return extensions;
  }
};
