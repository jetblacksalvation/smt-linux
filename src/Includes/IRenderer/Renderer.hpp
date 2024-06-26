#ifndef RENDERER
#define RENDERER

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../IState/GameState.hpp"
class IEvent {
public:
	using TEventFunction   = std::function<void(sf::Event)>;
	using TConditionalFunc = std::pair<TEventFunction, std::shared_ptr<IPlayerState>>;
	using TStateEventVec   = std::vector<TConditionalFunc>;


	static inline void SetEventHanlder(TStateEventVec vec) {
		/*
			Invoked by State Implementations, or by anything that must interact with IEvent.

		*/
		
		IEvent::_stateEvents = vec;
	}
	static inline TStateEventVec GetStateEventVec()
	{
		return {};
	};
	static inline sf::Event      event;

private:
	static inline sf::Keyboard   _keys;
	static inline TStateEventVec _stateEvents;

};

class Renderer {
public:

	using TWindowPtr		 = std::unique_ptr<sf::RenderWindow>;

	static inline TWindowPtr   window;



private:

	static inline void _renderThread() {
		while (window->pollEvent(IEvent::event) && !_blockInput) {
			for (auto& conditional_pair : IEvent::GetStateEventVec()) {
				conditional_pair.first(IEvent::event);
			}


		}
	}

	static inline bool _blockInput = false;
	static inline sf::Thread _RenderThread = sf::Thread(&_renderThread);

};

#endif

