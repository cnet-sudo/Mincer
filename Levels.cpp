#include "Levels.h"

Levels::Levels()
{
	std::array<std::string, 8> str{"graphics/level1.jpg", "graphics/level2.jpg", "graphics/level3.jpg", 
		"graphics/level4.jpg", "graphics/level5.jpg","graphics/back2.jpg","graphics/game_over.jpg","graphics/level6.jpg"};
	
	
	for (int i = 0; i < background.size(); i++)
	{
		background[i].setTexture(AssetManager::GetTexture(str[i]));
	}


}

sf::Sprite* Levels::getSprite(int index)
{
	bkgr = & background[index];		
	return bkgr;
}
