#pragma once
#include"AssetManager.h"
#include<array>

class Levels
{
	sf::RenderWindow& m_window;

	std::array<sf::Sprite, 7> m_background;

	// массив звуковых эффектов
	std::array<sf::Sound,7> m_sound;

	std::array<int, 7> m_time{11,8,5,9,5,12,12};

	sf::Sprite* m_bkgr=nullptr;
	sf::Sprite m_start;
	sf::Sprite m_splash_screen;
	sf::Sprite m_help;
	// номер кадра
	int m_frame = 0;
	// время смены кадра
	sf::Time m_time_frame;
	bool m_play = true;
	float m_scale_x;
	float m_scale_y;
public:

	Levels(sf::RenderWindow& window, float scale_x, float scale_y);

	sf::Sprite * getSprite(int index);

	void splash_SCR_update(sf::Time deltaTime);

	void splash_SCR_draw();

	void createLevels();

	void stop_sound();

	void start();

	void help();
};

