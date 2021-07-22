#pragma once
#include "log_subscriber_interface.h"
#include "log_target_interface.h"

#include <vector>

class log_target_interface_with_subscribers : public log_target_interface
{
  std::vector<log_subscriber_interface*> subscribers_;
public:
  auto push_log(int const severity_level, const char* message) -> void override
  {
    for(auto const& subscriber : subscribers_)
    {
      subscriber->beginPush();
    }
    push_log_impl(severity_level, message);
    for(auto const& subscriber : subscribers_)
    {
      subscriber->endPush();
    }
  }
  auto addSubscriber(log_subscriber_interface* subscriber) -> void
  {
    subscribers_.push_back(subscriber);
  }
};
