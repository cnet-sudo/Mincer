#include "GameEngine.h"

GameEngine::GameEngine()
{
	std::vector<std::string> str{ "sound/level1.wav","sound/plasma.wav","sound/mobv.wav","sound/per.wav",
	"sound/mobb.wav","sound/hit1.wav","sound/bonus1.wav"};
	m_musik.create_sound(str);
	//  Загрузка иконки приложения
	if (!icon.loadFromFile("game.png")) exit(3); 
	window.setIcon(128, 128, icon.getPixelsPtr());
	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(false);
	spriteCrosshair.setTexture(AssetManager::GetTexture("graphics/crosshair.png"));
	spriteCrosshair.setOrigin(25, 25);
	spriteCrosshair1.setTexture(AssetManager::GetTexture("graphics/crosshair1.png"));
	spriteCrosshair1.setOrigin(25, 25);
	
	// For the home/game over screen
	spriteGameOver.setTexture(AssetManager::GetTexture("graphics/back.jpg"));
	spriteGameOver.setPosition(0, 0);
	spriteGameBegin.setTexture(AssetManager::GetTexture("graphics/back2.jpg"));
	spriteGameBegin.setPosition(0, 0);
	// Create a sprite for the ammo icon
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setPosition(100, 970);
	
	// Paused
	pausedText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	pausedText.setCharacterSize(100);

	pausedText.setFillColor(sf::Color(99, 124, 0));
	pausedText.setOutlineColor(Color::Yellow);
	pausedText.setOutlineThickness(1);

	pausedText.setString(L"\t\tПАУЗА\nнажмите enter");
	pausedText.setPosition(resolution.x / 2 - pausedText.getGlobalBounds().width/2, resolution.y / 2 - pausedText.getGlobalBounds().height/2);
	
	// Game Over
	gameOverText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	gameOverText.setCharacterSize(80);
	gameOverText.setFillColor(sf::Color(99, 124, 0));
	gameOverText.setOutlineColor(Color::Yellow);
	gameOverText.setOutlineThickness(1);
	gameOverText.setString(L"Нажмите enter");
	gameOverText.setPosition(resolution.x / 2 - gameOverText.getGlobalBounds().width / 2, resolution.y - gameOverText.getGlobalBounds().height-50);
	// Следующая волна
	WaveUpText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	WaveUpText.setCharacterSize(70);
	WaveUpText.setFillColor(Color::Red);
	WaveUpText.setString(L"\t\t\tТревога!\n Следующая волна !");
	WaveUpText.setPosition(resolution.x/2- WaveUpText.getGlobalBounds().width/2, resolution.y / 2- WaveUpText.getGlobalBounds().height / 2);
	
	// Патроны
	ammoText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color(99,124,0));
	ammoText.setOutlineColor(Color::Yellow);
	ammoText.setOutlineThickness(1);
	ammoText.setPosition(200, 980);
	
	// Очки
	scoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color(99, 124, 0));
	scoreText.setOutlineColor(Color::Yellow);
	scoreText.setOutlineThickness(1);
	scoreText.setPosition(100, 20);

	// Загрузка рекорда
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		//Обновление переменной
		inputFile >> hiScore;
		inputFile.close();
	}
	// Рекорд
	hiScoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color(99, 124, 0));
	hiScoreText.setOutlineColor(Color::Yellow);
	hiScoreText.setOutlineThickness(1);
	hiScoreText.setPosition(1400, 20);
	
	// Монстры
	monsterRemainingText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	monsterRemainingText.setCharacterSize(55);
	monsterRemainingText.setFillColor(sf::Color(99, 124, 0));
	monsterRemainingText.setOutlineColor(Color::Yellow);
	monsterRemainingText.setOutlineThickness(1);
	monsterRemainingText.setPosition(1400, 980);
	
	// Номер волны
	waveNumberText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(sf::Color(99, 124, 0));
	waveNumberText.setOutlineColor(Color::Yellow);
	waveNumberText.setOutlineThickness(1);
	waveNumberText.setPosition(800, 20);
	
	// Линия жизни
	healthBar.setOutlineColor(Color::Yellow);
	healthBar.setOutlineThickness(2);
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(550, 980);
	// Сосуд жизни 
	healthBar1.setOutlineColor(Color::Yellow);
	healthBar1.setOutlineThickness(5);
	healthBar1.setFillColor(sf::Color(0,0,0,0));
	healthBar1.setPosition(550, 980);
	healthBar1.setSize(Vector2f(800, 50));
	restart();
}

