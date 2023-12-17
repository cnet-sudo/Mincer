#include "GameText.h"

GameText::GameText(sf::Vector2f m_resolution):m_resolution(m_resolution)
{
	// ���������������
	if (m_resolution.x > 1920) m_scale.x = 1 * (m_resolution.x / 1920);
	else
		if (m_resolution.x < 1920) m_scale.x = 1 / (1920 / m_resolution.x);
		

	if (m_resolution.y > 1080) m_scale.y = 1 * (m_resolution.y / 1080);
	else
		if (m_resolution.y < 1080) m_scale.y = 1 / (1080 / m_resolution.y);
	
	// ������ �������
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setScale(m_scale.x, m_scale.y);


	// �������
	ammoText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color(99, 124, 0));
	ammoText.setOutlineColor(sf::Color::Yellow);
	ammoText.setOutlineThickness(1);
	ammoText.setScale(m_scale.x, m_scale.y);


	// ����
	scoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color(99, 124, 0));
	scoreText.setOutlineColor(sf::Color::Yellow);
	scoreText.setOutlineThickness(1);
	scoreText.setScale(m_scale.x, m_scale.y);

	// ������
	hiScoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color(99, 124, 0));
	hiScoreText.setOutlineColor(sf::Color::Yellow);
	hiScoreText.setOutlineThickness(1);
	hiScoreText.setScale(m_scale.x, m_scale.y);


	// �������
	monsterRemainingText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	monsterRemainingText.setCharacterSize(55);
	monsterRemainingText.setFillColor(sf::Color(99, 124, 0));
	monsterRemainingText.setOutlineColor(sf::Color::Yellow);
	monsterRemainingText.setOutlineThickness(1);
	monsterRemainingText.setScale(m_scale.x, m_scale.y);

	// ����� �����
	levelNumberText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelNumberText.setCharacterSize(55);
	levelNumberText.setFillColor(sf::Color(99, 124, 0));
	levelNumberText.setOutlineColor(sf::Color::Yellow);
	levelNumberText.setOutlineThickness(1);
	levelNumberText.setScale(m_scale.x, m_scale.y);

	// ������
	HelpText.setFont(AssetManager::GetFont("fonts/Helvetica.otf"));
	HelpText.setCharacterSize(20);
	HelpText.setFillColor(sf::Color(99, 124, 0));
	HelpText.setOutlineColor(sf::Color::Yellow);
	HelpText.setOutlineThickness(1);
	HelpText.setScale(m_scale.x, m_scale.y);

	// ����� �����
	healthBar.setOutlineColor(sf::Color::Yellow);
	healthBar.setOutlineThickness(2);
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setScale(m_scale.x, m_scale.y);

	// ����� ����� 
	healthBar1.setOutlineColor(sf::Color::Yellow);
	healthBar1.setOutlineThickness(5);
	healthBar1.setFillColor(sf::Color(0, 0, 0, 0));
	healthBar1.setSize(sf::Vector2f(800, 50));
	healthBar1.setScale(m_scale.x, m_scale.y);


	//<<<<<<<<<<<<<<<<< ������ <<<<<<<<<<<<<<<<<<<<<<<<<<
	levelText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelText.setCharacterSize(40);
	levelText.setFillColor(sf::Color::Yellow);
	levelText.setScale(m_scale.x, m_scale.y);
	
	m_text.setFont(AssetManager::GetFont("fonts/Helvetica.otf"));
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);

	//<<<<<<<<<<<<<<<<<< ����� <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}


