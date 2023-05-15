#pragma once
#include"AssetManager.h"
#include<array>

class Levels
{
	sf::RenderWindow& window;

	std::array<sf::Sprite, 7> m_background;

	// ������ �������� ��������
	std::array<sf::Sound,7> m_sound;

	std::array<int, 7> m_time{11,8,5,9,5,12,12};

	sf::Sprite* m_bkgr=nullptr;
	sf::Sprite m_start;
	sf::Sprite m_splash_screen;
	sf::Sprite m_help;
	// ����� �����
	int m_frame = 0;
	// ����� ����� �����
	sf::Time m_time_frame;
	bool m_play = true;

public:

	Levels(sf::RenderWindow& window);

	sf::Sprite * getSprite(int index);

	void splash_SCR_update(sf::Time deltaTime);

	void splash_SCR_draw();

	void createLevels();

	void stop_sound();

	void start();

	void help();
};

