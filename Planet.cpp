#include "Planet.h"
#include "MonsterPlanet.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect planet)
{
    // Will be used to obtain a seed for the random number engine
    // ����� �������������� ��� ��������� ���������� ����� ��� ��������� ��������� �����
    std::random_device rd;
    // Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd()); 
   
    
        // ������ ������
        const int TILE_SIZE = 200;
        // ���������� ��������� ������
        const int TILE_TYPES = 9;
        // ���������� ������
        const int VERTS_IN_QUAD = 4;
        // ������ ����
        int worldWidth = planet.width / TILE_SIZE;
        // ������ ����
        int worldHeight = planet.height / TILE_SIZE;
        // What type of primitive are we using? (����� ��� ��������� �� ����������?)
        rVA.setPrimitiveType(sf::Quads);
        // Set the size of the vertex array (���������� ������ ������� ������)
        rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
        // Start at the beginning of the vertex array (������ � ������ ������� ������)
        int currentVertex = 0;

        for (int w = 0; w < worldWidth; w++)
        {
            for (int h = 0; h < worldHeight; h++)
            {
                // Position each vertex in the current quad (�������������� ������ ������� � ������� ����������������)
                rVA[currentVertex + 0].position =sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
                rVA[currentVertex + 1].position =sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
                rVA[currentVertex + 2].position =sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE)+ TILE_SIZE);
                rVA[currentVertex + 3].position =sf::Vector2f((w * TILE_SIZE), (h * TILE_SIZE)+ TILE_SIZE);

                // Define the position in the Texture for current quad
                // Either grass, stone, bush or wall
                // ���������� ������� � �������� ��� �������� ����������������
                // �����, ������, ���� ��� �����
                if (h == 0 || h == worldHeight - 1 ||
                    w == 0 || w == worldWidth - 1)
                {
                    // Use the wall texture
                    // ���������� �������� �����
                    rVA[currentVertex + 0].texCoords = sf::Vector2f(TILE_SIZE*TILE_TYPES,0);
                    rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE*TILE_TYPES+TILE_SIZE,0);
                    rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES + TILE_SIZE, TILE_SIZE);
                    rVA[currentVertex + 3].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES, TILE_SIZE);
                }
                else
                {
                    std::uniform_int_distribution<> dis(0, TILE_TYPES-1); // Same distribution as before, but explicit and without bias
                    // Use a random floor texture
                    // ������������ ��������� �������� ����
                    int mOrG = dis(gen);
                    int verticalOffset = mOrG * TILE_SIZE;
                    rVA[currentVertex + 0].texCoords =sf::Vector2f(verticalOffset,0);
                    rVA[currentVertex + 1].texCoords =sf::Vector2f(verticalOffset+TILE_SIZE,0);
                    rVA[currentVertex + 2].texCoords =sf::Vector2f(verticalOffset + TILE_SIZE, TILE_SIZE);
                    rVA[currentVertex + 3].texCoords =sf::Vector2f(verticalOffset, TILE_SIZE);
                }

                // Position ready for the next four vertices (������� ������ ��� ��������� ������� ������)
                currentVertex = currentVertex + VERTS_IN_QUAD;
            }
        }


        return TILE_SIZE;   
}

