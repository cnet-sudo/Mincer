#include "GameEngine.h"

GameEngine::GameEngine()
{   
	// масштабирование
	if (m_resolution.x > 1920) m_scale_x = 1 * (m_resolution.x / 1920);
	else
		if (m_resolution.x < 1920) m_scale_x = 1 / (1920 / m_resolution.x);
		else m_scale_x = 1;

	if (m_resolution.y > 1080) m_scale_y = 1 * (m_resolution.y / 1080);
	else
		if (m_resolution.y < 1080) m_scale_y = 1 / (1080 / m_resolution.y);
		else m_scale_y = 1;
	
	// Загрузка
	state = State::game_load;
	gtext.scale(m_scale_x,m_scale_y);
	levelText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelText.setCharacterSize(40);
	levelText.setFillColor(sf::Color::Yellow);
	levelText.setString(L"Загрузка ...");
	levelText.setScale(m_scale_x, m_scale_y);
	levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height-30*m_scale_y);
	levels.start();
	window->draw(levelText);
	window->display();
	//-------------------------------------------
	levels.createLevels();
	std::vector<std::string> str{ "sound/level1.wav","sound/plasma.wav","sound/mobv.wav","sound/per.wav",
	"sound/mobb.wav","sound/hit1.wav","sound/bonus1.wav"};
	m_musik.create_sound(str);
	// загрузка иконки приложения
	if (!icon.loadFromFile("game.png")) window->close(); 
	window->setIcon(128, 128, icon.getPixelsPtr());
	// прячем курсор
	window->setMouseCursorVisible(false);
	
	spriteCrosshair.setTexture(AssetManager::GetTexture("graphics/crosshair.png"));
	spriteCrosshair.setOrigin(25, 25);
	spriteCrosshair.setScale(m_scale_x, m_scale_y);
	spriteCrosshair1.setTexture(AssetManager::GetTexture("graphics/crosshair1.png"));
	spriteCrosshair1.setOrigin(25, 25);
	spriteCrosshair1.setScale(m_scale_x, m_scale_y);
	// иконка патроны
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setScale(m_scale_x, m_scale_y);
	
	
	// Патроны
	ammoText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color(99,124,0));
	ammoText.setOutlineColor(Color::Yellow);
	ammoText.setOutlineThickness(1);
	ammoText.setScale(m_scale_x, m_scale_y);
	
	
	// Очки
	scoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color(99, 124, 0));
	scoreText.setOutlineColor(Color::Yellow);
	scoreText.setOutlineThickness(1);
	scoreText.setScale(m_scale_x, m_scale_y);
	

	// Загрузка рекорда
	std::ifstream inputFile("gamedata/scores.txt", std::ios::binary | std::ios::in);
	if (inputFile.is_open())
	{
		//Обновление переменной
		inputFile.read((char*)& hiScore, sizeof hiScore);
		inputFile.close();
	}


	// Рекорд
	hiScoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color(99, 124, 0));
	hiScoreText.setOutlineColor(Color::Yellow);
	hiScoreText.setOutlineThickness(1);
	hiScoreText.setScale(m_scale_x, m_scale_y);
	
	
	// Монстры
	monsterRemainingText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	monsterRemainingText.setCharacterSize(55);
	monsterRemainingText.setFillColor(sf::Color(99, 124, 0));
	monsterRemainingText.setOutlineColor(Color::Yellow);
	monsterRemainingText.setOutlineThickness(1);
	monsterRemainingText.setScale(m_scale_x, m_scale_y);
		
	// Номер волны
	levelNumberText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelNumberText.setCharacterSize(55);
	levelNumberText.setFillColor(sf::Color(99, 124, 0));
	levelNumberText.setOutlineColor(Color::Yellow);
	levelNumberText.setOutlineThickness(1);
	levelNumberText.setScale(m_scale_x, m_scale_y);
	
	// Помощь
	HelpText.setFont(AssetManager::GetFont("fonts/Helvetica.otf"));
	HelpText.setCharacterSize(20);
	HelpText.setFillColor(sf::Color(99, 124, 0));
	HelpText.setOutlineColor(Color::Yellow);
	HelpText.setOutlineThickness(1);
	HelpText.setScale(m_scale_x, m_scale_y);
			
	// Линия жизни
	healthBar.setOutlineColor(Color::Yellow);
	healthBar.setOutlineThickness(2);
	healthBar.setFillColor(Color::Red);
	healthBar.setScale(m_scale_x, m_scale_y);
	
	// Сосуд жизни 
	healthBar1.setOutlineColor(Color::Yellow);
	healthBar1.setOutlineThickness(5);
	healthBar1.setFillColor(sf::Color(0,0,0,0));
	healthBar1.setSize(Vector2f(800, 50));
	healthBar1.setScale(m_scale_x, m_scale_y);	
	restart();
}

