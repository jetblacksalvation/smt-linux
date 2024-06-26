#ifndef GameMenuDef
#define GameMenuDef
#include "./IState/GameState.hpp"
#include "./IRenderer/Renderer.hpp"
class MenuState : public IPlayerState {
public:
    MenuState();
    
    sf::Vector2f playerPos = {400,400};
    sf::Vector2u windowSize;
    sf::Font     font;
    Renderer::TWindowPtr& window = Renderer::window;

    void HandleState();
    void OnLoad();
    void draw2DScene();
};
#endif