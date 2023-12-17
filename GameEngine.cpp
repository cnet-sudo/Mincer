#include "GameEngine.h"

GameEngine::GameEngine() {
	// ��������� �������� ����
	m_window.create(sf::VideoMode(m_resolution.x, m_resolution.y), L"������ �����", sf::Style::Fullscreen);
	// ���� �������� ����
	m_state = State::game_load;
	//<<<<<<<<<<<<<Begin<<<<<<<<<<<<<<<<
	m_levels.start();
	m_gametext.drawAssistant(m_window,0);
	m_window.display();
	m_levels.createLevels();
	// <<<<<<<<<<<<<<<<<<<<<<<End<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ������ ����
	m_mainView.setSize(m_resolution.x, m_resolution.y);
	// ��������� ���������� �������� ����
	m_planet.left = 0;
	m_planet.top = 0;
	// ������ �������� ����
	if (!m_icon.loadFromFile("game.png")) exit(3); 
	m_window.setIcon(194, 256, m_icon.getPixelsPtr());
	// ������ ������
	m_window.setMouseCursorVisible(false); //<<<<<<<<<<<<<<<<<<<<<<<<
    //�������� ������� ������ 
	std::vector<std::string> str{ "sound/level1.wav","sound/plasma.wav","sound/mobv.wav","sound/per.wav",
	"sound/mobb.wav","sound/hit1.wav","sound/bonus1.wav" };
	m_musik.create_sound(str);
	// ������ ��� ������
	m_Bullet.spriteCrosshair.setTexture(AssetManager::GetTexture("graphics/crosshair.png")); 
	m_Bullet.spriteCrosshair.setOrigin(25, 25);
	m_Bullet.spriteCrosshair.setScale(m_gametext.getScale().x, m_gametext.getScale().y);
	m_Bullet.spriteCrosshair1.setTexture(AssetManager::GetTexture("graphics/crosshair1.png")); 
	m_Bullet.spriteCrosshair1.setOrigin(25, 25);
	m_Bullet.spriteCrosshair1.setScale(m_gametext.getScale().x, m_gametext.getScale().y);
	
	//<<<<<<<<<<<<<Begin<<<<<<<<<<<<<<<<
	// �������� ������� 
	std::ifstream inputFile("gamedata/scores.txt", std::ios::binary | std::ios::in);
	if (inputFile.is_open())
	{
		//���������� ����������
		inputFile.read((char*)&m_HubText.hiScore, sizeof m_HubText.hiScore);
		inputFile.close();
	}
	// <<<<<<<<<<<<<<<<<<<<<<<End<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	restart();	
}

