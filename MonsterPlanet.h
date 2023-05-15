#pragma once

#include "Monster.h"


int createBackground(sf::VertexArray& rVA, sf::IntRect planet, int index);

int createHorde(int numMonster, std::deque<Monster>& monster, sf::Vector2i type, sf::IntRect planet, int complexity);

