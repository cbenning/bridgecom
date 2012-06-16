
#include <irrlicht.h> 
#include <string>
#include <iostream>
#include "targets.h"

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 
using namespace std;

#define PLANET_POLY_COUNT 32
#define BODY_PLANE_BUFFER 300

class Body : public TargetableObject {
private:
    int radius;
    std::string name;
    std::string type;
    int orbitRadius;
    f32 orbitSpeed;
    Body* parentBody;
    std::vector<Body*> children;
    int numChildren;
    ISceneNode* node;
    ISceneManager* smgr;
    IVideoDriver* driver;
    core::vector3df defaultPosition;
    std::string texture;
    int brightness;
    ISceneNodeAnimator* createMovableFlyCircleAnimator(
		const core::vector3df& center, f32 radius, f32 speed,
		const core::vector3df& direction,
		f32 startPosition,
		f32 radiusEllipsoid);

public:
    Body(ISceneManager* smgr, IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string desc, std::string type, int orbitRadius, f32 orbitSpeed, Body* parentBody, std::string texture, int brightness);
    void addChild(Body* child);
    void buildBody();
    core::vector3df getPosition();
    std::string getName();
    int getRadius();
};
