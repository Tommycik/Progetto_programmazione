//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SKILLS_H
#define MAIN_SKILLS_H

#include <iostream>
#include "Obstacle.h"


class Skills : public Entity {
public:

    void tracking(Entity &target) override;

    void behaviour(Entity &target) override;

    void move(float x, float y) override;

    void run(float x, float y) override;

    bool isOutOfRange(int posX, int posY, int initialX, int initialY);

    template<typename T>
    void targetSearch(std::vector<std::unique_ptr<Obstacle>> &enemies, Entity &mario, T *bosses = nullptr) {

        float minDistance = 1000;

        if (this->ostile == false) {

            if (!(enemies.empty())) {

                for (auto &gc: enemies) {

                    if (gc->isFixed() == false && gc->getHp() > 0) {

                        if (minDistance > l2Distance(*this, gc->getposX(), gc->getposY())) {
                            minDistance = l2Distance(*this, gc->getposX(), gc->getposY());
                            target = &(*gc);
                        }

                    }

                }

            }

            if (!(bosses->empty())) {

                for (auto &gc: *bosses) {

                    if (gc->getHp() > 0) {

                        if (minDistance > l2Distance(*this, gc->getposX(), gc->getposY())) {
                            minDistance = l2Distance(*this, gc->getposX(), gc->getposY());
                            target = &(*gc);
                        }

                    }

                }

            }

            if (minDistance > range) {

                if (!(enemies.empty())) {

                    for (auto &gc: enemies) {

                        if (gc->isFixed() == true && gc->getHp() > 0) {

                            if (minDistance > l2Distance(*this, gc->getposX(), gc->getposY())) {
                                minDistance = l2Distance(*this, gc->getposX(), gc->getposY());
                                target = &(*gc);
                            }

                        }

                    }

                }

            }

        } else if (this->isOstile()) {

            if (minDistance > l2Distance(*this, mario.getposX(), mario.getposY())) {
                minDistance = l2Distance(*this, mario.getposX(), mario.getposY());
                target = &mario;
            }

        }

        if (minDistance <= range) {
            targetLost = false;
            targetFound = true;
            target->setTarget(true);
        } else {
            target = nullptr;
            targetLost = true;
            damage = 0;
        }

    }

    Entity *getTarget() const;

    bool isTargetLost() const;

    float getRadius() const;

    bool isTargetFound() const;

    void setTargetFound(bool targetFound);

    int getstartX() const {
        return startX;
    }

    void setstartX(int posX) {
        Skills::startX = posX;
    }

    int getStamConsumption() const {
        return stamConsumption;
    }

    bool isOstile() const;

    int getDamage() const {
        return damage;
    }

    void setOstile(bool ostile);

    Entity *getUser() const;

    void setUser(Entity *user);

protected:

    Entity *target;
    int damage;
    int startX;
    int startY;
    int stamConsumption;
    int range;
    bool ostile;
    bool targetLost = false;
    bool targetFound = false;
    float radius = 0;
    Entity *user;

};

#endif //MAIN_SKILLS_H
