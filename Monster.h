#pragma once
#include <SFML/Graphics.hpp>
#include"AssetManager.h"
#include"Animator.h"
#include <random>
#include <deque>
#include <array>

class Monster
{
private:
	// �������� ��������
	const float mon1_speed = 1.0f;
	const float mon2_speed = 0.9f;
	const float mon3_speed = 0.8f;
	const float mon4_speed = 0.7f;
	const float mon5_speed = 0.6f;
	// ���������� ����� � ��������
	const float mon1_HEALTH = 1;
	const float mon2_HEALTH = 2;
	const float mon3_HEALTH = 3;
	const float mon4_HEALTH = 4;
	const float mon5_HEALTH = 5;
	// ���������� ��������
	sf::Vector2f m_Position;
	// ������ ��� �������
	sf::Sprite m_Sprite;
	// �������� ��������
	Animator m_AnimPlayer = Animator(m_Sprite);
	// �������� �������
	float m_Speed;
	// ����� �������
	float m_Health;
	// ��������� ��� - ����
	bool m_Alive = true;
	// ����� �� ����� ���� ��� ���
	bool m_novisible = false;
	// ��� �������
	int m_Type;
	sf::Time m_moveTime;
	public:

	Monster();
	// ��������� ��������� ���� � �������
	bool hit();
	// ������, ��� �� ������
	bool isAlive();
	bool getnovisible();
	void novisible();
	// ������� ������ �������
	void spawn(float startX, float startY, int type);
	// ���������� �������������, ������� �������� �������� � ����
	sf::FloatRect getPosition();
	// �������� ����� ������� ��� ���������
	sf::Sprite getSprite() const;
	// ��������� �������� ������ ����
	void update(sf::Time deltaTime, sf::Vector2f playerLocation, sf::Vector2f resolution);
	int getTypeMonster() const;
	
	};

