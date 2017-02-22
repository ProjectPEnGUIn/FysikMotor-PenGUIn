#include "Sound_system.h"

std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> Sound_System::s_SoundBufferCache;