#pragma once

#include "common.hpp"
#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace app {
class Config final {
private:
  Path rootPath;
  Seconds interval;
  MediaFiles extensions;

private:
  void loadExtensions(const File &filename);
  void setDefaultExtensions();

public:
  Config(Path path, Seconds interval, File configFile = "config.json");

  Path getRootPath() const;

  Seconds getInterval() const;

  const MediaFiles &getExtensions() const;
};
} // namespace app