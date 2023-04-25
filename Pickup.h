#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Pickup
{
private:
	
	// Спрайт, представляющий этот пикап
	sf::Sprite m_Sprite;
	// Сколько стоит этот пикап?
	int m_Value;
	// Что это за пикап?
    // 1 = здоровье, 2 = патроны
	int m_Type;
	// Обработка появления и исчезновения пикапа
	bool m_Spawned=true;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive=15;
		
public:
	// Готовим новый пикап
	void spawn(sf::Vector2f pos, int type);
	// Проверяем положение пикапа
	sf::FloatRect getPosition() const;
	// Получаем спрайт для рисования
	sf::Sprite getSprite() const;
	// Разрешить пикапу обновлять себя каждый кадр
	void update(float elapsedTime);
	// Создан ли этот пикап в настоящее время?
	bool isSpawned() const;
	// Получаем добро из пикапа
	int gotIt();
	// Получаем тип
	int getType() const;
};