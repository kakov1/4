#pragma once

#include "config.hpp"
#include <filesystem>
#include <mutex>
#include <string>
#include <vector>

namespace app {
  
class Scanner final {
private:
  const Config &cfg;
  Json currentData;
  std::mutex dataMutex;

  void scan();

public:
  explicit Scanner(const Config &config);

  void run();

  std::string getSerializedData();
};
} // namespace app