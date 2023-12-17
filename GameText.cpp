#include "GameText.h"

GameText::GameText(sf::Vector2f m_resolution):m_resolution(m_resolution)
{
	// масштабирование
	if (m_resolution.x > 1920) m_scale.x = 1 * (m_resolution.x / 1920);
	else
		if (m_resolution.x < 1920) m_scale.x = 1 / (1920 / m_resolution.x);
		

	if (m_resolution.y > 1080) m_scale.y = 1 * (m_resolution.y / 1080);
	else
		if (m_resolution.y < 1080) m_scale.y = 1 / (1080 / m_resolution.y);
	
	// иконка патроны
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setScale(m_scale.x, m_scale.y);


	// Патроны
	ammoText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color(99, 124, 0));
	ammoText.setOutlineColor(sf::Color::Yellow);
	ammoText.setOutlineThickness(1);
	ammoText.setScale(m_scale.x, m_scale.y);


	// Очки
	scoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color(99, 124, 0));
	scoreText.setOutlineColor(sf::Color::Yellow);
	scoreText.setOutlineThickness(1);
	scoreText.setScale(m_scale.x, m_scale.y);

	// Рекорд
	hiScoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color(99, 124, 0));
	hiScoreText.setOutlineColor(sf::Color::Yellow);
	hiScoreText.setOutlineThickness(1);
	hiScoreText.setScale(m_scale.x, m_scale.y);


	// Монстры
	monsterRemainingText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	monsterRemainingText.setCharacterSize(55);
	monsterRemainingText.setFillColor(sf::Color(99, 124, 0));
	monsterRemainingText.setOutlineColor(sf::Color::Yellow);
	monsterRemainingText.setOutlineThickness(1);
	monsterRemainingText.setScale(m_scale.x, m_scale.y);

	// Номер волны
	levelNumberText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelNumberText.setCharacterSize(55);
	levelNumberText.setFillColor(sf::Color(99, 124, 0));
	levelNumberText.setOutlineColor(sf::Color::Yellow);
	levelNumberText.setOutlineThickness(1);
	levelNumberText.setScale(m_scale.x, m_scale.y);

	// Помощь
	HelpText.setFont(AssetManager::GetFont("fonts/Helvetica.otf"));
	HelpText.setCharacterSize(20);
	HelpText.setFillColor(sf::Color(99, 124, 0));
	HelpText.setOutlineColor(sf::Color::Yellow);
	HelpText.setOutlineThickness(1);
	HelpText.setScale(m_scale.x, m_scale.y);

	// Линия жизни
	healthBar.setOutlineColor(sf::Color::Yellow);
	healthBar.setOutlineThickness(2);
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setScale(m_scale.x, m_scale.y);

	// Сосуд жизни 
	healthBar1.setOutlineColor(sf::Color::Yellow);
	healthBar1.setOutlineThickness(5);
	healthBar1.setFillColor(sf::Color(0, 0, 0, 0));
	healthBar1.setSize(sf::Vector2f(800, 50));
	healthBar1.setScale(m_scale.x, m_scale.y);


	//<<<<<<<<<<<<<<<<< Начало <<<<<<<<<<<<<<<<<<<<<<<<<<
	levelText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelText.setCharacterSize(40);
	levelText.setFillColor(sf::Color::Yellow);
	levelText.setScale(m_scale.x, m_scale.y);
	
	m_text.setFont(AssetManager::GetFont("fonts/Helvetica.otf"));
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);

	//<<<<<<<<<<<<<<<<<< Конец <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}


void GameText::update(GameHubText Hub) {

	healthBar.setSize(sf::Vector2f(Hub.bar_x, 50));

	// текст обновления патронов
	ammoText.setString(std::format("{}/{}", Hub.bulletsInClip, Hub.bulletsSpare));
	// текст обновления очков
	scoreText.setString(std::format(L"Очки: {}", Hub.score));
	// текст обновления рекорда
	hiScoreText.setString(std::format(L"Рекорд: {}", Hub.hiScore));

	// текст обновления уровня
	levelNumberText.setString(std::format(L"Уровень: {}", Hub.level));
	// текст обновления текущего количества монстров
	monsterRemainingText.setString(std::format(L"Монстры: {}", Hub.numMonsterAlive));
	// сложность игры
	HelpText.setString(std::format(L"Помощь - < TAB >              Сложность: {}", Hub.complexity));
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

sf::Vector2f GameText::getScale()  // возвращает масштаб
{
	return m_scale;
}

//<<<<<<<<<<<<<<<<< Начало <<<<<<<<<<<<<<<<<<<<<<<<<<
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
		levelText.setString(L"Загрузка ...");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 100 * m_scale.y);
		 break;
	case 1: 
		levelText.setString(L"для продолжения нажмите пробел "); 
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 100 * m_scale.y);
		
		break;
	case 2:
		levelText.setString(L"ПАУЗА"); 
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y / 2 - levelText.getGlobalBounds().height / 2);
		 
		break;
	default:
		break;
	}
	
	window.draw(levelText);
}

//<<<<<<<<<<<<<<<<<< Конец <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



