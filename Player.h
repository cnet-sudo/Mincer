#pragma once
#include"Animator.h"

class Player
{
public:
	Player();
	// направления движения игрока
	enum class playermove { UpPressed, UpRg, UpLf, DownPressed, DownRg, DownLf, LeftPressed, RightPressed, Stop };
	// метод появление игрока на игровом поле
	void spawn(sf::IntRect planet, sf::Vector2f resolution, int tileSize);
	// метод рестарт параметров игрока
	void resetPlayerStats();
	// возвращает состояние жизни игрока
	bool getLive() const;
	// метод получения урона игроком
	bool hit(sf::Time timeHit);
	// возвращает время как давно был последний удар по игроку
	sf::Time getLastHitTime() const;
	// возвращает координаты игрока
	sf::FloatRect getPosition() const;
	// возвращает центральные координаты игрока
	sf::Vector2f getCenter() const;
	// возвращает угол поворота игрока
	float getRotation() const;
	// возврщает копию спрайта игрока
	sf::Sprite getSprite() const;
	// рисуем игрока
	void draw(sf::RenderWindow& win) const;
	// перемещаем игрока
	void move(playermove mov);
	// обновление игровой логики 
	void update(sf::Time deltaTime, sf::Vector2i mousePosition);
	// увеличиваем максимальное количество здоровья 
	void upgradeHealth(float heal);
	// пополняем здоровье игрока
	void increaseHealthLevel(float amount);
	// возвращает сколько здоровья у игрока на данный момент?
	float getHealth() const;
	// возвращает максимальное здоровье игрока
	float getMaxHealth() const;

private:
	// стартовая жизнь игрока
	const float START_HEALTH = 200;
	// позиция игрока
	sf::Vector2f m_Position;
	// отображение игрока спрайт и  объект анимации
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	// разрешение анимировать игрока
	bool m_animMove = false;
	// разрешение экрана
	sf::Vector2f m_Resolution;
	// размер игрового поля 
	sf::IntRect m_planet;
	// размер текстур игрового поля 
	int m_TileSize;
	// в каком направлении(ях) движется игрок в данный момент
	playermove m_move;
	// живой ли игрок
	bool m_live = true;
	// здоровье игрока
	float m_Health;
	// максимальное здоровье игрока
	float m_MaxHealth;
	// время нанесения последнего удара по игроку 
	sf::Time m_LastHit;
	// частота перемещения игрока
	sf::Time m_time_moving;
	// скорость перемещения игрока в пикселях в секунду
	float m_Speed;
	
};

