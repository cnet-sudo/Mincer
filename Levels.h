#pragma once
#include"AssetManager.h"
#include<array>

class Levels
{
	sf::RenderWindow& m_window;
	// массив картин уровней
	std::array<sf::Sprite, 7> m_background;
	// массив озвучки предистории игры
	std::array<sf::Sound,7> m_sound;
	// задержка кадра предистории игры
	std::array<int, 7> m_time{11,8,5,9,5,12,7};
	// ссылка на картинку текущего уровня
	sf::Sprite* m_bkgr=nullptr;
	// титульная картинка игры
	sf::Sprite m_start;
	// спрайт содержащий кадры предистории 
	sf::Sprite m_splash_screen;
	// картинка с клавишами управления
	sf::Sprite m_help;
	// номер кадра
	int m_frame = 0;
	// время смены кадра
	sf::Time m_time_frame;
	// проигрывание анимации предистории
	bool m_play = true;
	// масштаб отображения графики
	float m_scale_x;
	float m_scale_y;
	// окончание проигривания предистории  
	bool vstup = false;  
public:

	Levels(sf::RenderWindow& window, float scale_x, float scale_y);
	// возвращает титульный кадр текущего уровня
	sf::Sprite * getSprite(int index);
	// возвращает окончание предистории
	bool getVstup();    
	// обновление кадров анимации предистории
	void splash_SCR_update(sf::Time deltaTime);
	// отрисовка кадров анимации в графическом окне
	void splash_SCR_draw();
	// открываем уровень загружаем графику в оперативную память
	void createLevels();
	// выключаем озвучку
	void stop_sound();
	// отрисовка титульной картинки игры
	void start();
	// отображаем картинку помощи
	void help();
};

