#pragma once
#include <SFML/Graphics.hpp>
#include"AssetManager.h"
#include"Animator.h"
#include <random>
#include <deque>
#include <array>

class Monster
{
private:
	// Скорость монстров
	const float mon1_speed = 1.0f;
	const float mon2_speed = 0.9f;
	const float mon3_speed = 0.8f;
	const float mon4_speed = 0.7f;
	const float mon5_speed = 0.6f;
	// Количество жизей у монстров
	const float mon1_HEALTH = 1;
	const float mon2_HEALTH = 2;
	const float mon3_HEALTH = 3;
	const float mon4_HEALTH = 4;
	const float mon5_HEALTH = 5;
	// Координаты монстров
	sf::Vector2f m_Position;
	// Спрайт для монстра
	sf::Sprite m_Sprite;
	// Анимация монтстра
	Animator m_AnimPlayer = Animator(m_Sprite);
	// Скорость монстра
	float m_Speed;
	// Жизнь монстра
	float m_Health;
	// Состояние жив - мёртв
	bool m_Alive = true;
	// Видно на карте труп или нет
	bool m_novisible = false;
	// Тип моснтра
	int m_Type;
	sf::Time m_moveTime;
	public:

	Monster();
	// Обработка попадания пули в монстра
	bool hit();
	// Узнаем, жив ли монстр
	bool isAlive();
	bool getnovisible();
	void novisible();
	// Создаем нового монстра
	void spawn(float startX, float startY, int type);
	// Возвращаем прямоугольник, который является позицией в мире
	sf::FloatRect getPosition();
	// Получаем копию спрайта для рисования
	sf::Sprite getSprite() const;
	// Обновляем монстров каждый кадр
	void update(sf::Time deltaTime, sf::Vector2f playerLocation, sf::Vector2f resolution);
	int getTypeMonster() const;
	
	};

