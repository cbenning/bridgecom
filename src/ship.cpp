
#include "ship.h"

Ship::Ship(ISceneManager* smgr, IVideoDriver* driver, b2World* gameWorld, const int model)
{

    this->shipForwardThrust=1.0f;
    this->shipForwardThrustOn=false;
    this->shipTurnThrust=0.6f;
    this->shipReverseThrust=0.4f;
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
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.01f;
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
    fixtureDef.friction = 0.1f;

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
        b2Vec2 pos = this->dynamicBody->GetPosition();
        cout << "dynbody X: " << pos.x << ", Y: " << pos.y << "\n";
        this->shipForwardThrustOn = true;
    }
}

void Ship::cancelForwardThrust(){
    if(this->shipForwardThrustOn){
        cout << "Forward Thrust Off\n"; 
        b2Vec2 pos = this->dynamicBody->GetPosition();
        cout << "dynbody X: " << pos.x << ", Y: " << pos.y << "\n";
        this->shipForwardThrustOn = false;
    }
}

void Ship::applyReverseThrust(){
    return;
}

void Ship::applyLeftThrust(){
    vector3df rot = this->node->getRotation();
    //TODO: Do something more clever than this
    rot.Y-=this->shipTurnThrust/4;
    this->node->setRotation(rot);
}

void Ship::applyRightThrust(){
    //body->ApplyTorque(50.0f);
    vector3df rot = this->node->getRotation();
    //TODO: Do something more clever than this
    rot.Y+=this->shipTurnThrust/4;
    this->node->setRotation(rot);
}

core::vector3df Ship::getCamFollowPosition(){
    //vector3df tmp = this->getPosition();
    vector3df tmp2 = vector3df(20.0f,20.0f,0.0f);
    return tmp2;
}

IAnimatedMeshSceneNode* Ship::getSceneNode(){
    return this->node;
}

void Ship::update(){

    if(this->shipForwardThrustOn){
        //b2Vec2 point = this->dynamicBody->GetPosition();
        //b2Vec2 f = this->dynamicBody->GetWorldVector(b2Vec2(0.0f, 2.0f));
        //b2Vec2 p = this->dynamicBody->GetWorldPoint(b2Vec2(0.0f, 0.0f));
        this->dynamicBody->ApplyForce(b2Vec2(1,0), this->dynamicBody->GetWorldCenter());
        //this->dynamicBody->ApplyForce(f,p);
    }

    b2Vec2 pos = this->dynamicBody->GetPosition();
    //vector3df pos2 = this->getPosition();
    this->node->setPosition(vector3df(0.0f,pos.x,pos.y));
    //cout << "dynbody X: " << pos.x << ", Y: " << pos.y << "\n";
    //cout << "node    X: " << pos2.X << ", Y: " << pos2.Y << "\n";
}

/*core::vector3df Ship::getCamFollowRotation(){
    vector3df tmp = this->getPosition();
    return vector3df(tmp.X,tmp.Y,-100);
}*/
