#include <spdlog/spdlog.h>

#include <duplicate_scanner/duplicate_scanner.hpp>

auto main(int argc, char* argv[]) -> int {
  spdlog::set_pattern("[DuplicateScanner][%^%L%$][%H:%M:%S %z] %v");
  try {
    duplicate_scanner::core::CmdLineParser parser{};
    parser.parse({argv, static_cast<std::span<char const* const>::size_type>(argc)});
    if (parser.helpDescriptionRequested()) {
      duplicate_scanner::core::CmdLineParser::printHelpDescription();
      return 0;
    }
    duplicate_scanner::core::Scanner scanner{parser.createConfiguration()};
    scanner.run();
  } catch (std::exception const& error) {
    spdlog::error("Exception: {}", error.what());
  } catch (...) {
    spdlog::error("Unknown exception");
  }

  return 0;
}
