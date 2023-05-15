#pragma once
#include <SFML/Graphics.hpp>
#include"Animator.h"
#include <random>
#include <deque>
#include <array>

class Monster
{
private:
	// сложность
	int m_complexity = 0;
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
	// Тип монстра
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
	void spawn(float startX, float startY, int type, int complexity);
	// Возвращаем прямоугольник, который является позицией в мире
	sf::FloatRect getPosition();
	// Получаем копию спрайта для рисования
	sf::Sprite getSprite() const;
	// Обновляем монстров каждый кадр
	void update(sf::Time deltaTime, sf::Vector2f playerLocation, sf::Vector2f resolution);
	int getTypeMonster() const;
	
	};

