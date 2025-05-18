#include "playback.h"

void Playback::start() {
  if (playback_thread_) {
    return; // Already running
  }

  // Initialize the playback status
  status_ = PLAYBACK_STATUS::RUNNING;

  playback_thread_ = std::make_unique<std::jthread>(
    [this](std::stop_token st) {
      while (!st.stop_requested()) {
        // Simulate playback

        std::unique_lock lock{ mtx_ };
        cv_.wait(lock, [this,&st]() {
          return st.stop_requested() || status_ != PLAYBACK_STATUS::PAUSE; });

        if (st.stop_requested()) {
          break;
        }

        lock.unlock();

        callback_();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Check for pause or stop conditions
        // If pause is requested, wait until it is resumed
      }
    }
  );
}

void Playback::pause() {
  if (!playback_thread_) {
    return; // Not running
  }

  // Notify the playback thread to pause
  std::unique_lock lock{ mtx_ };
  if (status_ == PLAYBACK_STATUS::PAUSE) {
    return; // Already paused
  }
  status_ = PLAYBACK_STATUS::PAUSE;
  lock.unlock();

  cv_.notify_one();
}

void Playback::resume() {
  if (!playback_thread_) {
    return; // Not running
  }



  // Notify the playback thread to resume
  std::unique_lock lock{ mtx_ };
  if (status_ == PLAYBACK_STATUS::RUNNING) {
    return; // Already running
  }
  status_ = PLAYBACK_STATUS::RUNNING;
  lock.unlock();
  cv_.notify_one();
}

void Playback::stop() {
  if (!playback_thread_) {
    return; // Not running
  }

  if (playback_thread_->get_stop_source().stop_possible()) {
    playback_thread_->request_stop();
  }

  cv_.notify_one();

  if (playback_thread_->joinable()) {
    playback_thread_->join();
  }

  playback_thread_.reset();
  std::lock_guard lock{ mtx_ };
  status_ = PLAYBACK_STATUS::IDLE;
}