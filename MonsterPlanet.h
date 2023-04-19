#pragma once

#include "Monster.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena);

Monster* createHorde(int numZombies, sf::IntRect arena);