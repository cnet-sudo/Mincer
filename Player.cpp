#include "Player.h"

Player::Player()
{
		m_Speed = START_SPEED;
		m_Health = START_HEALTH;
		m_MaxHealth = START_HEALTH;
		
		auto& idleForward = m_AnimPlayer.CreateAnimation("idleForward", "graphics/player.png", sf::seconds(0.8), true);
		idleForward.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(179, 135), 8, 1);
		m_AnimPlayer.SwitchAnimation("idleForward");
		m_AnimPlayer.Update(sf::seconds(0));
		// Set the origin of the sprite to the center,
		// for smooth rotation
		// ”станавливаем начало спрайта в центр,
        // дл€ плавного вращени€
		m_Sprite.setOrigin(50, 60);
		
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	// ѕоместите игрока в центр арены
	m_Position.x = static_cast<float>(arena.width / 2);
	m_Position.y = static_cast<float>(arena.height / 2);
	// Copy the details of the arena
	//  опируем детали арены
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;
	// Remember how big the tiles are in this arena
	// ѕомните, насколько большие плитки на этой арене
	m_TileSize = tileSize;
	// Store the resolution for future use
	// —охраните разрешение дл€ использовани€ в будущем
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

sf::Time Player::getLastHitTime() const
{
	return m_LastHit;
}

bool Player::hit(sf::Time timeHit)
{
	if (timeHit.asMilliseconds()- m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

sf::FloatRect Player::getPosition() const
{
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter() const
{
	return m_Position;
}
float Player::getRotation() const
{
	return m_Sprite.getRotation();
}

sf::Sprite Player::getSprite() const
{
	return m_Sprite;
}

float Player::getHealth() const
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}
void Player::moveRight()
{
	m_RightPressed = true;
}
void Player::moveUp()
{
	m_UpPressed = true;
}
void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}
void Player::stopRight()
{
	m_RightPressed = false;
}
void Player::stopUp()
{
	m_UpPressed = false;
}
void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(sf::Time deltaTime, sf::Vector2i mousePosition)
{
	float elapsedTime = deltaTime.asSeconds();
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
		
	}
	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
		
	}
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
		
	}
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
		
	}
	m_Sprite.setPosition(m_Position);
	if (m_UpPressed|| m_DownPressed|| m_RightPressed|| m_LeftPressed)m_AnimPlayer.Update(deltaTime);

	// Keep the player in the arena
	// ƒержите игрока на арене
	if (m_Position.x > static_cast<float>(m_Arena.width - m_TileSize))
	{
		m_Position.x = static_cast<float>(m_Arena.width - m_TileSize);
	}
	if (m_Position.x < static_cast<float>(m_Arena.left + m_TileSize))
	{
		m_Position.x = static_cast<float>(m_Arena.left + m_TileSize);
	}
	if (m_Position.y > static_cast<float>(m_Arena.height - m_TileSize))
	{
		m_Position.y = static_cast<float>(m_Arena.height - m_TileSize);
	}
	if (m_Position.y < static_cast<float>(m_Arena.top + m_TileSize))
	{
		m_Position.y = static_cast<float>(m_Arena.top + m_TileSize);
	}
	// Calculate the angle the player is facing
	// ¬ычислить угол, на который смотрит игрок
	auto angle = static_cast<float>((atan2(static_cast<float>(mousePosition.y) - m_Resolution.y / 2, static_cast<float>(mousePosition.x) - m_Resolution.x / 2)* 180) / 3.141);
	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	// 20% speed upgrade
	// 20% повышение скорости
	m_Speed += (START_SPEED * 0.2f);
}
void Player::upgradeHealth()
{
	// 20% max health upgrade
	// 20% максимальное улучшение здоровь€
	m_MaxHealth += (START_HEALTH * 0.2f);
}
void Player::increaseHealthLevel(float amount)
{
	m_Health += amount;
	// But not beyond the maximum
	// Ќо не выше максимума
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