void GameEngine::input()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			
			// Загрузка
			if (state == State::game_load)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					state = State::splash_screen;
					return;
				}

			}

			if (state == State::splash_screen)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					levels.stop_sound();
					state = State::level_up;
					return;
				}
			}



			if (state == State::level)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					state = State::playing;
				}
			}



			// Конец игры
			if (state == State::game_over)
			{
				if ((event.key.code == sf::Keyboard::Space) )
				{
					restart();
					state = State::level_up;
				}
			}
			
			if (state == State::game_victory)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					start_complexity();
					m_complexity++;
					state = State::level_up;
				}
			}

			if (state == State::paused)
			{
				if (event.key.code == sf::Keyboard::Pause)
				{
					state = State::playing;
					return;
				}
				
			}
			if (state == State::help)
			{
				if (event.key.code == sf::Keyboard::Tab)
				{
					state = State::playing;
					return;
				}
				
			}
			


			if ((event.key.code == sf::Keyboard::M)) {

				if (m_musik.play(0, true)) {
				
					m_musik.stop(0);
				};
			}

			// Выход из игры
			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 
			{
				saveHiScore();
				
				window->close();
			}
			if (state == State::transition)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					state = State::level_up;
					return;
				}
			}

			// Игра
			if (state == State::playing || state == State::transition)
			{
				
			// Игровая пауза
			if (event.key.code == sf::Keyboard::Pause && state != State::transition)
			{
				state = State::paused;
				return;
			}
			
			// Игровая пауза
			if (event.key.code == sf::Keyboard::Tab && state != State::transition)
			{
				state = State::help;
				return;
			}

			if (event.key.code == sf::Keyboard::Space)
			{
				mainView.setSize(1920,1080);
				return;
			}
			
				// Перезарядка
				if (event.key.code == Keyboard::R)
				{
					m_musik.play(3, false);
					recharge();	
				}
				// Перемещение
				
				if (event.key.code==sf::Keyboard::W)
				{
					player.move(Player::playermove::UpPressed);
				}
				
				if (event.key.code == sf::Keyboard::E)
				{
					player.move(Player::playermove::UpRg);
				}
				
				if (event.key.code == sf::Keyboard::C)
				{
					player.move(Player::playermove::DownRg);
					
				}
				
				if (event.key.code == sf::Keyboard::S)
				{
					player.move(Player::playermove::DownPressed);					
				}
				
				if (event.key.code == sf::Keyboard::Z)
				{
					player.move(Player::playermove::DownLf);
				}
				
				if (event.key.code == sf::Keyboard::Q)
				{
					player.move(Player::playermove::UpLf);
				}
				
				if (event.key.code == sf::Keyboard::A)
				{
					player.move(Player::playermove::LeftPressed);
					
				}
				
				if (event.key.code == sf::Keyboard::D)
				{
					player.move(Player::playermove::RightPressed);
				}
				
				if (event.key.code == sf::Keyboard::X)
				{
					player.move(Player::playermove::Stop);
				}

			} // Конец игры

			
		}

		// Масштаб
		if (state == State::playing || state == State::transition)
		{
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta < 0) {
					mainView.zoom(0.9f);
					if (mainView.getSize().x < 1280) mainView.setSize(1280, 720);
				}

				else if (event.mouseWheelScroll.delta > 0) {
					mainView.zoom(1.1f);
					if (mainView.getSize().x > 3840) mainView.setSize(3840, 2160);
				}

			}
		}

		
		
		if (state == State::playing || state == State::transition)
		{
				// стрельба
				if (Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 200 && bulletsInClip > 0)
					{
						m_musik.play(1, false);
						// Стрельба в прицел
						bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
						currentBullet++;
						if (currentBullet > bullets.size()-1)
						{
							currentBullet = 0;
						}
						lastPressed = gameTimeTotal;
						bulletsInClip--;
					}
				}// конец стрельбы

				if (Mouse::isButtonPressed(sf::Mouse::Right))
				{
					m_musik.play(3, false);
					recharge();
				}

		}
		
	}
}



