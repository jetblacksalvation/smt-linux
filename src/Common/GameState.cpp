#include "GameState.hpp"
// re-decs

#include "CommonMath.hpp"
#include "Common.hpp"
std::unordered_map<std::type_index, std::shared_ptr<IPlayerState>> PlayerStateRegistrar::instances;

sf::Event IPlayerState::event;
float IPlayerState::angle  = 0; 

void RoamingState::setGridPos(const sf::Vector2<uint32_t> &&vec)
{
    setGridPos(vec);
};
void RoamingState::setGridPos(const sf::Vector2<uint32_t> &vec)
{
    this->gridPos = (sf::Vector2u)vec;
    playerPos = sf::Vector2f{((float)(vec.x) * 100) + 100, ((float)(vec.y) * 100) + 200};
};

void RoamingState::OnLoad()
{
    setGridPos({1, 2});
    // offset each point via player offset in world array

    windowSize = Game::gameInstance->window->getSize();

    // a scale factor of ten seems to work ?
}

// GameState::GameState()
// {
//     angle = M_PI / 4;
//     PlayerStateRegistrar::HandleChangeState<RoamingState>();
// }
RoamingState::RoamingState()
{
    std::cout << "Roaming State Instantiated!\n";
    gridData = GridHelper(this);

    texture.loadFromFile("brickWall.png");
    sprite.setTexture(texture);
    OnLoad();
}
void RoamingState::MovePlayer()
{
    std::cout << faceIndex << " is face index\n";
    sf::Vector2u newPosition = gridPos;

    switch (faceIndex)
    {
    case 0:
        newPosition.y += 1;
        break;  
    case 1:
        newPosition.x -= 1;
        break;
    case 2:
        newPosition.y -= 1; 
        break;
    case 3:
        newPosition.x += 1;
        break;
    default:
        std::cerr << "Invalid face index\n";
        return;
    }

    if (newPosition.x < gridData.gridData.size() && newPosition.y < gridData.gridData[newPosition.x].size())
    {
        if (gridData.gridData[newPosition.x][newPosition.y] == 0)
        {
            setGridPos(newPosition);
        }
    }
}

