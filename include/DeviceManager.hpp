#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::filesystem::directory_iterator;
using std::filesystem::filesystem_error;
using std::vector;

struct InputDevice {
  std::filesystem::path path;
  string name;
  int vendor;
  int product;
  int bus;
  string phys;
  string uniq;

  InputDevice(std::filesystem::path path) : path(path), name(""), vendor(0), product(0), bus(0), phys(""), uniq("") {}
};

class DeviceManager {
public:
  DeviceManager();
  ~DeviceManager();

  vector<InputDevice> scan();
  bool populateMetadata(vector<InputDevice> &input_devices);
};
