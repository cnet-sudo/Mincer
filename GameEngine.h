#pragma once
#include<iostream>
#include <fstream>
#include"AssetManager.h"
#include"Player.h"
#include"Monster.h"
#include "MonsterPlanet.h"
#include "Bullet.h"
#include "Pickup.h"
#include "array"
#include <vector>
#include <deque>
#include "GameSound.h"
#include <algorithm>
#include <iterator>
#include "Levels.h"
#include "GameText.h"

class GameEngine
{
public:
	GameEngine();
	
	// Метод запуска игрового цикла
	void run();
private:
	
	// Менеджер ресурсов
	AssetManager manager; 
	
	// Графическое окно
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_resolution.x, m_resolution.y),L"Мясорубка", sf::Style::Fullscreen);
	sf::Image icon;
	GameSound m_musik;
	// Метод обработки событий 
	void input();
	
	// Метод обновления переменных, свойств и методов 
	void update(sf::Time const& deltaTime);
	
	// Метод отрисовки объектов в графическом окне
	void draw();
	
	// Игра всегда будет в одном из четырех состояний
	enum class State {paused, level, level_up,game_over, playing, game_victory,game_load, splash_screen, transition,help };
	
	// Состояние игры
	State state;
	Levels levels=Levels(*window);
	// разрешение экрана
	sf::Vector2f m_resolution = sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width),
		static_cast<float>(sf::VideoMode::getDesktopMode().height));
	// Окно mainView
	sf::View mainView=sf::View(sf::FloatRect(0, 0,m_resolution.x, m_resolution.y));
	// Общее игровое время
	sf::Time gameTimeTotal;
	// мировые координаты мышки
	sf::Vector2f mouseWorldPosition;
	// координаты мышки в окне
	sf::Vector2i mouseScreenPosition;

	// игрок
	Player player;

	// фон уровня
	sf::VertexArray background;
	// Размер уровня
	sf::IntRect planet;

	// Количество монстров
	int numMonsterAlive;
	// массив монстров
	std::deque<Monster> monster;
	// 100 патронов
	std::array<Bullet,200> bullets;
	int currentBullet = 0;
	// Ящик с патронами
	int bulletsSpare;
	// Обойма
	int bulletsInClip;
	// Максимальный размер обоймы
	int clipSize;

	// интервал стрельбы
	Time lastPressed;
    
	// Прицел
	Sprite spriteCrosshair;
	Sprite spriteCrosshair1;
	// Придметы для подъёма
    std::vector<Pickup>  pickup;
	// очки
	int score;
	// рекорд
	int hiScore = 0;
	void saveHiScore();
	// рестарт
	void restart();
	// новый уровень
	void newLevel();
	int level=1;
	sf::Time timewave;
	// перезарядка оружия
	void recharge();
	// окно HUD
	View hudView=sf::View(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y));
	// патроны в интерфейсе
	Sprite spriteAmmoIcon;
	// текст
	Text levelText;
	Text ammoText;
	Text scoreText;
	Text hiScoreText;
	Text monsterRemainingText;
	Text levelNumberText;
	Text HelpText;
	// линия жизни
	RectangleShape healthBar;
	RectangleShape healthBar1;
	GameText gtext;
};

