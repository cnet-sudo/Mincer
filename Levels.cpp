#include "Levels.h"

Levels::Levels()
{
	

}

sf::Sprite* Levels::getSprite(int index)
{
	m_bkgr = & m_background[index];		
	return m_bkgr;
}

void Levels::splash_SCR_update(sf::Time deltaTime)
{
	m_time_frame += deltaTime;

	if (m_sound[m_frame].getStatus() == sf::SoundSource::Status::Stopped && m_play) {
		m_sound[m_frame].play(); m_play = false;
		}

	if (m_time_frame > sf::seconds(m_time[m_frame])) {
	
		m_time_frame = sf::seconds(0);

		if (m_frame < 6) { m_frame++; m_play = true; 
		int step = 1920 * m_frame;
		m_splash_screen.setTextureRect(sf::IntRect(step, 0, 1920, 1080));
		}
		
	}
}

void Levels::splash_SCR_draw(sf::RenderWindow& window)
{
	window.draw(m_splash_screen);
}

void Levels::createLevels()
{
	std::array<std::string, 7> str{ "graphics/level1.jpg", "graphics/level2.jpg", "graphics/level3.jpg",
		"graphics/level4.jpg", "graphics/level5.jpg","graphics/game_over.jpg","graphics/level6.jpg" };


	for (int i = 0; i < m_background.size(); i++)
	{
		m_background[i].setTexture(AssetManager::GetTexture(str[i]));
	}

	m_splash_screen.setTexture(AssetManager::GetTexture("graphics/pow.png"));
	m_splash_screen.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	std::array<std::string, 7> str1{ "sound/r1.wav", "sound/r2.wav", "sound/r3.wav",
		"sound/r4.wav", "sound/r5.wav","sound/r6.wav","sound/r7.wav" };

	for (int i = 0; i < m_sound.size(); i++)
	{
		m_sound[i].setBuffer(AssetManager::GetSoundBuffer(str1[i]));
		m_sound[i].setLoop(false);
	}
}

void Levels::stop_sound() {

			for (int i = 0; i < m_sound.size(); i++) {

			if (m_sound[i].getStatus() == sf::SoundSource::Status::Playing) m_sound[i].stop();
		}
	
}