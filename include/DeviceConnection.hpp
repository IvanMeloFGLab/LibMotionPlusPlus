#pragma once

#include "DeviceManager.hpp"
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using std::runtime_error;

class DeviceConnection {
public:
  DeviceConnection(const InputDevice &device);
  ~DeviceConnection();

  input_event read();

private:
  const InputDevice& device_;
  libevdev *dev_;
  int fd_, rc_;
};
