#pragma once
#include <SFML/Graphics.hpp>
#include"AssetManager.h"
#include <random>

class Monster
{
private:
	// ��������� ����� ������ ��� ��������?
	// How fast is each monster type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;
	// ��������� ���� ������ ��� ��������
	// How strong each monster type is
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;
	// ��������� ������� ������� ������� �������� ���� ��������
	// Make each monster change its speed a little
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 100;
	// ��� ���� ������?
	// Where is this monster?
	sf::Vector2f m_Position;
	// ������ ��� �������
	// Sprite for the monster
	sf::Sprite m_Sprite;
	// ��� ������ ��� ����� ��������/�����������?
	// How fast can this one run/crawl?
	float m_Speed;
	// ������� � ���� ��������?
	// How much health has it got?
	float m_Health;
	// �� ��� ���?
	// Is it still alive?
	bool m_Alive;
public:
	// ��������� ��������� ���� � �������
	// Handling a bullet hitting a monster
	bool hit();
	// ������, ��� �� ������
	// Find out if the monster is alive
	bool isAlive();
	// ������� ������ �������
	// Spawn a new monster
	void spawn(float startX, float startY, int type);
	// ���������� �������������, ������� �������� �������� � ����
	// Return a rectangle that is the position in the world
	sf::FloatRect getPosition();
	// �������� ����� ������� ��� ���������
	// Get a copy of the sprite to draw
	sf::Sprite getSprite();
	// ��������� �������� ������ ����
	// Update the monsters each frame
	void update(float elapsedTime, sf::Vector2f playerLocation);
};

