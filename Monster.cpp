#include "Monster.h"

Monster::Monster()
{
	auto& d1 = m_AnimPlayer.CreateAnimation("d1", "graphics/mon4.png", sf::seconds(0.5), false);
	d1.AddFrames(sf::Vector2i(0, 928), sf::Vector2i(170, 140), 4, 1);
	auto& mon1 = m_AnimPlayer.CreateAnimation("mon1", "graphics/mon4.png", sf::seconds(0.5), true);
	mon1.AddFrames(sf::Vector2i(0, 756), sf::Vector2i(170, 140), 4, 1);
	auto& mon2 = m_AnimPlayer.CreateAnimation("mon2", "graphics/mon4.png", sf::seconds(1), true);
	mon2.AddFrames(sf::Vector2i(0, 556), sf::Vector2i(170, 185), 4, 1);
	auto& mon3 = m_AnimPlayer.CreateAnimation("mon3", "graphics/mon4.png", sf::seconds(1), true);
	mon3.AddFrames(sf::Vector2i(0, 391), sf::Vector2i(170, 160), 4, 1);
	auto& mon4 = m_AnimPlayer.CreateAnimation("mon4", "graphics/mon4.png", sf::seconds(1), true);
	mon4.AddFrames(sf::Vector2i(0, 210), sf::Vector2i(170, 160), 4, 1);
	auto& mon5 = m_AnimPlayer.CreateAnimation("mon5", "graphics/mon4.png", sf::seconds(1), true);
	mon5.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(195, 206), 4, 1);
}

void Monster::spawn(float startX, float startY, int type)
{
	// Будет использоваться для получения начального числа для механизма случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());

	switch (type)
	{
	case 0:
		// монстр 1
		m_AnimPlayer.SwitchAnimation("mon1");
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		// монстр 2
		m_AnimPlayer.SwitchAnimation("mon2");
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		// монстр 3
		m_AnimPlayer.SwitchAnimation("mon3");
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	case 3:
		// монстр 3
		m_AnimPlayer.SwitchAnimation("mon4");
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	case 4:
		// монстр 3
		m_AnimPlayer.SwitchAnimation("mon5");
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	}
	std::uniform_int_distribution<> dis(MAX_VARRIANCE, OFFSET);

	auto modifier = static_cast<float>(dis(gen));
	modifier /= 100; 
	m_Speed *= modifier;
	// Initialize its location
	//Инициализировать его местоположение
	m_Position.x = startX;
	m_Position.y = startY;
	// Set its origin to its center
	// Отцентровуем объект
	m_Sprite.setOrigin(25, 25);
	// Устанавливаем место положения на карте
	m_Sprite.setPosition(m_Position);
}



bool Monster::hit()
{
	m_Health--;
	if (m_Health <= 0)
	{
		// dead
		if (m_AnimPlayer.GetCurrentAnimationName() != "d1") m_AnimPlayer.SwitchAnimation("d1");
		return true;
	}
	// injured but not dead yet
	return false;
}

bool Monster::isAlive()
{
	return m_Alive;
}
sf::FloatRect Monster::getPosition()
{
	return m_Sprite.getGlobalBounds();
}
sf::Sprite Monster::getSprite()
{
	return m_Sprite;
}

void Monster::update(sf::Time deltaTime,	sf::Vector2f playerLocation)
{
	m_AnimPlayer.Update(deltaTime);
	if (m_AnimPlayer.getEndAnim())
	{
		m_Alive = false;
	}
	float elapsedTime = deltaTime.asSeconds();
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	// Update the zombie position variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}
	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}
	// Move the sprite
	m_Sprite.setPosition(m_Position);
	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x)* 180) / 3.141;
	m_Sprite.setRotation(angle);
}