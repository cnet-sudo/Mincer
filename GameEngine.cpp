#include "GameEngine.h"

GameEngine::GameEngine()
{   
	// ��������
	state = State::game_load;
	spriteGameBegin.setTexture(AssetManager::GetTexture("graphics/back2.jpg"));
	spriteGameBegin.setPosition(0, 0);
	
	levelText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelText.setCharacterSize(40);
	levelText.setFillColor(sf::Color::White);
	levelText.setString(L"�������� ...");
	levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height-50);
	window.draw(spriteGameBegin);
	window.draw(levelText);
	window.display();
	//-------------------------------------------
	std::vector<std::string> str{ "sound/level1.wav","sound/plasma.wav","sound/mobv.wav","sound/per.wav",
	"sound/mobb.wav","sound/hit1.wav","sound/bonus1.wav"};
	m_musik.create_sound(str);
	// �������� ������ ����������
	if (!icon.loadFromFile("game.png")) exit(3); 
	window.setIcon(128, 128, icon.getPixelsPtr());
	// ������ ������
	window.setMouseCursorVisible(false);
	spriteCrosshair.setTexture(AssetManager::GetTexture("graphics/crosshair.png"));
	spriteCrosshair.setOrigin(25, 25);
	spriteCrosshair1.setTexture(AssetManager::GetTexture("graphics/crosshair1.png"));
	spriteCrosshair1.setOrigin(25, 25);
	
	// �������� ����� ����
	spriteGameOver.setTexture(AssetManager::GetTexture("graphics/game_over.jpg"));
	spriteGameOver.setPosition(0, 0);
	
	// ������ �������
	spriteAmmoIcon.setTexture(AssetManager::GetTexture("graphics/ammo.png"));
	spriteAmmoIcon.setPosition(100, 970);
	
	// �������
	ammoText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color(99,124,0));
	ammoText.setOutlineColor(Color::Yellow);
	ammoText.setOutlineThickness(1);
	ammoText.setPosition(200, 980);
	
	// ����
	scoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color(99, 124, 0));
	scoreText.setOutlineColor(Color::Yellow);
	scoreText.setOutlineThickness(1);
	scoreText.setPosition(100, 20);

	// �������� �������
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		//���������� ����������
		inputFile >> hiScore;
		inputFile.close();
	}
	// ������
	hiScoreText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color(99, 124, 0));
	hiScoreText.setOutlineColor(Color::Yellow);
	hiScoreText.setOutlineThickness(1);
	hiScoreText.setPosition(1400, 20);
	
	// �������
	monsterRemainingText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	monsterRemainingText.setCharacterSize(55);
	monsterRemainingText.setFillColor(sf::Color(99, 124, 0));
	monsterRemainingText.setOutlineColor(Color::Yellow);
	monsterRemainingText.setOutlineThickness(1);
	monsterRemainingText.setPosition(1400, 980);
	
	// ����� �����
	levelNumberText.setFont(AssetManager::GetFont("fonts/Broken.ttf"));
	levelNumberText.setCharacterSize(55);
	levelNumberText.setFillColor(sf::Color(99, 124, 0));
	levelNumberText.setOutlineColor(Color::Yellow);
	levelNumberText.setOutlineThickness(1);
	levelNumberText.setPosition(800, 20);
	
	// ����� �����
	healthBar.setOutlineColor(Color::Yellow);
	healthBar.setOutlineThickness(2);
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(550, 980);
	// ����� ����� 
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
			
			// ��������
			if (state == State::game_load)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					state = State::playing;
				}
			}



			// ����� ����
			if (state == State::game_over)
			{
				if ((event.key.code == sf::Keyboard::Space) )
				{
					restart();
					state = State::playing;
				}
			}
			
			if (state == State::paused)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					state = State::playing;
				}
			}

			if ((event.key.code == sf::Keyboard::M)) {

				if (m_musik.play(0, true)) {
				
					m_musik.stop(0);
				};
			}

			// ����� �� ����
			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) 
			{
				std::ofstream outFile("gamedata/scores.txt");
				if (outFile.is_open())
				{
					//���������� ����������
					outFile << hiScore;
					outFile.close();
				}
				
				window.close();
			}
						

			// ����
			if (state == State::playing)
			{

			// ������� �����
			if (event.key.code == sf::Keyboard::Pause)
			{
				state = State::paused;
			}
			 
			
				// �����������
				if (event.key.code == Keyboard::R)
				{
					m_musik.play(3, false);
					recharge();	
				}
				// �����������
				
				if (event.key.code==sf::Keyboard::W)
				{
					player.moveUp();
				}
				else
				{
					player.stopUp();
				}

				if (event.key.code == sf::Keyboard::E)
				{
					player.moveUpRg();
				}
				else
				{
					player.stopUpRg();
				}
				if (event.key.code == sf::Keyboard::C)
				{
					player.moveDownRg();
				}
				else
				{
					player.stopDownRg();
				}
				if (event.key.code == sf::Keyboard::S)
				{
					player.moveDown();
				}
				else
				{
					player.stopDown();
				}
				if (event.key.code == sf::Keyboard::Z)
				{
					player.moveDownLf();
				}
				else
				{
					player.stopDownLf();
				}

				if (event.key.code == sf::Keyboard::Q)
				{
					player.moveUpLf();
				}
				else
				{
					player.stopUpLf();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					player.moveLeft();
				}
				else
				{
					player.stopLeft();
				}
				if (event.key.code == sf::Keyboard::D)
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
				// ��������
				if (Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 100 && bulletsInClip > 0)
					{
						m_musik.play(1, false);
						// �������� � ������
						bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);
						currentBullet++;
						if (currentBullet > 99)
						{
							currentBullet = 0;
						}
						lastPressed = gameTimeTotal;
						bulletsInClip--;
					}
				}// ����� ��������

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

	// ������� �����
	if (state == State::playing)
	{
		// ���������� ������ �������� �������
		gameTimeTotal += deltaTime;
		// ��������� �����
		mouseScreenPosition = sf::Mouse::getPosition();
		// ������������ ��������� ����� � ������� ���������� ���� mainView
		mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);
		// ��������� �������
		spriteCrosshair.setPosition(mouseWorldPosition);
		spriteCrosshair1.setPosition(mouseWorldPosition);

		if (!player.getLive()) {
			state = State::game_over;
			std::ofstream outputFile("gamedata/scores.txt");
			// << writes the data
			outputFile << hiScore;
			outputFile.close();
		}

		// ���������� ������ ������
		player.update(deltaTime, sf::Mouse::getPosition());
		// ���������� ��������� ������ � ���������� 
		sf::Vector2f playerPosition(player.getCenter());
		// ������������� ����� ���� mainView, �������� ��������� ������
		mainView.setCenter(player.getCenter());
		// ������� ��������� ������
		sf::Vector2f minview;
		sf::Vector2f maxview;
		minview.x = player.getSprite().getPosition().x - m_resolution.x / 2;
		maxview.x = player.getSprite().getPosition().x + m_resolution.x / 2;
		minview.y = player.getSprite().getPosition().y - m_resolution.y / 2;
		maxview.y = player.getSprite().getPosition().y + m_resolution.y / 2;
		// ���������� ������ ��������
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


		// ���������� ������ ����
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				bullets[i].update(deltaTime.asSeconds());
			}
		}

		// ���������� ������ ���������
		if (!pickup.empty()) 
		{
			
			for (int i = 0; i < pickup.size(); i++) 
			{
				if (pickup[i].isSpawned()) 
				{
			pickup[i].update(deltaTime.asSeconds());
			// ������ ���������
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

		// �������� ������������ ���� � ��������
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < numMonster; j++)
			{
				if (bullets[i].isInFlight() &&	monster[j].isAlive())
				{
					if (bullets[i].getPosition().intersects
					(monster[j].getPosition()))
					{
						// ���������� ����
						bullets[i].stop();
						// �������� ��������� � �������
						if (monster[j].hit())
						{ // ������ �������
							if (monster[j].getTypeMonster() > 0 && monster[j].getTypeMonster() < 3) m_musik.play(2, false); else m_musik.play(4, false);
							score += 5*monster[j].getTypeMonster();
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
								state = State::level_up;
							}
						}
					}
				}
			}
		}// ����� �������� ������������ ���� � ��������

		// ������������ ������� � �������
		for (int i = 0; i < numMonster; i++)
		{
			if (player.getPosition().intersects
			(monster[i].getPosition()) && monster[i].isAlive())
			{
				if (player.hit(gameTimeTotal))
				{
					m_musik.play(5, false);
				}
				
			}
		}// ����� ������������ ������� � �������
				
		
		    // ����� �����
		    healthBar.setSize(Vector2f(player.getHealth() * 4, 50));
		
			// ����� ���������� ��������
			ammoText.setString(std::to_string(bulletsInClip)+"/"+ std::to_string(bulletsSpare));
			// ����� ���������� �����
			scoreText.setString(L"����: " + std::to_string(score));
			// ����� ���������� �������
			hiScoreText.setString(L"������: "+std::to_string(hiScore));
			// ����� ���������� ������
			levelNumberText.setString(L"�������: "+ std::to_string(level));
			// ����� ���������� �������� ���������� ��������
			monsterRemainingText.setString(L"�������: "+ std::to_string(numMonsterAlive));
			


	}// ����� ������� �����
	
	if (state == State::level_up)
	{
		level++;
		newLevel();
	    state = State::playing;	
	}
}

