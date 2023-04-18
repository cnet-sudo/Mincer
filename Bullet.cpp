#include "Bullet.h"

Bullet::Bullet()
{	
	m_BulletShape.setFillColor(sf::Color::Red);
	m_BulletShape.setRadius(10);
}

void Bullet::shoot(float startX, float startY,
	float targetX, float targetY)
{
	// Keep track of the bullet
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;
	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);
	// Any gradient less than 1 needs to be negative
	if (gradient < 0)
	{
		gradient *= -1;
	}
	// Calculate the ratio between x and y
	float ratioXY = m_BulletSpeed / (1 + gradient);
	// Set the "speed" horizontally and vertically
	m_BulletDistance.y = ratioXY;
	m_BulletDistance.x = ratioXY * gradient;
	// Point the bullet in the right direction
	if (targetX < startX)
	{
		m_BulletDistance.x *= -1;
	}
	if (targetY < startY)
	{
		m_BulletDistance.y *= -1;
	}
	// Set a max range of 1000 pixels
	float range = 1000;
	m_Min.x = startX - range;
	m_Max.x = startX + range;
	m_Min.y = startY - range;
	m_Max.y = startY + range;
	// Position the bullet ready to be drawn
	m_BulletShape.setPosition(m_Position);
}

void Bullet::stop()
{
	m_InFlight = false;
}
bool Bullet::isInFlight()
{
	return m_InFlight;
}
FloatRect Bullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}
CircleShape Bullet::getShape()
{
	return m_BulletShape;
}

void Bullet::update(float elapsedTime)
{
	
	// Update the bullet position variables
	m_Position.x += m_BulletDistance.x * elapsedTime;
	m_Position.y += m_BulletDistance.y * elapsedTime;
	// Move the bullet
	m_BulletShape.setPosition(m_Position);
	// Has the bullet gone out of range?
	if (m_Position.x < m_Min.x || m_Position.x > m_Max.x ||
		m_Position.y < m_Min.y || m_Position.y > m_Max.y)
	{
		m_InFlight = false;
	}
}