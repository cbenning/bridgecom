
#include "ship.h"

#define MODEL_DIR "../media/model/"

Ship::Ship(ISceneManager* smgr, const int model)
{

    //TODO: Make this better. suck it from a file?
    shipModel[0] = "ship1.b3d";

    //std::string modelPath = MODEL_DIR;
    //strcat(modelPath,shipModel[model]); //TODO Check model is >=0 < MAX_SHIP_MODELS
    cout<<(MODEL_DIR+shipModel[model]).c_str();
    mesh = smgr->getMesh((MODEL_DIR+shipModel[model]).c_str());
    if (!mesh)
    {
        //device->drop();
    }
    node = smgr->addAnimatedMeshSceneNode(mesh);
    
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMaterialFlag(EMF_WIREFRAME, true);
    } 
    node->setPosition(vector3df(0,0,0));
    node->setRotation(vector3df(0,-90,0));

}

