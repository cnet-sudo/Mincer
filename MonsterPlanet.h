#pragma once

#include "Monster.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena);

void createHorde(int numMonster, std::deque<Monster> & monster, sf::Vector2i type, sf::IntRect arena);