#ifndef RENDERER
#define RENDERER
#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../Includes/Common.hpp"
class Renderer {
public:
	using TEventFunction	 = std::function<void(sf::Event)>;
	using TConditionalFunc   = std::pair<TEventFunction, std::shared_ptr<IPlayerState>>;
	using TWindowPtr		 = std::unique_ptr<sf::RenderWindow>;
	using TStateEventVec	 = std::vector<TConditionalFunc>;

	static inline TWindowPtr   window;
	static inline sf::Event    event;

	static inline void SetStateHandler(TStateEventVec vec) {
		Renderer::_stateEvents = vec;
	}

private:

	static inline void _renderThread() {
		while (window->pollEvent(IPlayerState::event) && !_blockInput) {
			for (auto& conditional_pair : _stateEvents) {
				conditional_pair.first(Renderer::event);
			}

			IPlayerState::keys[UP]		  = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			IPlayerState::keys[LEFT]	  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			IPlayerState::keys[DOWN]	  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			IPlayerState::keys[RIGHT]	  = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			IPlayerState::keys[ROT_LEFT]  = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
			IPlayerState::keys[ROT_RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		}
	}

	static inline bool _blockInput = false;
	static inline TStateEventVec _stateEvents = {};
	static inline sf::Thread _RenderThread = sf::Thread(&_renderThread);

};

#endif

