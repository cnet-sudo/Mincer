#pragma once
#include"Animator.h"
#include <random>
#include <deque>
#include <array>

class Monster
{
private:
	// сложность игры
	int m_complexity = 0;
	// координаты монстров
	sf::Vector2f m_Position;
	// спрайт для монстра
	sf::Sprite m_Sprite;
	// анимация монтстра
	Animator m_AnimPlayer = Animator(m_Sprite);
	// скорость монстра
	float m_Speed;
	// жизнь монстра
	float m_Health;
	// состояние жив - мёртв
	bool m_Alive = true;
	// видно на карте труп или нет
	bool m_novisible = false;
	// тип монстра
	int m_Type;
	// интервал перемещения моба
	sf::Time m_moveTime;

	public:

	Monster();
	// обработка попадания пули в моба
	bool hit();
	// узнаем, жив ли монстр
	bool isAlive();
	// виден монстр или нет
	bool getnovisible();
	// изменение видимости монстра
	void novisible();
	// создаем нового монстра
	void spawn(float startX, float startY, int type, int complexity);
	// возвращаем прямоугольник, который является позицией в мире
	sf::FloatRect getPosition();
	// получаем копию спрайта для рисования
	sf::Sprite getSprite() const;
	// обновляем монстров каждый кадр
	void update(sf::Time deltaTime, sf::Vector2f playerLocation, sf::Vector2f resolution);
	// возвращает тип монстра
	int getTypeMonster() const;
	
	};

