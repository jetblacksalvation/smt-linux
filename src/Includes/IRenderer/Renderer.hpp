#ifndef RENDERER
#define RENDERER
#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class IEvent {
	using TEventFunction   = std::function<void(sf::Event)>;
	using TConditionalFunc = std::pair<TEventFunction, std::shared_ptr<IEvent>>;
	using TStateEventVec   = std::vector<TConditionalFunc>;

	static inline sf::Keyboard keys;
	static inline sf::Event   event;

	static inline void SetEventHanlder(TStateEventVec vec) {
		/*
			Invoked by State Implementations, or by anything that must interact with IEvent.

		*/
		
		IEvent::_stateEvents = vec;
	}
};

class Renderer {
public:

	using TWindowPtr		 = std::unique_ptr<sf::RenderWindow>;

	static inline TWindowPtr   window;



private:

	static inline void _renderThread() {
		while (window->pollEvent(IEvent::event) && !_blockInput) {
			for (auto& conditional_pair : _stateEvents) {
				conditional_pair.first(Renderer::event);
			}


		}
	}

	static inline bool _blockInput = false;
	static inline TStateEventVec _stateEvents = {};
	static inline sf::Thread _RenderThread = sf::Thread(&_renderThread);

};

#endif

