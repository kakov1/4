#include "config.hpp"
#include "scanner.hpp"
#include <boost/program_options.hpp>
#include <filesystem>
#include <httplib.h>
#include <iostream>
#include <thread>

namespace po = boost::program_options;

using namespace app;

int main(int argc, char *argv[]) {
  std::string path_str;
  Seconds interval;

  po::options_description desc("Options");
  desc.add_options()("help", "help message")(
      "path",
      po::value<std::string>(&path_str)->default_value(
          fs::current_path().string()),
      "path to scan")("interval",
                      po::value<Seconds>(&interval)->default_value(10),
                      "interval between scans(seconds)");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  Path rootPath(path_str);

  if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) {
    std::cerr << "Error: Invalid path." << std::endl;
    return 1;
  }

  Config config(rootPath, interval);
  Scanner scanner(config);

  std::thread scannerThread([&scanner]() { scanner.run(); });

  httplib::Server server;

  server.Get("/media_files",
             [&scanner](const httplib::Request &, httplib::Response &res) {
               res.set_content(scanner.getSerializedData(), "application/json");
               res.set_header("Connection", "close");
             });

  std::cout << "Server started at http://localhost:1234/media_files"
            << std::endl;

  server.listen("127.0.0.1", 1234);

  if (scannerThread.joinable())
    scannerThread.join();

  return 0;
}