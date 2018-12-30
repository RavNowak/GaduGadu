#pragma once
#include <SFML\Network.hpp>
#include <string>

class MyClock : public sf::Clock
{
private:
    int hour { 0 };
    int minute { 0 };
    int second { 0 };
    std::string getCorrectClockFormat() const  noexcept;
public:
    std::string getTimeElapsedSinceLoggingIn() noexcept;
};