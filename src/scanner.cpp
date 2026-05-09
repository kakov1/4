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
    auto options = std::filesystem::directory_options::skip_permission_denied;

    for (auto &&entry :
         fs::recursive_directory_iterator(cfg.getRootPath(), options)) {
      if (entry.is_regular_file()) {
        std::string ext = entry.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

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
  currentData = std::move(newData);
}

std::string Scanner::getSerializedData() {
  std::lock_guard<std::mutex> lock(dataMutex);

  try {
    return currentData.dump(4, ' ', false,
                            nlohmann::json::error_handler_t::replace);
  } catch (std::exception &e) {
    return "{}";
  }
}
} // namespace app