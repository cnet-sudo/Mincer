#include "GameEngine.h"

GameEngine::GameEngine():resolution(sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width), 
static_cast<float>(sf::VideoMode::getDesktopMode().height)))
{
	//  Загрузка иконки приложения
	if (!icon.loadFromFile("game.png")) exit(3); 
	window->setIcon(128, 128, icon.getPixelsPtr());
	textureBackground.loadFromFile("graphics/plan.png");
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

			// Обработка события нажатия на клавишу Esc
			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 	window->close();

			// Handle WASD while playing
			if (state == State::playing)
			{
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
		// Update the player
		player.update(deltaTime, sf::Mouse::getPosition());
		// Make a note of the players new position
		sf::Vector2f playerPosition(player.getCenter());
		// Make the view centre around the player
		mainView.setCenter(player.getCenter());
	}// End updating the scene
}

void GameEngine::draw()
{
	if (state == State::playing)
	{
		window->clear();
		// set the mainView to be displayed in the window
        // And draw everything related to it
		window->setView(mainView);
		// Draw the background
		window->draw(background, &textureBackground);
		// Draw the player
		window->draw(player.getSprite());
	}
	if (state == State::leveling_up)
	{
	}
	if (state == State::paused)
	{
	}
	if (state == State::game_over)
	{
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
	// Reset the clock so there isn't a frame jump
	//clock.restart();
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
