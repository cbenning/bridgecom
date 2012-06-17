
#include "ship.h"
#include "targets.h"
#include <iostream>


Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, IGUIEnvironment* guiEnv, b2World* gameWorld, const int model)
{

    //this->shipForwardThrust=1.0f;
    this->shipForwardThrustOn=false;
    this->shipReverseThrustOn=false;
    this->shipLeftThrustOn=false;
    this->shipRightThrustOn=false;
    this->shipLeftStrafeThrustOn=false;
    this->shipRightStrafeThrustOn=false;
    this->gameWorld=gameWorld;
    this->cameraZoomY = DEFAULT_CAM_ZOOM_Y; 
    this->cameraZoomX = DEFAULT_CAM_ZOOM_X; 
    this->cameraZoomingOut = false;
    this->cameraZoomingIn = false;
    this->currentlyTargetting = false;
    this->guiEnv = guiEnv;

    // Gui stuff, for targetting text TODO
    this->guiEnv->addStaticText(L"Current Target",rect<s32>(10,10,400,40), true , true, 0, -1, true);
    this->guiTargetNameText = this->guiEnv->addStaticText(L"No Target",rect<s32>(10,50,400,80), true, true, 0, -1, true);
    this->guiTargetTypeText = this->guiEnv->addStaticText(L"i",rect<s32>(10,90,400,120), true, true, 0, -1, true);
    this->guiTargetDescText = this->guiEnv->addStaticText(L"i",rect<s32>(10,130,400,200), true, true, 0, -1, true);

    //std::string shipModel = "patrol_frigate.3ds";
    std::string shipModel = "transport_1.b3d";

    f32 defX = 400.0f;
    f32 defY = 400.0f;
    f32 defZ = 0.0f;
    //
    // Irrlicht Stuff
    //
    this->mesh = smgr->getMesh((MODEL_DIR+shipModel).c_str());
    this->node = smgr->addAnimatedMeshSceneNode(mesh);
    
    if (this->node)
    {
        //this->node->setMaterialTexture(0, driver->getTexture("../media/img/patrol_frigate_default.png"));
        this->node->setMaterialTexture(0, driver->getTexture("../media/img/transport_1_rivets.png"));
        this->node->setMaterialFlag(EMF_LIGHTING, false);
        //this->node->getMaterial(0).Shininess = 20.0f;
        this->node->setMaterialType(irr::video::EMT_LIGHTMAP_M4);
        //this->node->setMaterialFlag(EMF_WIREFRAME, true);
        this->node->setMaterialType(video::EMT_SOLID);
    } 
    this->node->setPosition(vector3df(defX,defY,defZ)); //TODO
    this->node->setRotation(vector3df(0,0,0));

    //
    // Box2D stuff
    //

    //Body Def
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(defX,defY);   // the body's origin position.
    bodyDef.angle = b2_pi;      // the body's angle in radians.
    bodyDef.linearDamping = 0.02f;
    bodyDef.angularDamping = 0.4f;
    bodyDef.gravityScale = 0.0f; // Set the gravity scale to zero so this body will float
    bodyDef.allowSleep = false;
    //bodyDef.awake = true;
    //bodyDef.fixedRotation = false;
    //bodyDef.userData = this;
    //bodyDef.active = true;

    //shape Def
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1, 1);


    //fixture def 
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.0f;

    //Fire it up
    this->dynamicBody = this->gameWorld->CreateBody(&bodyDef);
    this->dynamicBody->CreateFixture(&fixtureDef);

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

b2Vec2 Ship::get2DPosition(){
    vector3df tmp = this->node->getPosition();
    return b2Vec2(tmp.X,tmp.Y);
}

void Ship::set2DPosition(b2Vec2 pos){
    this->node->setPosition(vector3df(pos.x,pos.y,0.0f));
}

b2Vec2 Ship::get2DRotation(){
    vector3df tmp = this->node->getRotation();
    return b2Vec2(tmp.X,tmp.Y);
}

void Ship::set2DRotation(b2Vec2 rot){
    this->node->setPosition(vector3df(rot.x,rot.y,0.0f));
}

void Ship::applyForwardThrust(){
    if(!this->shipForwardThrustOn){
        this->shipForwardThrustOn = true;
    }
}

void Ship::cancelForwardThrust(){
    if(this->shipForwardThrustOn){
        this->shipForwardThrustOn = false;
    }
}

void Ship::applyReverseThrust(){
    if(!this->shipReverseThrustOn){
        this->shipReverseThrustOn = true;
    }
}

void Ship::cancelReverseThrust(){
    if(this->shipReverseThrustOn){
        this->shipReverseThrustOn = false;
    }
}

void Ship::applyLeftThrust(){
    if(!this->shipLeftThrustOn){
        this->shipLeftThrustOn = true;
    }
}

void Ship::cancelLeftThrust(){
    if(this->shipLeftThrustOn){
        this->shipLeftThrustOn = false;
    }
}

void Ship::applyRightThrust(){
    if(!this->shipRightThrustOn){
        this->shipRightThrustOn = true;
    }
}

void Ship::cancelRightThrust(){
    if(this->shipRightThrustOn){
        this->shipRightThrustOn = false;
    }
}

void Ship::applyLeftStrafeThrust(){
    if(!this->shipLeftStrafeThrustOn){
        this->shipLeftStrafeThrustOn = true;
    }
}

