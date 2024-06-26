#include "SFML/Graphics.hpp"
#include "../Includes/IRenderer/Renderer.hpp"
#include "../Includes/IState/GameState.hpp"
#include "../Includes/Common.hpp"
std::shared_ptr<IPlayerState> Game::playerState;
Game::TGameInstance Game::gameInstance;

Game::Game()
{
    gameInstance = std::shared_ptr<Game>(this);

    if (!Renderer::window)
    {
        Renderer::window = std::make_unique<sf::RenderWindow>();
        Renderer::window->create({800, 800}, "Shin Megami Tensei");
    }
    std::cout << "created roaming state\n";
    PlayerStateRegistrar::HandleChangeState<RoamingState>();
}
void Game::run()
{
    Renderer::window->setFramerateLimit(60);
    Renderer::window->setVerticalSyncEnabled(true);

    // activate the window
    Renderer::window->setActive(true);


    while (Renderer::window->isOpen())
    {
        Renderer::window->clear(sf::Color::White);
        PlayerStateRegistrar::currentState->HandleState();
    }
    exit(0);
}