void GameEngine::input() {

	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) {
			
			// ��������
			if (m_state == State::game_load) {

				if ((event.key.code == sf::Keyboard::Space)) {

					m_state = State::splash_screen;
					return;
				}

			}

			if (m_state == State::splash_screen) {

				if ((event.key.code == sf::Keyboard::Space)) {

					m_levels.stop_sound();//<<<<<<<<<<<<<<<<<<<<<<<
					m_state = State::level_up;
					return;
				}
			}



			if (m_state == State::level) {

				if ((event.key.code == sf::Keyboard::Space)) {

					m_state = State::playing;
				}
			}


			// ����� ����
			if (m_state == State::game_over) {

				if ((event.key.code == sf::Keyboard::Space) ) {

					restart(); //<<<<<<<<<<<<<
					m_state = State::level_up;
				}
			}
			
			if (m_state == State::game_victory) {

				if ((event.key.code == sf::Keyboard::Space)) {

					start_complexity();           //<<<<<<<<<<<
					m_HubText.complexity++;       // <<<<<<<<<<<<<<<<<<<<
					m_state = State::level_up;
				}
			}

			if (m_state == State::paused) {

				if (event.key.code == sf::Keyboard::Pause) {

					m_state = State::playing;
					return;
				}
				
			}
			// ������
			if (m_state == State::help)  {

				if (event.key.code == sf::Keyboard::Tab) {

					m_state = State::playing;
					return;
				}
				
			}
			
			// ��������� ���������� ������    
			if ((event.key.code == sf::Keyboard::M)) {
				
				if (m_musik.play(0, true)) {
				
					m_musik.stop(0);
				};
				
			}

			// ����� �� ����
			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed)) {

				saveHiScore(); //<<<<<<<<<<<<<<<<<<<<<<<<<<<
				
				m_window.close();
			}

			if (m_state == State::transition) {

				if ((event.key.code == sf::Keyboard::Space))
				{
					m_state = State::level_up;
					return;
				}
			}

			// ����
			if (m_state == State::playing || m_state == State::transition) {
				
				// ������� �����
				if (event.key.code == sf::Keyboard::Pause && m_state != State::transition) {

					m_state = State::paused;
					return;
				}
			
				// ������ � ����
				if (event.key.code == sf::Keyboard::Tab && m_state != State::transition) {

					m_state = State::help;
					return;
				}

				// ������� ������� ���� ����
				if (event.key.code == sf::Keyboard::Space) {

					m_mainView.setSize(1920,1080);
					return;
				}
			
				// ����������� ������               
				if (event.key.code == sf::Keyboard::R) {
						
					m_musik.play(3, false); 
					// �����������
					recharge();		                 			
				}

				// ����������� ������
				if (event.key.code==sf::Keyboard::W) {

					m_player.move(Player::playermove::UpPressed);
				}
				
				if (event.key.code == sf::Keyboard::E) {

					m_player.move(Player::playermove::UpRg);
				}
				
				if (event.key.code == sf::Keyboard::C) {

					m_player.move(Player::playermove::DownRg);
					
				}
				
				if (event.key.code == sf::Keyboard::S) {

					m_player.move(Player::playermove::DownPressed);					
				}
				
				if (event.key.code == sf::Keyboard::Z) {

					m_player.move(Player::playermove::DownLf);
				}
				
				if (event.key.code == sf::Keyboard::Q) {

					m_player.move(Player::playermove::UpLf);
				}
				
				if (event.key.code == sf::Keyboard::A) {

					m_player.move(Player::playermove::LeftPressed);
					
				}
				
				if (event.key.code == sf::Keyboard::D) {

					m_player.move(Player::playermove::RightPressed);
				}
				
				if (event.key.code == sf::Keyboard::X) {

					m_player.move(Player::playermove::Stop);
				}

			} // ����� ����

			
		}

		// �������
		if (m_state == State::playing || m_state == State::transition) {

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta < 0) {
					m_mainView.zoom(0.9f);
					if (m_mainView.getSize().x < 1280) m_mainView.setSize(1280, 720);
				}

				else if (event.mouseWheelScroll.delta > 0) {
					m_mainView.zoom(1.1f);
					if (m_mainView.getSize().x > 3840) m_mainView.setSize(3840, 2160);
				}
			}
		}

		
		
		if (m_state == State::playing || m_state == State::transition)  // ������� ������� �������� ��� ��� ������� ������ �� ���� ������������ 
		{
			if (event.type == sf::Event::MouseButtonPressed) {  // ������� ������ ����
			
				if (event.mouseButton.button == sf::Mouse::Left) {
				
					if (m_gameTimeTotal.asMilliseconds() - m_lastPressed.asMilliseconds() > 100 && m_HubText.bulletsInClip > 0) {
					
						m_musik.play(1, false); 

						// �������� � ������
						m_Bullet.bullets[m_Bullet.currentBullet].shoot(m_player.getCenter().x, m_player.getCenter().y, m_mouseWorldPosition.x, m_mouseWorldPosition.y);
						m_Bullet.currentBullet++;
						if (m_Bullet.currentBullet > m_Bullet.bullets.size() - 1) {
						
							m_Bullet.currentBullet = 0;
						}
						m_Bullet.lastPressed = m_gameTimeTotal;
						m_HubText.bulletsInClip--;
					}
				}
				// ����� ��������

				if (event.mouseButton.button == sf::Mouse::Right) {
					
					m_musik.play(3, false);   
					// �����������
					recharge();                 
				}

			}
		}
		
	}
}

