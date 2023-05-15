#include "Player.h"

Player::Player()
{
		m_Speed = 2;
		m_Health = START_HEALTH;
		m_MaxHealth = START_HEALTH;
		m_move = playermove::Stop;
		m_TileSize = 0;
		auto& idleForward = m_AnimPlayer.CreateAnimation("idleForward", "graphics/player.png", sf::seconds(0.5), true);
		idleForward.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(135, 105), 4, 1);
		auto& dead = m_AnimPlayer.CreateAnimation("dead", "graphics/player.png", sf::seconds(0.5), false);
		dead.AddFrames(sf::Vector2i(405, 0), sf::Vector2i(135, 105), 4, 1);
		m_AnimPlayer.SwitchAnimation("idleForward");
		m_AnimPlayer.Update(sf::seconds(0));
		
		m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
		
}

// появление игрока в мире
void Player::spawn(sf::IntRect planet, sf::Vector2f resolution, int tileSize)
{
	// Поместите игрока в центр арены
	m_Position.x = static_cast<float>(planet.width / 2);
	m_Position.y = static_cast<float>(planet.height / 2);
	// Копируем детали арены
	m_planet.left = planet.left;
	m_planet.width = planet.width;
	m_planet.top = planet.top;
	m_planet.height = planet.height;
	// Сохраняем размер плиток
	m_TileSize = tileSize;
	// Сохраняем разрешение экрана
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}
// сброс свойств игрока
void Player::resetPlayerStats()
{
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_live = true;
	m_AnimPlayer.SwitchAnimation("idleForward");
	m_AnimPlayer.Update(sf::seconds(0));
}

// состояние игрока жив мёртв
bool Player::getLive() const {

	return m_live;
}

// время получения урона
sf::Time Player::getLastHitTime() const {

	return m_LastHit;
}

bool Player::hit(sf::Time timeHit) {

	if (timeHit.asMilliseconds()- m_LastHit.asMilliseconds() > 200 && m_Health>0) {
		
		m_LastHit = timeHit;
		if (m_Health>100) m_Health -= 10; else m_Health -= 5;
		if (m_Health < 0) m_Health = 0;
		return true;
	}
	else {

		return false;
	}
}
// область нахождения игрока
sf::FloatRect Player::getPosition() const {

	auto myGlobalBounds = sf::FloatRect(m_Sprite.getGlobalBounds().left+20,
	m_Sprite.getGlobalBounds().top+20, m_Sprite.getGlobalBounds().width - 40, m_Sprite.getGlobalBounds().height - 40);

	return myGlobalBounds;
}

// координаты расположения игрока
sf::Vector2f Player::getCenter() const {

	return m_Position;
}

// угол поворота игрока
float Player::getRotation() const {

	return m_Sprite.getRotation();
}
// спрайт игрока
sf::Sprite Player::getSprite() const {

	return m_Sprite;
}

// количество жизни игрока
float Player::getHealth() const {

	return m_Health;
}

// максимальное количество жизни
float Player::getMaxHealth() const
{
	return m_MaxHealth;
}

// рисуем игрока
void Player::draw(sf::RenderWindow& win) const {

	win.draw(m_Sprite);
}

// перемещение игрока
void Player::move(playermove mov) {

	m_move = mov;
}

// увеличение максимального количества жизни
void Player::upgradeHealth(float heal) {

	if (m_Health!=0) m_MaxHealth += heal;
}


// востановление жизни игрока
void Player::increaseHealthLevel(float amount) {

	if (m_Health != 0) {
	m_Health += amount;
	// Но не выше максимума
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
	}
}

// обновление свойств игрока
void Player::update(sf::Time deltaTime, sf::Vector2i mousePosition)
{
	m_time_moving += deltaTime;
	// анимация перемещения игрока
	if (m_animMove && m_Health>0) m_AnimPlayer.Update(deltaTime);
	// если игрок потерял здоровье
	if (m_Health <= 0) 
	{
		if (m_AnimPlayer.GetCurrentAnimationName() != "dead") m_AnimPlayer.SwitchAnimation("dead");
		
		m_AnimPlayer.Update(deltaTime);

		if (m_AnimPlayer.getEndAnim()) {
		m_live = false;
		}
	}
	// начало раздела если игрок полон сил
	else {

		if (m_time_moving> sf::microseconds(5000)) {

		m_time_moving = sf::microseconds(0);

		switch (m_move)
		{
		case Player::playermove::UpPressed:
			m_Position.y -= m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::UpRg:
			m_Position.y -= m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
			m_Position.x += m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::UpLf:
			m_Position.y -= m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
			m_Position.x -= m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::DownPressed:
			m_Position.y += m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::DownRg:
			m_Position.y += m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
			m_Position.x += m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::DownLf:
			m_Position.y += m_Speed / (100 / (m_Resolution.y / (m_Resolution.x / 100)));
			m_Position.x -= m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::LeftPressed:
			m_Position.x -= m_Speed;
			m_animMove = true;
			break;
		case Player::playermove::RightPressed:
			m_animMove = true;
			m_Position.x += m_Speed;
			break;
		default:
			m_animMove = false;
			break;
		}
		
		m_Sprite.setPosition(m_Position);
		
		// Держите игрока на арене
		if (m_Position.x > static_cast<float>((m_planet.width - m_TileSize)-(m_Sprite.getGlobalBounds().width/2))) {

		m_Position.x = static_cast<float>((m_planet.width - m_TileSize) - (m_Sprite.getGlobalBounds().width / 2));
		}
		if (m_Position.x < static_cast<float>((m_planet.left + m_TileSize)+ (m_Sprite.getGlobalBounds().width / 2))) {

		m_Position.x = static_cast<float>((m_planet.left + m_TileSize) + (m_Sprite.getGlobalBounds().width / 2));
		}
		if (m_Position.y > static_cast<float>((m_planet.height - m_TileSize) - (m_Sprite.getGlobalBounds().height / 2))) {

		m_Position.y = static_cast<float>((m_planet.height - m_TileSize) - (m_Sprite.getGlobalBounds().height / 2));
		}
		if (m_Position.y < static_cast<float>((m_planet.top + m_TileSize)+(m_Sprite.getGlobalBounds().height / 2)))	{

		m_Position.y = static_cast<float>((m_planet.top + m_TileSize)+(m_Sprite.getGlobalBounds().height / 2));
		}
		// Вычислить угол, на который смотрит игрок
		auto angle = static_cast<float>((atan2(static_cast<float>(mousePosition.y) - m_Resolution.y / 2, 
		static_cast<float>(mousePosition.x) - m_Resolution.x / 2)* 180) / 3.141);

		m_Sprite.setRotation(angle);
		}
	}  // конец раздела если игрок полон сил
}



