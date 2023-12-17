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
	// �����������
	GameEngine();
	// ����� ������� �������� �����
	void run();
private:
	// �������� ��������
	AssetManager m_manager; 
	// ���������� ������
	sf::Vector2f m_resolution = sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width), 
		static_cast<float>(sf::VideoMode::getDesktopMode().height));
	// ����������� ���� 
	sf::RenderWindow m_window; 
	// ���� ������ ����� � ����� �� ������������� ���������
	enum class State { paused, level, level_up, game_over, playing, 
		game_victory, game_load, splash_screen, transition, help };
	// c�������� ����
	State m_state;
	Levels m_levels = Levels(m_window, m_resolution.x, m_resolution.y); //<<<<<<<<<<<<<<
	// ������
	sf::Image m_icon;
	
	// ���� mainView
	sf::View m_mainView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
	// ������� ������
	GameSound m_musik;

	// o���� ������� �����
	sf::Time m_gameTimeTotal;
	// �������� ��������
	sf::Time m_lastPressed;
	// ������� ���������� �����
	sf::Vector2f m_mouseWorldPosition;
	// ���������� ����� � ����
	sf::Vector2i m_mouseScreenPosition;
	// �����
	Player m_player;

	// ������ ��������
	std::deque<Monster> m_monster;
	// �������� ��� �������
	std::vector<Pickup>  pickup; 
	// ������� 
	GameBullet m_Bullet;   
	// ����������� ������
	void recharge();
	
	// ������ �������� ������
	sf::IntRect m_planet;
	// ��� �������� ������
	sf::VertexArray m_background;
		
	// ����� ��������� ������� 
	void input();
	// ����� ���������� ����������, ������� � ������� 
	void update(sf::Time const& deltaTime);
	// ����� ��������� �������� � ����������� ����
	void draw();
	// ������� ����
	void restart();
	// ������� ����� ������� �������
	void start_complexity(); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ����� �������
	void newLevel();
	// ������ �������
	void saveHiScore(); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ���� HUD
	sf::View m_hudView = sf::View(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y));
	
	GameHubText m_HubText;
	GameText m_gametext= GameText(m_resolution);
};

