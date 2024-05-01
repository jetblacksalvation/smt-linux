#ifndef GameState
#define GameState 1
#include <cmath>

#define M_PI           3.14159265358979323846  /* pi */

#include <fstream> 
#include <thread>

#include <typeindex>
#include <type_traits>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp> 
//apparently the fastest hash map in c++ stl
//eventually add scenario interpreter
#include <unordered_map>
/*
    wrapps TplayerState... game only invokes player state, ill clean up what is and isn't used later.
    this object persists beyond this scope, within PlayerStateRegistrar

*/
class IPlayerState: public std::enable_shared_from_this<IPlayerState> {
public:
	//variables 
    bool blockInput = false;
    static sf::Event event;

    static inline bool keys[6] = {0,0,0,0,0,0};
    static float angle; 
    static const float constexpr magicAngleOffset = M_PI / 4; //exists because of how i render... keep this in mind

    IPlayerState() {
        isLoaded = false;
    };

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
            throw std::runtime_error("ERR: getInstance could not find type " + std::string(typeid(T).name()) + "!");

        }
    }
    template<typename T, typename = std::enable_if_t<std::is_default_constructible<T>::value>>
    static void HandleChangeState() {
        std::cout << "Changing global state...\n";
        try {

            std::shared_ptr<IPlayerState> v  = PlayerStateRegistrar::getInstance<T>();

            currentState = v;

        }
        catch (...) {
            PlayerStateRegistrar::registerInstance(std::make_shared<T>());
            std::cout << "Registered " << typeid(T).name() << std::endl; 
            currentState = instances[typeid(T)];
        }

    }

    template <typename U>
    static void HandleChangeState(U&& value) {
        std::cout << "Changing global state with value...\n";
        PlayerStateRegistrar::registerInstance(std::make_shared<std::remove_reference_t<U>>(std::forward<U>(value)));
        currentState = PlayerStateRegistrar::getInstance<std::remove_reference_t<U>>();
    }
    static void PrintInfo() {
        for (auto it : instances) {
            std::cout << it.first.name() << " -> " << it.second << std::endl; 
        }
    }
private:
    static std::unordered_map<std::type_index, std::shared_ptr<IPlayerState>> instances;
};
#define GetInstance(arg) *(arg*)PlayerStateRegistrar::getInstance<arg>().get()









class RoamingState : public IPlayerState {
public:
    RoamingState();
    sf::Vector2f playerPos = { 0,0 };
    sf::Vector2<uint32_t> gridPos = {3,1 };
    //grid position is used to set playerPos... cry about it because its bad. not enough that i remove it though :P
    sf::Texture texture;
    sf::Sprite sprite;


    sf::Keyboard lastKey; 

    float offset = (float)M_PI / 4.F;
    int faceIndex = 0;
    float faces[4] = { 0 + offset, ((float)M_PI / 2) + offset, ((float)M_PI) + offset, 3 * ((float)M_PI / 2) + offset};

    class GridHelper {
    public: 
        GridHelper() {};
        GridHelper(RoamingState*);
        GridHelper(std::ifstream);
        void gridToWorld(); //loads datas into world... 
        std::vector<std::vector<int>> gridData; 
        
        void loadGrid();


    private:
        std::vector<int> gridValues; 
    };
    GridHelper gridData;

    void setGridPos(const sf::Vector2<uint32_t>&&);
    void setGridPos(const sf::Vector2<uint32_t>&);

    void MovePlayer();
    void HandleState();
    void OnLoad() ;
    void draw3DScene();
    sf::Vector2u windowSize ;

};
#include "Common.hpp"

#include "GameMenu.hpp"
#endif