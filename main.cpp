#include "playback.h"
#include <iostream>
void func() {
  for (auto i = 0; i < 100000; i++) {
    std::cout << i << std::endl;
  }
}

int main() {

  Playback playback;
  playback.set_callback([]() {
    func();
    });

  playback.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(1678));

  playback.pause();

  std::this_thread::sleep_for(std::chrono::milliseconds(1678));

  playback.resume();

  std::this_thread::sleep_for(std::chrono::milliseconds(1678));

  playback.stop();

  std::this_thread::sleep_for(std::chrono::milliseconds(1678));

  playback.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(1678));

  playback.stop();

  return 0;
}