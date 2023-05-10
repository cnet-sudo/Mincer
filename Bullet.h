#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet
{
private:
	// Координаты пули
	Vector2f m_Position;
	// Форма пули
	CircleShape m_BulletShape;
	// Пуля в полёте
	bool m_InFlight = false;
	// Скорость пули
	float m_BulletSpeed = 1000;
	// растояние полёта
	sf::Vector2f m_BulletDistance;
	// Границы полёта пули
	sf::Vector2f m_Max;
	sf::Vector2f m_Min;
	
public:
	
	Bullet();
	// Остановить полёт пули
	void stop();
	// Вернуть состояние пули
	bool isInFlight();
	// Запустить пулю
	void shoot(float startX, float startY,
		float xTarget, float yTarget);
	// Вернуть координаты в плоскости пули
	FloatRect getPosition();
	// Вернуть фигуру пули
	CircleShape getShape();
	// Обновление игровой логики
	void update(float elapsedTime);
};
