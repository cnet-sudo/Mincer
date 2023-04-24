#pragma once
#include<iostream>
#include"AssetManager.h"
#include"Player.h"
#include"Planet.h"
#include"Monster.h"
#include "MonsterPlanet.h"
#include "Bullet.h"
#include "Pickup.h"
#include "array"
#include <fstream>
#include <vector>
#include <deque>
#include "GameSound.h"


class GameEngine
{
public:
	GameEngine();
	
	// Метод запуска игрового цикла
	void run();
private:
	
	// Менеджер ресурсов
	AssetManager manager; 
	
	// Умный указатель на графическое окно 
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(m_resolution.x, m_resolution.y),L"Мясорубка", sf::Style::Fullscreen);
	sf::Image icon;
	GameSound m_musik;
	// Метод обработки событий 
	void input();
	
	// Метод обновления переменных, свойств и методов 
	void update(sf::Time const& deltaTime);
	
	// Метод отрисовки объектов в графическом окне
	void draw();
	
	// Игра всегда будет в одном из четырех состояний
	enum class State {paused, wave_up,game_over, playing, game_victory,game_load};
	
	// Начните с состояния GAME_OVER
	State state;
	
	// create an SFML window
	sf::Vector2f m_resolution = sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width),
		static_cast<float>(sf::VideoMode::getDesktopMode().height));
	// Create a an SFML View for the main action
	sf::View mainView=sf::View(sf::FloatRect(0, 0,m_resolution.x, m_resolution.y));
	// How long has the PLAYING state been active
	sf::Time gameTimeTotal;
	// Where is the mouse in
	// relation to world coordinates
	sf::Vector2f mouseWorldPosition;
	// Where is the mouse in
	// relation to screen coordinates
	sf::Vector2i mouseScreenPosition;
	// Create an instance of the Player class
	Player player;

	// Create the background
	sf::VertexArray background;
	// The boundaries of the arena
	sf::IntRect planet;

	// Prepare for a horde of zombies
	int numMonster;
	int numMonsterAlive;
	// массив монстров
	std::deque<Monster> monster;
	// 100 bullets should do
	std::array<Bullet,100> bullets;
	int currentBullet = 0;
	// Ящик с патронами
	int bulletsSpare;
	// Обойма
	int bulletsInClip;
	// Максимальный размер обоймы
	const int clipSize = 50;

	float fireRate = 1;
	// When was the fire button last pressed?
	Time lastPressed;
	Sprite spriteCrosshair;
	Sprite spriteCrosshair1;
    std::vector<Pickup>  pickup;
	// About the game
	int score;
	int hiScore = 0;
	// рестарт
	void restart();
	// новая волна
	void newLevel();
	int level=1;
	sf::Time timewave;
	bool textWave=false;
	// перезарядка оружия
	void recharge();
	// Create a view for the HUD
	View hudView=sf::View(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y));
	Sprite spriteGameOver;
	Sprite spriteGameBegin;
	Sprite spriteAmmoIcon;
	Text pausedText;
	Text gameOverText;
	Text WaveUpText;
	Text ammoText;
	Text scoreText;
	Text hiScoreText;
	Text monsterRemainingText;
	Text waveNumberText;
	RectangleShape healthBar;
	RectangleShape healthBar1;
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	std::vector<int> deadMonster;
};

