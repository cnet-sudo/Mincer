#include "Planet.h"
#include "MonsterPlanet.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect planet)
{
    // Will be used to obtain a seed for the random number engine
    // Ѕудет использоватьс€ дл€ получени€ начального числа дл€ механизма случайных чисел
    std::random_device rd;
    // Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd()); 
   
    
        // размер плитки
        const int TILE_SIZE = 200;
        // количество вариантов плиток
        const int TILE_TYPES = 9;
        // количество вершин
        const int VERTS_IN_QUAD = 4;
        // ширина мира
        int worldWidth = planet.width / TILE_SIZE;
        // высота мира
        int worldHeight = planet.height / TILE_SIZE;
        // What type of primitive are we using? ( акой тип примитива мы используем?)
        rVA.setPrimitiveType(sf::Quads);
        // Set the size of the vertex array (”становить размер массива вершин)
        rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
        // Start at the beginning of the vertex array (Ќачать с начала массива вершин)
        int currentVertex = 0;

        for (int w = 0; w < worldWidth; w++)
        {
            for (int h = 0; h < worldHeight; h++)
            {
                // Position each vertex in the current quad (ѕозиционируйте каждую вершину в текущем четырехугольнике)
                rVA[currentVertex + 0].position =sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
                rVA[currentVertex + 1].position =sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
                rVA[currentVertex + 2].position =sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE)+ TILE_SIZE);
                rVA[currentVertex + 3].position =sf::Vector2f((w * TILE_SIZE), (h * TILE_SIZE)+ TILE_SIZE);

                // Define the position in the Texture for current quad
                // Either grass, stone, bush or wall
                // ќпредел€ем позицию в текстуре дл€ текущего четырехугольника
                // “рава, камень, куст или стена
                if (h == 0 || h == worldHeight - 1 ||
                    w == 0 || w == worldWidth - 1)
                {
                    // Use the wall texture
                    // »спользуем текстуру стены
                    rVA[currentVertex + 0].texCoords = sf::Vector2f(TILE_SIZE*TILE_TYPES,0);
                    rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE*TILE_TYPES+TILE_SIZE,0);
                    rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES + TILE_SIZE, TILE_SIZE);
                    rVA[currentVertex + 3].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES, TILE_SIZE);
                }
                else
                {
                    std::uniform_int_distribution<> dis(0, TILE_TYPES-1); // Same distribution as before, but explicit and without bias
                    // Use a random floor texture
                    // »спользовать случайную текстуру пола
                    int mOrG = dis(gen);
                    int verticalOffset = mOrG * TILE_SIZE;
                    rVA[currentVertex + 0].texCoords =sf::Vector2f(verticalOffset,0);
                    rVA[currentVertex + 1].texCoords =sf::Vector2f(verticalOffset+TILE_SIZE,0);
                    rVA[currentVertex + 2].texCoords =sf::Vector2f(verticalOffset + TILE_SIZE, TILE_SIZE);
                    rVA[currentVertex + 3].texCoords =sf::Vector2f(verticalOffset, TILE_SIZE);
                }

                // Position ready for the next four vertices (ѕозици€ готова дл€ следующих четырех вершин)
                currentVertex = currentVertex + VERTS_IN_QUAD;
            }
        }


        return TILE_SIZE;   
}

