#pragma once
#include"Animator.h"

class Player
{
public:
	Player();
	// ����������� �������� ������
	enum class playermove { UpPressed, UpRg, UpLf, DownPressed, DownRg, DownLf, LeftPressed, RightPressed, Stop };
	// ����� ��������� ������ �� ������� ����
	void spawn(sf::IntRect planet, sf::Vector2f resolution, int tileSize);
	// ����� ������� ���������� ������
	void resetPlayerStats();
	// ���������� ��������� ����� ������
	bool getLive() const;
	// ����� ��������� ����� �������
	bool hit(sf::Time timeHit);
	// ���������� ����� ��� ����� ��� ��������� ���� �� ������
	sf::Time getLastHitTime() const;
	// ���������� ���������� ������
	sf::FloatRect getPosition() const;
	// ���������� ����������� ���������� ������
	sf::Vector2f getCenter() const;
	// ���������� ���� �������� ������
	float getRotation() const;
	// ��������� ����� ������� ������
	sf::Sprite getSprite() const;
	// ������ ������
	void draw(sf::RenderWindow& win) const;
	// ���������� ������
	void move(playermove mov);
	// ���������� ������� ������ 
	void update(sf::Time deltaTime, sf::Vector2i mousePosition);
	// ����������� ������������ ���������� �������� 
	void upgradeHealth(float heal);
	// ��������� �������� ������
	void increaseHealthLevel(float amount);
	// ���������� ������� �������� � ������ �� ������ ������?
	float getHealth() const;
	// ���������� ������������ �������� ������
	float getMaxHealth() const;

private:
	// ��������� ����� ������
	const float START_HEALTH = 200;
	// ������� ������
	sf::Vector2f m_Position;
	// ����������� ������ ������ �  ������ ��������
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	// ���������� ����������� ������
	bool m_animMove = false;
	// ���������� ������
	sf::Vector2f m_Resolution;
	// ������ �������� ���� 
	sf::IntRect m_planet;
	// ������ ������� �������� ���� 
	int m_TileSize;
	// � ����� �����������(��) �������� ����� � ������ ������
	playermove m_move;
	// ����� �� �����
	bool m_live = true;
	// �������� ������
	float m_Health;
	// ������������ �������� ������
	float m_MaxHealth;
	// ����� ��������� ���������� ����� �� ������ 
	sf::Time m_LastHit;
	// ������� ����������� ������
	sf::Time m_time_moving;
	// �������� ����������� ������ � �������� � �������
	float m_Speed;
	
};

