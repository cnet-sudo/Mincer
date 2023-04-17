#include "Monster.h"

void Monster::spawn(float startX, float startY, int type)
{
	// Будет использоваться для получения начального числа для механизма случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());

	switch (type)
	{
	case 0:
		// монстр 1
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/mon1.png"));
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		// монстр 2
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/mon2.png"));
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		// монстр 3
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/mon3.png"));
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