#pragma once
#include<SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound
{   
	// массив звуковых эффектов
    std::vector<sf::Sound> m_sound; 	
		
public:
	
	// создать массив звуковых эффектов
	void create_sound(std::vector<std::string>& sound);
	// метод включения звукового эффекта согласно установленного в параметрах индекса
	bool play(int index, bool loop);
	// метод выключения звукового эффекта согласно установленного в параметрах индекса
	void stop(int index);
	// метод выключения всех звуковых эффектов
	void all_stop();
};