void Ship::cancelLeftStrafeThrust(){
    if(this->shipLeftStrafeThrustOn){
        this->shipLeftStrafeThrustOn = false;
    }
}

void Ship::applyRightStrafeThrust(){
    if(!this->shipRightStrafeThrustOn){
        this->shipRightStrafeThrustOn = true;
    }
}

void Ship::cancelRightStrafeThrust(){
    if(this->shipRightStrafeThrustOn){
        this->shipRightStrafeThrustOn = false;
    }
}

void Ship::beginCycleTarget(){
    if(!this->currentlyTargetting){
        this->currentlyTargetting = true;
    }
}

void Ship::commitCycleTarget(){
    if(this->currentlyTargetting){
        this->currentlyTargetting = false;
        //Actually cycle the target
        TargetableObject* tmpTarget = Targets::getInstance().cycleTarget();
        if(tmpTarget){
            this->setTargetText(tmpTarget->getTName(),tmpTarget->getTDesc(),tmpTarget->getTType());
        }
    }
}

void Ship::setTargetText(std::string name, std::string desc, std::string type){

    wstring tmpWName,tmpWDesc,tmpWType;
    tmpWName = Util::stringToWstring(name);
    tmpWDesc = Util::stringToWstring(desc);
    tmpWType = Util::stringToWstring(type);

    this->guiTargetNameText->setText(tmpWName.c_str());
    this->guiTargetDescText->setText(tmpWDesc.c_str());
    this->guiTargetTypeText->setText(tmpWType.c_str());
}


core::vector3df Ship::getCamFollowPosition(){

    f32 angle = this->dynamicBody->GetAngle();
    b2Vec2 rot = Util::deg2vec(angle);
    rot.Normalize();
    vector3df pos = this->node->getPosition();
    //cout << "pos.X:" << pos.X << " , pos.Y:" <<pos.Y << " , pos.Z:" << pos.Z << "\n";
    //cout << "rot.x:" << rot.x << " , rot.y:" <<rot.y << "\n";
    rot = -20*rot; //Get inverse and scale
    vector3df tmp2 = vector3df(pos.X+rot.x,pos.Y+cameraZoomY,pos.Z+rot.y);

    return tmp2;
}

IAnimatedMeshSceneNode* Ship::getSceneNode(){
    return this->node;
}

void Ship::update(ICameraSceneNode* camera){

    //Sync rotation
    f32 angle = this->dynamicBody->GetAngle();
    this->node->setRotation(vector3df(0.0f,-angle+90,0.0f));

    //Forward/Reverse thrust
    if(this->shipForwardThrustOn && !this->shipReverseThrustOn){
        b2Vec2 rot = Util::deg2vec(angle);
        rot.Normalize();
        this->dynamicBody->ApplyForce(5*rot, this->dynamicBody->GetWorldCenter());
    }
    else if(this->shipReverseThrustOn && !this->shipForwardThrustOn){
        b2Vec2 rot = Util::deg2vec(angle);
        rot.Normalize();
        this->dynamicBody->ApplyForce(-3*rot, this->dynamicBody->GetWorldCenter());
    }

    //Strafe thrust
    if(this->shipLeftStrafeThrustOn && !this->shipRightStrafeThrustOn){
        b2Vec2 rot = Util::deg2vec(angle+90);
        rot.Normalize();
        this->dynamicBody->ApplyForce(2*rot, this->dynamicBody->GetWorldCenter());
    }
    else if(this->shipRightStrafeThrustOn && !this->shipLeftStrafeThrustOn){
        b2Vec2 rot = Util::deg2vec(angle-90);
        rot.Normalize();
        this->dynamicBody->ApplyForce(2*rot, this->dynamicBody->GetWorldCenter());
    }

    //Sync position
    b2Vec2 pos = this->dynamicBody->GetPosition();
    this->node->setPosition(vector3df(pos.x,0.0f,pos.y));
    
    //Left/Right thrust
    if(this->shipLeftThrustOn && !this->shipRightThrustOn){
        this->dynamicBody->ApplyTorque(10.0f);
    }
    else if(this->shipRightThrustOn && !this->shipLeftThrustOn){
        this->dynamicBody->ApplyTorque(-10.0f);
    }

    //Catch up camera
    camera->setPosition(this->getCamFollowPosition()); 
    camera->setTarget(this->getPosition()); 

    //Deal with camera zoom
    if(this->cameraZoomingOut && this->cameraZoomY<MAX_CAM_ZOOM){
        this->cameraZoomY+=CAM_ZOOM_DELTA;
        this->cameraZoomX++;
    }
    else if(this->cameraZoomingIn && this->cameraZoomY>MIN_CAM_ZOOM){
        this->cameraZoomY-=CAM_ZOOM_DELTA;
        this->cameraZoomX--;
    }
}

void Ship::increaseCameraZoom(bool cancel = false){
    if(cancel){
        this->cameraZoomingOut = false;
    }
    else{
        this->cameraZoomingOut = true;
        this->cameraZoomingIn = false;
    }

}

void Ship::decreaseCameraZoom(bool cancel = false){
    if(cancel){
        this->cameraZoomingIn = false;
    }
    else{
        this->cameraZoomingIn = true;
        this->cameraZoomingOut = false;
    }
}
