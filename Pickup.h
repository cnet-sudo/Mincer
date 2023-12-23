

#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Pickup
{
private:
	
	// Спрайт, представляющий этот пикап
	sf::Sprite m_Sprite;
	// Размер боннуса который содержит пикап
	int m_Value;
	// Что это за пикап (здоровье, патроны и т.д.)
    int m_Type;
	// Обработка появления и исчезновения пикапа
	bool m_Spawned=true;
	float m_SecondsSinceSpawn;
	float m_SecondsToLive=15;
		
public:
	// Создаём новый пикап
	void spawn(sf::Vector2f pos, int type);
	// Проверяем положение пикапа
	sf::FloatRect getPosition() const;
	// Получаем спрайт для рисования
	sf::Sprite getSprite() const;
	// Обновляем пикап каждый кадр
	void update(float elapsedTime);
	// Существует или нет пикап
	bool isSpawned() const;
	// Подбор пикапа
	int gotIt();
	// Получаем тип пикапа
	int getType() const;
};




