
#include "ship.h"
#include "def.h"

Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, const int model)
{

    this->movementSpeed=1.0f;
    //TODO: Make this better. suck it from a file?
    shipModel[0] = "ship2.b3d";

    cout<<(MODEL_DIR+shipModel[model]).c_str();
    mesh = smgr->getMesh((MODEL_DIR+shipModel[model]).c_str());
    node = smgr->addAnimatedMeshSceneNode(mesh);
    
    if (node)
    {       
        //node->setMaterialTexture(0, driver->getTexture("../media/img/ship2.png"));
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMaterialFlag(EMF_WIREFRAME, true);
    } 
    node->setPosition(vector3df(400,400,400));
    node->setRotation(vector3df(0,-90,0));
}

core::vector3df Ship::getPosition(){
    this->node->getPosition();
}

void Ship::setPosition(core::vector3df pos){
    this->node->setPosition(pos);
}

core::vector3df Ship::getRotation(){
    this->node->getRotation();
}

void Ship::setRotation(core::vector3df rot){
    this->node->setRotation(rot);
}

f32 Ship::getMovementSpeed(){
    this->movementSpeed;
}
