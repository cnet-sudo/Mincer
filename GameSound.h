#pragma once
#include<SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound
{   
	// ������ �������� ��������
    std::vector<sf::Sound> m_sound; 	
		
public:
	
	// ������� ������ �������� ��������
	void create_sound(std::vector<std::string>& sound);
	// ����� ��������� ��������� ������� �������� �������������� � ���������� �������
	bool play(int index, bool loop);
	// ����� ���������� ��������� ������� �������� �������������� � ���������� �������
	void stop(int index);
	// ����� ���������� ���� �������� ��������
	void all_stop();
};

