#pragma once
#include"Animator.h"
#include <random>
#include <deque>
#include <array>

class Monster
{
private:
	// ��������� ����
	int m_complexity = 0;
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
	// �������� ����������� ����
	sf::Time m_moveTime;

	public:

	Monster();
	// ��������� ��������� ���� � ����
	bool hit();
	// ������, ��� �� ������
	bool isAlive();
	// ����� ������ ��� ���
	bool getnovisible();
	// ��������� ��������� �������
	void novisible();
	// ������� ������ �������
	void spawn(float startX, float startY, int type, int complexity);
	// ���������� �������������, ������� �������� �������� � ����
	sf::FloatRect getPosition();
	// �������� ����� ������� ��� ���������
	sf::Sprite getSprite() const;
	// ��������� �������� ������ ����
	void update(sf::Time deltaTime, sf::Vector2f playerLocation, sf::Vector2f resolution);
	// ���������� ��� �������
	int getTypeMonster() const;
	
	};