void GameEngine::draw()
{
	if (state == State::playing)
	{
		window.clear();
		// ������� ����
		window.setView(mainView);
		// ���
		window.draw(background, &AssetManager::GetTexture("graphics/plan.png"));
		// ���� ��������
		for (int i = 0; i < monster.size(); i++) {
		if ((!monster[i].isAlive()) && (!monster[i].getnovisible()))  window.draw(monster[i].getSprite());
		}
				
		// ������
		if (!pickup.empty())
		{
			for (int i = 0; i < pickup.size(); i++)
			{
				if (pickup[i].isSpawned())	window.draw(pickup[i].getSprite());

			}
		}

		// �������
		for (int i = 0; i < monster.size(); i++){

			if (monster[i].isAlive() ) window.draw(monster[i].getSprite());
		}


		// ����
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				window.draw(bullets[i].getShape());
			}
		}
		// �����
		window.draw(player.getSprite());
				
		// ������
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
		
		// ���������
		window.setView(hudView);
		// �������� ����������
		window.draw(spriteAmmoIcon);
		window.draw(ammoText);
		window.draw(scoreText);
		window.draw(hiScoreText);
		window.draw(healthBar);
		window.draw(healthBar1);
		window.draw(levelNumberText);
		window.draw(monsterRemainingText);
		
	}
	if (state == State::game_load)
	{
		window.clear();
		levelText.setString(L"��� ����������� ������� ������ ");
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 50);
		window.draw(spriteGameBegin);
		window.draw(levelText);		
	}
	if (state == State::paused)
	{
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y/2 - levelText.getGlobalBounds().height/2);
		window.draw(levelText);	
	}
	
	if (state == State::game_over)
	{
		window.draw(spriteGameOver);
		levelText.setPosition(m_resolution.x / 2 - levelText.getGlobalBounds().width / 2, m_resolution.y - levelText.getGlobalBounds().height - 50);
		window.draw(levelText);
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
	planet.width = 30000;
	planet.height = 30000;
	planet.left = 0;
	planet.top = 0;
	// Pass the vertex array by reference
	// to the createBackground function
	int tileSize = createBackground(background, planet);
	// Spawn the player in the middle of the arena
	player.spawn(planet, m_resolution, tileSize);
	// Configure the pick-ups
	newLevel();
	numMonsterAlive = numMonster;
}

