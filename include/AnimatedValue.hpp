#pragma once

#include <chrono>
#include <functional>

#include "Easings.hpp"
#include "debug.hpp"

using namespace std::literals;

template <typename T>
class AnimatedValue {
public:
    AnimatedValue() {}
    AnimatedValue(T value) : startValue(value), endValue(value) {}
    AnimatedValue(T startValue, T endValue, std::chrono::milliseconds duration)
        : startValue(startValue),
          endValue(endValue),
          duration(duration),
          done(false) {
        DEBUG("[DEBUG] BEGINNING ANIMATION " + S(startValue) + " -> " +
              S(endValue) + " in " + S(duration.count()) + "ms");
    }

    void update(std::chrono::milliseconds delta);
    T get();

private:
    T startValue;
    T endValue;
    std::chrono::milliseconds elapsed = 0s;
    std::chrono::milliseconds duration;
    bool done = true;
    std::function<double(double)> timingFunction = easings::easeOutCubic;
};

template <typename T>
void AnimatedValue<T>::update(std::chrono::milliseconds deltaTime) {
    if (done) return;
    if (elapsed >= duration) {
        elapsed = duration;
        done = true;
        return;
    }

    elapsed += deltaTime;
}

template <typename T>
T AnimatedValue<T>::get() {
    if (done) {
        return endValue;
    }

    float elapsedPercent = (float)elapsed.count() / duration.count();
    return startValue +
           (endValue - startValue) * timingFunction(elapsedPercent);
}