void GameEngine::update(sf::Time const& deltaTime)
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> tis(1, 20);
	if (state == State::splash_screen)
	{
		levels.splash_SCR_update(deltaTime);
	}
	// Игровая сцена
	if (state == State::playing || state == State::transition)
	{
		// Обновление общего игрового времени
		gameTimeTotal += deltaTime;
		// Положение мышки
		mouseScreenPosition = sf::Mouse::getPosition();
		// Конвертируем положение мышки в мировые координаты окна mainView
		mouseWorldPosition = window->mapPixelToCoords(sf::Mouse::getPosition(), mainView);
		// Положение курсора
		spriteCrosshair.setPosition(mouseWorldPosition);
		spriteCrosshair1.setPosition(mouseWorldPosition);

		if (!player.getLive()) {
			state = State::game_over;

			gtext.genText("dead");
			
			saveHiScore();

		}

		// Обновление логики игрока
		player.update(deltaTime, sf::Mouse::getPosition());
		// Записываем положение игрока в переменную 
		sf::Vector2f playerPosition(player.getCenter());
		// Устанавливаем центр окна mainView, согласно положению игрока
		mainView.setCenter(player.getCenter());
		
		// Область видимости игрока
		sf::Vector2f minview;
		sf::Vector2f maxview;
		minview.x = player.getSprite().getPosition().x - m_resolution.x / 2;
		maxview.x = player.getSprite().getPosition().x + m_resolution.x / 2;
		minview.y = player.getSprite().getPosition().y - m_resolution.y / 2;
		maxview.y = player.getSprite().getPosition().y + m_resolution.y / 2;
		// обновление логики монстров
		for (int i = 0; i < monster.size(); i++)
		{
			if (monster[i].isAlive()){

				monster[i].update(deltaTime, playerPosition, m_resolution);
			}
			else
			{
				if (monster[i].getSprite().getPosition().x > maxview.x || monster[i].getSprite().getPosition().x < minview.x
					|| monster[i].getSprite().getPosition().y > maxview.y || monster[i].getSprite().getPosition().y < minview.y)
				{
					monster[i].novisible();
				}
			}
		}


		// обновление логики пуль
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isInFlight())
			{
				bullets[i].update(deltaTime.asSeconds());
			}
		}

		// обновление логики предметов
		if (!pickup.empty()) 
		{
			
			for (int i = 0; i < pickup.size(); i++) 
			{
				if (pickup[i].isSpawned()) 
				{
			pickup[i].update(deltaTime.asSeconds());
			// Подбор предметов
			if (player.getPosition().intersects(pickup[i].getPosition()))
			{
				m_musik.play(6, false);
				switch (pickup[i].getType())
				{
				case 1: {player.increaseHealthLevel(pickup[i].gotIt()); break;}
				case 2: {bulletsSpare += pickup[i].gotIt(); break;}
				case 3: {player.upgradeHealth(pickup[i].gotIt()); break; }
				case 4: {clipSize += pickup[i].gotIt(); break; }
				default:
					break;
				}

				}
				}
			}
			
			if (pickup.size()>20) 
			{
			std::vector<Pickup> tmp;
			for (int i = 0; i < pickup.size(); i++)
			{
				if (pickup[i].isSpawned()) tmp.emplace_back(pickup[i]);
			}
			pickup.clear();
			for (int i = 0; i < tmp.size(); i++)
			{
				pickup.emplace_back(tmp[i]);
			}
			tmp.clear();
			}
		}

		// проверка столкновения пули с монстром
		for (int i = 0; i < bullets.size(); i++)
		{
			for (int j = 0; j < monster.size(); j++)
			{
				if (bullets[i].isInFlight() &&	monster[j].isAlive())
				{
					if (bullets[i].getPosition().intersects
					(monster[j].getPosition()))
					{
						// остановить пулю
						bullets[i].stop();
						// отмечаем попадание в монстра
						if (monster[j].hit())
						{ // Монстр умирает
							if (monster[j].getTypeMonster() > 0 && monster[j].getTypeMonster() < 3) m_musik.play(2, false); else m_musik.play(4, false);
							score += 5*(monster[j].getTypeMonster()+1);
							int typ = tis(gen);
							if (typ<7 || typ==10 || typ == 15)
							{
								pickup.push_back(Pickup());
								pickup[pickup.size() - 1].spawn(monster[j].getSprite().getPosition(),typ);
							}
							if (score >= hiScore){

								hiScore = score;
							}
							numMonsterAlive--;
							// When all the zombies are dead (again)
							if (numMonsterAlive == 0) {
								state = State::transition;
							}
						}
					}
				}
			}
		}// конец проверки столкновения пули с монстром

		// столкновения монстра с игроком
		for (int i = 0; i < monster.size(); i++)
		{
			if (player.getPosition().intersects
			(monster[i].getPosition()) && monster[i].isAlive())
			{
				if (player.hit(gameTimeTotal))
				{
					m_musik.play(5, false);
				}
				
			}
		}// конец столкновения монстра с игроком
				
		
		    // линия жизни
			float koff = player.getMaxHealth() / 200;
		    healthBar.setSize(Vector2f((player.getHealth() * 4)/koff, 50));
		
			// текст обновления патронов
			ammoText.setString(std::to_string(bulletsInClip)+"/"+ std::to_string(bulletsSpare));
			// текст обновления очков
			scoreText.setString(L"Очки: " + std::to_string(score));
			// текст обновления рекорда
			hiScoreText.setString(L"Рекорд: "+std::to_string(hiScore));
			// текст обновления уровня
			levelNumberText.setString(L"Уровень: "+ std::to_string(level));
			// текст обновления текущего количества монстров
			monsterRemainingText.setString(L"Монстры: "+ std::to_string(numMonsterAlive));
			// сложность игры
			HelpText.setString(L"Помощь - < TAB >              Сложность: "+ std::to_string(m_complexity));

	}// Конец игровой сцены
	
	if (state == State::level_up)
	{
		level++;
		if (level > 5) {
			state = State::game_victory;
			gtext.genText("vic");
			saveHiScore();
		}
		else {
		newLevel();
	    state = State::level;
		}	
	}
}

