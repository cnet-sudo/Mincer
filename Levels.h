#pragma once
#include"AssetManager.h"
#include<array>

class Levels
{

	std::array<sf::Sprite, 5> background;

	sf::Sprite* bkgr=nullptr;

public:

	Levels();

	sf::Sprite * getSprite(int index);
};

