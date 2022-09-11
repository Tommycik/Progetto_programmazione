//
// Created by tommy on 08/09/2022.
//

#include "Dreadgen.h"

Dreadgen::Dreadgen(int posX,int posY,int dungeonType){
    this->hp=150+30*dungeonType;
    this->maxStam=100;
    this->stamina=this->maxStam/2;
    this->dungeonNumber=dungeonType;
    this->movements=0.5;
    this->posX=posX;
    this->posY=posY;
    this->statIncrease=1;
    this->textureMultiplier=2;
    this->activated=false;
    this->contactDamage=30+20*dungeonType;
    this->textureFile="assets/enemies.png";
    this->killable=true;
    this->type=1;
    this->tileNumber=97;
}

void Dreadgen::behaviour(Entity &target){
    if(l2Distance(*this,target.getposX(),target.getposY())<=20){
        this->activated=true;
        if(stamina<=maxStam-maxStam/200)
            this->stamina+=maxStam/200;
    }else{
        this->activated=false;
    }

    if(activated){
        directX=0;
        directY=0;
        abilityUsed=false;
        skillType=0;
        tracking(target);

        if(this->stamina>=(maxStam/3)){
            int n=0;
            int i=0;
            int random=1;
            n = 2-1+ 1;
            i = rand() % n;
            if (i < 0)
                i = -i;
            random=1 + i;
            switch(random){

                case 1:
                    abilityUsed= true;
                    skillType=1;
                    break;

                case 2:
                    abilityUsed= true;
                    skillType=2;
                    break;

                default:
                    abilityUsed= true;
                    skillType=1;
                    break;
            }
        }

    }
}

void Dreadgen::tracking(Entity &target){
    float xDistance=0;
    float yDistance=0;
    xDistance=this->posX-target.getposX();
    if(xDistance<0.00)
        xDistance*=-1;
    yDistance=this->posY-target.getposY();
    if(yDistance<0.00)
        yDistance*=-1;

    if(xDistance>yDistance){

        if((this->posX-target.getposX())>0){
            directX=-movements;
        }else if((this->posX-target.getposX())<0){
            directX=movements;
        }

    }else if(xDistance<yDistance){

        if((this->posY-target.getposY())>0){
            directY=-movements;
        }else if((this->posY-target.getposY())<0){
            directY=movements;
        }

    }else if((xDistance==yDistance)){

        if((this->posX-target.getposX())>0){
            directX=-movements;
        }else if((this->posX-target.getposX())<0){
            directX=movements;
        }

        if((this->posY-target.getposY())>0){
            directY=-movements;
        }else if((this->posY-target.getposY())<0){
            directY=movements;
        }

    }
}

void Dreadgen::move(float x, float y){
    posX +=x;
    posY +=y;
}

std::unique_ptr<Skills> Dreadgen::skillUse(){
    switch (skillType) {

        case 1: {
            auto newSkill = std::make_unique<Fireball>(this->getposX(), this->getposY(), dungeonNumber*2);
            newSkill->setOstile(true);
            newSkill->setUser(this);
            this->stamina-=newSkill->getStamConsumption();
            return newSkill;
        }
        case 2:{
            auto newSkill = std::make_unique<CrystalWall>(this->getposX(), this->getposY(), dungeonNumber);
            newSkill->setUser(this);
            this->stamina-=newSkill->getStamConsumption();
            return newSkill;
        }
        default:{
            auto newSkill = std::make_unique<Fireball>(this->getposX(), this->getposY(), dungeonNumber*2);
            newSkill->setUser(this);
            newSkill->setOstile(true);
            this->stamina-=newSkill->getStamConsumption();
            return newSkill;
        }
    }
}