void GameEngine::draw()
{
	if (state == State::playing || state == State::transition)
	{
		window->clear();
		// Игровое окно
		window->setView(mainView);
		// Фон
		window->draw(background, &AssetManager::GetTexture("graphics/plan.png"));
		// тела монстров
		for (int i = 0; i < monster.size(); i++) {
		if ((!monster[i].isAlive()) && (!monster[i].getnovisible()))  window->draw(monster[i].getSprite());
		}
				
		// Пикапы
		if (!pickup.empty())
		{
			for (int i = 0; i < pickup.size(); i++)
			{
				if (pickup[i].isSpawned())	window->draw(pickup[i].getSprite());

			}
		}

		// монстры
		for (int i = 0; i < monster.size(); i++){

			if (monster[i].isAlive() ) window->draw(monster[i].getSprite());
		}


		// пули
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isInFlight())
			{
				window->draw(bullets[i].getShape());
			}
		}
		// игрок
		player.draw(*window);
		// курсор
		for (int j = 0; j < monster.size(); j++)
		{
			if ((spriteCrosshair1.getGlobalBounds().intersects(monster[j].getPosition())) && (monster[j].isAlive()))
			{
				window->draw(spriteCrosshair1); break;
			}
			else
			{
				window->draw(spriteCrosshair);
			}
		}
		
		// Интерфейс
		window->setView(hudView);
		// Элементы интерфейса
		spriteAmmoIcon.setPosition(20 * m_scale_x, m_resolution.y - spriteAmmoIcon.getGlobalBounds().height - 40 * m_scale_y);
		window->draw(spriteAmmoIcon);
		ammoText.setPosition(30 * m_scale_x + spriteAmmoIcon.getGlobalBounds().width, m_resolution.y - ammoText.getGlobalBounds().height - 40 * m_scale_y);
		window->draw(ammoText);
		scoreText.setPosition(100 * m_scale_x, 20 * m_scale_y);
		window->draw(scoreText);
		hiScoreText.setPosition(m_resolution.x - 520 * m_scale_x, 20 * m_scale_y);
		window->draw(hiScoreText);
		healthBar.setPosition(m_resolution.x / 2 - healthBar1.getGlobalBounds().width / 2, m_resolution.y - 100 * m_scale_y);
		window->draw(healthBar);
		healthBar1.setPosition(m_resolution.x / 2 - healthBar1.getGlobalBounds().width / 2, m_resolution.y - 100 * m_scale_y);
		window->draw(healthBar1);
		levelNumberText.setPosition(m_resolution.x / 2 - levelNumberText.getGlobalBounds().width/2, 20 * m_scale_y);
		window->draw(levelNumberText);
		monsterRemainingText.setPosition(m_resolution.x - 520 * m_scale_x, m_resolution.y - monsterRemainingText.getGlobalBounds().height - 40* m_scale_y);
		window->draw(monsterRemainingText);
		HelpText.setPosition(m_resolution.x / 2 - HelpText.getGlobalBounds().width /2, m_resolution.y - 40 * m_scale_y);
		window->draw(HelpText);
		
	}
	if (state == State::game_load)
	{
		levelText.setString(L"для продолжения нажмите пробел ");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 30 * m_scale_y);
		levels.start();
		window->draw(levelText);		
	}
	if (state == State::splash_screen)
	{
		levels.splash_SCR_draw();
	}
	
	if (state == State::level)
	{
		window->clear();
		levelText.setString(L"для продолжения нажмите пробел ");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 30 * m_scale_y);
		window->draw(*levels.getSprite(level-1));
		window->draw(levelText);
	}

	if (state == State::paused)
	{
		levelText.setString(L"ПАУЗА");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y/2 - levelText.getGlobalBounds().height/2);
		window->draw(levelText);	
	}

	if (state == State::help)
	{
		levels.help();
	}

	if (state == State::transition)
	{
		levelText.setString(L"для продолжения нажмите пробел ");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y / 2 - levelText.getGlobalBounds().height / 2);
		window->draw(levelText);
	}
	if (state == State::game_over)
	{
		window->draw(*levels.getSprite(5));
		levelText.setString(L"для продолжения нажмите пробел ");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 30 * m_scale_y);
		window->draw(levelText);
		gtext.DrawText(*window, m_resolution.x, m_resolution.y);
		window->draw(scoreText);
		window->draw(hiScoreText);
	}

	if (state == State::game_victory)
	{
		window->draw(*levels.getSprite(6));
		levelText.setString(L"для продолжения нажмите пробел ");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 30 * m_scale_y);
		window->draw(levelText);
		gtext.DrawText(*window, m_resolution.x, m_resolution.y);
		window->draw(scoreText);
		window->draw(hiScoreText);
	}
		
	window->display();
}

