#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <SFML/System/Vector2.hpp>
#include <cmath>
#define M_PI           3.14159265358979323846  /* pi */
#include <fstream> 
#include <thread>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp> 
#include <unordered_map>

class IPlayerState: public std::enable_shared_from_this<IPlayerState> {
public:
	//variables 
    static sf::Event event;

    static inline bool keys[6] = {0,0,0,0,0,0};
    static float angle; 
    static const float constexpr magicAngleOffset = M_PI / 4; //exists because of how i render... keep this in mind

    IPlayerState() {
        isLoaded = false;
    };

    // Renderer::TStateEventVec myEventHanlders {};

    virtual ~IPlayerState() = default;
     
	virtual void HandleState() {
		static_assert("ERR: This object has no defined virtual override for HanldeState!\n");
	}

    virtual void OnLoad() {
        static_assert("ERR: This object has no defined virtual override for OnLoad!\n");

    };

    bool isLoaded;
    
private:

};

// This state shall run in the background and not be affected by the current state of the player. It is used for things like music, printing debug info, and grabbing player input...
// hopefully...
// while IPlayerState runs only one instance at a time, StateRegistrar will run all registered instances of IBackgroundState. Unless IBackgroundState is disbaled or destroyed
class IBackgroundState : public std::enable_shared_from_this<IBackgroundState> {
public:
    IBackgroundState() {
        isLoaded = false;
        isDestroyed = false;
    };

    // Renderer::TStateEventVec myEventHanlders {};

    virtual ~IBackgroundState() = default;

    virtual void HandleState() {
        static_assert("ERR: This object has no defined virtual override for HanldeState!\n");
    }

    virtual void OnLoad() {
        static_assert("ERR: This object has no defined virtual override for OnLoad!\n");

    };

    bool isLoaded;
    bool isDestroyed;

};

class PlayerStateRegistrar{
public:
    static inline std::shared_ptr<IPlayerState> currentState;
    template <typename T, typename = void>
    static void registerInstance(const std::shared_ptr<T>& instance) {

        for (auto it : instances) {
            //std::cout << it.first.name() << " : "<<typeid(T).name() << " ?= " << instance << std::endl;//debug

            if (it.first.name() == typeid(T).name()) {
                std::cout << "Instance of type " << typeid(T).name() << " already registered." << std::endl;

                return;
            }
        }
        instances[typeid(T)] = instance;
        std::cout << "NEW: Instance of type " << typeid(T).name() << " registered!" << std::endl;

        
    }

    template <typename T>
    static std::shared_ptr<IPlayerState> getInstance() {
        auto it = instances.find(typeid(T));
        if (it != instances.end()) {
            return (it->second);
        }
        else {
            throw std::runtime_error(std::string("ERR: getInstance could not find type ") + std::string(typeid(T).name()) + "!");

        }
    }
    template <typename T>
    static std::shared_ptr<IBackgroundState> getBackGroundInstance() {
        auto it = background_instances.find(typeid(T));
        if (it != background_instances.end()) {
            return (it->second);
        }
        else {
            throw std::runtime_error(std::string("ERR: getBackGroundInstance could not find type ") + std::string(typeid(T).name()) + "!");

        }
    }
    template<typename T, typename = std::enable_if_t<std::is_base_of<IBackgroundState, T>::value&& std::is_default_constructible<T>::value>>
    static void AddBackgroundInstance() {
        std::cout << "Changing global state...\n";
        try {

            //std::shared_ptr<IBackgroundState> v = PlayerStateRegistrar::getBackGroundInstance<T>();
			background_instances[typeid(T)] = std::make_shared<T>();

        }
        catch (const std::runtime_error& error) {
            std::cout << "Registered " << typeid(T).name() << std::endl;
        }

    }
    template<typename T, typename = std::enable_if_t<std::is_base_of<IBackgroundState, T>::value&& std::is_default_constructible<T>::value>>
    static void RemoveBackgroundInstance() {
        std::cout << "Changing global state...\n";
        try {

            background_instances.erase(typeid(T));

        }
        catch (const std::runtime_error& error) {
            std::cout << "Could not find or remove " << typeid(T).name() << std::endl;
        }

    }

    template<typename T, typename = std::enable_if_t<std::is_base_of<IPlayerState,T>::value && std::is_default_constructible<T>::value>>
    static void HandleChangeState() {
        std::cout << "Changing global state...\n";
        try {

            std::shared_ptr<IPlayerState> v  = PlayerStateRegistrar::getInstance<T>();

            currentState = v;

        }
        catch (const std::runtime_error& error) {
            PlayerStateRegistrar::registerInstance(std::make_shared<T>());

            currentState = instances[typeid(T)];
            std::cout << "Registered " << typeid(T).name() << std::endl; 
        }

    }

    template <typename U>
    static void HandleChangeState(U&& value) {
        std::cout << "Changing global state with value...\n";
        PlayerStateRegistrar::registerInstance(std::make_shared<std::remove_reference_t<U>>(std::forward<U>(value)));
        try {
            currentState = PlayerStateRegistrar::getInstance<std::remove_reference_t<U>>();

        }
        catch (const std::runtime_error& error) {

        }
    }
    static void Run()
    {
        currentState->HandleState();

		for (auto it : background_instances) {
			if (!it.second->isDestroyed) {
				it.second->HandleState();
			}
		}

    }
    static void PrintInfo() {
        for (auto it : instances) {
            std::cout << it.first.name() << " -> " << it.second << std::endl; 
        }
    }
private:
    static std::unordered_map<std::type_index, std::shared_ptr<IPlayerState>> instances;


    static std::unordered_map<std::type_index, std::shared_ptr<IBackgroundState>> background_instances;

};

/*
    Wtf was i smoking why did i write this and never use it
    edit ngl this one is useful asf
    
*/
#define GetInstance(arg) (*(arg*)PlayerStateRegistrar::getInstance<arg>().get())


#endif