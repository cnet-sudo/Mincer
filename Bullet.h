#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet
{
private:
	// ���������� ����
	Vector2f m_Position;
	// ����� ����
	CircleShape m_BulletShape;
	// ���� � �����
	bool m_InFlight = false;
	// �������� ����
	float m_BulletSpeed = 1000;
	// ��������� �����
	sf::Vector2f m_BulletDistance;
	// ������� ����� ����
	sf::Vector2f m_Max;
	sf::Vector2f m_Min;
	
public:
	
	Bullet();
	// ���������� ���� ����
	void stop();
	// ������� ��������� ����
	bool isInFlight();
	// ��������� ����
	void shoot(float startX, float startY,
		float xTarget, float yTarget);
	// ������� ���������� � ��������� ����
	FloatRect getPosition();
	// ������� ������ ����
	CircleShape getShape();
	// ���������� ������� ������
	void update(float elapsedTime);
};
