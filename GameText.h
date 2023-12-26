#pragma once

#include<array>
#include<random>
#include<format>
#include"MonsterPlanet.h"
#include"AssetManager.h"
#include <fstream>    

class GameText
{
	//масштаб
	sf::Vector2f  m_scale{1,1};   

	sf::Vector2f m_resolution;

	// патроны в интерфейсе
	sf::Sprite spriteAmmoIcon;

	// текст
	sf::Text levelText;
	sf::Text ammoText;
	sf::Text scoreText;
	sf::Text hiScoreText;
	sf::Text monsterRemainingText;
	sf::Text levelNumberText;
	sf::Text HelpText;

	// линия жизни
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBar1;

	std::array<sf::String, 6> m_deadText{L"Никогда не давай страху поражения удержать тебя от игры",L"Когда мне тяжело, я всегда напоминаю себе о том,\n\t что если я сдамся – лучше не станет"
	,L"Мы никогда не потерпим поражения,\n пока душа готова побеждать ...",L"Успеха часто добиваются те, кто не подозревает\n\t\t о неизбежности поражения",
		L"Я могу принять поражение, но я не могу принять\n\t\t\t отсутствие попыток",L"Никакая победа не принесет столько, \nсколько может отнять одно поражение"
	};

	std::array<sf::String, 6> m_victoriqText{ L"Победа над другими даёт силу,\n победа над собой — бесстрашие",L"Величайшая победа —\n победа над самим собой",
		L"В жизни есть более важные вещи,\n\t чем победа и поражение",L"Тактика победителя — убедить врага в том,\n\t\t что он делает всё правильно",
		L"У победителя много друзей, и лишь\n у побежденного они настоящие",L"Пришел, увидел, победил."
	};

	sf::Text m_text;	
	
public:

	explicit GameText(sf::Vector2f m_resolution);

	void update(GameHubText Hub);

	void draw(sf::RenderWindow& window);

	sf::Vector2f getScale(); // возвращает масштаб

	void drawText(sf::RenderWindow& window);

	void genText(std::string str);

	void drawGameOver(sf::RenderWindow& window);

	void drawAssistant(sf::RenderWindow& window, int num);

};

