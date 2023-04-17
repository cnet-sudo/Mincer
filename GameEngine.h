#pragma once
#include<iostream>
#include"AssetManager.h"
#include"Player.h"
#include"Planet.h"

class GameEngine
{
public:
	GameEngine();
	// Game Loop Launch Method
	// ����� ������� �������� �����
	void run();
private:
	// Resource manager
	// �������� ��������
	AssetManager manager; 
	// Smart pointer to graphics window
	// ����� ��������� �� ����������� ���� 
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(resolution.x, resolution.y),L"���������", sf::Style::Fullscreen);
	sf::Image icon;
	// Event handling method
	// ����� ��������� ������� 
	void input();
	// Method for updating variables, properties and methods
	// ����� ���������� ����������, ������� � ������� 
	void update(sf::Time const& deltaTime);
	// Method for drawing objects in the graphics window
	// ����� ��������� �������� � ����������� ����
	void draw();
	// The game will always be in one of four states
	// ���� ������ ����� � ����� �� ������� ���������
	enum class State {paused, leveling_up,game_over, playing};
	// Start with the GAME_OVER state
	// ������� � ��������� GAME_OVER
	State state = State::playing;
	// Get the screen resolution and
	// create an SFML window
	sf::Vector2f resolution;
	// Create a an SFML View for the main action
	sf::View mainView=sf::View(sf::FloatRect(0, 0,resolution.x, resolution.y));
	// How long has the PLAYING state been active
	sf::Time gameTimeTotal;
	// Where is the mouse in
	// relation to world coordinates
	sf::Vector2f mouseWorldPosition;
	// Where is the mouse in
	// relation to screen coordinates
	sf::Vector2i mouseScreenPosition;
	// Create an instance of the Player class
	Player player;

	// Create the background
	sf::VertexArray background;
	// Load the texture for our background vertex array
	sf::Texture textureBackground;
	
	// The boundaries of the arena
	sf::IntRect planet;

	void restart();
};

