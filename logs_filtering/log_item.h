#pragma once
#include <string>

class log_item final
{
  int severity_level_;
  std::string message_;
public:
  explicit log_item(int const severity_level, std::string const& message)
  : severity_level_(severity_level)
  , message_(message)
  {
  }
  auto severity_level() const noexcept -> int
  {
    return severity_level_;
  }
  auto message() const noexcept -> std::string
  {
    return message_;
  }
};
