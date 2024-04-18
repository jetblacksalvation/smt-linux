#include "GameState.hpp"


MenuState::MenuState()
{
    std::cout << "Menu state created\n";
    windowSize = Game::gameInstance->window->getSize();
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load default font!" << std::endl;
    }
}
void MenuState::HandleState()
{
    // std::cout << "menu state active\n";
    auto &angle     = IPlayerState::angle;
    auto &window    = Game::gameInstance->window;
    auto &worldData = Game::gameInstance->worldData;

    while (Game::gameInstance->window->pollEvent(IPlayerState::event))
    {
        Game::gameInstance->mousePos = sf::Mouse::getPosition(*Game::gameInstance->window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {

            auto ptr = PlayerStateRegistrar::getInstance<RoamingState>();
            ptr->isLoaded = true;
            // PlayerStateRegistrar::PrintInfo();
            PlayerStateRegistrar::HandleChangeState<RoamingState>();
            // PlayerStateRegistrar::PrintInfo();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            auto &playerData = *(RoamingState *)PlayerStateRegistrar::getInstance<RoamingState>().get();
            std::cout << playerData.faceIndex << " : index\n";
            std::cout << playerData.playerPos.x << ", " << playerData.playerPos.y << " is player pos" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            // auto& playerData = *(RoamingState*)PlayerStateRegistrar::getInstance<RoamingState>().get();
            // sf::Vector2u update;
            // std::cin >> update.x;
            // std::cin >> update.y;
            // update.y++;
            // update.x *= 100;
            // update.y *= 100;
            // std::cin.clear();

            // playerData.setGridPos({ update });
        }
        IPlayerState::keys[UP]        = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        IPlayerState::keys[LEFT]      = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        IPlayerState::keys[DOWN]      = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        IPlayerState::keys[RIGHT]     = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        IPlayerState::keys[ROT_LEFT]  = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
        IPlayerState::keys[ROT_RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    }
    if (IPlayerState::keys[UP])
    {
        for (auto &it : worldData.worldObjects)
        {
            for (auto &vec : it)
            {
                vec.x += cosf(angle - (3 * (M_PI / 4))) * 2.5f;
                vec.y += sinf(angle - (3 * (M_PI / 4))) * 2.5f;
            }
        }
    }
    if (IPlayerState::keys[ROT_LEFT])
    {
        IPlayerState::angle -= 0.05;
    }
    if (IPlayerState::keys[ROT_RIGHT])
    {
        IPlayerState::angle += 0.05;
    }
    if (IPlayerState::angle < 0.0)
    {
        IPlayerState::angle += 2 * M_PI;
    }
    else if (IPlayerState::angle >= 2 * M_PI)
    {
        IPlayerState::angle -= 2 * M_PI;
    }
    window->clear(sf::Color::White);
    auto &playerData = *(RoamingState *)PlayerStateRegistrar::getInstance<RoamingState>().get();

    for (unsigned int x = 0; x < playerData.gridData.gridData.size(); x++)
    {
        for (unsigned int y = 0; y < playerData.gridData.gridData[x].size(); y++)
        {
            if (playerData.gridPos == sf::Vector2u{x, y})
            {
                std::cout << "p ";
            }
            else
                std::cout << playerData.gridData.gridData[x][y] << ' ';
        }
        std::cout << std::endl;
    }
    draw2DScene();
}

void MenuState::OnLoad()
{
}
void MenuState::draw2DScene()
{
    auto worldData = Game::gameInstance->worldData;
    auto &window = Game::gameInstance->window;
    float angle = IPlayerState::angle;
    auto &playerData = *(RoamingState *)PlayerStateRegistrar::getInstance<RoamingState>().get();
    playerPos = playerData.playerPos;
    sf::Texture texture;
    texture.loadFromFile("Arrow.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition({400, 400});
    sprite.setRotation((angle + (3 * (M_PI / 4))) * (180.0 / M_PI));
    sprite.setOrigin(16, 16);
    window->draw(sprite);

    // Load default font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load default font!" << std::endl;
    }

    // Create text for collision
    sf::Text collisionText;
    collisionText.setFont(font);
    collisionText.setString("Collision!"); // Set a simple string for testing
    collisionText.setCharacterSize(24);
    collisionText.setFillColor(sf::Color::Red);

    for (auto it : worldData.worldObjects)
    {
        sf::VertexArray objToDraw(sf::LinesStrip, it.size());
        for (int indexOfObjectVec = 0; indexOfObjectVec < it.size(); indexOfObjectVec++)
        {
            // Apply the rotation transform to each vertex
            sf::Vector2f rotatedPoint = it[indexOfObjectVec];
            objToDraw[indexOfObjectVec].position.x = rotatedPoint.x - playerPos.x + 400;
            objToDraw[indexOfObjectVec].position.y = rotatedPoint.y - playerPos.y + 400;
            objToDraw[indexOfObjectVec].color = sf::Color::Black;
        }

        if (objToDraw.getBounds().contains(Game::gameInstance->mousePos.x, Game::gameInstance->mousePos.y))
        {
            // Draw labels at each corner
            for (const sf::Vector2f &vertex : it)
            {
                // Convert the vertex position to screen coordinates
                sf::Vector2f screenPos = vertex - playerPos + sf::Vector2f(400.f, 400.f);

                // Draw text label at each corner
                sf::Text cornerLabel;
                cornerLabel.setFont(font);
                cornerLabel.setString("(" + std::to_string(static_cast<int>(vertex.x)) + ", " + std::to_string(static_cast<int>(vertex.y)) + ")");
                cornerLabel.setCharacterSize(14);
                cornerLabel.setFillColor(sf::Color::Blue);
                cornerLabel.setPosition(screenPos);
                window->draw(cornerLabel);
            }
        }

        if (objToDraw.getBounds().contains(Game::gameInstance->mousePos.x, Game::gameInstance->mousePos.y))
        {
            // Draw collision text
            collisionText.setString("CUBE ID:");
            collisionText.setPosition(Game::gameInstance->mousePos.x, Game::gameInstance->mousePos.y);
            window->draw(collisionText);
        }
        window->draw(objToDraw);
    }

    window->display();
}
