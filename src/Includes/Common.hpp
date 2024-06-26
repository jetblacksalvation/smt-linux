#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <functional>
#include "CommonMath.hpp"
#include "./IState/GameState.hpp"
enum DIRECTIONS { LEFT, RIGHT, UP, DOWN, ROT_LEFT, ROT_RIGHT }; 

class Game:public std::enable_shared_from_this<Game>{
public:
	typedef std::shared_ptr<Game>			  TGameInstance; 
	static std::shared_ptr<IPlayerState>	  playerState;
	static TGameInstance 					  gameInstance;
	WorldHelper 							  worldData; 


	Game();
	void run();
};

