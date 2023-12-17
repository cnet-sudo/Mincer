#pragma once
#include "Monster.h"
#include "Bullet.h"  

int createBackground(sf::VertexArray& rVA, sf::IntRect planet, int index);

int createHorde(int numMonster, std::deque<Monster>& monster, sf::Vector2i type, sf::IntRect planet, int complexity);

struct GameHubText          // игровой интерфейс
{
	float bar_x=0;          // линия жизни
	int score=0;			// очки
	int hiScore=0;			// рекорд
	int level=0;			// уровень игры
	int numMonsterAlive=0;	// количество монстров
	int complexity=1;		// уровень сложности игры
	
	// Ящик с патронами
	int bulletsSpare;
	// Обойма
	int bulletsInClip;
	
};			

struct GameBullet           // переменные для стрельбы     
{
	// 100 патронов
	std::array<Bullet, 100> bullets;
	int currentBullet = 0;
	// Максимальный размер обоймы
	int clipSize=60;
	// интервал стрельбы
	Time lastPressed;
	// Прицел
	Sprite spriteCrosshair;
	Sprite spriteCrosshair1;
};

