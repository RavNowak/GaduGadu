#include "MyClock.h"

std::string MyClock::getCorrectClockFormat() const noexcept
{
    std::string time { "" };
    if (hour <= 9) time += "0" + std::to_string(hour);
    else time += std::to_string(hour);
    if (minute <= 9) time += ":0" + std::to_string(minute);
    else time += ":" + std::to_string(minute);
    if (second <= 9) time += ":0" + std::to_string(second);
    else time += ":" + std::to_string(second);
    return time;
}

std::string MyClock::getTimeElapsedSinceLoggingIn() noexcept
{
    int time = static_cast<int>(getElapsedTime().asSeconds());
    second = time % 60;
    minute = time / 60;
    if (minute >= 60)
    {
        minute %= 60;
        hour = minute / 60;
    }
    return getCorrectClockFormat();
}


