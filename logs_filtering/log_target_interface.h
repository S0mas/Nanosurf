#pragma once
#include "log_subscriber_interface.h"

class log_target_interface
{
protected:
  virtual auto push_log_impl(int const severity_level, const char* message) -> void = 0;
public:
  virtual ~log_target_interface() = default;
  virtual auto push_log(int const severity_level, const char* message) -> void
  {
    push_log_impl(severity_level, message);
  }
};
