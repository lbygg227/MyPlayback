#pragma once

#include <thread>
#include <memory>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <mutex>
#include <functional>

enum class PLAYBACK_STATUS {
  RUNNING,
  PAUSE,
  IDLE
};

class Playback final {
public:
  void set_callback(std::function<void()> callback) {
    callback_ = std::move(callback);
  }

  void start();

  void pause();

  void resume();

  void stop();

  PLAYBACK_STATUS get_status() const {
    return status_;
  }
private:
  std::function<void()> callback_;
  std::unique_ptr<std::jthread> playback_thread_;
  PLAYBACK_STATUS status_{ PLAYBACK_STATUS::IDLE };
  std::condition_variable cv_;
  std::mutex mtx_;
};