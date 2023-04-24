#include "MonsterPlanet.h"
#include "Monster.h"
Monster* createHorde(int numMonster, sf::Vector2i type, sf::IntRect arena)
{
	// Will be used to obtain a seed for the random number engine
	// Ѕудет использоватьс€ дл€ получени€ начального числа дл€ механизма случайных чисел
	std::random_device rd;
	// Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(rd());
	
	auto * monster = new Monster[numMonster];
	auto max= sf::Vector2i(arena.width - 300, arena.height - 300);
	auto min= sf::Vector2i(arena.left + 300, arena.top + 300);
    //std::uniform_int_distribution<> rside(0, 4);
	std::uniform_int_distribution<> rLR(min.x, max.x);
	std::uniform_int_distribution<> rTB(min.y, max.y);
	std::uniform_int_distribution<> rtype(type.x, type.y);

	bool collis;

	for (int i = 0; i < numMonster; i++){
		int type = rtype(gen);
		do {
			// — какой стороны должен по€витьс€ зомби
			sf::Vector2f pos;
			collis = false;
			//int side = rside(gen);
		/*
			switch (side)
			{
			case 0:
				// слева
				pos.x = static_cast<float>(rLR(gen));
				pos.y = static_cast<float>(min.y);
				break;
			case 1:
				// справа
				pos.x = static_cast<float>(rLR(gen));
				pos.y = static_cast<float>(max.y);
				break;
			case 2:
				// верх
				pos.x = static_cast<float>(min.x);
				pos.y = static_cast<float>(rTB(gen));
				break;
			case 3:
				// низ
				pos.x = static_cast<float>(max.x);
				pos.y = static_cast<float>(rTB(gen));
				break;
			case 4:
				// везде
				pos.x = static_cast<float>(rLR(gen));
				pos.y = static_cast<float>(rTB(gen));
				break;
			}
         */
			
			// Bloater, crawler or runner
			
			// Spawn the new zombie into the array
			pos.x = static_cast<float>(rLR(gen));
			pos.y = static_cast<float>(rTB(gen));
			monster[i].spawn(pos.x, pos.y, type);


			for (int j = 0; j < i; j++)
			{
				if (monster[i].getPosition().intersects(monster[j].getPosition())) collis = true;
			}
		} while (collis);

	}
	return monster;
}