#include "scanner.hpp"
#include <chrono>
#include <iostream>
#include <thread>

namespace app {
Scanner::Scanner(const Config &config) : cfg(config) {}

void Scanner::run() {
  while (true) {
    scan();
    std::this_thread::sleep_for(std::chrono::seconds(cfg.getInterval()));
  }
}

void Scanner::scan() {
  Json newData;

  for (auto &&[category, exts] : cfg.getExtensions()) {
    newData[category] = FileList();
  }

  try {
    for (auto &&entry : fs::recursive_directory_iterator(cfg.getRootPath())) {
      if (entry.is_regular_file()) {
        std::string ext = entry.path().extension().string();

        for (auto &&[category, exts] : cfg.getExtensions()) {
          if (std::find(exts.begin(), exts.end(), ext) != exts.end()) {
            newData[category].push_back(entry.path().filename().string());
          }
        }
      }
    }
  } catch (std::exception &e) {
    std::cerr << "Scan error: " << e.what() << std::endl;
  }

  std::lock_guard<std::mutex> lock(dataMutex);
  currentData = newData;
}

std::string Scanner::getSerializedData() {
  std::lock_guard<std::mutex> lock(dataMutex);
  
  return currentData.dump(4);
}
} // namespace app