void GameEngine::newLevel()
{   
	monster.clear();
	pickup.clear();

	switch (level)
	{
	case 1: 
	{   // ���������� ��������
		numMonster = 100;
		createHorde(numMonster,monster, sf::Vector2i(0, 1), planet);
		numMonsterAlive = numMonster; 
		break; 
	}
	case 2:
	{   // ���������� ��������
		numMonster = 150;
		createHorde(numMonster, monster,sf::Vector2i(0, 2), planet);
		numMonsterAlive = numMonster;
		break;
	}
	case 3:
	{   // ���������� ��������
		numMonster = 200;
		createHorde(numMonster,monster, sf::Vector2i(1, 3), planet);
		numMonsterAlive = numMonster;
		break;
	}
	case 4:
	{   // ���������� ��������
		numMonster = 250;
		createHorde(numMonster, monster, sf::Vector2i(2, 4), planet);
		numMonsterAlive = numMonster;
		break;
	}
	case 5:
	{   // ���������� ��������
		numMonster = 300;
		createHorde(numMonster, monster, sf::Vector2i(3, 4), planet);
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
	// ���������� ���������� ����
	sf::Clock clock;
	// ���� �������� ���� ���� �������
	while (window.isOpen())
	{
		// ������� ����� ����������� ���������� ������� dt
		sf::Time dt = clock.restart();
		input();
		update(dt);
		draw();
	}

}
