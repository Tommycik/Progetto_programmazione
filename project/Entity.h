//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "Object.h"
#include "Dungeonarea.h"
#include <time.h>
#include <iostream>
#include <random>

 class Entity : public  Object{
public:

     virtual ~Entity(){}

     virtual void behaviour(Entity &target)=0;
     virtual void tracking(Entity &target)=0;
     virtual void move(float x, float y)=0;
     virtual void run(float x,float y)=0;
     float getHp() const;
     void receiveDamage(int damage);
     void setHp(float hp);
     int getTextureMultiplier() const;
     float getDirectX() const;
     float getDirectY() const;
     bool isChecked() const;
     void setChecked(bool checked);
     double getTimeSinceDamage() const;
     void setTimeSinceDamage(double timeDamage);
     int getType() const;
     int getSkillUsed() const;
     bool isKillable() const;
     bool isActivated() const;
     float getContactDamage() const;
     void setActivated(bool activated);
     bool isTarget() const;
     void setTarget(bool target);
     bool isAbilityUsed() const;
     void setAbilityUsed(bool abilityUsed);
     void recoverStam();
     float getInvulnerabilityFrame() const;
     void setInvulnerabilityFrame(float invulnerabilityFrame);

 protected:

     int skillUsed=0;
     bool activated=false;
     bool target=false;
     float contactDamage=0;
     float hp=0;
     float textureMultiplier=1;
     int oldseed=0;
     float directX=0;
     float directY=0;
     bool checked=false;
     double timeSinceDamage=0;
     int type=0;
     bool killable=false;
     bool abilityUsed=false;
     float stamina=0;
     float maxStam=0;
     float invulnerabilityFrame=0.5;
 };

#endif //MAIN_ENTITY_H
