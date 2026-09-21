#include "../Includes/IState/GameState.hpp"
#include "../Includes/Common.hpp"
#include "Grid.hpp"
#include "PlayerState.hpp"
#include <sstream>
GridHelper::GridHelper() {
   //safer to not default initialize because im trying to obtain a registered state before its fully constructed.
   
}
void GridHelper::gridToWorld() {

    const int scaleFactor = 100;
    WorldHelper::T_WorldObjects& allWorldShapes = Game::gameInstance->worldData.worldObjects;
    std::cout << "Populating world...\n";
    auto& playerData = GetInstance(RoamingState);

    //my stupid ahh, if x=0 the walls would be screwed up. so i have magic number here to offset when needed, and it starts at 1 so calcs dont get fucked 
    WorldHelper::T_PrimitiveShape points({ sf::Vector2f{-50,50}, sf::Vector2f{50, 50}, sf::Vector2f{-50,50 }, sf::Vector2f{-50,150},  sf::Vector2f{50,150},sf::Vector2f{50,50 } });//last index is so that lines can wrap back to start 

    int vertexCount = 0;

    for (uint32_t x = 1; x <= this->gridData.size(); x++)
    {
        for (uint32_t y = 1; y <= this->gridData[x - 1].size(); y++)
        {
            WorldHelper::T_PrimitiveShape temp;

            if (gridData[x - 1][y - 1] == 1)
            {
                for (auto point : points)
                {
                    temp.push_back({
                        point.x + x * scaleFactor,
                        point.y + y * scaleFactor
                        });
                }
            }

            if (gridData[x - 1][y - 1] == 2)
            {
                std::cout << "Spawn: "
                    << x << ", "
                    << y << '\n';

                playerData.setGridPos({ x-1, y-1 });
            }

            if (!temp.empty())
            {
                ++vertexCount;
                allWorldShapes.push_back(temp);
            }
        }
    }
}
 GridHelper::GridHelper(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Could not open grid file: " + path
        );
    }

    gridData.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream stream(line);
        std::vector<int> row;
        int value;

        while (stream >> value)
        {
            row.push_back(value);
        }

        if (row.empty())
            continue;

        if (!gridData.empty() &&
            row.size() != gridData[0].size())
        {
            throw std::runtime_error(
                "Invalid map: rows have different lengths"
            );
        }

        gridData.push_back(row);
    }

    std::cout << "Loaded grid: " << path << '\n';
    std::cout << "Rows: " << gridData.size() << '\n';

    if (!gridData.empty())
    {
        std::cout << "Columns: "
            << gridData[0].size()
            << '\n';
    }
}