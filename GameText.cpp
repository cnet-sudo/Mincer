#include "GameText.h"

GameText::GameText()
{
	m_text.setFont(AssetManager::GetFont("fonts/Helvetica.otf"));
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);
}

void GameText::DrawText(sf::RenderWindow & window, float resx, float resy) {
	
	m_text.setPosition(resx / 2 - m_text.getGlobalBounds().width / 2, resy / 2 - m_text.getGlobalBounds().height / 2);
	window.draw(m_text);
}

void GameText::genText(std::string str )
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> speed_plus(0, 5);

	if (str=="vic") m_text.setString(m_victoriqText[speed_plus(gen)]);

	if (str == "dead") m_text.setString(m_deadText[speed_plus(gen)]);
}


