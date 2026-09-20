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
    GridHelper(std::ifstream);
    void gridToWorld(); //loads datas into world... 

    struct ObjectTypeWithOptionalEvent
    {
        char wallType; // 
        std::optional<std::string> id;// id can be unique or not, it determins what the function associated with the cell will do. 
    };


    std::vector<std::vector<int>> gridData; 
    
    void loadGrid();

    // sf::Vector2f getPlayerPosFromFileOrStorage();
    

private:
    std::vector<int> gridValues; 
};


#endif