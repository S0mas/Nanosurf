#pragma once

class log_subscriber_interface
{
public:
  virtual ~log_subscriber_interface() = default;
  virtual auto beginPush() -> void = 0;
  virtual auto endPush() -> void = 0;
};
