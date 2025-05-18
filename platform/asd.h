//
// Created by lby on 25-5-19.
//

#ifndef ASD_H
#define ASD_H
#include <functional>
#include <vector>

namespace my_playback::util {

    /**
     * @brief an observable object, which allows a lambda or a function to be bound as the observer.
     * @tparam S subject or event will be emitted to all bound observers.
     *
     */
    template<typename S>
    class observable_bindable{
    public:
        virtual ~observable_bindable() { clear(); }
        using subject_t = S;
        using FN = std::function<void(subject_t const &)>;

        template<typename _Callable, typename... _Args>
        observable_bindable &add_callback(_Callable &&f, _Args &&...args) {
            FN fn = std::bind(std::forward<_Callable>(f), std::forward<_Args>(args)...);
            _callbacks.push_back(fn);
            return (*this);
        }
        template<typename _Callable, typename... _Args>
        observable_bindable &on(_Callable &&f, _Args &&...args) {
            return add_callback(f, args...);
        }

        /**
         * @brief fire an event along the observers chain.
         * @param event_or_subject
         */
        void emit(const subject_t &event_or_subject) {
            for (auto &fn : _callbacks)
                fn(event_or_subject);
        }

    private:
        void clear() {}

    private:
        std::vector<FN> _callbacks{};
    };

}
#endif //ASD_H
