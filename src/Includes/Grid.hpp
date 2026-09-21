#ifndef GRIDHELPER_HPP
#define GRIDHELPER_HPP
#include <SFML/System/Vector2.hpp>
#define M_PI           3.14159265358979323846  /* pi */
#include <typeindex>
#include <type_traits>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp> 
#include <unordered_map>
#include  "./IState/GameState.hpp"
class GridHelper {
public: 
    GridHelper() ;
    //GridHelper(RoamingState*);
    GridHelper(const std::string& path);
    void gridToWorld(); //loads datas into world... 


    std::vector<std::vector<int>> gridData; 
    
    void loadGrid();

    // sf::Vector2f getPlayerPosFromFileOrStorage();
    

private:
};


#endif