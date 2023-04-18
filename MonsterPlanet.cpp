#include "MonsterPlanet.h"
#include "Monster.h"
Monster* createHorde(int numZombies, IntRect arena)
{
	// Will be used to obtain a seed for the random number engine
	// Ѕудет использоватьс€ дл€ получени€ начального числа дл€ механизма случайных чисел
	std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(rd());
	
	auto * zombies = new Monster[numZombies];
	
	auto max= sf::Vector2i(arena.width - 20, arena.height - 20);
	auto min= sf::Vector2i(arena.left + 20, arena.top + 20);
    std::uniform_int_distribution<> rside(0, 4);
	std::uniform_int_distribution<> rLR(min.y, max.y);
	std::uniform_int_distribution<> rTB(min.x, max.x);
	std::uniform_int_distribution<> rtype(0, 3);
	for (int i = 0; i < numZombies; i++)
	{
		// Which side should the zombie spawn
		// — какой стороны должен по€витьс€ зомби
		
		int side = rside(gen);
		sf::Vector2f pos;

		switch (side)
		{
		case 0:
			// left
			// слева
			pos.x = static_cast<float>(min.x);
			pos.y = static_cast<float>(rLR(gen));
			break;
		case 1:
			// right
			// справа
			pos.x = static_cast<float>(max.x);
			pos.y = static_cast<float>(rLR(gen));
			break;
		case 2:
			// top
			// верх
			pos.x = static_cast<float>(rTB(gen));
			pos.y = static_cast<float>(min.y);
			break;
		case 3:
			// bottom
			// низ
			pos.x = static_cast<float>(rTB(gen));
			pos.y = static_cast<float>(max.y);
			break;
		}
		// Bloater, crawler or runner
		int type = rtype(gen);
		// Spawn the new zombie into the array
		zombies[i].spawn(pos.x, pos.y, type);
	}
	return zombies;
}