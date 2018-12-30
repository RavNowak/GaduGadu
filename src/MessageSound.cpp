#include "MessageSound.h"

MessageSound::MessageSound()
{
    soundBuffer.loadFromFile("sounds/message.wav");
    setBuffer(soundBuffer);
}

void MessageSound::changeMessageSoundStatus() noexcept
{
    messageSoundStatus = !messageSoundStatus;
}

bool MessageSound::getMessageSoundStatus() const noexcept
{
    return messageSoundStatus;
}
