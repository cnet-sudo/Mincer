#pragma once
#include<SFML/Graphics.hpp>
#include"Animator.h"

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	// Player position (Позиция игрока)
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	Animator m_AnimPlayer = Animator(m_Sprite);
	sf::Texture m_Texture;
	// Screen resolution (Разрешение экрана)
	sf::Vector2f m_Resolution;
	// Battlefield size (Размер поля боя)
	sf::IntRect m_Arena;
	// Battlefield texture size (Размер текстур поля боя)
	int m_TileSize;
	// Which direction(s) is the player currently moving in
	// В каком направлении(ях) движется игрок в данный момент
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
	// Player Health (Здоровье игрока)
	float m_Health;
	// Player maximum health (Максимальное здоровье у игрока)
	float m_MaxHealth;
	// The time of the last hit on the player
	// Время нанесения последнего удара по игроку 
	sf::Time m_LastHit;
	// Speed in pixels per second (Скорость в пикселях в секунду)
	float m_Speed;
public:

	Player();
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	// restart (перезапуск)
	void resetPlayerStats();
	// Player control when hit by a monster
	// Управление игроком, когда его сбил монстр
	bool hit(sf::Time timeHit);
	// How long ago was the player last hit
	// Как давно был последний удар игрока
	sf::Time getLastHitTime() const;
	// Where is the player
	// Где игрок
	sf::FloatRect getPosition() const;
	// Where is the center of the player
	// Где находится центр игрока
	sf::Vector2f getCenter() const;
	// What angle is the player facing
	// Под каким углом смотрит игрок
	float getRotation() const;
	// Send a copy of the sprite to the main function
	// Отправить копию спрайта в основную функцию
	sf::Sprite getSprite() const;
	// The next four functions move the player
	// Следующие четыре функции перемещают игрока
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	// Stop the player moving in a specific direction
	// Остановить движение игрока в определенном направлении
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
	// We will call this function once every frame
	// Мы будем вызывать эту функцию один раз в каждом кадре
	void update(sf::Time deltaTime, sf::Vector2i mousePosition);
	// Give the player a speed boost
	// Дайте игроку ускорение
	void upgradeSpeed();
	// Give the player some health
	// Дайте игроку немного здоровья
	void upgradeHealth();
	// Increase the maximum amount of health the player can have
	// Увеличьте максимальное количество здоровья, которое может иметь игрок
	void increaseHealthLevel(float amount);
	// How much health has the player currently got?
	// Сколько здоровья у игрока на данный момент?
	float getHealth() const;
};

