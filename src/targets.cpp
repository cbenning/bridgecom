
#include <string>
#include "targets.h"

TargetableObject::TargetableObject(std::string tname,std::string tdesc,std::string ttype){
    this->tname = tname;
    this->tdesc = tdesc;
    this->ttype = ttype;
    this->friendlyState = NEUTRAL;
}

std::string TargetableObject::getTName(){
    return tname;
}

std::string TargetableObject::getTDesc(){
    return tdesc;
}

std::string TargetableObject::getTType(){
    return ttype;
}

bool TargetableObject::isHostile(){
    if(friendlyState==HOSTILE){
        return true;
    }
    return false;
}

bool TargetableObject::isFriendly(){
    if(friendlyState==FRIENDLY){
        return true;
    }
    return false;
}

TargetableObject* Targets::cycleTarget(){
    if(allTargets.size() < 1){
        return 0;
    }
    if(index >= allTargets.size()-1){
        index = 0;
    }
    index++;
    return &allTargets[index];
}

TargetableObject* Targets::cycleHostileTarget(){

    TargetableObject* tmp;
    unsigned int maxiters = 0;
    
    tmp = cycleTarget();
    while(!tmp->isHostile()){
        if(maxiters>allTargets.size()){
            return tmp; //If there werent any, stop and return any one
        }
        tmp = cycleTarget();
        maxiters++;
    }
    return tmp;
    
}

TargetableObject* Targets::cycleFriendlyTarget(){

    TargetableObject* tmp;
    unsigned int maxiters = 0;
    
    tmp = cycleTarget();
    while(!tmp->isFriendly()){
        if(maxiters>allTargets.size()){
            return tmp; //If there werent any, stop and return any one
        }
        tmp = cycleTarget();
        maxiters++;
    }
    return tmp;

}

Targets::Targets(){
    index = 0; 
}

void Targets::addTarget(TargetableObject newobj){
    allTargets.push_back(newobj);
}


