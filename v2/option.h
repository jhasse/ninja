#pragma once

#include <optional>
#include <span>
#include <sstream>
#include <string>

struct Option {
  std::optional<char> shortFlag;
  std::string longFlag;
  std::string parameter;
  std::string help;
};

inline std::string printHelp(std::span<Option> options) {
  int maxLengthLeftSide = 0;
  for (const auto& option : options) {
    if (option.help.empty()) {
      continue;
    }
    int length = 2;  // padding
    if (option.shortFlag) {
      length += 2;  // for '-' and the character
      if (!option.longFlag.empty()) {
        length += 2;  // for ", "
      }
    }
    if (!option.longFlag.empty()) {
      length += 2 + option.longFlag.size();  // for "--" and the flag
    }
    if (!option.parameter.empty()) {
      length += 1 + option.parameter.size();  // for " " and the parameter
    }
    if (length > maxLengthLeftSide) {
      maxLengthLeftSide = length;
    }
  }
  std::ostringstream helpStream;
  for (const auto& option : options) {
    if (option.help.empty()) {
      continue;
    }
    std::ostringstream leftSideStream;
    if (option.shortFlag) {
      leftSideStream << "-" << *option.shortFlag;
      if (!option.longFlag.empty()) {
        leftSideStream << ", ";
      }
    }
    if (!option.longFlag.empty()) {
      leftSideStream << "--" << option.longFlag;
    }
    if (!option.parameter.empty()) {
      leftSideStream << " " << option.parameter;
    }
    helpStream << "  " << leftSideStream.str()
               << std::string(maxLengthLeftSide - leftSideStream.str().size(),
                              ' ')
               << option.help << '\n';
  }
  return helpStream.str();
}
