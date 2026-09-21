#ifndef PLAYERSTATE_HPP
#define PLAYERSTATE_HPP
#include <SFML/System/Vector2.hpp>
#define M_PI           3.14159265358979323846  /* pi */
#include <fstream> 
#include "Grid.hpp"
#include <SFML/Graphics.hpp> 
#include "./IState/GameState.hpp"
#include <string>
class RoamingState : public IPlayerState {
public:
    RoamingState();
    sf::Vector2f playerPos = { 0,0 };
    sf::Vector2<uint32_t> gridPos = {0,0 };
    std::string currentLevel = "levels/level0";
    //grid position is used to set playerPos... cry about it because its bad. not enough that i remove it though :P
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Keyboard lastKey; 

    float offset = (float)M_PI / 4.F;
    int faceIndex = 0;
    float faces[4] = { 0 + offset, ((float)M_PI / 2) + offset, ((float)M_PI) + offset, 3 * ((float)M_PI / 2) + offset};


    GridHelper gridData{
        (std::string(ASSET_PATH) + "levels/level0/map.txt")
    };
    void setGridPos(const sf::Vector2<uint32_t>&&);
    void setGridPos(const sf::Vector2<uint32_t>&);

    void MovePlayer();
    void HandleState();
    void OnLoad() ;
    void draw3DScene();
    sf::Vector2u windowSize ;

};

#endif