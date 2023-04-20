#pragma once
#include <SFML/Graphics.hpp>

class Pickup
{
private:
	//Начальные значения для подбора 
	const int HEALTH_START_VALUE = 100;
	const int AMMO_START_VALUE = 100;

	// Спрайт, представляющий этот пикап
	sf::Sprite m_Sprite;
	// Сколько стоит этот пикап?
	int m_Value;
	// Что это за пикап?
    // 1 = здоровье, 2 = патроны
	int m_Type;
	// Обработка появления и исчезновения
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive=10;
		
public:
	Pickup();
	// Готовим новый пикап
	void spawn(sf::Vector2f pos, int type);
	// Проверяем положение пикапа
	sf::FloatRect getPosition();
	// Получаем спрайт для рисования
	sf::Sprite getSprite();
	// Разрешить пикапу обновлять себя каждый кадр
	void update(float elapsedTime);
	// Создан ли этот пикап в настоящее время?
	bool isSpawned();
	// Получаем добро из пикапа
	int gotIt();
	// Получаем тип
	int getType();
};