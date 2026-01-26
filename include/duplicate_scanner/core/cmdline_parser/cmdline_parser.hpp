#ifndef DUPSCANNER_CMDLINE_PARSER_HPP
#define DUPSCANNER_CMDLINE_PARSER_HPP

#include <boost/program_options.hpp>
#include <duplicate_scanner/core/scanner/scanner.hpp>
#include <duplicate_scanner/utility/config/config.hpp>
#include <span>
#include <string_view>
#include <type_traits>

namespace duplicate_scanner::core {

class [[nodiscard]] CmdLineParser {
  static constexpr std::uintmax_t kDefaultFileSize{1};
  static constexpr unsigned kDefaultScanDepth{0};
  static constexpr unsigned kDefaultBlockSize{1024};

  static constexpr std::string_view kCmdArgHelp{"help"};
  static constexpr std::string_view kCmdArgBlockSize{"block-size"};
  static constexpr std::string_view kCmdArgFileSize{"file-size"};
  static constexpr std::string_view kCmdArgScanDepth{"scan-depth"};
  static constexpr std::string_view kCmdArgScanDir{"scan-dir"};
  static constexpr std::string_view kCmdArgExcludeDir{"exclude-dir"};
  static constexpr std::string_view kCmdArgHashFunc{"hash-func"};
  static constexpr std::string_view kCmdArgFilenameMask{"filename-mask"};

 public:
  CmdLineParser() noexcept(std::is_nothrow_default_constructible_v<boost::program_options::variables_map>) = default;

  CmdLineParser(
    CmdLineParser const&
  ) noexcept(std::is_nothrow_copy_constructible_v<boost::program_options::variables_map>) = default;

  CmdLineParser(CmdLineParser&&) noexcept(std::is_nothrow_move_constructible_v<boost::program_options::variables_map>) =
    default;

  ~CmdLineParser() = default;

  auto operator=(
    CmdLineParser const&
  ) noexcept(std::is_nothrow_copy_assignable_v<boost::program_options::variables_map>) -> CmdLineParser& = default;

  auto operator=(CmdLineParser&&) noexcept(std::is_nothrow_move_assignable_v<boost::program_options::variables_map>)
    -> CmdLineParser& = default;

  auto parse(std::span<char const* const> args) -> void;

  [[nodiscard]] auto helpDescriptionRequested() const -> bool;

  static auto normalizePaths(std::pmr::vector<std::filesystem::path>& paths) -> void;

  [[nodiscard]] auto createConfiguration() const -> utility::Configuration;

  static auto printHelpDescription() -> void;

 private:
  [[nodiscard]] static auto descriptionInstance() -> boost::program_options::options_description const&;

  boost::program_options::variables_map variables_map_;
};

}  // namespace duplicate_scanner::core

#endif  // DUPSCANNER_CMDLINE_PARSER_HPP
