#include "Monster.h"

Monster::Monster()
{
	auto& d2 = m_AnimPlayer.CreateAnimation("d2", "graphics/mon4.png", sf::seconds(0.5), false);
	d2.AddFrames(sf::Vector2i(0, 1098), sf::Vector2i(170, 140), 4, 1);
	auto& d1 = m_AnimPlayer.CreateAnimation("d1", "graphics/mon4.png", sf::seconds(0.5), false);
	d1.AddFrames(sf::Vector2i(0, 928), sf::Vector2i(170, 140), 4, 1);
	auto& mon1 = m_AnimPlayer.CreateAnimation("mon1", "graphics/mon4.png", sf::seconds(0.5), true);
	mon1.AddFrames(sf::Vector2i(0, 756), sf::Vector2i(170, 140), 4, 1);
	auto& mon2 = m_AnimPlayer.CreateAnimation("mon2", "graphics/mon4.png", sf::seconds(1), true);
	mon2.AddFrames(sf::Vector2i(0, 556), sf::Vector2i(170, 185), 4, 1);
	auto& mon3 = m_AnimPlayer.CreateAnimation("mon3", "graphics/mon4.png", sf::seconds(1), true);
	mon3.AddFrames(sf::Vector2i(0, 390), sf::Vector2i(160, 160), 4, 1);
	auto& mon4 = m_AnimPlayer.CreateAnimation("mon4", "graphics/mon4.png", sf::seconds(1), true);
	mon4.AddFrames(sf::Vector2i(0, 210), sf::Vector2i(170, 160), 4, 1);
	auto& mon5 = m_AnimPlayer.CreateAnimation("mon5", "graphics/mon4.png", sf::seconds(1), true);
	mon5.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(195, 206), 4, 1);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width/2, m_Sprite.getGlobalBounds().height/2);	
}

void Monster::spawn(float startX, float startY, int type)
{
	std::array<std::string, 5> name_monster{ "mon1","mon2","mon3","mon4","mon5" };
	m_Type = type;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> speed_plus(0,9);
	
	m_AnimPlayer.SwitchAnimation(name_monster[type]);
	m_Speed = 1-(type*0.1f)+(speed_plus(gen)*0.01f);
	m_Health = type+1;
		
	//Инициализировать его местоположение
	m_Position.x = startX;
	m_Position.y = startY;
	// Отцентровуем объект
	m_Sprite.setOrigin(25, 25);
	// Устанавливаем место положения на карте
	m_Sprite.setPosition(m_Position);
}



bool Monster::hit()
{
	if (m_Health <= 0) return false;
	m_Health--;
	if (m_Health <= 0)
	{
		// dead
		if (m_AnimPlayer.GetCurrentAnimationName() == "mon2" || m_AnimPlayer.GetCurrentAnimationName() == "mon3")
		{if (m_AnimPlayer.GetCurrentAnimationName() != "d2") m_AnimPlayer.SwitchAnimation("d2");}
		else 
		{if (m_AnimPlayer.GetCurrentAnimationName() != "d1") m_AnimPlayer.SwitchAnimation("d1");}
		
		return true;
	}
	return false;
}

bool Monster::isAlive()
{
	return m_Alive;
}

bool Monster::getnovisible()
{
	return m_novisible;
}

void Monster::novisible()
{
	if (!m_Alive) m_novisible = true;
}

sf::FloatRect Monster::getPosition()
{
	auto myGlobalBounds = sf::FloatRect(m_Sprite.getGlobalBounds().left+40,	m_Sprite.getGlobalBounds().top+40, 
	m_Sprite.getGlobalBounds().width-80, m_Sprite.getGlobalBounds().height - 80);
	
	return myGlobalBounds;
}

sf::Sprite Monster::getSprite() const
{
	return m_Sprite;
}

void Monster::update(sf::Time deltaTime, sf::Vector2f playerLocation, sf::Vector2f resolution)
{
	m_AnimPlayer.Update(deltaTime);
	if (m_AnimPlayer.getEndAnim())
	{
		m_Alive = false;
	}

	m_moveTime+= deltaTime;
	
	if (m_moveTime > sf::microseconds(5000)) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	m_moveTime = sf::microseconds(0);

	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x + m_Speed;
	}
	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +m_Speed / (100 / (resolution.y / (resolution.x / 100)));

	}
	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x - m_Speed;

	}
	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y - m_Speed / (100 / (resolution.y / (resolution.x / 100)));

	}

	m_Sprite.setPosition(m_Position);
	auto angle = static_cast<float>((atan2(playerY - m_Position.y, playerX - m_Position.x)* 180) / 3.141);
	m_Sprite.setRotation(angle);
	}
}

int Monster::getTypeMonster() const
{
	return m_Type;
}

