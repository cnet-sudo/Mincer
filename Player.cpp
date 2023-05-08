#include "Player.h"

Player::Player()
{
		m_Speed = START_SPEED;
		m_Health = START_HEALTH;
		m_MaxHealth = START_HEALTH;
		
		auto& idleForward = m_AnimPlayer.CreateAnimation("idleForward", "graphics/player.png", sf::seconds(0.5), true);
		idleForward.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(135, 105), 4, 1);
		auto& dead = m_AnimPlayer.CreateAnimation("dead", "graphics/player.png", sf::seconds(0.5), false);
		dead.AddFrames(sf::Vector2i(405, 0), sf::Vector2i(135, 105), 4, 1);
		m_AnimPlayer.SwitchAnimation("idleForward");
		m_AnimPlayer.Update(sf::seconds(0));
		// ”станавливаем начало спрайта в центр,
        // дл€ плавного вращени€
		m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
		
}

void Player::spawn(sf::IntRect planet, sf::Vector2f resolution, int tileSize)
{
	// ѕоместите игрока в центр арены
	m_Position.x = static_cast<float>(planet.width / 2);
	m_Position.y = static_cast<float>(planet.height / 2);
	//  опируем детали арены
	m_planet.left = planet.left;
	m_planet.width = planet.width;
	m_planet.top = planet.top;
	m_planet.height = planet.height;
	// ѕомните, насколько большие плитки на этой арене
	m_TileSize = tileSize;
	// —охраните разрешение дл€ использовани€ в будущем
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_live = true;
	m_AnimPlayer.SwitchAnimation("idleForward");
	m_AnimPlayer.Update(sf::seconds(0));
}

bool Player::getLive() const
{
	return m_live;
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
	auto myGlobalBounds = sf::FloatRect(m_Sprite.getGlobalBounds().left+20,
	m_Sprite.getGlobalBounds().top+20, m_Sprite.getGlobalBounds().width - 40, m_Sprite.getGlobalBounds().height - 40);

	return myGlobalBounds;
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

void Player::draw(sf::RenderWindow& win) const
{
	win.draw(m_Sprite);
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
void Player::moveUpRg()
{
	m_UpRg = true;
}
void Player::stopUpRg()
{
	m_UpRg = false;
}
void Player::moveUpLf()
{
	m_UpLf = true;
}
void Player::stopUpLf()
{
	m_UpLf = false;
}
void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::moveDownRg()
{
	m_DownRg = true;
}
void Player::stopDownRg()
{
	m_DownRg = false;
}
void Player::moveDownLf()
{
	m_DownLf = true;
}
void Player::stopDownLf()
{
	m_DownLf = false;
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
	m_time_moving += deltaTime;
	if ((m_UpPressed|| m_DownPressed|| m_RightPressed|| m_LeftPressed || m_UpRg || m_DownLf || m_DownRg || m_UpLf)&& m_Health>0) m_AnimPlayer.Update(deltaTime);
	if (m_Health < 0) 
	{
		if (m_AnimPlayer.GetCurrentAnimationName() != "dead") m_AnimPlayer.SwitchAnimation("dead");
		m_AnimPlayer.Update(deltaTime);
	if (m_AnimPlayer.getEndAnim())
	{
		m_live = false;
	}
	}
	else {


	if (m_time_moving> sf::microseconds(5000)){

		m_time_moving = sf::microseconds(0);

	if (m_UpPressed){

		m_Position.y -= m_Speed;	
	}

	if (m_UpLf) {
		m_Position.y -= m_Speed /(100/(m_Resolution.y/(m_Resolution.x/100)));
		m_Position.x-= m_Speed;
	}

	if (m_UpRg) {
		m_Position.y -= m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
		m_Position.x += m_Speed;
	}
	if (m_DownPressed)
	{
		m_Position.y += m_Speed;
		
	}
	if (m_DownLf) {
		m_Position.y += m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
		m_Position.x -= m_Speed;
	}

	if (m_DownRg) {
		m_Position.y += m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
		m_Position.x += m_Speed;
	}
	if (m_RightPressed)
	{
		m_Position.x += m_Speed;
		
	}
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed;
		
	}
	m_Sprite.setPosition(m_Position);
		

	// ƒержите игрока на арене
	if (m_Position.x > static_cast<float>((m_planet.width - m_TileSize)-(m_Sprite.getGlobalBounds().width/2)))
	{
		m_Position.x = static_cast<float>((m_planet.width - m_TileSize) - (m_Sprite.getGlobalBounds().width / 2));
	}

	if (m_Position.x < static_cast<float>((m_planet.left + m_TileSize)+ (m_Sprite.getGlobalBounds().width / 2)))
	{
		m_Position.x = static_cast<float>((m_planet.left + m_TileSize) + (m_Sprite.getGlobalBounds().width / 2));
	}

	if (m_Position.y > static_cast<float>((m_planet.height - m_TileSize) - (m_Sprite.getGlobalBounds().height / 2)))
	{
		m_Position.y = static_cast<float>((m_planet.height - m_TileSize) - (m_Sprite.getGlobalBounds().height / 2));
	}
	if (m_Position.y < static_cast<float>((m_planet.top + m_TileSize)+(m_Sprite.getGlobalBounds().height / 2)))
	{
		m_Position.y = static_cast<float>((m_planet.top + m_TileSize)+(m_Sprite.getGlobalBounds().height / 2));
	}
	// ¬ычислить угол, на который смотрит игрок
	auto angle = static_cast<float>((atan2(static_cast<float>(mousePosition.y) - m_Resolution.y / 2, static_cast<float>(mousePosition.x) - m_Resolution.x / 2)* 180) / 3.141);
	m_Sprite.setRotation(angle);

		}
	}
}

void Player::upgradeSpeed()
{
	// 20% повышение скорости
	m_Speed += (START_SPEED * 0.2f);
}
void Player::upgradeHealth()
{
	// 20% максимальное улучшение здоровь€
	m_MaxHealth += (START_HEALTH * 0.2f);
}
void Player::increaseHealthLevel(float amount)
{
	m_Health += amount;
	// Ќо не выше максимума
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

