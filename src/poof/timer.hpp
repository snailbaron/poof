#pragma once

#include <chrono>

class FrameTimer {
public:
    FrameTimer(int fps);

    bool frameTime();
    float deltaSec() const;

private:
    using Clock = std::chrono::high_resolution_clock;

    Clock::time_point _prevFrameTime;
    Clock::duration _frameDuration;
    Clock::duration _delta;
};