#ifndef DEBUG_SERVICE
#define DEBUG_SERVICE
#include "../IState/GameState.hpp"
#include "../PlayerState.hpp"
#include "../IRenderer/Renderer.hpp"

class DebugService : public IBackgroundState
{
    void HandleState() {
        RoamingState& playerref = GetInstance(RoamingState);

        std::cout << playerref.angle << " is angle," << playerref.faceIndex << " is face index\n";

    }

};




#endif 