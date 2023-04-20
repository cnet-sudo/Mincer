#pragma once
#include <SFML/Graphics.hpp>
#include"AssetManager.h"
#include"Animator.h"
#include <random>

class Monster
{
private:
	// ��������� ����� ������ ��� ��������?
	// How fast is each monster type?
	const float mon1_speed = 70;
	const float mon2_speed = 60;
	const float mon3_speed = 50;
	const float mon4_speed = 40;
	const float mon5_speed = 30;
	// ��������� ���� ������ ��� ��������
	// How strong each monster type is
	const float mon1_HEALTH = 1;
	const float mon2_HEALTH = 2;
	const float mon3_HEALTH = 3;
	const float mon4_HEALTH = 4;
	const float mon5_HEALTH = 5;
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
	Animator m_AnimPlayer = Animator(m_Sprite);
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
	Monster();
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
	void update(sf::Time deltaTime, sf::Vector2f playerLocation);
	
};

