#include "GameEngine.h"

GameEngine::GameEngine()
{
	//  Загрузка иконки приложения
	if (!icon.loadFromFile("game.png")) exit(3); 
	window->setIcon(128, 128, icon.getPixelsPtr());
	// Hide the mouse pointer and replace it with crosshair
	window->setMouseCursorVisible(false);
	spriteCrosshair.setTexture(AssetManager::GetTexture("graphics/crosshair.png"));
	spriteCrosshair.setOrigin(25, 25);
	spriteCrosshair1.setTexture(AssetManager::GetTexture("graphics/crosshair1.png"));
	spriteCrosshair1.setOrigin(25, 25);
	
	// For the home/game over screen
	spriteGameOver.setTexture(AssetManager::GetTexture("graphics/back.jpg"));
	spriteGameOver.setPosition(0, 0);
	// Create a sprite for the ammo icon
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setPosition(100, 970);
	
	// Paused
	pausedText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");
	// Game Over
	gameOverText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to play");
	// LEVELING up
	levelUpText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increased rate of fire" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());
	
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

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			// Pause a game while playing
			if (event.key.code == sf::Keyboard::Return && state == State::playing)
			{
				state = State::paused;
			}
			// Restart while paused
			else 
			if (event.key.code == sf::Keyboard::Return && state == State::paused)
			{
				state = State::playing;
				// Reset the clock so there isn't a frame jump
				//clock.restart();
			}
			// Start a new game while in GAME_OVER state
			else 
			if (event.key.code == sf::Keyboard::Return &&	state == State::game_over)
			{
				state = State::leveling_up;
			}
			

			// Обработка события нажатия на клавишу Esc
			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 	window->close();

			if (state == State::leveling_up)
			{
				if (event.key.code == sf::Keyboard::Return )
				{
					restart();
					state = State::playing;
				}
			}
			// Handle WASD while playing
			if (state == State::playing)
			{
				// Reloading
				if (event.key.code == Keyboard::R)
				{
					if (bulletsSpare > 0)
					{
						if (bulletsInClip < clipSize)
						{
							if (bulletsSpare >= (clipSize - bulletsInClip)) 
							{
								int myammo = clipSize - bulletsInClip;
							bulletsInClip+= myammo;
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
				// Handle the pressing and releasing of the WASD keys
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					player.moveUp();
				}
				else
				{
					player.stopUp();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					player.moveDown();
				}
				else
				{
					player.stopDown();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					player.moveLeft();
				}
				else
				{
					player.stopLeft();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
						// Pass the centre of the player
						// and the centre of the cross-hair
						// to the shoot function
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
		}
		}
	}
}



void GameEngine::update(sf::Time const& deltaTime)
{
	if (state == State::playing)
	{
		// Update the total game time
		gameTimeTotal += deltaTime;
		// Where is the mouse pointer
		mouseScreenPosition = sf::Mouse::getPosition();
		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = window->mapPixelToCoords(sf::Mouse::getPosition(), mainView);
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
		healthPickup.update(deltaTime.asSeconds());
		ammoPickup.update(deltaTime.asSeconds());

		// Collision detection
// Have any zombies been shot?
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < numMonster; j++)
			{
				if (bullets[i].isInFlight() &&
					monster[j].isAlive())
				{
					if (bullets[i].getPosition().intersects
					(monster[j].getPosition()))
					{
						// Stop the bullet
						bullets[i].stop();
						// Register the hit and see if it was a kill
						if (monster[j].hit())
						{// Not just a hit but a kill too
							score += 10;
							if (score >= hiScore)
							{
								hiScore = score;
							}
							numMonsterAlive--;
							// When all the zombies are dead (again)
							if (numMonsterAlive == 0) {
								state = State::leveling_up;
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
					// More here later
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

		// Has the player touched health pickup
		if (player.getPosition().intersects
		(healthPickup.getPosition()) && healthPickup.isSpawned())
		{
			player.increaseHealthLevel(healthPickup.gotIt());
		}
		// Has the player touched ammo pickup
		if (player.getPosition().intersects
		(ammoPickup.getPosition()) && ammoPickup.isSpawned())
		{
			bulletsSpare += ammoPickup.gotIt();
		}

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
			waveNumberText.setString(L"Волна: "+ std::to_string(wave));
			// Update the high score text
			monsterRemainingText.setString(L"Монстры: "+ std::to_string(numMonsterAlive));
			framesSinceLastHUDUpdate = 0;
		}// End HUD update

	}// End updating the scene
}

void GameEngine::draw()
{
	sf::Vector2f minview;
	sf::Vector2f maxview;
	minview.x = player.getSprite().getPosition().x - resolution.x / 2;
	maxview.x = player.getSprite().getPosition().x + resolution.x / 2;
	minview.y = player.getSprite().getPosition().y - resolution.y / 2;
	maxview.y = player.getSprite().getPosition().y + resolution.y / 2;

	if (state == State::playing)
	{
		window->clear();
		// set the mainView to be displayed in the window
        // And draw everything related to it
		window->setView(mainView);
		// Draw the background
		window->draw(background, &AssetManager::GetTexture("graphics/plan.png"));
		
		// Draw the zombies
		for (int i = 0; i < numMonster; i++)
		{
			bool pass = true;
			if (!deadMonster.empty()) for (int j = 0; j < deadMonster.size();j++) if (i == deadMonster[j]) pass = false;
			
			if ((monster[i].isAlive() == false) && (pass)) 
			{
				window->draw(monster[i].getSprite());
				
				if (monster[i].getSprite().getPosition().x > maxview.x || monster[i].getSprite().getPosition().x < minview.x
					|| monster[i].getSprite().getPosition().y > maxview.y || monster[i].getSprite().getPosition().y < minview.y) 
				{
					deadMonster.push_back(i);
				}
			}
		}
		for (int i = 0; i < numMonster; i++)
		{
			if (monster[i].isAlive()) window->draw(monster[i].getSprite());
		}
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				window->draw(bullets[i].getShape());
			}
		}
		// Draw the player
		window->draw(player.getSprite());
		// Draw the pick-ups, if currently spawned
		if (ammoPickup.isSpawned())
		{
			window->draw(ammoPickup.getSprite());
		}
		if (healthPickup.isSpawned())
		{
			window->draw(healthPickup.getSprite());
		}
		// Draw the crosshair
		
		for (int j = 0; j < numMonster; j++)
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
		// Switch to the HUD view
		window->setView(hudView);
		// Draw all the HUD elements
		window->draw(spriteAmmoIcon);
		window->draw(ammoText);
		window->draw(scoreText);
		window->draw(hiScoreText);
		window->draw(healthBar);
		window->draw(healthBar1);
		window->draw(waveNumberText);
		window->draw(monsterRemainingText);
	}
	
	if (state == State::leveling_up)
	{
		window->draw(spriteGameOver);
		window->draw(levelUpText);
	}
	if (state == State::paused)
	{
		window->draw(pausedText);
	}
	if (state == State::game_over)
	{
		window->draw(spriteGameOver);
		window->draw(gameOverText);
		window->draw(scoreText);
		window->draw(hiScoreText);
	}
	window->display();
}

void GameEngine::restart()
{
	player.resetPlayerStats();
	score = 0;
	wave = 0;
	bulletsSpare = 50;
	bulletsInClip = 10;
	// Prepare the level
	// We will modify the next two lines later
	planet.width = 3000;
	planet.height = 3000;
	planet.left = 0;
	planet.top = 0;
	// Pass the vertex array by reference
	// to the createBackground function
	int tileSize = createBackground(background, planet);
	// Spawn the player in the middle of the arena
	player.spawn(planet, resolution, tileSize);
	// Configure the pick-ups
	healthPickup.setArena(planet);
	ammoPickup.setArena(planet);
	// Create a horde of zombies
	numMonster = 2;
	// Delete the previously allocated memory (if it exists)
	delete[] monster;
	monster = createHorde(numMonster, planet);
	numMonsterAlive = numMonster;
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

	delete [] monster;
}
