#pragma once
#include <string>
#include "asd.h"
class Platform {
public:
  ~Platform() = default;

  template<typename Func, typename... Args>
  void registerPlugin(const std::string& func_name, Func&& f, Args&&... args) {
    observable_.on(func_name, std::forward<Func>(f), std::forward<Args>(args)...);
  }

  void removePlugin(const std::string& func_name) {
    observable_.erase(func_name);
  }

  void notifyAllPlugin(msg&& message) {
    observable_.emit(message);
  }


private:
  my_playback::util::observable_bindable<msg> observable_;
};
