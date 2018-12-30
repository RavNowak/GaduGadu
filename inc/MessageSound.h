#pragma once
#include <SFML\Audio.hpp>

class MessageSound : public sf::Sound
{
private:
    sf::SoundBuffer soundBuffer;
    bool messageSoundStatus{ true };
public:
    MessageSound();
    void changeMessageSoundStatus() noexcept;
    bool getMessageSoundStatus()const noexcept;
};