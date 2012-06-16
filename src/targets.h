
#define NEUTRAL 0
#define HOSTILE 1
#define FRIENDLY 2

#include <vector>

class TargetableObject{
    private:
        unsigned int friendlyState;
        std::string tdesc;
        std::string tname;
        std::string ttype; 
    public:
        TargetableObject(std::string tname,std::string tdesc,std::string ttype);
        bool isHostile();
        bool isFriendly();
        std::string getTName();
        std::string getTDesc();
        std::string getTType();
};

class Targets{ //Singleton
    private: 
        std::vector<TargetableObject> allTargets;
        unsigned int index;
    public:
        static Targets& getInstance(){
            static Targets instance; 
            return instance;
        }
        Targets();
        void addTarget(TargetableObject newobj);
        TargetableObject* cycleTarget();
        TargetableObject* cycleHostileTarget();
        TargetableObject* cycleFriendlyTarget();
};
