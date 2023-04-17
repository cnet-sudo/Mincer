#pragma once
#include<SFML/Graphics.hpp>
#include"Animator.h"

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	// Player position (������� ������)
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	sf::Texture m_Texture;
	// Screen resolution (���������� ������)
	sf::Vector2f m_Resolution;
	// Battlefield size (������ ���� ���)
	sf::IntRect m_Arena;
	// Battlefield texture size (������ ������� ���� ���)
	int m_TileSize;
	// Which direction(s) is the player currently moving in
	// � ����� �����������(��) �������� ����� � ������ ������
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
	// Player Health (�������� ������)
	float m_Health;
	// Player maximum health (������������ �������� � ������)
	float m_MaxHealth;
	// The time of the last hit on the player
	// ����� ��������� ���������� ����� �� ������ 
	sf::Time m_LastHit;
	// Speed in pixels per second (�������� � �������� � �������)
	float m_Speed;
public:

	Player();
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	// restart (����������)
	void resetPlayerStats();
	// Player control when hit by a monster
	// ���������� �������, ����� ��� ���� ������
	bool hit(sf::Time timeHit);
	// How long ago was the player last hit
	// ��� ����� ��� ��������� ���� ������
	sf::Time getLastHitTime() const;
	// Where is the player
	// ��� �����
	sf::FloatRect getPosition() const;
	// Where is the center of the player
	// ��� ��������� ����� ������
	sf::Vector2f getCenter() const;
	// What angle is the player facing
	// ��� ����� ����� ������� �����
	float getRotation() const;
	// Send a copy of the sprite to the main function
	// ��������� ����� ������� � �������� �������
	sf::Sprite getSprite() const;
	// The next four functions move the player
	// ��������� ������ ������� ���������� ������
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	// Stop the player moving in a specific direction
	// ���������� �������� ������ � ������������ �����������
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
	// We will call this function once every frame
	// �� ����� �������� ��� ������� ���� ��� � ������ �����
	void update(sf::Time deltaTime, sf::Vector2i mousePosition);
	// Give the player a speed boost
	// ����� ������ ���������
	void upgradeSpeed();
	// Give the player some health
	// ����� ������ ������� ��������
	void upgradeHealth();
	// Increase the maximum amount of health the player can have
	// ��������� ������������ ���������� ��������, ������� ����� ����� �����
	void increaseHealthLevel(float amount);
	// How much health has the player currently got?
	// ������� �������� � ������ �� ������ ������?
	float getHealth() const;
};

