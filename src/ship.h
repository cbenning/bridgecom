
#include <irrlicht.h> 
#include <string>
#include <iostream>
#include "def.h"
#include "Box2D/Box2D.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;

#define MAX_SHIP_MODELS 1
#define MAX_SHIP_THRUST 10

class Ship
{
private:
    std::string shipModel[MAX_SHIP_MODELS];
    f32 shipForwardThrust;
    bool shipForwardThrustOn;
    f32 shipTurnThrust;
    f32 shipReverseThrust;
    core::vector3df shipMovement;
    scene::IAnimatedMesh* mesh;
    scene::IAnimatedMeshSceneNode* node;
    //Box2D stuff
    b2BodyDef bodyDef;
    b2World* gameWorld;
    b2Body* dynamicBody;

public:
    Ship(ISceneManager* smgr, IVideoDriver* driver, b2World* gameWorld, const int model);
    core::vector3df getPosition();
    void setPosition(core::vector3df pos);
    core::vector3df getRotation();
    void setRotation(core::vector3df rot);
    b2Vec2 get2DPosition();
    void set2DPosition(b2Vec2 pos);
    b2Vec2 get2DRotation();
    void set2DRotation(b2Vec2 rot);
    core::vector3df getShipMovement();
    void applyForwardThrust();
    void cancelForwardThrust();
    void applyReverseThrust();
    void applyLeftThrust();
    void applyRightThrust();
    core::vector3df getCamFollowPosition();
    IAnimatedMeshSceneNode* getSceneNode();
    void update();
};
