#pragma once

#include <thread>
#include <atomic>

enum class RUNING_STATUS:int32_t {
  RUNING,
  PAUSE,
  STOP
};

struct ReadData {
  void operator()(std::atomic<RUNING_STATUS> status) {
    while (status == RUNING_STATUS::RUNING) {
      // Read data from the source
      // Process the data
      // If pause is requested, wait until it is resumed
      if (status == RUNING_STATUS::PAUSE) {
        std::this_thread::yield();
      }
    }
  }

};