void GameText::update(GameHubText Hub) {

	healthBar.setSize(sf::Vector2f(Hub.bar_x, 50));

	// ����� ���������� ��������
	ammoText.setString(std::format("{}/{}", Hub.bulletsInClip, Hub.bulletsSpare));
	// ����� ���������� �����
	scoreText.setString(std::format(L"����: {}", Hub.score));
	// ����� ���������� �������
	hiScoreText.setString(std::format(L"������: {}", Hub.hiScore));

	// ����� ���������� ������
	levelNumberText.setString(std::format(L"�������: {}", Hub.level));
	// ����� ���������� �������� ���������� ��������
	monsterRemainingText.setString(std::format(L"�������: {}", Hub.numMonsterAlive));
	// ��������� ����
	HelpText.setString(std::format(L"������ - < TAB >              ���������: {}", Hub.complexity));
}

void GameText::draw(sf::RenderWindow& window)
{
	spriteAmmoIcon.setPosition(20 * m_scale.x, m_resolution.y - spriteAmmoIcon.getGlobalBounds().height - 40 * m_scale.y);
	window.draw(spriteAmmoIcon);
	ammoText.setPosition(30 * m_scale.x + spriteAmmoIcon.getGlobalBounds().width, m_resolution.y - ammoText.getGlobalBounds().height - 40 * m_scale.y);
	window.draw(ammoText);
	scoreText.setPosition(100 * m_scale.x, 20 * m_scale.y);
	window.draw(scoreText);
	hiScoreText.setPosition(m_resolution.x - 520 * m_scale.x, 20 * m_scale.y);
	window.draw(hiScoreText);
	healthBar.setPosition(m_resolution.x / 2 - healthBar1.getGlobalBounds().width / 2, m_resolution.y - 100 * m_scale.y);
	window.draw(healthBar);
	healthBar1.setPosition(m_resolution.x / 2 - healthBar1.getGlobalBounds().width / 2, m_resolution.y - 100 * m_scale.y);
	window.draw(healthBar1);
	levelNumberText.setPosition(m_resolution.x / 2 - levelNumberText.getGlobalBounds().width / 2, 20 * m_scale.y);
	window.draw(levelNumberText);
	monsterRemainingText.setPosition(m_resolution.x - 520 * m_scale.x, m_resolution.y - monsterRemainingText.getGlobalBounds().height - 40 * m_scale.y);
	window.draw(monsterRemainingText);
	HelpText.setPosition(m_resolution.x / 2 - HelpText.getGlobalBounds().width / 2, m_resolution.y - 40 * m_scale.y);
	window.draw(HelpText);
}

sf::Vector2f GameText::getScale()  // ���������� �������
{
	return m_scale;
}

//<<<<<<<<<<<<<<<<< ������ <<<<<<<<<<<<<<<<<<<<<<<<<<
void GameText::drawText(sf::RenderWindow& window) {

	m_text.setPosition(m_resolution.x / 2 - m_text.getGlobalBounds().width / 2, m_resolution.y / 2 - m_text.getGlobalBounds().height / 2);
	window.draw(m_text);
}

void GameText::genText(std::string str)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> speed_plus(0, 5);

	if (str == "vic") m_text.setString(m_victoriqText[speed_plus(gen)]);

	if (str == "dead") m_text.setString(m_deadText[speed_plus(gen)]);
}

void GameText::drawGameOver(sf::RenderWindow& window)
{
	scoreText.setPosition(100 * m_scale.x, 20 * m_scale.y);
	window.draw(scoreText);
	hiScoreText.setPosition(m_resolution.x - 520 * m_scale.x, 20 * m_scale.y);
	window.draw(hiScoreText);
}

void GameText::drawAssistant(sf::RenderWindow& window, int num)
{
	switch (num)
	{
	case 0: 
		levelText.setString(L"�������� ...");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 100 * m_scale.y);
		 break;
	case 1: 
		levelText.setString(L"��� ����������� ������� ������ "); 
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 100 * m_scale.y);
		
		break;
	case 2:
		levelText.setString(L"�����"); 
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y / 2 - levelText.getGlobalBounds().height / 2);
		 
		break;
	default:
		break;
	}
	
	window.draw(levelText);
}

//<<<<<<<<<<<<<<<<<< ����� <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



