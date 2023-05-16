#pragma once
#include<SFML/Graphics.hpp>
#include"Animator.h"

class Player
{

public:
	// направления движения игрока
	enum class playermove { UpPressed, UpRg, UpLf, DownPressed, DownRg, DownLf, LeftPressed, RightPressed, Stop };
	Player();
	// появление игрока на игровом поле
	void spawn(sf::IntRect planet, sf::Vector2f resolution, int tileSize);
	// рестарт параметров игрока
	void resetPlayerStats();
	// возвращает состояние жизни игрока
	bool getLive() const;
	// время получения урона игроком
	bool hit(sf::Time timeHit);
	// как давно был последний удар по игроку
	sf::Time getLastHitTime() const;
	// координаты игрока
	sf::FloatRect getPosition() const;
	// центральные координаты игрока
	sf::Vector2f getCenter() const;
	// угол поворота игрока
	float getRotation() const;
	// вернуть копию спрайта игрока
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
	// Сколько здоровья у игрока на данный момент?
	float getHealth() const;
	float getMaxHealth() const;

private:
	// Стартовая жизнь игрока
	const float START_HEALTH = 200;
	// Позиция игрока
	sf::Vector2f m_Position;
	// Отображение игрока
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	bool m_animMove = false;
	// Разрешение экрана
	sf::Vector2f m_Resolution;
	//Размер поля поля
	sf::IntRect m_planet;
	// Размер текстур поля поля
	int m_TileSize;
	// В каком направлении(ях) движется игрок в данный момент
	playermove m_move;
	// Живой ли игрок
	bool m_live = true;
	// Здоровье игрока
	float m_Health;
	// Максимальное здоровье у игрока
	float m_MaxHealth;
	// Время нанесения последнего удара по игроку 
	sf::Time m_LastHit;
	// Частота перемещения игрока
	sf::Time m_time_moving;
	// Скорость в пикселях в секунду
	float m_Speed;
	
};

