#include "MonsterPlanet.h"
#include "Monster.h"
Monster* createHorde(int numMonster, sf::Vector2i type, sf::IntRect arena)
{
	// Will be used to obtain a seed for the random number engine
	// ����� �������������� ��� ��������� ���������� ����� ��� ��������� ��������� �����
	std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(rd());
	
	auto * zombies = new Monster[numMonster];
	
	auto max= sf::Vector2i(arena.width - 300, arena.height - 300);
	auto min= sf::Vector2i(arena.left + 300, arena.top + 300);
    std::uniform_int_distribution<> rside(0, 4);
	std::uniform_int_distribution<> rLR(min.x, max.x);
	std::uniform_int_distribution<> rTB(min.y, max.y);
	std::uniform_int_distribution<> rtype(type.x, type.y);
	for (int i = 0; i < numMonster; i++)
	{
		// Which side should the zombie spawn
		// � ����� ������� ������ ��������� �����
		
		int side = rside(gen);
		sf::Vector2f pos;

		switch (side)
		{
		case 0:
			// �����
			pos.x = static_cast<float>(rLR(gen));
			pos.y = static_cast<float>(min.y);
		break;
		case 1:
			// ������
			pos.x = static_cast<float>(rLR(gen));
			pos.y = static_cast<float>(max.y);
			break;
		case 2:
			// ����
			pos.x = static_cast<float>(min.x);
			pos.y = static_cast<float>(rTB(gen));
			break;
		case 3:
			// ���
			pos.x = static_cast<float>(max.x);
			pos.y = static_cast<float>(rTB(gen));
			break;
		case 4:
			// �����
			pos.x = static_cast<float>(rLR(gen));
			pos.y = static_cast<float>(rTB(gen));
			break;
		}
		// Bloater, crawler or runner
		int type = rtype(gen);
		// Spawn the new zombie into the array
		zombies[i].spawn(pos.x, pos.y, type);
	}
	return zombies;
}