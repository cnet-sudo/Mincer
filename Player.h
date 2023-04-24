#pragma once
#include<SFML/Graphics.hpp>
#include"Animator.h"

class Player
{
private:
	const float START_SPEED = 2;
	const float START_HEALTH = 200;
	//������� ������
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	// ���������� ������
	sf::Vector2f m_Resolution;
	//������ ���� ����
	sf::IntRect m_Arena;
	// ������ ������� ���� ����
	int m_TileSize;
	// � ����� �����������(��) �������� ����� � ������ ������
	bool m_UpPressed;
	bool m_UpRg;
	bool m_UpLf;
	bool m_DownPressed;
	bool m_DownRg;
	bool m_DownLf;
	bool m_LeftPressed;
	bool m_RightPressed;
	// �������� ������
	float m_Health;
	// ������������ �������� � ������
	float m_MaxHealth;
	// ����� ��������� ���������� ����� �� ������ 
	sf::Time m_LastHit;
	// ������� ����������� ������
	sf::Time m_time_moving;
	// �������� � �������� � �������
	float m_Speed;
public:

	Player();
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	// ����������
	void resetPlayerStats();
	// ����� ��������� ����� �������
	bool hit(sf::Time timeHit);
	// ��� ����� ��� ��������� ���� ������
	sf::Time getLastHitTime() const;
	// ��� �����
	sf::FloatRect getPosition() const;
	// ��� ��������� ����� ������
	sf::Vector2f getCenter() const;
	// What angle is the player facing
	// ��� ����� ����� ������� �����
	float getRotation() const;
	// ��������� ����� ������� � �������� �������
	sf::Sprite getSprite() const;
	// ��������� ������ ������� ���������� ������
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveUpRg();
	void moveUpLf();
	void moveDown();
	void moveDownRg();
	void moveDownLf();
	// ���������� �������� ������ � ������������ �����������
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopUpRg();
	void stopUpLf();
	void stopDown();
	void stopDownRg();
	void stopDownLf();
	// �� ����� �������� ��� ������� ���� ��� � ������ �����
	void update(sf::Time deltaTime, sf::Vector2i mousePosition);
	// ����� ������ ���������
	void upgradeSpeed();
	// ����� ������ ������� ��������
	void upgradeHealth();
	// ��������� ������������ ���������� ��������, ������� ����� ����� �����
	void increaseHealthLevel(float amount);
	// ������� �������� � ������ �� ������ ������?
	float getHealth() const;
};

