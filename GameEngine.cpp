#include "GameEngine.h"

GameEngine::GameEngine():resolution(sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width), 
static_cast<float>(sf::VideoMode::getDesktopMode().height)))
{
	//  �������� ������ ����������
	if (!icon.loadFromFile("game.png")) exit(3); 
	window->setIcon(128, 128, icon.getPixelsPtr());
	// Hide the mouse pointer and replace it with crosshair
	window->setMouseCursorVisible(false);
	spriteCrosshair.setTexture(AssetManager::GetTexture("graphics/crosshair.png"));
	spriteCrosshair.setOrigin(25, 25);

	
	// For the home/game over screen
	spriteGameOver.setTexture(AssetManager::GetTexture("graphics/back.jpg"));
	spriteGameOver.setPosition(0, 0);
	// Create a sprite for the ammo icon
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setPosition(20, 980);
	
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
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());
	// Ammo
	ammoText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);
	// Score
	scoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		// >> Reads the data
		inputFile >> hiScore;
		inputFile.close();
	}
	// Hi Score
	hiScoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());
	// Zombies remaining
	zombiesRemainingText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1500, 980);
	zombiesRemainingText.setString("Zombies: 100");
	// Wave number
	waveNumberText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(1250, 980);
	waveNumberText.setString("Wave: 0");
	// Health bar
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);

	// Debug HUD
	
	debugText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	debugText.setCharacterSize(25);
	debugText.setFillColor(Color::White);
	debugText.setPosition(20, 220);
	
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
			if (event.key.code == sf::Keyboard::Return &&
				state == State::playing)
			{
				state = State::paused;
			}
			// Restart while paused
			else if (event.key.code == sf::Keyboard::Return &&
				state == State::paused)
			{
				state = State::playing;
				// Reset the clock so there isn't a frame jump
				//clock.restart();
			}
			// Start a new game while in GAME_OVER state
			else if (event.key.code == sf::Keyboard::Return &&
				state == State::game_over)
			{
				state = State::leveling_up;
			}
			if (state == State::playing)
			{
			}

			// ��������� ������� ������� �� ������� Esc
			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 	window->close();

			// Handle WASD while playing
			if (state == State::playing)
			{
				// Reloading
				if (event.key.code == Keyboard::R)
				{
					if (bulletsSpare >= clipSize)
					{
						// Plenty of bullets. Reload.
						bulletsInClip = clipSize;
						bulletsSpare -= clipSize;
					}
					else if (bulletsSpare > 0)
					{
						// Only few bullets left
						bulletsInClip = bulletsSpare;
						bulletsSpare = 0;
					}
					else
					{
						// More here soon?!
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

				// Fire a bullet
				if (Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (gameTimeTotal.asMilliseconds()- lastPressed.asMilliseconds()> 100 / fireRate && bulletsInClip > 0)
					{
						// Pass the centre of the player
						// and the centre of the cross-hair
						// to the shoot function
						bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y,mouseWorldPosition.x, mouseWorldPosition.y);
						currentBullet++;
						if (currentBullet > 99)
						{
							currentBullet = 0;
						}
						lastPressed = gameTimeTotal;
						bulletsInClip--;
					}
				}// End fire a bullet

			} // End Handle WASD while playing
								

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
		healthBar.setSize(Vector2f(player.getHealth() * 3, 50));
		// Increment the number of frames since the previous update
		framesSinceLastHUDUpdate++;
		// re-calculate every fpsMeasurementFrameInterval frames
		if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
		{
			// Update game HUD text
			std::stringstream ssAmmo;
			std::stringstream ssScore;
			std::stringstream ssHiScore;
			std::stringstream ssWave;
			std::stringstream ssZombiesAlive;
			// Update the ammo text
			ssAmmo << bulletsInClip << "/" << bulletsSpare;
			ammoText.setString(ssAmmo.str());
			// Update the score text
			ssScore << "Score:" << score;
			scoreText.setString(ssScore.str());
			// Update the high score text
			ssHiScore << "Hi Score:" << hiScore;
			hiScoreText.setString(ssHiScore.str());
			// Update the wave
			ssWave << "Wave:" << wave;
			waveNumberText.setString(ssWave.str());
			// Update the high score text
			ssZombiesAlive << "Zombies:" << numMonsterAlive;
			zombiesRemainingText.setString(ssZombiesAlive.str());
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
			if (monster[i].isAlive() != true) 
			{
				window->draw(monster[i].getSprite());
				if (monster[i].getSprite().getPosition().x > maxview.x || monster[i].getSprite().getPosition().x < minview.x
					|| monster[i].getSprite().getPosition().y > maxview.y || monster[i].getSprite().getPosition().y < minview.y) 
				{}
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
		window->draw(spriteCrosshair);

		// Switch to the HUD view
		window->setView(hudView);
		// Draw all the HUD elements
		window->draw(spriteAmmoIcon);
		window->draw(ammoText);
		window->draw(scoreText);
		window->draw(hiScoreText);
		window->draw(healthBar);
		window->draw(waveNumberText);
		window->draw(zombiesRemainingText);
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
	// Prepare the level
	// We will modify the next two lines later
	planet.width = 5000;
	planet.height = 5000;
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
	numMonster = 50;
	// Delete the previously allocated memory (if it exists)
	delete[] monster;
	monster = createHorde(numMonster, planet);
	numMonsterAlive = numMonster;
}



void GameEngine::run()
{
	// ���������� ���������� ����
	sf::Clock clock;
	// ���� �������� ���� ���� �������
	while (window->isOpen())
	{
		// ������� ����� ����������� ���������� ������� dt
		sf::Time dt = clock.restart();
		input();
		update(dt);
		draw();
	}

	delete[] monster;
}
