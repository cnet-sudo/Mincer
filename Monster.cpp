#include "Monster.h"

void Monster::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/bloater.png"));
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		// Chaser
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/chaser.png"));
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		// Crawler
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/crawler.png"));
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	}
	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0)* seed);
	// Somewhere between 80 and 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express this as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;
	// Initialize its location
	m_Position.x = startX;
	m_Position.y = startY;
	// Set its origin to its center
	m_Sprite.setOrigin(25, 25);
	// Set its position
	m_Sprite.setPosition(m_Position);
}