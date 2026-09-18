# LibMotionPlusPlus

> A modern C++ library for turning motion controllers into customizable input devices on Linux.

LibMotionPlusPlus is an open-source C++ library focused on bringing advanced support for motion-based controllers such as the Nintendo Wii Remote, Wii MotionPlus, Sony PS Move, and future devices to Linux.

It handles device discovery, hotplug/disconnect handling, and decoding raw controller state — buttons, motion, extensions — reliably and without needing root access. It intentionally does not map input to actions or emulate devices; that's left to the projects built on top of it.

It is part of a small ecosystem:

- **`LibMotionPlusPlus`** *(this repository)* — the core library. Discovers controllers, manages their lifecycle, and exposes raw decoded input. No mapping, no virtual devices, no configuration.
- **[`MotionPlusPlus`](https://github.com/IvanMeloFGLab/MotionPlusPlus)**  the desktop daemon built on top of this library. Maps controller input to actions and creates virtual input devices via `uinput`, driven by a per-controller TOML config. **Released — v1.0.0.**
- **`ros2_motionplusplus`** *(planned)* — a ROS 2 package for robotics use cases: motion-controller data collection, sensor fusion/pose estimation, and RViz visualization support.

A small demo executable showing basic usage of the library is included under [`example/`](example/).
But the biggest example is the MotionPlusPlus project.

## Status

Stable and in active real-world use — this library is what [`MotionPlusPlus`](https://github.com/IvanMeloFGLab/MotionPlusPlus) v1.0.0 is built on, and has been exercised extensively under real hardware: multiple simultaneous controllers, hotplug races, partial extension connect/disconnect, and permission edge cases.

Currently supports:

- Device discovery with runtime hotplug/disconnect handling, robust to transient per-device scan failures (a single unreadable or misclassified device no longer aborts the whole scan)
- Metadata extraction via libevdev
- udev-based permission setup — no root required for normal use, only for the one-time udev rule install
- Wii Remote input decoding: buttons, accelerometer, MotionPlus, IR camera, with LED and battery support
- Correct multi-controller tracking with no spurious duplicate-connection events

## Known limitations

- **Device scanning is still poll-based**, not event-driven. It's correct (no known stall/race conditions remaining) but has an inherent latency floor tied to the scan interval, and does a small amount of unnecessary work every tick regardless of whether anything changed. A migration to `udev_monitor` (kernel-pushed hotplug events instead of polling) is planned for a future v2.0.0, not yet started.
- **`WiiMote` is intentionally non-copyable and non-movable.** It owns a background LED-animation thread that captures `this` directly, so moving the object would leave that thread pointing at stale memory. Always construct/store it behind `unique_ptr`.
- **IR camera registration can be slow or delayed on first connect** (up to a minute, occasionally requiring a Motion Plus reconnect to unstick). This is a confirmed `hid-wiimote` kernel driver quirk — Motion Plus hotplug is polled internally by the driver on a fixed timer, and IR init appears tied to that same state machine. Nothing actionable on this library's side.

## Project Goals

- Native Linux support
- Low-latency input processing
- Modular and extensible architecture, packaged as a reusable library
- Hotplug handling (connect/disconnect, partial extension loss)
- Support for multiple controller families

## Planned Controller Support

- Nintendo Wii Remote
- Wii MotionPlus
- Wii Nunchuk
- Sony PS Move
- Additional HID motion controllers in the future

## Dependencies

- C++23 compatible compiler
- CMake ≥ 3.20
- libevdev
- pkg-config

## Building

```bash
git clone https://github.com/IvanMeloFGLab/LibMotionPlusPlus.git
cd LibMotionPlusPlus
mkdir build && cd build
cmake .. -DMOTIONPLUSPLUS_BUILD_EXAMPLES=ON
cmake --build .
```

To install the library system-wide (headers, compiled library, and CMake package config for `find_package`):

```bash
sudo cmake --install .
```

### Using it as a library in your own CMake project

Once installed:

```cmake
find_package(LibMotionPlusPlus REQUIRED)
target_link_libraries(your_target PRIVATE LibMotionPlusPlus::libmotionplusplus)
```

### Device permissions (no `sudo` required)

Accessing a Wii Remote's input, LED, and battery interfaces normally requires elevated privileges. LibMotionPlusPlus ships a udev rule set to avoid this.

**Option 1 — let CMake install it:**

```bash
cmake .. -DMOTIONPLUSPLUS_INSTALL_UDEV_RULES=ON
sudo cmake --install .
```

**Option 2 — install manually:**

```bash
sudo cp udev/99-libmotionplusplus.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo usermod -aG input $USER
```

Then **log out and back in** (group membership is applied at login), and physically disconnect/reconnect your controller so the new rule is applied to it. After that, running the demo:

```bash
./example/motionplusplus_demo
```

## License

This project is licensed under the **GNU General Public License v3.0**. See [`LICENSE`](LICENSE) for the full text.
