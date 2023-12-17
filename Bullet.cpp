
#include "Bullet.h"

Bullet::Bullet() {	
	m_BulletShape.setFillColor(sf::Color::Red);
	m_BulletShape.setRadius(10);
	m_BulletShape.setOrigin(5,5);
}
void Bullet::shoot(float startX, float startY,
	float targetX, float targetY) {	
	// ���� � �����
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;
	// ���������� �������� ���������� ������
	float gradient = (startX - targetX) / (startY - targetY);
	// �������� ������ 1 ������ ���� �������������
	if (gradient < 0) {
		gradient *= -1;
	}
	// ��������� ��������� ����� x � y
	float ratioXY = m_BulletSpeed / (1 + gradient);
	// ���������� ���������� �� ����������� � ���������
	m_BulletDistance.y = ratioXY;
	m_BulletDistance.x = ratioXY * gradient;
	// ��������� ���� � ���������� �����������
	if (targetX < startX) {
		m_BulletDistance.x *= -1;
	}
	if (targetY < startY) {
		m_BulletDistance.y *= -1;
	}
	// ���������� ������������ �������� 1000 ��������
	float range = 1000;
	m_Min.x = startX - range;
	m_Max.x = startX + range;
	m_Min.y = startY - range;
	m_Max.y = startY + range;
	// ���������� ���������� ��� ����
	m_BulletShape.setPosition(m_Position);
}

void Bullet::stop() {
	m_InFlight = false;
}

bool Bullet::isInFlight() {
	return m_InFlight;
}

FloatRect Bullet::getPosition() {
	return m_BulletShape.getGlobalBounds();
}

CircleShape Bullet::getShape() {
	return m_BulletShape;
}

void Bullet::update(float elapsedTime) {
	if (m_InFlight) {
	// �������� ���������� ������� �������
	m_Position.x += m_BulletDistance.x * elapsedTime;
	m_Position.y += m_BulletDistance.y * elapsedTime;
	// ����������� ����
	m_BulletShape.setPosition(m_Position);
	// ���� ����� �� ������� ������������?
	if (m_Position.x < m_Min.x || m_Position.x > m_Max.x ||
		m_Position.y < m_Min.y || m_Position.y > m_Max.y) {
		m_InFlight = false;
	}
	}
}









