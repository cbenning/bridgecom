
#include <irrlicht.h> 
#include <string>
#include <iostream>

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;

#define MAX_SHIP_MODELS 1

class Ship
{
private:
    std::string shipModel[MAX_SHIP_MODELS];
    f32 movementSpeed;
    scene::IAnimatedMesh* mesh;
    scene::IAnimatedMeshSceneNode* node;
public:
    Ship(ISceneManager* smgr, IVideoDriver* driver, const int model);
    core::vector3df getPosition();
    void setPosition(core::vector3df pos);
    core::vector3df getRotation();
    void setRotation(core::vector3df rot);
    f32 getMovementSpeed();
};
