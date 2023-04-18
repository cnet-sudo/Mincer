#pragma once

#include "Monster.h"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);

Monster* createHorde(int numZombies, IntRect arena);