#pragma once

#include<array>
#include<random>
#include<format>
#include"MonsterPlanet.h"
#include"AssetManager.h"
#include <fstream>    

class GameText
{
	//�������
	sf::Vector2f  m_scale{1,1};   

	sf::Vector2f m_resolution;

	// ������� � ����������
	sf::Sprite spriteAmmoIcon;

	// �����
	sf::Text levelText;
	sf::Text ammoText;
	sf::Text scoreText;
	sf::Text hiScoreText;
	sf::Text monsterRemainingText;
	sf::Text levelNumberText;
	sf::Text HelpText;

	// ����� �����
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBar1;

	std::array<sf::String, 6> m_deadText{L"������� �� ����� ������ ��������� �������� ���� �� ����",L"����� ��� ������, � ������ ��������� ���� � ���,\n\t ��� ���� � ������ � ����� �� ������"
	,L"�� ������� �� �������� ���������,\n ���� ���� ������ ��������� ...",L"������ ����� ���������� ��, ��� �� �����������\n\t\t � ������������ ���������",
		L"� ���� ������� ���������, �� � �� ���� �������\n\t\t\t ���������� �������",L"������� ������ �� �������� �������, \n������� ����� ������ ���� ���������"
	};

	std::array<sf::String, 6> m_victoriqText{ L"������ ��� ������� ��� ����,\n ������ ��� ����� � ����������",L"���������� ������ �\n ������ ��� ����� �����",
		L"� ����� ���� ����� ������ ����,\n\t ��� ������ � ���������",L"������� ���������� � ������� ����� � ���,\n\t\t ��� �� ������ �� ���������",
		L"� ���������� ����� ������, � ����\n � ������������ ��� ���������",L"������, ������, �������."
	};

	sf::Text m_text;	
	
public:

	explicit GameText(sf::Vector2f m_resolution);

	void update(GameHubText Hub);

	void draw(sf::RenderWindow& window);

	sf::Vector2f getScale(); // ���������� �������

	void drawText(sf::RenderWindow& window);

	void genText(std::string str);

	void drawGameOver(sf::RenderWindow& window);

	void drawAssistant(sf::RenderWindow& window, int num);

};

