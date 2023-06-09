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
	
	// ����� ������� �������� �����
	void run();
private:
	// ���������� ������
	sf::Vector2f m_resolution = sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width),
		static_cast<float>(sf::VideoMode::getDesktopMode().height));
	// �������� ��������
	AssetManager manager; 
	// ����������� ����
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_resolution.x, m_resolution.y),L"���������", sf::Style::Fullscreen);
	sf::Image icon;
	GameSound m_musik;
	// ����� ��������� ������� 
	void input();
	
	// ����� ���������� ����������, ������� � ������� 
	void update(sf::Time const& deltaTime);
	
	// ����� ��������� �������� � ����������� ����
	void draw();
	
	// ���� ������ ����� � ����� �� ������� ���������
	enum class State {paused, level, level_up,game_over, playing, game_victory,game_load, splash_screen, transition,help };
	
	// ��������� ����
	State state;
	Levels levels=Levels(*window, m_resolution.x, m_resolution.y);
	
	// ���� mainView
	sf::View mainView=sf::View(sf::FloatRect(0, 0, 1920, 1080));
	// ����� ������� �����
	sf::Time gameTimeTotal;
	// ������� ���������� �����
	sf::Vector2f mouseWorldPosition;
	// ���������� ����� � ����
	sf::Vector2i mouseScreenPosition;
	// �����
	Player player;
	// ������ ������
	sf::IntRect planet;

	//�������
	float m_scale_x;
	float m_scale_y;
	
	// ��� ������
	sf::VertexArray background;
	sf::Transform transform;
	

	// ���������� ��������
	int numMonsterAlive;
	// ������ ��������
	std::deque<Monster> monster;
	// 100 ��������
	std::array<Bullet,100> bullets;
	int currentBullet = 0;
	// ���� � ���������
	int bulletsSpare;
	// ������
	int bulletsInClip;
	// ������������ ������ ������
	int clipSize;
	// ���������
	int m_complexity = 1;
	// �������� ��������
	Time lastPressed;
    
	// ������
	Sprite spriteCrosshair;
	Sprite spriteCrosshair1;
	// �������� ��� �������
    std::vector<Pickup>  pickup;
	// ����
	int score;
	// ������
	int hiScore = 0;
	void saveHiScore();
	// �������
	void restart();
	void start_complexity();
	// ����� �������
	void newLevel();
	int level=1;
	sf::Time timewave;
	// ����������� ������
	void recharge();
	// ���� HUD
	View hudView=sf::View(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y));
	// ������� � ����������
	Sprite spriteAmmoIcon;
	// �����
	Text levelText;
	Text ammoText;
	Text scoreText;
	Text hiScoreText;
	Text monsterRemainingText;
	Text levelNumberText;
	Text HelpText;
	// ����� �����
	RectangleShape healthBar;
	RectangleShape healthBar1;
	GameText gtext;
};

