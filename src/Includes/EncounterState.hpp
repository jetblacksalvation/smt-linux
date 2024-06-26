#ifndef EncounterStateDef 
#define EncounterStateDef 1 
#include "./IState/GameState.hpp"

class EncounterState : public IPlayerState {
public:


    class EncounterT{
        
    };
    class IEncounterEntry{

        inline static const char* enemy_src_path_ = "./enemy_src";


    };          
    class IEncounterEntryLoader: public IEncounterEntry{
        IEncounterEntryLoader(){
            
        }
    };
    class IEncounterFactoryConfig;//settings here apply both to factory and its entries...
    class IEncounterFactory; 

    EncounterState();




    void OnLoad() override{

    }
    void HandleState() override{


    };
};


#endif