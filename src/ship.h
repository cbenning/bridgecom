
#include <irrlicht.h> 
#include <string>
#include <iostream>
#include "def.h"
#include "util.h"
#include "Box2D/Box2D.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;

#define DEFAULT_CAM_ZOOM_Y 12
#define DEFAULT_CAM_ZOOM_X 0
#define MAX_CAM_ZOOM 80 
#define MIN_CAM_ZOOM 2
#define CAM_ZOOM_DELTA 0.05f

class Ship
{
private:
    std::string shipModel;
    bool shipForwardThrustOn;
    bool shipLeftThrustOn;
    bool shipRightThrustOn;
    bool shipReverseThrustOn;
    bool cameraZoomingOut;
    bool cameraZoomingIn;
    float cameraZoomY;
    float cameraZoomX;
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
    void applyForwardThrust();
    void cancelForwardThrust();
    void applyReverseThrust();
    void cancelReverseThrust();
    void applyLeftThrust();
    void cancelLeftThrust();
    void applyRightThrust();
    void cancelRightThrust();
    core::vector3df getCamFollowPosition();
    IAnimatedMeshSceneNode* getSceneNode();
    void update(ICameraSceneNode* camera);
    void increaseCameraZoom(bool cancel);
    void decreaseCameraZoom(bool cancel);
};
