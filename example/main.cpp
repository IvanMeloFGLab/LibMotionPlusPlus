#include <print>
#include <chrono>
#include "libmotionplusplus/WiiMote.hpp"
#include "libmotionplusplus/ControllerManager.hpp"

using std::println;

using namespace std::chrono_literals;
using namespace motionplusplus;

int main() {
  ControllerManager cm;

  while (true) {
    auto up = cm.update(10ms);

    if (cm.isNewContrllers()) {
      println("New device connected.");
      for (auto &ctrl_id : cm.getActiveControllers()) {
        println("{}", *(cm.getController(ctrl_id)));
      }
    }

    if (!up) {
      if (up.error().value() == EAGAIN) continue;
      if (up.error().value() == POLLHUP) {
        println("Device disconnected.");
        for (auto &ctrl_id : cm.getActiveControllers()) {
          println("{}", *(cm.getController(ctrl_id)));
        }
        continue;
      }
      println("Update error: {}", up.error().message());
      return 1;
    }

    //auto wm = dynamic_cast<WiiMote*>(cm.getController(1));
    //auto wm2 = dynamic_cast<WiiMote*>(cm.getController(2));

    /*if (wm && wm2) {
      println("A button {} 1: {}, {} 2: {}", wm->getType(), wm->getButtons().a, wm2->getType(), wm2->getButtons().a);
    }*/

  }

  return 0;
}
