#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Pickup
{
private:
	
	// ������, �������������� ���� �����
	sf::Sprite m_Sprite;
	// ������� ����� ���� �����?
	int m_Value;
	// ��� ��� �� �����?
    // 1 = ��������, 2 = �������
	int m_Type;
	// ��������� ��������� � ������������ ������
	bool m_Spawned=true;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive=15;
		
public:
	// ������� ����� �����
	void spawn(sf::Vector2f pos, int type);
	// ��������� ��������� ������
	sf::FloatRect getPosition() const;
	// �������� ������ ��� ���������
	sf::Sprite getSprite() const;
	// ��������� ������ ��������� ���� ������ ����
	void update(float elapsedTime);
	// ������ �� ���� ����� � ��������� �����?
	bool isSpawned() const;
	// �������� ����� �� ������
	int gotIt();
	// �������� ���
	int getType() const;
};