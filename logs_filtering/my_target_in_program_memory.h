#pragma once
#include <memory>
#include <boost/circular_buffer.hpp>
#include "log_item.h"
#include "log_target_interface_with_subscribers.h"

class my_target_in_program_memory final : public log_target_interface_with_subscribers
{
  std::shared_ptr<boost::circular_buffer<log_item>> buffer_{std::make_shared<boost::circular_buffer<log_item>>(20)};
  auto push_log_impl(int const severity_level, const char* message) -> void override
  {
    buffer_->push_back(log_item{severity_level, message});
  }
public:
  auto buffer() const -> std::shared_ptr<boost::circular_buffer<log_item>>
  {
    return buffer_;
  }
};
