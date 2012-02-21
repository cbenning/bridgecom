

#include "body.h"
#include "def.h"

Body::Body(ISceneManager* smgr,IVideoDriver* driver, core::vector3df position, const int radius, std::string name, std::string type, int orbitRadius, f32 orbitSpeed, Body* parentBody, std::string texture, int brightness)
{

    this->radius=radius;
    this->name=name;
    this->type=type;
    this->orbitRadius=orbitRadius;
    this->orbitSpeed=orbitSpeed;
    this->parentBody=parentBody;
    this->numChildren=0;
    this->smgr=smgr;
    this->driver=driver;
    this->defaultPosition=position;
    this->texture=texture;
    this->brightness=brightness;
    this->node=NULL;

    cout << "Created " << this->name << " with " << this->texture << "\n";

}

void Body::addChild(Body* child)
{
    this->children.resize(this->numChildren+1);
    this->children[this->numChildren]=child;
    this->numChildren++;
}

void Body::buildBody()
{

	this->node = this->smgr->addSphereSceneNode(this->radius, PLANET_POLY_COUNT);
    if (this->node)
    {
        this->node->setPosition(this->getPosition());
        this->node->setMaterialTexture(0, this->driver->getTexture((IMG_DIR+this->texture).c_str()));

        cout << "Type: " << this->type << "\n";
        if(this->type=="star"){
            ILightSceneNode* light1 = this->smgr->addLightSceneNode(0,this->getPosition(),video::SColorf(100.0f,100.0f,100.0f),this->radius,1); 
            this->node->setMaterialFlag(EMF_LIGHTING, false); // enable dynamic lighting
        }
        else{
            this->node->setMaterialFlag(EMF_LIGHTING, true); // enable dynamic lighting
        }

        if(this->parentBody)
        {

            cout << this->name << ", Orbit speed: " << this->orbitSpeed << "Parent: " << this->parentBody->getName() << "\n";
            //cout << "Orbit speed: " << this->orbitSpeed << "\n";
            ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(this->parentBody->getPosition(), this->orbitRadius, this->orbitSpeed);
            if (anim)
            {
                this->node->addAnimator(anim);
                anim->drop();
            }
        }



    }
    else{
        cout<<"Failed to setup the body";
        return;
    }

    int i;
    for(i = 0; i< this->numChildren; i++){
        this->children[i]->buildBody();
    }
    
}
core::vector3df Body::getPosition(){
    if(this->node==NULL){
        return this->defaultPosition;
    }
    else{
        return this->node->getPosition();
    }
}

std::string Body::getName(){
    return this->name;
}
