//
// Created by lby on 25-5-19.
//

#ifndef ASD_H
#define ASD_H
#include <functional>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

struct msg {
};

struct msgA : public msg {
  int a;
};

struct msgB : public msg {
  int b;
};

namespace my_playback::util {
  /**
   * @brief an observable object, which allows a lambda or a function to be bound as the observer.
   * @tparam S subject or event will be emitted to all bound observers.
   *
   */
  template<typename S>
  class observable_bindable final {
  public:
    ~observable_bindable() { clear(); }
    using subject_t = S;
    using FN = std::function<void(subject_t const &)>;

    template<typename _Callable, typename... _Args>
    observable_bindable &on(_Callable &&f, _Args &&... args) {
      return add_callback(f, args...);
    }

    /**
     * @brief fire an event along the observers chain.
     * @param event_or_subject
     */
    void emit(const subject_t &event_or_subject) {
      std::shared_lock lock{shared_mutex_};
      for (auto &fn: callbacks_)
        // Todo: add fn to thread pool and asynchronously call it.
        fn(event_or_subject);
    }

    void erase(const std::string& func_name) {
      std::unique_lock lock{shared_mutex_};
      callbacks_.erase(func_name);
    }

  private:
    template<typename Func, typename... _Args>
     observable_bindable &add_callback(const std::string& func_name, Func &&f, _Args &&... args) {
      FN fn = std::bind(std::forward<Func>(f), std::forward<_Args>(args)...);
      {
        std::unique_lock lock{shared_mutex_};
        callbacks_.emplace(func_name, fn);
      }
      return (*this);
    }

    void clear() {
    }

  private:
    std::shared_mutex shared_mutex_{};
    std::unordered_map<std::string, FN> callbacks_{};
  };
}
#endif //ASD_H
