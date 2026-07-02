#pragma once

#include "DeviceManager.hpp"
#include <expected>
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

class DeviceConnection {
public:
  DeviceConnection(const InputDevice &device);
  ~DeviceConnection();

  std::expected<input_event, std::string> read();

private:
  const InputDevice& device_;
  libevdev *dev_;
  int fd_, rc_;
};
