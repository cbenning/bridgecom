
#include "ship.h"

Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, b2World* gameWorld, const int model)
{

    this->shipForwardThrust=1.0f;
    this->shipTurnThrust=0.6f;
    this->shipReverseThrust=0.4f;
    this->gameWorld=gameWorld;

    //TODO: Fixme
    this->shipMovement = vector3df(0,0,0);

    //TODO: Make this better. suck it from a file?
    shipModel[0] = "ship2.b3d";

    f32 defX = 400.0f;
    f32 defY = 400.0f;
    f32 defZ = 400.0f;

    //
    // Irrlicht Stuff
    //
    cout<<(MODEL_DIR+shipModel[model]).c_str();
    mesh = smgr->getMesh((MODEL_DIR+shipModel[model]).c_str());
    node = smgr->addAnimatedMeshSceneNode(mesh);
    
    if (node)
    {
        //node->setMaterialTexture(0, driver->getTexture("../media/img/ship2.png"));
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMaterialFlag(EMF_WIREFRAME, true);
    } 
    this->node->setPosition(vector3df(defX,defY,defZ)); //TODO
    this->node->setRotation(vector3df(0,0,0));

    //
    // Box2D stuff
    //
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(defX,defY);   // the body's origin position.
    bodyDef.angle = 0.25f * b2_pi;      // the body's angle in radians.
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.01f;
    bodyDef.gravityScale = 0.0f; // Set the gravity scale to zero so this body will float
    bodyDef.allowSleep = true;
    bodyDef.awake = true;
    bodyDef.fixedRotation = false;
    bodyDef.userData = this;
    bodyDef.active = true;
    this->dynamicBody = this->gameWorld->CreateBody(&bodyDef);
    //myWorld->DestroyBody(dynamicBody);
    //dynamicBody = NULL;

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
    return;
}

void Ship::applyReverseThrust(){
    return;
}

void Ship::applyLeftThrust(){
    vector3df rot = this->node->getRotation();
    //TODO: Do something more clever than this
    rot.Y-=this->shipTurnThrust;
    this->node->setRotation(rot);
}

void Ship::applyRightThrust(){
    vector3df rot = this->node->getRotation();
    //TODO: Do something more clever than this
    rot.Y+=this->shipTurnThrust;
    this->node->setRotation(rot);
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
