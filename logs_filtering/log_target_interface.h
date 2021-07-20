#pragma once

class log_target_interface {
public:
  virtual ~log_target_interface() = default;
  virtual auto push_log(int const severity_level, const char* message) -> void = 0;
};
