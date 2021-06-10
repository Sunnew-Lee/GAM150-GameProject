/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: GAM150
Author:
-----------------------------------------------------------------*/
#pragma once

#include <SFML/Audio.hpp> // sounds and music stuffs
#include <vector>   // std::vector

struct Sound
{
public:
    void Set_up_sound();
    void Set_music(const std::string& file_path, bool isLoop);
    void Load_sound(const std::string& file_path);
    void Set_sound(void);
    void Play_sound(const int soundType);
    bool Is_sound_playing(const int soundType);
    void Stop_sound();

    std::vector<sf::SoundBuffer> SoundBuffers{};
    std::vector<sf::Sound>       Sounds{};
    sf::Music                    Music;
};