void GameEngine::restart()
{
	player.resetPlayerStats();
	score = 0;
	level = 0;
	mainView.setSize(m_resolution.x, m_resolution.y);
	bulletsSpare = 300;
	bulletsInClip = 50;
	clipSize = 50;
	planet.left = 0;
	planet.top = 0;	

}

void GameEngine::start_complexity()
{
	level = 0;
	mainView.setSize(m_resolution.x, m_resolution.y);
	planet.left = 0;
	planet.top = 0;
}

void GameEngine::saveHiScore()
{
	std::ofstream outputFile("gamedata/scores.txt", std::ios::binary | std::ios::out);
	outputFile.write((char*)&hiScore, sizeof hiScore);
	outputFile.close();
}

void GameEngine::newLevel()
{   
	planet.width = 10000*level;
	planet.height = 10000*level;

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].isInFlight() == true) bullets[i].stop();
	}

	background.clear();
	monster.clear();
	pickup.clear();
	int tileSize = createBackground(background, planet,level);
	player.spawn(planet, m_resolution, tileSize);
	numMonsterAlive = createHorde(50*level, monster, sf::Vector2i(0, level-1), planet,m_complexity);
}

void GameEngine::recharge()
{
	if (bulletsSpare > 0)
	{
		if (bulletsInClip < clipSize)
		{
			if (bulletsSpare >= (clipSize - bulletsInClip))
			{
				int myammo = clipSize - bulletsInClip;
				bulletsInClip += myammo;
				bulletsSpare -= myammo;
			}
			else
			{
				bulletsInClip += bulletsSpare;
				bulletsSpare = 0;
			}
		}

	}
}



void GameEngine::run()
{
	// Объявление переменной часы
	sf::Clock clock;
	// Цикл работает пока окно открыто
	while (window->isOpen())
	{
		// Текущее время присваиваем переменной времени dt
		sf::Time dt = clock.restart();
		input();
		update(dt);
		draw();
	}

}
