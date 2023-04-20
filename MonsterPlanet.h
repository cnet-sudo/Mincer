#pragma once

#include "Monster.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena);

Monster* createHorde(int numMonster, sf::Vector2i type, sf::IntRect arena);