void GameEngine::input()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			
			// Начало игры
			if (state == State::game_begin)
			{
				if ((event.key.code == sf::Keyboard::Return))
				{
					state = State::playing;
				}
			}

			// Конец игры
			if (state == State::game_over)
			{
				if ((event.key.code == sf::Keyboard::Return) )
				{
					restart();
					state = State::playing;
				}
			}
			
			if (state == State::paused)
			{
				if ((event.key.code == sf::Keyboard::Return))
				{
					state = State::playing;
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
				std::ofstream outFile("gamedata/scores.txt");
				if (outFile.is_open())
				{
					//Обновление переменной
					outFile << hiScore;
					outFile.close();
				}
				
				window.close();
			}
						

			// Игра
			if (state == State::playing)
			{

			// Игровая пауза
			if (event.key.code == sf::Keyboard::Pause)
			{
				state = State::paused;
			}
			 
			
				// Перезарядка
				if (event.key.code == Keyboard::R)
				{
					m_musik.play(3, false);
					recharge();	
				}
				// Перемещение
				if (event.key.code==sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
				{
					player.moveUp();
				}
				else
				{
					player.stopUp();
				}
				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
				{
					player.moveDown();
				}
				else
				{
					player.stopDown();
				}
				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
				{
					player.moveLeft();
				}
				else
				{
					player.stopLeft();
				}
				if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
				{
					player.moveRight();
				}
				else
				{
					player.stopRight();
				}
			} // End Handle WASD while playing

			
		}


		if (event.type == sf::Event::MouseButtonPressed)
		{
		
		if (state == State::playing)
		{
				// Fire a bullet
				if (Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 100 / fireRate && bulletsInClip > 0)
					{
						m_musik.play(1, false);
						// Стрельба в прицел
						bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
						currentBullet++;
						if (currentBullet > 99)
						{
							currentBullet = 0;
						}
						lastPressed = gameTimeTotal;
						bulletsInClip--;
					}
				}// End fire a bullet

				if (Mouse::isButtonPressed(sf::Mouse::Right))
				{
					m_musik.play(3, false);
					recharge();
				}

		}
		}
	}
}



void GameEngine::update(sf::Time const& deltaTime)
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> tis(1, 10);
	if (state == State::playing)
	{
		// Update the total game time
		gameTimeTotal += deltaTime;
		if (textWave) 
		{
			timewave += deltaTime;
			if (timewave.asSeconds() > 3) 
			{
				textWave = false; timewave = seconds(0);
			}
		}
		// Where is the mouse pointer
		mouseScreenPosition = sf::Mouse::getPosition();
		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);
		// Set the crosshair to the mouse world location
		spriteCrosshair.setPosition(mouseWorldPosition);
		spriteCrosshair1.setPosition(mouseWorldPosition);
		// Update the player
		player.update(deltaTime, sf::Mouse::getPosition());
		// Make a note of the players new position
		sf::Vector2f playerPosition(player.getCenter());
		// Make the view centre around the player
		mainView.setCenter(player.getCenter());

		for (int i = 0; i < numMonster; i++)
		{
			if (monster[i].isAlive())
			{
				monster[i].update(deltaTime, playerPosition);
			}
		}

		// Update any bullets that are in-flight
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				bullets[i].update(deltaTime.asSeconds());
			}
		}

		// Update the pickups
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
				default:
					break;
				}

				}
				}
			}
			if (pickup.size()>10) 
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

// Collision detection
// Have any zombies been shot?
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < numMonster; j++)
			{
				if (bullets[i].isInFlight() &&	monster[j].isAlive())
				{
					if (bullets[i].getPosition().intersects
					(monster[j].getPosition()))
					{
						// Stop the bullet
						bullets[i].stop();
						// Register the hit and see if it was a kill
						if (monster[j].hit())
						{ // Монстр умирает
							if (monster[j].getMonster() > 0 && monster[j].getMonster() < 3) m_musik.play(2, false); else m_musik.play(4, false);
							score += 10;
							int typ = tis(gen);
							if (typ<3) 
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
								state = State::wave_up;
							}
						}
					}
				}
			}
		}// End zombie being shot
		// Have any zombies touched the player
		for (int i = 0; i < numMonster; i++)
		{
			if (player.getPosition().intersects
			(monster[i].getPosition()) && monster[i].isAlive())
			{
				if (player.hit(gameTimeTotal))
				{
					m_musik.play(5, false);
				}
				if (player.getHealth() <= 0)
				{
					state = State::game_over;
					std::ofstream outputFile("gamedata/scores.txt");
					// << writes the data
					outputFile << hiScore;
					outputFile.close();
				}
			}
		}// End player touched

		// size up the health bar
		healthBar.setSize(Vector2f(player.getHealth() * 4, 50));
		// Increment the number of frames since the previous update
		framesSinceLastHUDUpdate++;
		// re-calculate every fpsMeasurementFrameInterval frames
		if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
		{
			// Update the ammo text
			ammoText.setString(std::to_string(bulletsInClip)+"/" + std::to_string(bulletsSpare));
			// Update the score text
			scoreText.setString(L"Очки: " + std::to_string(score));
			// Update the high score text
			hiScoreText.setString(L"Рекорд: "+std::to_string(hiScore));
			// Update the wave
			waveNumberText.setString(L"Уровень: "+ std::to_string(level));
			// Update the high score text
			monsterRemainingText.setString(L"Монстры: "+ std::to_string(numMonsterAlive));
			framesSinceLastHUDUpdate = 0;

		}// End HUD update

	}// End updating the scene
	
	if (state == State::wave_up)
	{
		level++;
		textWave = true;
		newLevel();
	    state = State::playing;	
	}
}

