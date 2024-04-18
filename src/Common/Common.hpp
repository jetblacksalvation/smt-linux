
#pragma once 

#include "GameState.hpp"
#include "CommonMath.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN, ROT_LEFT, ROT_RIGHT }; //left is 0, right is 1, up is 2, down is 3

class Game:public std::enable_shared_from_this<Game>{
public:
	typedef std::unique_ptr<sf::RenderWindow> TWindowPtr;
	typedef std::shared_ptr<Game> TGameInstance; 

	static TWindowPtr	 				  window;
	static std::shared_ptr<IPlayerState>  playerState;
	static TGameInstance 				  gameInstance;

	WorldHelper 		 worldData; 
	sf::Vector2i 		 mousePos;
	
	Game();
	void run();
};

