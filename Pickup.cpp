#include "Pickup.h"
#include "AssetManager.h"

void Pickup::spawn(sf::Vector2f pos, int type){
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> health_ammo(15, 150);
	std::uniform_int_distribution<> extension(5, 25);

	if (type >0 && type < 4) {
	
	m_Value = health_ammo(gen);

	m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/medical.png"));
	
	m_Type = 1;
	}
	if (type >= 4 && type < 7) {

	m_Value = health_ammo(gen);
	m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/ammo1.png"));
	m_Type = 2;
	}
	if (type == 15) {

		m_Value = extension(gen);
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/ammo2.png"));
		m_Type = 3;
	}

	if (type == 10) {

		m_Value = extension(gen);
		m_Sprite = sf::Sprite(AssetManager::GetTexture("graphics/medical1.png"));
		m_Type = 4;
	}

	m_SecondsSinceSpawn = 0;
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(pos.x, pos.y);
}

sf::FloatRect Pickup::getPosition() const
{
	return m_Sprite.getGlobalBounds();
}
sf::Sprite Pickup::getSprite() const
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

int Pickup::getType() const
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
	
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}
	
}

