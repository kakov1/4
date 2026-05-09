#pragma once

#include <cstdint>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace app {

namespace fs = std::filesystem;

using File = std::string;
using FileList = std::vector<File>;
using MediaFiles = std::unordered_map<std::string, FileList>;
using Seconds = uint64_t;
using Path = fs::path;
using Json = nlohmann::json;

} // namespace app