#pragma once
#include "Monster.h"
#include "Bullet.h"  

int createBackground(sf::VertexArray& rVA, sf::IntRect planet, int index);

int createHorde(int numMonster, std::deque<Monster>& monster, sf::Vector2i type, sf::IntRect planet, int complexity);

struct GameHubText          // ������� ���������
{
	float bar_x=0;          // ����� �����
	int score=0;			// ����
	int hiScore=0;			// ������
	int level=0;			// ������� ����
	int numMonsterAlive=0;	// ���������� ��������
	int complexity=1;		// ������� ��������� ����
	
	// ���� � ���������
	int bulletsSpare;
	// ������
	int bulletsInClip;
	
};			

struct GameBullet           // ���������� ��� ��������     
{
	// 100 ��������
	std::array<Bullet, 100> bullets;
	int currentBullet = 0;
	// ������������ ������ ������
	int clipSize=60;
	// �������� ��������
	Time lastPressed;
	// ������
	Sprite spriteCrosshair;
	Sprite spriteCrosshair1;
};

