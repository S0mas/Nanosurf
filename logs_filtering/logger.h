#pragma once
#include "log_item.h"
#include "log_target_interface.h"

#include <vector>

class logger final {
  std::vector<log_target_interface*> targets_;
public:
  auto log(int const severity_level, const char* message) -> void
  {
    for(auto const& target : targets_)
    {
      target->push_log(severity_level, message);
    }
  }
  auto addTarget(log_target_interface* target) -> void
  {
    targets_.push_back(target);
  }
};
