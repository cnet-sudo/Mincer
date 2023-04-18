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
#include <sstream>

class GameEngine
{
public:
	GameEngine();
	// Game Loop Launch Method
	// Метод запуска игрового цикла
	void run();
private:
	// Resource manager
	// Менеджер ресурсов
	AssetManager manager; 
	// Smart pointer to graphics window
	// Умный указатель на графическое окно 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(resolution.x, resolution.y),L"Мясорубка", sf::Style::Fullscreen);
	sf::Image icon;
	// Event handling method
	// Метод обработки событий 
	void input();
	// Method for updating variables, properties and methods
	// Метод обновления переменных, свойств и методов 
	void update(sf::Time const& deltaTime);
	// Method for drawing objects in the graphics window
	// Метод отрисовки объектов в графическом окне
	void draw();
	// The game will always be in one of four states
	// Игра всегда будет в одном из четырех состояний
	enum class State {paused, leveling_up,game_over, playing};
	// Start with the GAME_OVER state
	// Начните с состояния GAME_OVER
	State state = State::playing;
	// Get the screen resolution and
	// create an SFML window
	sf::Vector2f resolution;
	// Create a an SFML View for the main action
	sf::View mainView=sf::View(sf::FloatRect(0, 0,resolution.x, resolution.y));
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
	Monster* monster = nullptr;

	// 100 bullets should do
	std::array<Bullet,100> bullets;
	int currentBullet = 0;
	int bulletsSpare = 50;
	int bulletsInClip = 10;
	int clipSize = 6;
	float fireRate = 1;
	// When was the fire button last pressed?
	Time lastPressed;

	Sprite spriteCrosshair;
	Pickup healthPickup= Pickup(1);
	Pickup ammoPickup= Pickup(2);
	// About the game
	int score = 0;
	int hiScore = 0;
	void restart();
	// Create a view for the HUD
	View hudView=sf::View(sf::FloatRect(0, 0, resolution.x, resolution.y));
	Sprite spriteGameOver;
	Sprite spriteAmmoIcon;
	Text pausedText;
	Text gameOverText;
	Text levelUpText;
	Text ammoText;
	Text scoreText;
	Text hiScoreText;
	Text zombiesRemainingText;
	Text waveNumberText;
	int wave = 0;
	RectangleShape healthBar;
	Text debugText;
	std::ostringstream ss;
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;
};

