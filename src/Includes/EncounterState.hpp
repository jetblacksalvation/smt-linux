#ifndef EncounterStateDef 
#define EncounterStateDef 
#include "./IState/GameState.hpp"

class EncounterState : public IPlayerState {
public:

    EncounterState();//should keep it empty because if you are unlucky maybe it could try to get playerstate or some shi

    


    void OnLoad() override{

    }
    void HandleState() override{

    };

    //called probably by players roaming state sometimes, maybe sometimes by 
    void UpdateEncounters() 
    {
        
    }

    //called by  roaming state on move, 
    void RandomEncounters()
    {

    }
};


#endif