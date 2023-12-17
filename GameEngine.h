#pragma once
#include<iostream>
#include "AssetManager.h"
#include "Player.h"
#include "MonsterPlanet.h"
#include "GameText.h"
#include "Pickup.h"   
#include "GameSound.h" 
#include "Levels.h"		 //<<<<<<<<<<<<<<<<<<<
class GameEngine
{
public:
	// конструктор
	GameEngine();
	// метод запуска игрового цикла
	void run();
private:
	// менеджер ресурсов
	AssetManager m_manager; 
	// разрешение экрана
	sf::Vector2f m_resolution = sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width), 
		static_cast<float>(sf::VideoMode::getDesktopMode().height));
	// графическое окно 
	sf::RenderWindow m_window; 
	// игра всегда будет в одном из перечисленных состояний
	enum class State { paused, level, level_up, game_over, playing, 
		game_victory, game_load, splash_screen, transition, help };
	// cостояние игры
	State m_state;
	Levels m_levels = Levels(m_window, m_resolution.x, m_resolution.y); //<<<<<<<<<<<<<<
	// иконка
	sf::Image m_icon;
	
	// окно mainView
	sf::View m_mainView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
	// Игровая музыка
	GameSound m_musik;

	// oбщее игровое время
	sf::Time m_gameTimeTotal;
	// интервал стрельбы
	sf::Time m_lastPressed;
	// мировые координаты мышки
	sf::Vector2f m_mouseWorldPosition;
	// координаты мышки в окне
	sf::Vector2i m_mouseScreenPosition;
	// игрок
	Player m_player;

	// массив монстров
	std::deque<Monster> m_monster;
	// Придметы для подъёма
	std::vector<Pickup>  pickup; 
	// патроны 
	GameBullet m_Bullet;   
	// перезарядка оружия
	void recharge();
	
	// размер игрового уровня
	sf::IntRect m_planet;
	// фон игрового уровня
	sf::VertexArray m_background;
		
	// метод обработки событий 
	void input();
	// метод обновления переменных, свойств и методов 
	void update(sf::Time const& deltaTime);
	// метод отрисовки объектов в графическом окне
	void draw();
	// рестарт игры
	void restart();
	// рестарт более сложный уровень
	void start_complexity(); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// новый уровень
	void newLevel();
	// запись рекорда
	void saveHiScore(); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// окно HUD
	sf::View m_hudView = sf::View(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y));
	
	GameHubText m_HubText;
	GameText m_gametext= GameText(m_resolution);
};

