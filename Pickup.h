#pragma once
#include <SFML/Graphics.hpp>

class Pickup
{
private:
	//��������� �������� ��� ������� 
	const int HEALTH_START_VALUE = 100;
	const int AMMO_START_VALUE = 100;

	// ������, �������������� ���� �����
	sf::Sprite m_Sprite;
	// ������� ����� ���� �����?
	int m_Value;
	// ��� ��� �� �����?
    // 1 = ��������, 2 = �������
	int m_Type;
	// ��������� ��������� � ������������
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive=10;
		
public:
	Pickup();
	// ������� ����� �����
	void spawn(sf::Vector2f pos, int type);
	// ��������� ��������� ������
	sf::FloatRect getPosition();
	// �������� ������ ��� ���������
	sf::Sprite getSprite();
	// ��������� ������ ��������� ���� ������ ����
	void update(float elapsedTime);
	// ������ �� ���� ����� � ��������� �����?
	bool isSpawned();
	// �������� ����� �� ������
	int gotIt();
	// �������� ���
	int getType();
};