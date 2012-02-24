
#include "ship.h"
#include "def.h"

Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, const int model)
{

    this->shipForwardThrust=1.0f;
    this->shipTurnThrust=0.6f;
    this->shipStopThrust=0.4f;

    //TODO: Fixme
    this->shipMovement = vector3df(0,0,0);


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
    this->node->setPosition(vector3df(400.0f,400.0f,400.0f)); //TODO
    this->node->setRotation(vector3df(0,-90,0));
}

core::vector3df Ship::getPosition(){
    return this->node->getPosition();
}

void Ship::setPosition(core::vector3df pos){
    this->node->setPosition(pos);
}

core::vector3df Ship::getRotation(){
    return this->node->getRotation();
}

void Ship::setRotation(core::vector3df rot){
    this->node->setRotation(rot);
}

core::vector3df Ship::getShipMovement(){
    return this->shipMovement;
}

void Ship::applyForwardThrust(){
    //this>
}

core::vector3df Ship::getCamFollowPosition(){
    vector3df tmp = this->getPosition();
    vector3df tmp2 = vector3df(tmp.X-20,tmp.Y-50,tmp.Z);
    return tmp2;
}

/*core::vector3df Ship::getCamFollowRotation(){
    vector3df tmp = this->getPosition();
    return vector3df(tmp.X,tmp.Y,-100);
}*/
