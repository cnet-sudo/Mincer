#pragma once
#include <SFML/Graphics.hpp>
#include"AssetManager.h"
#include <random>

class Monster
{
private:
	// Насколько быстр каждый тип монстров?
	// How fast is each monster type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;
	// Насколько силён каждый тип монстров
	// How strong each monster type is
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;
	// Заставьте каждого монстра немного изменить свою скорость
	// Make each monster change its speed a little
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 100;
	// Где этот монстр?
	// Where is this monster?
	sf::Vector2f m_Position;
	// Спрайт для монстра
	// Sprite for the monster
	sf::Sprite m_Sprite;
	// Как быстро это может работать/сканировать?
	// How fast can this one run/crawl?
	float m_Speed;
	// Сколько у него здоровья?
	// How much health has it got?
	float m_Health;
	// Он еще жив?
	// Is it still alive?
	bool m_Alive;
public:
	// Обработка попадания пули в монстра
	// Handling a bullet hitting a monster
	bool hit();
	// Узнаем, жив ли монстр
	// Find out if the monster is alive
	bool isAlive();
	// Создаем нового монстра
	// Spawn a new monster
	void spawn(float startX, float startY, int type);
	// Возвращаем прямоугольник, который является позицией в мире
	// Return a rectangle that is the position in the world
	sf::FloatRect getPosition();
	// Получаем копию спрайта для рисования
	// Get a copy of the sprite to draw
	sf::Sprite getSprite();
	// Обновляем монстров каждый кадр
	// Update the monsters each frame
	void update(float elapsedTime, sf::Vector2f playerLocation);
};

