
#include "ship.h"

Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, b2World* gameWorld, const int model)
{

    //this->shipForwardThrust=1.0f;
    this->shipForwardThrustOn=false;
    this->shipReverseThrustOn=false;
    this->shipLeftThrustOn=false;
    this->shipRightThrustOn=false;
    //this->shipTurnThrust=0.6f;
    //this->shipReverseThrust=0.4f;
    this->gameWorld=gameWorld;

    //TODO: Fixme
    this->shipMovement = vector3df(0,0,0);

    //TODO: Make this better. suck it from a file?
    shipModel[0] = "ship2.b3d";

    f32 defX = 400.0f;
    f32 defY = 400.0f;
    f32 defZ = 0.0f;

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

    //Body Def
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(defX,defY);   // the body's origin position.
    bodyDef.angle = b2_pi;      // the body's angle in radians.
    bodyDef.linearDamping = 0.05f;
    bodyDef.angularDamping = 0.5f;
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
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.05f;

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

core::vector3df Ship::getShipMovement(){
    return this->shipMovement;
}

void Ship::applyForwardThrust(){
    if(!this->shipForwardThrustOn){
        cout << "Forward Thrust On\n";
        this->shipForwardThrustOn = true;
    }
}

void Ship::cancelForwardThrust(){
    if(this->shipForwardThrustOn){
        cout << "Forward Thrust Off\n"; 
        this->shipForwardThrustOn = false;
    }
}

void Ship::applyReverseThrust(){
    if(!this->shipReverseThrustOn){
        cout << "Reverse Thrust On\n";
        this->shipReverseThrustOn = true;
    }
}

void Ship::cancelReverseThrust(){
    if(this->shipReverseThrustOn){
        cout << "Reverse Thrust Off\n"; 
        this->shipReverseThrustOn = false;
    }
}

void Ship::applyLeftThrust(){
    if(!this->shipLeftThrustOn){
        cout << "Left Thrust On\n"; 
        this->shipLeftThrustOn = true;
    }
}

void Ship::cancelLeftThrust(){
    if(this->shipLeftThrustOn){
        cout << "Left Thrust Off\n"; 
        this->shipLeftThrustOn = false;
    }
}

void Ship::applyRightThrust(){
    if(!this->shipRightThrustOn){
        cout << "Right Thrust On\n"; 
        this->shipRightThrustOn = true;
    }
}

void Ship::cancelRightThrust(){
    if(this->shipRightThrustOn){
        cout << "Right Thrust Off\n"; 
        this->shipRightThrustOn = false;
    }
}

core::vector3df Ship::getCamFollowPosition(){

    f32 angle = this->dynamicBody->GetAngle();
    b2Vec2 rot = Util::deg2vec(angle);
    rot.Normalize();
    vector3df pos = this->node->getPosition();
    //cout << "pos.X:" << pos.X << " , pos.Y:" <<pos.Y << " , pos.Z:" << pos.Z << "\n";
    //cout << "rot.x:" << rot.x << " , rot.y:" <<rot.y << "\n";
    rot = -20*rot; //Get inverse and scale
    vector3df tmp2 = vector3df(pos.X+rot.x,pos.Y+8,pos.Z+rot.y);

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
        //cout << "angle : " << angle << ", ";
        //cout << "rot    X: " << rot.x << ", Y: " << rot.y << "\n";
        this->dynamicBody->ApplyForce(10*rot, this->dynamicBody->GetWorldCenter());
    }
    else if(this->shipReverseThrustOn && !this->shipForwardThrustOn){
        b2Vec2 rot = Util::deg2vec(angle);
        rot.Normalize();
        //cout << "angle : " << angle << ", ";
        //cout << "rot    X: " << rot.x << ", Y: " << rot.y << "\n";
        this->dynamicBody->ApplyForce(-10*rot, this->dynamicBody->GetWorldCenter());
    }

    //vector3df tmp = this->node->getRotation();
    //cout << "node   Y: " << tmp.Y << "\n";

    //Sync position
    b2Vec2 pos = this->dynamicBody->GetPosition();
    this->node->setPosition(vector3df(pos.x,0.0f,pos.y));
    
    //Left/Right thrust
    if(this->shipLeftThrustOn && !this->shipRightThrustOn){
        this->dynamicBody->ApplyTorque(4.0f);
    }
    else if(this->shipRightThrustOn && !this->shipLeftThrustOn){
        this->dynamicBody->ApplyTorque(-4.0f);
    }
    
    //Catch up camera
    camera->setPosition(this->getCamFollowPosition()); 
    camera->setTarget(this->getPosition()); 

    //cout << "dynbody X: " << pos.x << ", Y: " << pos.y << "\n";
}