void RoamingState::HandleState()
{



    // do something

    while (Game::gameInstance->window->pollEvent(IPlayerState::event) && !this->blockInput)
    {
        if (IPlayerState::event.type == IPlayerState::event.Closed)
        {
            std::cout << "Closing\n";
            Game::gameInstance->window->close();
            abort();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        {
            std::cout << "ECHO PPOS\n";
            std::cout << "current pos = " << playerPos.x << ", " << playerPos.y << std::endl;
            std::cin >> playerPos.x;
            std::cin >> playerPos.y;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            // show 2d representation for the world...
            // it is seperate state, for menu. for now its debug
            PlayerStateRegistrar::HandleChangeState<MenuState>();
            return;
        }

        IPlayerState::keys[ROT_RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
        IPlayerState::keys[ROT_LEFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);

        IPlayerState::keys[UP] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        IPlayerState::keys[LEFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        IPlayerState::keys[DOWN] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        IPlayerState::keys[RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    }
    // float offset = M_PI / 4;
    // int face = 0;
    // float faces[4] = { 0 + offset, (M_PI / 2) + offset, (M_PI)+offset, 3 * (M_PI / 2) + offset };
    if (IPlayerState::keys[UP])
    {
        std::cout << gridPos.x << ", " << gridPos.y << std::endl;

        std::cout << "max = " << gridData.gridData.size() << ", " << gridData.gridData[gridPos.x].size() << std::endl;
        std::cout << "facesIndex :" << faces[faceIndex] << std::endl;

        // PlayerStateRegistrar::HandleChangeState<MenuState>();

        MovePlayer();

        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // this handles rotations, for the game world. this works by using the player as the center of the transformation ...
    }
    // offset anlge by M_PI

    if (IPlayerState::keys[ROT_LEFT])
    {
        (this->faceIndex - 1 < 0) ? faceIndex = 3 : this->faceIndex--;
    }
    if (IPlayerState::keys[ROT_RIGHT])
    {
        // new comment
        (this->faceIndex + 1 > 3) ? faceIndex = 0 : faceIndex++;
        // delta of this
    }
    std::cout << "INDEX = " << faceIndex << std::endl;

if (IPlayerState::keys[ROT_LEFT] || IPlayerState::keys[ROT_RIGHT]) {
    // Calculate the midpoint angle
    float midpointAngle = (IPlayerState::angle + faces[faceIndex]) / 2.0f;
    Game& game = *Game::gameInstance.get();
    Game::TWindowPtr& window = game.window;
    // Perform other actions (e.g., draw3DScene())

    // Update the angle
    IPlayerState::angle = midpointAngle;
    draw3DScene();
    std::this_thread::sleep_for(std::chrono::milliseconds(175));
    window->clear(sf::Color::White);
    IPlayerState::keys[ROT_RIGHT] = false;
    IPlayerState::keys[ROT_LEFT]  = false; 
}

    if (IPlayerState::angle < 0.0)
    {
        IPlayerState::angle += 2 * M_PI;
    }
    else if (IPlayerState::angle >= 2 * M_PI)
    {
        IPlayerState::angle -= 2 * M_PI;
    }
    // std::cout << "IN ROAMING\n";
    for(auto angle : faces){
        if(IPlayerState::angle != angle){
            std::cout<<angle <<":: isn't angle;\n";
        }
        else{
            std::cout<<angle <<":: is angle --- CHECK;\n";

        }
    }
    IPlayerState::angle = faces[faceIndex];

    draw3DScene();

}

void RoamingState::draw3DScene()
{
    Game &game = *Game::gameInstance.get();
    WorldHelper::T_WorldObjects &allWorldShapes = game.worldData.worldObjects;
    Game::TWindowPtr &window = game.window;

    int rayNum = 100;
    auto angle = IPlayerState::angle;

    for (int i = 0; i <= rayNum; ++i)
    {
        float distance = 0;
        sf::Vector2f interceptToDraw;
        sf::Vector2f p3Closest;
        sf::Vector2f p4Closest;

        for (auto it : allWorldShapes)
        {
            sf::Transform transform;
            transform.rotate(angle, playerPos.x, playerPos.y);

            std::vector<sf::Vector2f> transformedPoints;
            for (int indexOfObjectVec = 0; indexOfObjectVec < it.size(); indexOfObjectVec++)
            {
                sf::Vector2f rotatedPoint = transform.transformPoint(it[indexOfObjectVec]);
                transformedPoints.push_back(rotatedPoint);
            }

            float angleInRadians = i * (M_PI / 180.0);

            for (int x = 0; x < it.size() - 1; x++)
            {
                sf::Vector2f playerRayEnd;
                playerRayEnd.x = (cosf(angle + angleInRadians) * 1000) + playerPos.x;
                playerRayEnd.y = (sinf(angle + angleInRadians) * 1000) + playerPos.y;

                auto p3 = it[x];
                auto p4 = it[x + 1];
                sf::Vector2f *interceptPoint = calc_hit(p3, p4, playerPos, playerRayEnd);

                if (interceptPoint)
                {
                    float currDistance = std::hypotf(playerPos.x - interceptPoint->x, playerPos.y - interceptPoint->y);
                    if (distance == 0 || currDistance < distance)
                    {
                        distance = currDistance;
                        interceptToDraw = *interceptPoint;
                        p3Closest = p3;
                        p4Closest = p4;
                    }
                    delete interceptPoint;
                }
            }
        }

        if (distance > 0)
        {
            sf::Vector2f wallVector = p4Closest - p3Closest;
            float wallLength = std::sqrt(wallVector.x * wallVector.x + wallVector.y * wallVector.y);
            float distanceAlongWall = ((interceptToDraw.x - p3Closest.x) * (wallVector.x / wallLength) + (interceptToDraw.y - p3Closest.y) * (wallVector.y / wallLength));
            float textureX = distanceAlongWall / wallLength;
            float columnHeight = windowSize.y / (distance * 0.02f);

            // Calculate the position of the column
            float columnX = i * (windowSize.x / rayNum);
            float columnY = (windowSize.y - columnHeight) / 2.0f;

            // Ensure the column stays within the bounds of the screen
            if (columnX + (windowSize.x / rayNum) > windowSize.x)
            {
                columnX = windowSize.x - (windowSize.x / rayNum);
            }

            // Create and draw the column
            sf::RectangleShape column(sf::Vector2f(windowSize.x / rayNum, columnHeight));
            column.setPosition(columnX, columnY);
            int texX = static_cast<int>(textureX * texture.getSize().x);
            column.setTexture(&texture);
            sf::IntRect textureRect(texX, 0, 1, texture.getSize().y);
            column.setTextureRect(textureRect);
            window->draw(column);
        }
    }

    window->display();
}

// PlayerState::GameState()
//{
// }
