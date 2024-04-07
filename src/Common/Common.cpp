#include "Common.hpp"
#include "SFML/Graphics.hpp"
Game::TWindowPtr Game::window;
Game::TGameInstance Game::gameInstance; // helper obj, its so that game state can grab whatever is needed.



Game::Game() {
    //instanceList.push_back(std::make_shared<Game>(this));
    gameInstance = std::shared_ptr<Game>(this);
    
    

    if (!window) {
        window = std::make_unique< sf::RenderWindow>();
        (*window).create({ 800,800 }, "Shin Megami Tensei");
        // Check if window creation was successful
        if (!window) {
            
            // Handle the error, perhaps throw an exception or exit the program
        }
    }
    else {
        // Handle the case where the window is already created
    }

    GameState inst{};
}
void Game::run() {
    //WorldHelper::T_PrimitiveShape points({ sf::Vector2f{-50,50}, sf::Vector2f{50, 50}, sf::Vector2f{-50,50 }, sf::Vector2f{-50,150},  sf::Vector2f{50,150},sf::Vector2f{50,50 } });//last index is so that lines can wrap back to start 
    
    std::cout << "Hello Rotation!\n";

    window->setFramerateLimit(60);
    //square 




    std::cout << "Hello Rotation!\n";
    auto windowSize = window->getSize();

    while (window->isOpen()) {


        //eventually the movement will be changed, for now this will do.
            

            
        window->clear(sf::Color::White);
        //draw3DScene(this->worldData.worldObjects, angle, playerPos);
        std::cout<<GameState::playerStateInstance<<" is the inst <<\n";
        GameState::playerStateInstance->HandleState();


    }
    exit(0);
}
