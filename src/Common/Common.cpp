#include "Common.hpp"
#include "SFML/Graphics.hpp"

Game::TWindowPtr Game::window;
std::shared_ptr<IPlayerState> Game::playerState;
Game::TGameInstance Game::gameInstance;

Game::Game()
{
    gameInstance = std::shared_ptr<Game>(this);

    if (!window)
    {
        window = std::make_unique<sf::RenderWindow>();
        window->create({800, 800}, "Shin Megami Tensei");
    }
    else
    {
        // Handle the case where the window is already created
    }
    std::cout << "created roaming state\n";
    PlayerStateRegistrar::HandleChangeState<RoamingState>();
}
void Game::run()
{

    window->setFramerateLimit(60);

    auto windowSize = window->getSize();

    while (window->isOpen())
    {

        // eventually the movement will be changed, for now this will do.

        window->clear(sf::Color::White);
        PlayerStateRegistrar::currentState->HandleState();
    }
    exit(0);
}
