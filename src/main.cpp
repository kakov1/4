#include "config.hpp"
#include "scanner.hpp"
#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>

namespace po = boost::program_options;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  std::string path_str;
  uint64_t interval;

  po::options_description desc("Options");
  desc.add_options()("help", "help message")(
      "path",
      po::value<std::string>(&path_str)->default_value(
          fs::current_path().string()),
      "path to scan")("interval",
                      po::value<uint64_t>(&interval)->default_value(10),
                      "interval between scans(seconds)");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 0;
  }

  fs::path rootPath(path_str);

  if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) {
    std::cerr << "Error: Invalid path." << std::endl;
    return 1;
  }

  Config config(rootPath, interval);

  return 0;
}