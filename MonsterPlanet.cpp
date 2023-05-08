#include "MonsterPlanet.h"
#include "Monster.h"

int createHorde(int numMonster, std::deque<Monster>& monster, sf::Vector2i type, sf::IntRect planet)
{   
    auto min= sf::Vector2i(planet.left + 300, planet.top + 300);
	auto max= sf::Vector2i(planet.width - 300, planet.height - 300);
    int num = 0;
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> rx(min.x, max.x);
	std::uniform_int_distribution<> ry(min.y, max.y);
	std::uniform_int_distribution<> rtype(type.x, type.y);
    sf::Vector2f pos;
    int mtype;
	
	for (int i = 0; i < numMonster; i++){
		    
            mtype = rtype(gen);
		    pos.x = static_cast<float>(rx(gen));
			pos.y = static_cast<float>(ry(gen));
            monster.emplace_back();
            monster[i].spawn(pos.x, pos.y, mtype);
            num++;
	}
	
    return num;
}

int createBackground(sf::VertexArray& rVA, sf::IntRect planet, int index)
{
    // Ѕудет использоватьс€ дл€ получени€ начального числа дл€ механизма случайных чисел
    std::random_device rd;
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
    // тип примитива
    rVA.setPrimitiveType(sf::Quads);
    // ”становить размер массива вершин
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
    // Ќачать с начала массива вершин
    int currentVertex = 0;

    for (int w = 0; w < worldWidth; w++)
    {
        for (int h = 0; h < worldHeight; h++)
        {
            // ѕозиционируйте каждую вершину в текущем четырехугольнике
            rVA[currentVertex + 0].position = sf::Vector2f(static_cast<float>(w * TILE_SIZE), static_cast<float>(h * TILE_SIZE));
            rVA[currentVertex + 1].position = sf::Vector2f(static_cast<float>((w * TILE_SIZE) + TILE_SIZE), static_cast<float>(h * TILE_SIZE));
            rVA[currentVertex + 2].position = sf::Vector2f(static_cast<float>((w * TILE_SIZE) + TILE_SIZE), static_cast<float>((h * TILE_SIZE) + TILE_SIZE));
            rVA[currentVertex + 3].position = sf::Vector2f(static_cast<float>(w * TILE_SIZE), static_cast<float>((h * TILE_SIZE) + TILE_SIZE));

            // ќпредел€ем позицию в текстуре дл€ текущего четырехугольника
            // “рава, камень, куст или стена
            if (h == 0 || h == worldHeight - 1 ||
                w == 0 || w == worldWidth - 1)
            {
                // »спользуем текстуру стены
                rVA[currentVertex + 0].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES, TILE_SIZE*(index-1));
                rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES + TILE_SIZE, TILE_SIZE*(index-1));
                rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES + TILE_SIZE, TILE_SIZE*index);
                rVA[currentVertex + 3].texCoords = sf::Vector2f(TILE_SIZE * TILE_TYPES, TILE_SIZE*index);
            }
            else
            {
                std::uniform_int_distribution<> dis(0, TILE_TYPES - 1); 
                // »спользовать случайную текстуру пола
                int mOrG = dis(gen);
                int verticalOffset = mOrG * TILE_SIZE;
                rVA[currentVertex + 0].texCoords = sf::Vector2f(static_cast<float>(verticalOffset), TILE_SIZE * (index - 1));
                rVA[currentVertex + 1].texCoords = sf::Vector2f(static_cast<float>(verticalOffset + TILE_SIZE), TILE_SIZE * (index - 1));
                rVA[currentVertex + 2].texCoords = sf::Vector2f(static_cast<float>(verticalOffset + TILE_SIZE), TILE_SIZE * index);
                rVA[currentVertex + 3].texCoords = sf::Vector2f(static_cast<float>(verticalOffset), TILE_SIZE * index);
            }

            // ѕозици€ готова дл€ следующих четырех вершин
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }


    return TILE_SIZE;
}

