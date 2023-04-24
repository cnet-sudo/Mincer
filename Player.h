#pragma once
#include<SFML/Graphics.hpp>
#include"Animator.h"

class Player
{
private:
	const float START_SPEED = 2;
	const float START_HEALTH = 200;
	//Позиция игрока
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	// Разрешение экрана
	sf::Vector2f m_Resolution;
	//Размер поля поля
	sf::IntRect m_Arena;
	// Размер текстур поля поля
	int m_TileSize;
	// В каком направлении(ях) движется игрок в данный момент
	bool m_UpPressed;
	bool m_UpRg;
	bool m_UpLf;
	bool m_DownPressed;
	bool m_DownRg;
	bool m_DownLf;
	bool m_LeftPressed;
	bool m_RightPressed;
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
public:

	Player();
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	// перезапуск
	void resetPlayerStats();
	// Время получения урона игроком
	bool hit(sf::Time timeHit);
	// Как давно был последний удар игрока
	sf::Time getLastHitTime() const;
	// Где игрок
	sf::FloatRect getPosition() const;
	// Где находится центр игрока
	sf::Vector2f getCenter() const;
	// What angle is the player facing
	// Под каким углом смотрит игрок
	float getRotation() const;
	// Отправить копию спрайта в основную функцию
	sf::Sprite getSprite() const;
	// Следующие четыре функции перемещают игрока
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveUpRg();
	void moveUpLf();
	void moveDown();
	void moveDownRg();
	void moveDownLf();
	// Остановить движение игрока в определенном направлении
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopUpRg();
	void stopUpLf();
	void stopDown();
	void stopDownRg();
	void stopDownLf();
	// Мы будем вызывать эту функцию один раз в каждом кадре
	void update(sf::Time deltaTime, sf::Vector2i mousePosition);
	// Дайте игроку ускорение
	void upgradeSpeed();
	// Дайте игроку немного здоровья
	void upgradeHealth();
	// Увеличьте максимальное количество здоровья, которое может иметь игрок
	void increaseHealthLevel(float amount);
	// Сколько здоровья у игрока на данный момент?
	float getHealth() const;
};