void GameEngine::update(sf::Time const& deltaTime) {
	// ������
	std::random_device rd; 
	std::mt19937 gen(rd());              
	std::uniform_int_distribution<> tis(1, 20);
	///------����� ������� -----------------------
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	if (m_state == State::splash_screen)
	{
		m_levels.splash_SCR_update(deltaTime);
		if (m_levels.getVstup()) m_state = State::level_up;
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ������� �����
	if (m_state == State::playing || m_state == State::transition)
	{
		// ���������� ������ �������� �������
		m_gameTimeTotal += deltaTime;
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if (!m_player.getLive()) {
			m_state = State::game_over;

			m_gametext.genText("dead");

			saveHiScore();
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		// ��������� �����                    
		m_mouseScreenPosition = sf::Mouse::getPosition();
		// ������������ ��������� ����� � ������� ���������� ���� mainView
		m_mouseWorldPosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(), m_mainView);
		// ��������� �������
		m_Bullet.spriteCrosshair.setPosition(m_mouseWorldPosition);
		m_Bullet.spriteCrosshair1.setPosition(m_mouseWorldPosition);
		///-----------����� ��������� �����  ------------------------

		// ���������� ������ ������
		m_player.update(deltaTime, sf::Mouse::getPosition());
		// ���������� ��������� ������ � ���������� 
		sf::Vector2f playerPosition(m_player.getCenter());
		// ������������� ����� ���� mainView, �������� ��������� ������
		m_mainView.setCenter(m_player.getCenter());

		// ������� ��������� ������
		sf::Vector2f minview{ m_player.getSprite().getPosition().x - m_resolution.x / 2, m_player.getSprite().getPosition().y - m_resolution.y / 2 };
		sf::Vector2f maxview{ m_player.getSprite().getPosition().x + m_resolution.x / 2, m_player.getSprite().getPosition().y + m_resolution.y / 2 };
		
		// ���������� ������ ��������
		for (int i = 0; i < m_monster.size(); i++)	{
			if (m_monster[i].isAlive()) {

				m_monster[i].update(deltaTime, playerPosition, m_resolution);
			}
			else {
				if (m_monster[i].getSprite().getPosition().x > maxview.x || m_monster[i].getSprite().getPosition().x < minview.x
					|| m_monster[i].getSprite().getPosition().y > maxview.y || m_monster[i].getSprite().getPosition().y < minview.y)
				{
					m_monster[i].novisible();
				}
			}
		}// ����� ������ ��������

		// ---- ���������� ������ ���� 
		for (int i = 0; i < m_Bullet.bullets.size(); i++) {
			if (m_Bullet.bullets[i].isInFlight()) {
				m_Bullet.bullets[i].update(deltaTime.asSeconds());
			}
		}
		// ---- �������� ������������ ���� � ��������
		for (int i = 0; i < m_Bullet.bullets.size(); i++) {
			for (int j = 0; j < m_monster.size(); j++) {
				if (m_Bullet.bullets[i].isInFlight() && m_monster[j].isAlive())
				{
					if (m_Bullet.bullets[i].getPosition().intersects
					(m_monster[j].getPosition()))
					{
						// ���������� ����
						m_Bullet.bullets[i].stop();
						// �������� ��������� � �������
						if (m_monster[j].hit())
						{ // ������ �������
							if (m_monster[j].getTypeMonster() > 0 && m_monster[j].getTypeMonster() < 3) { m_musik.stop(2); m_musik.play(2, false); }  //<<<<<<<<<<<<<<<<<<<<
							else { m_musik.stop(4); m_musik.play(4, false); }        //<<<<<<<<<<<<<<<<<<<<
							m_HubText.score += 5 * (m_monster[j].getTypeMonster() + 1);
							// ��������� ������� 
							int typ = tis(gen);
							if (typ < 7 || typ == 10 || typ == 15)
							{
								pickup.push_back(Pickup());
								pickup[pickup.size() - 1].spawn(m_monster[j].getSprite().getPosition(), typ);
							}
							//-------- ����� ��������� ������� ----------------------
							if (m_HubText.score >= m_HubText.hiScore) {

								m_HubText.hiScore = m_HubText.score;
							}
							m_HubText.numMonsterAlive--;
							// ����� ��� ����� ������ (�����)
							if (m_HubText.numMonsterAlive == 0) {
								m_state = State::transition;
							}
						}
					}
				}
			}
		}// ---------����� �������� ������������ ���� � �������� --------
		
		// ���������� ������ ���������  
		if (!pickup.empty())
		{

			for (int i = 0; i < pickup.size(); i++)
			{
				if (pickup[i].isSpawned())
				{
					pickup[i].update(deltaTime.asSeconds());
					// ������ ���������
					if (m_player.getPosition().intersects(pickup[i].getPosition()))
					{
						m_musik.stop(6);
						m_musik.play(6, false); 
						switch (pickup[i].getType())
						{
						case 1: {m_player.increaseHealthLevel(pickup[i].gotIt()); break; }
						case 2: {m_HubText.bulletsSpare += pickup[i].gotIt(); break; }
						case 3: {m_player.upgradeHealth(pickup[i].gotIt()); break; }
						case 4: {m_Bullet.clipSize += pickup[i].gotIt(); break; }
						default:
							break;
						}

					}
				}
			}

			if (pickup.size() > 20)
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
		//---------- ����� ������ ��������� -------------------------------

		// ������������ ������� � �������
		for (int i = 0; i < m_monster.size(); i++)	{

			if (m_player.getPosition().intersects(m_monster[i].getPosition()) && m_monster[i].isAlive()) {

				if (m_player.hit(m_gameTimeTotal))	{

					m_musik.play(5, false); 
				}

			}
		}// ����� ������������ ������� � �������


		// ���������
		 
		// ����� �����
		// ���������� ��������� ������� ������������ ����������� ����� ����� � ��������� �������� 
		m_HubText.bar_x= (m_player.getHealth() * 4) / (m_player.getMaxHealth() / 200); 
		// ���������� �������� �������� ����������
		m_gametext.update(m_HubText);
				 
	} // ����� ������� �����

	if (m_state == State::level_up)
	{
		m_HubText.level++;
		if (m_HubText.level > 5) {
			m_state = State::game_victory;
			
			m_gametext.genText("vic"); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			saveHiScore();			   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		}
		else {
			newLevel();
			m_state = State::level;
		}
	}
}

void GameEngine::draw() {

	if (m_state == State::playing || m_state == State::transition)
	{
		m_window.clear();
		// ������� ����
		m_window.setView(m_mainView);
		// ���
		m_window.draw(m_background, &AssetManager::GetTexture("graphics/plan.png"));
		
		// ������ 
		if (!pickup.empty())
		{
			for (int i = 0; i < pickup.size(); i++)
			{
				if (pickup[i].isSpawned())	m_window.draw(pickup[i].getSprite());

			}
		}
				
		// ����                       
		for (int i = 0; i < m_Bullet.bullets.size(); i++)
		{
			if (m_Bullet.bullets[i].isInFlight())
			{
				m_window.draw(m_Bullet.bullets[i].getShape());
			}
		}
		
		// �������� �������  
		for (int i = 0; i < m_monster.size(); i++) {
			// �������� �������
			if ((!m_monster[i].isAlive()) && (!m_monster[i].getnovisible()))  m_window.draw(m_monster[i].getSprite());
			// ����� �������
			if (m_monster[i].isAlive()) m_window.draw(m_monster[i].getSprite());
		}
		// ����� �������� �������
		
		// ������
		for (int j = 0; j < m_monster.size(); j++)
		{
			if ((m_Bullet.spriteCrosshair1.getGlobalBounds().intersects(m_monster[j].getPosition())) && (m_monster[j].isAlive()))
			{
				m_window.draw(m_Bullet.spriteCrosshair1); break;
			}
			else
			{
				m_window.draw(m_Bullet.spriteCrosshair);
			}
		}
		
		// �����
		m_player.draw(m_window);
		
		
		// ���������
		m_window.setView(m_hudView);
		
		// �������� ����������
		m_gametext.draw(m_window);

	}

	//<<<<<<<<<<<<<Begin<<<<<<<<<<<<<<<<

	if (m_state == State::game_load)
	{
		m_levels.start();
		m_gametext.drawAssistant(m_window, 1);
	}
	if (m_state == State::splash_screen)
	{
		m_levels.splash_SCR_draw();
	}

	if (m_state == State::level)
	{
		m_window.clear();
		m_window.draw(*m_levels.getSprite(m_HubText.level - 1));
		m_gametext.drawAssistant(m_window, 1);
	}

	if (m_state == State::paused)
	{
		m_gametext.drawAssistant(m_window, 2);
	}

	if (m_state == State::help)
	{
		m_levels.help();
	}

	if (m_state == State::transition)
	{
		m_gametext.drawAssistant(m_window, 1);
	}
	if (m_state == State::game_over)
	{
		m_window.draw(*m_levels.getSprite(5));
		m_gametext.drawAssistant(m_window, 1);
		m_gametext.drawText(m_window);
		m_gametext.drawGameOver(m_window);
		
	}

	if (m_state == State::game_victory)
	{
		m_window.draw(*m_levels.getSprite(6));
		m_gametext.drawAssistant(m_window, 1);
		m_gametext.drawText(m_window);
		m_gametext.drawGameOver(m_window);
	}
	//<<<<<<<<<<<<<End<<<<<<<<<<<<<<<<
	m_window.display();
}


void GameEngine::run()
{
	// ���������� ���������� ����
	sf::Clock clock;
	// ���� �������� ���� ���� �������
	while (m_window.isOpen())
	{
		// ������� ����� ����������� ���������� ������� dt
		sf::Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}

void GameEngine::restart() {   // �������

	m_player.resetPlayerStats();
	m_HubText.score = 0;
	m_HubText.level = 0;
	m_HubText.bulletsSpare = 300;
	m_HubText.bulletsInClip = 50;
	m_Bullet.clipSize = 50;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void GameEngine::start_complexity()
{
	m_HubText.level = 0;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void GameEngine::newLevel() {

	m_planet.width = 10000 * m_HubText.level;
	m_planet.height = 10000 * m_HubText.level;
	m_background.clear();
	int tileSize = createBackground(m_background, m_planet, m_HubText.level);
	m_player.spawn(m_planet, m_resolution, tileSize);

	m_monster.clear();
	m_HubText.numMonsterAlive = createHorde(50 * m_HubText.level, m_monster, sf::Vector2i(0, m_HubText.level - 1), m_planet, m_HubText.complexity);
	
	
	for (int i = 0; i < m_Bullet.bullets.size(); i++) {     // ������������� ���� ���� ����
	if (m_Bullet.bullets[i].isInFlight() == true) m_Bullet.bullets[i].stop();
	}
	// ������� ������ �������
	pickup.clear();
	
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void GameEngine::saveHiScore()
{
	std::ofstream outputFile("gamedata/scores.txt", std::ios::binary | std::ios::out);
	outputFile.write((char*)&m_HubText.hiScore, sizeof m_HubText.hiScore);
	outputFile.close();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            

void GameEngine::recharge() {         // ����������� ��������   
	
	if (m_HubText.bulletsSpare > 0)	{  // ���� � ��������� ������ ����

		if (m_HubText.bulletsInClip < m_Bullet.clipSize) {   // ������ �� ���������

			// � ����� ������ ��� ������� �� ��������, ������� ��������� � ������
			if (m_HubText.bulletsSpare >= (m_Bullet.clipSize - m_HubText.bulletsInClip)) 
			{
				int myammo = m_Bullet.clipSize - m_HubText.bulletsInClip;
				m_HubText.bulletsInClip += myammo;  // ��������� ������� � ������
				m_HubText.bulletsSpare -= myammo;   // �������� ������� � �����
			}
			else
			{
				m_HubText.bulletsInClip += m_HubText.bulletsSpare; // ��������� ������� �������� � ������
				m_HubText.bulletsSpare = 0;                        // ���������� ��� � ����� ���� ��������
			}
		}

	}
}

