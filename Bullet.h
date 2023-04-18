#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet
{
private:
	// Where is the bullet?
	Vector2f m_Position;
	// What each bullet looks like
	CircleShape m_BulletShape;
	// Is this bullet currently whizzing through the air
	bool m_InFlight = false;
	// How fast does a bullet travel?
	float m_BulletSpeed = 1000;
	// What fraction of 1 pixel does the bullet travel,
	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	sf::Vector2f m_BulletDistance;
	// Some boundaries so the bullet doesn't fly forever
	sf::Vector2f m_Max;
	sf::Vector2f m_Min;
	// Public function prototypes go here
public:
	// The constructor
	Bullet();
	// Stop the bullet
	void stop();
	// Returns the value of m_InFlight
	bool isInFlight();
	// Launch a new bullet
	void shoot(float startX, float startY,
		float xTarget, float yTarget);
	// Tell the calling code where the bullet is in the world
	FloatRect getPosition();
	// Return the actual shape (for drawing)
	CircleShape getShape();
	// Update the bullet each frame
	void update(float elapsedTime);
};
