#include "../Includes/IState/GameState.hpp"
#include "../Includes/IRenderer/Renderer.hpp"
#include "../Includes/Common.hpp"
#include "GameMenu.hpp"
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

    windowSize = Renderer::window->getSize();

}

IEvent::TEventFunction function = [](sf::Event event) {
    auto player = GetInstance(RoamingState);

    if (event.type == sf::Event::Resized)
    {
        // adjust the viewport when the window is resized
        
        //glViewport(0, 0, event.size.width, event.size.height);
    }
    if (IPlayerState::event.type == IPlayerState::event.Closed)
    {
        std::cout << "Closing\n";
        Renderer::window->close();
        exit(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    {
        std::cout << "ECHO PPOS\n";
        std::cout << "current pos = " << player.playerPos.x << ", " << player.playerPos.y << std::endl;
        std::cin >> player.playerPos.x;
        std::cin >> player.playerPos.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        PlayerStateRegistrar::HandleChangeState<MenuState>();
        return;
    }
    };

RoamingState::RoamingState()
{
    
    //auto myEventHanlders = { IEvent::TConditionalFunc{function, shared_from_this()}};


    std::cout << "Roaming State Instantiated!\n";
    gridData = GridHelper(this);
    texture.loadFromFile(std::string(ASSET_PATH) + "brickWall.png");
    sprite.setTexture(texture);
    OnLoad();
}
void RoamingState::MovePlayer()
{
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
    if (IPlayerState::keys[UP])
    {
        MovePlayer();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    if (IPlayerState::keys[ROT_LEFT])
    {
        (this->faceIndex - 1 < 0) ? faceIndex = 3 : this->faceIndex--;
    }
    if (IPlayerState::keys[ROT_RIGHT])
    {
        (this->faceIndex + 1 > 3) ? faceIndex = 0 : faceIndex++;
    }

    if (IPlayerState::keys[ROT_LEFT] || IPlayerState::keys[ROT_RIGHT]) {
        float midpointAngle          = (IPlayerState::angle + faces[faceIndex]) / 2.0f;
        Game& game                   = *Game::gameInstance.get();
        Renderer::TWindowPtr& window = Renderer::window;
        IPlayerState::angle          = midpointAngle;

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

    IPlayerState::angle = faces[faceIndex];

    draw3DScene();

}

void RoamingState::draw3DScene()
{
    Game &game                                  = *Game::gameInstance.get();
    WorldHelper::T_WorldObjects &allWorldShapes = game.worldData.worldObjects;
    Renderer::TWindowPtr &window                = Renderer::window;

    int rayNum = 100;
    auto angle = IPlayerState::angle;

    for (int i = 0; i <= rayNum; ++i)
    {
        float        distance = 0;
        sf::Vector2f interceptToDraw;
        sf::Vector2f p3Closest;
        sf::Vector2f p4Closest;
        float        rayRelativeAngle = i * (M_PI / 180.0);

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


            for (int x = 0; x < it.size() - 1; x++)
            {
                sf::Vector2f playerRayEnd;
                playerRayEnd.x = (cosf(angle + rayRelativeAngle) * 1000) + playerPos.x;
                playerRayEnd.y = (sinf(angle + rayRelativeAngle) * 1000) + playerPos.y;

                auto p3 = it[x];
                auto p4 = it[x + 1];
                sf::Vector2f *interceptPoint = calc_hit(p3, p4, playerPos, playerRayEnd);

                if (interceptPoint)
                {
                    float currDistance = std::hypotf(playerPos.x - interceptPoint->x, playerPos.y - interceptPoint->y);
                    if (distance == 0 || currDistance < distance)
                    {
                        distance        = currDistance;
                        interceptToDraw = *interceptPoint;
                        p3Closest       = p3;
                        p4Closest       = p4;
                    }
                    delete interceptPoint;
                }
            }
        }

        if (distance > 0)
        {
            distance               *= cosf(magicAngleOffset); // apparently this is supposed to fix the fish eye effect...
            sf::Vector2f wallVector = p4Closest - p3Closest;
            float wallLength        = std::sqrt(wallVector.x * wallVector.x + wallVector.y * wallVector.y);
            float distanceAlongWall = ((interceptToDraw.x - p3Closest.x) * (wallVector.x / wallLength) + (interceptToDraw.y - p3Closest.y) * (wallVector.y / wallLength));
            int texX                = static_cast<int>((distanceAlongWall / wallLength) * texture.getSize().x);
            float columnHeight      = windowSize.y / (distance /20.0f);
            float columnX           = i * (windowSize.x / rayNum);
            float columnY           = (windowSize.y - columnHeight) / 2.0f;

            if (columnX + (windowSize.x / rayNum) > windowSize.x)
            {
                columnX = windowSize.x - (windowSize.x / rayNum);
            }

            sf::RectangleShape column(sf::Vector2f(windowSize.x / rayNum, columnHeight));
            column.setPosition(columnX, columnY);
            column.setTexture(&texture);

            sf::IntRect textureRect(texX, 0, 1, texture.getSize().y);
            column.setTextureRect(textureRect);
            window->draw(column);
        }
    }

    window->display();
}