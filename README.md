# MotionPlusPlus

> A modern C++ daemon for turning motion controllers into powerful, customizable input devices on Linux.

MotionPlusPlus is an open-source project focused on bringing advanced support for motion-based controllers such as the Nintendo Wii Remote, Wii MotionPlus, Sony PS Move, and future devices to Linux.

Unlike simple mouse emulation tools, MotionPlusPlus is designed as a modular controller framework capable of reading raw controller data and mapping it to configurable actions. The long-term goal is to provide a flexible foundation for desktop interaction, gaming, accessibility, automation, and experimentation.

## Project Goals

* Modern C++20 codebase
* Modular and extensible architecture
* Native Linux support
* Low-latency input processing
* Configurable action system
* Support for multiple controller families
* Clean separation between hardware, controller logic, and actions

## Planned Controller Support

* Nintendo Wii Remote
* Wii MotionPlus
* Wii Nunchuk
* Wii Classic Controller
* Wii Balance Board
* Sony PS Move
* DualSense (selected motion features)
* Additional HID motion controllers in the future

## Planned Features

### Input

* Button mapping
* Mouse emulation
* Keyboard emulation
* Scroll emulation
* Gamepad emulation
* Gesture recognition
* Motion-based actions
* Controller profiles
* Multi-controller support

### Controller Features

* MotionPlus support
* Accelerometer support
* IR camera support
* Nunchuk support
* Extension detection
* LEDs
* Rumble
* Battery monitoring
* Speaker support (where available)

### System Integration

* User-defined actions
* Launch applications
* Media controls
* Volume and brightness control
* Desktop shortcuts
* Sleep, suspend, and power actions
* Profile switching

Example ideas:

* Press the Wii Power button to suspend the computer.
* Hold B to enable mouse mode.
* Shake the controller to trigger a shortcut.
* Point at the sensor bar to control the cursor.
* Use controller orientation to scroll or switch desktops.

## Architecture

The project is intentionally built in layers.

```text
Linux Input Devices (/dev/input/event*)

        │

        ▼

DeviceManager
    Device discovery
    Metadata collection

        │

        ▼

InputDevice
    Metadata describing one Linux input device

        │

        ▼

DeviceConnection
    Reads events through libevdev
    Manages device lifetime (RAII)

        │

        ▼

Controller
    Groups multiple input devices into one physical controller

        │

        ▼

Action Engine
    Maps controller input to configurable actions
```

The application model intentionally differs from the Linux kernel model.

Linux exposes multiple `/dev/input/event*` devices for a single physical controller (for example, a Wii Remote exposes separate devices for buttons, MotionPlus, accelerometer, and IR). MotionPlusPlus groups these endpoints into a single logical controller before processing input.

## Current Status

Current milestone:

* CMake build system
* C++20 project structure
* Device discovery
* Metadata extraction using libevdev

The project is under active development and is **not yet ready for daily use**.

## Dependencies

Current dependencies:

* C++20 compatible compiler
* CMake
* libevdev

Future optional dependencies may include:

* libudev
* spdlog
* fmt
* toml++

## Building

```bash
git clone https://github.com/IvanMeloFGLab/MotionPlusPlus.git

cd MotionPlusPlus

mkdir build

cd build

cmake ..

cmake --build .
```

Run:

```bash
sudo ./MotionPlusPlus
```

(Currently elevated permissions are required to access input devices. Future releases will support running as a normal user through appropriate udev rules.)

## Roadmap

### Phase 1 — Core Input Layer

* Device discovery
* Metadata extraction
* Event reading
* Controller grouping

### Phase 2 — Controller Support

* Wii Remote
* MotionPlus
* IR camera
* Nunchuk
* Extension support

### Phase 3 — Action Engine

* Mouse
* Keyboard
* Profiles
* Configurable actions
* Configuration files

### Phase 4 — Advanced Features

* Gestures
* Speaker support
* VR experimentation
* Plugin system
* Additional controllers

## Robotics

MotionPlusPlus focuses on desktop interaction and controller functionality.

A separate companion project, **ros2_motionplusplus**, will provide robotics-oriented functionality such as pose estimation, visualization, sensor fusion, and ROS 2 integration while sharing concepts and potentially parts of the core codebase.
