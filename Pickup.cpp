#include "Pickup.h"
#include "AssetManager.h"

void Pickup::spawn(sf::Vector2f pos, int type)
{
	// Store the type of this pickup
	m_Type = type;

	switch (m_Type)
	{
	case 1:
	{
	m_Value = HEALTH_START_VALUE;
	m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/medical.png"));
	break;
	}
	case 2: 
	{
	m_Value = AMMO_START_VALUE;
	m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/ammo1.png"));
	break;
	}
	default:
		break;
	}
	m_SecondsSinceSpawn = 0;
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(pos.x, pos.y);
}

sf::FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}
sf::Sprite Pickup::getSprite()
{
	return m_Sprite;
}
bool Pickup::isSpawned() const
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

int Pickup::getType()
{
	return m_Type;
}

void Pickup::update(float elapsedTime)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}
	// Do we need to hide a pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Remove the pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}
	
}

