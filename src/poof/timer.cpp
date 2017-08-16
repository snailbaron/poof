#include "timer.hpp"

FrameTimer::FrameTimer(int fps)
    : _prevFrameTime(Clock::now())
    , _frameDuration(
        std::chrono::duration_cast<Clock::duration>(
            std::chrono::duration<double>(1.0 / fps)))
{ }

bool FrameTimer::frameTime()
{
    auto now = Clock::now();
    auto delta = now - _prevFrameTime;
    if (delta >= _frameDuration) {
        _prevFrameTime = now;
        _delta = delta;
        return true;
    }
    return false;
}

float FrameTimer::deltaSec() const
{
    return std::chrono::duration<float>(_delta).count();
}