void GameEngine::draw()
{
	if (state == State::game_begin)
	{
		window.draw(spriteGameBegin);
	}

	sf::Vector2f minview;
	sf::Vector2f maxview;
	minview.x = player.getSprite().getPosition().x - resolution.x / 2;
	maxview.x = player.getSprite().getPosition().x + resolution.x / 2;
	minview.y = player.getSprite().getPosition().y - resolution.y / 2;
	maxview.y = player.getSprite().getPosition().y + resolution.y / 2;
	
	if (state == State::playing)
	{
		window.clear();
		// Игровое окно
		window.setView(mainView);
		// Фон
		window.draw(background, &AssetManager::GetTexture("graphics/plan.png"));
		// Пикапы
		if (!pickup.empty())
		{
			for (int i = 0; i < pickup.size(); i++)
			{
				if (pickup[i].isSpawned())	window.draw(pickup[i].getSprite());

			}
		}
		// Монстры
		for (int i = 0; i < numMonster; i++)
		{
			bool pass = true;
			if (!deadMonster.empty()) for (int j = 0; j < deadMonster.size();j++) if (i == deadMonster[j]) pass = false;
			
			if ((monster[i].isAlive() == false) && (pass)) 
			{
				window.draw(monster[i].getSprite());
				
				if (monster[i].getSprite().getPosition().x > maxview.x || monster[i].getSprite().getPosition().x < minview.x
					|| monster[i].getSprite().getPosition().y > maxview.y || monster[i].getSprite().getPosition().y < minview.y) 
				{
					deadMonster.push_back(i);
				}
			}
		}
		for (int i = 0; i < numMonster; i++)
		{
			if (monster[i].isAlive()) window.draw(monster[i].getSprite());
		}
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				window.draw(bullets[i].getShape());
			}
		}
		// Игрок
		window.draw(player.getSprite());
				
		// Курсор
		for (int j = 0; j < numMonster; j++)
		{
			if ((spriteCrosshair1.getGlobalBounds().intersects(monster[j].getPosition())) && (monster[j].isAlive()))
			{
				window.draw(spriteCrosshair1); break;
			}
			else
			{
				window.draw(spriteCrosshair);
			}
		}
		if (textWave)
		{
		window.draw(WaveUpText);
		}
		// Интерфейс
		window.setView(hudView);
		// Элементы интерфейса
		window.draw(spriteAmmoIcon);
		window.draw(ammoText);
		window.draw(scoreText);
		window.draw(hiScoreText);
		window.draw(healthBar);
		window.draw(healthBar1);
		window.draw(waveNumberText);
		window.draw(monsterRemainingText);
		
	}
	
	
	if (state == State::paused)
	{
		window.draw(pausedText);
	}
	
	if (state == State::game_over)
	{
		window.draw(spriteGameOver);
		window.draw(gameOverText);
		window.draw(scoreText);
		window.draw(hiScoreText);
	}
	
	
	window.display();
}

void GameEngine::restart()
{
	player.resetPlayerStats();
	score = 0;
	level = 1;
	bulletsSpare = 200;
	bulletsInClip = 50;
	// Prepare the level
	// We will modify the next two lines later
	planet.width = 10000;
	planet.height = 10000;
	planet.left = 0;
	planet.top = 0;
	// Pass the vertex array by reference
	// to the createBackground function
	int tileSize = createBackground(background, planet);
	// Spawn the player in the middle of the arena
	player.spawn(planet, resolution, tileSize);
	// Configure the pick-ups
	newLevel();
	numMonsterAlive = numMonster;
}

void GameEngine::newLevel()
{   
	delete[] monster;
	pickup.clear();
	switch (level)
	{
	case 1: 
	{   // Количество монстров
		numMonster = 100;
		// Delete the previously allocated memory (if it exists)
		
		monster = createHorde(numMonster, sf::Vector2i(0, 1), planet);
		numMonsterAlive = numMonster; 
		break; 
	}
	case 2:
	{   // Количество монстров
		numMonster = 150;
		// Delete the previously allocated memory (if it exists)
		
		monster = createHorde(numMonster, sf::Vector2i(0, 2), planet);
		numMonsterAlive = numMonster;
		break;
	}
	case 3:
	{   // Количество монстров
		numMonster = 200;
		// Delete the previously allocated memory (if it exists)
		
		monster = createHorde(numMonster, sf::Vector2i(1, 3), planet);
		numMonsterAlive = numMonster;
		break;
	}
	case 4:
	{   // Количество монстров
		numMonster = 250;
		// Delete the previously allocated memory (if it exists)
		
		monster = createHorde(numMonster, sf::Vector2i(2, 4), planet);
		numMonsterAlive = numMonster;
		break;
	}
	case 5:
	{   // Количество монстров
		numMonster = 300;
		// Delete the previously allocated memory (if it exists)
		
		monster = createHorde(numMonster, sf::Vector2i(3, 4), planet);
		numMonsterAlive = numMonster;
		break;
	}
	default:
		break;
	}
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
	while (window.isOpen())
	{
		// Текущее время присваиваем переменной времени dt
		sf::Time dt = clock.restart();
		input();
		update(dt);
		draw();
	}

	delete [] monster;
}
