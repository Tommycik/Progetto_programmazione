//
// Created by tommy on 18/06/2022.
//

#ifndef MAIN_UTILITIES_H
#define MAIN_UTILITIES_H

#include <cmath>
#include <typeinfo>
#include <SFML/System.hpp>

template<typename T, typename U>
float l1Distance(const T &p, const U &q) {
    float distance = abs(p.getposX() - q.getposX()) + abs(p.getposY() - q.getposY());
    return distance;
}

template<typename T>
float l2Distance(const T &p, const float &x, const float &y) {
    float xDistance = 0;
    float yDistance = 0;

    xDistance = p.getposX() - x;
    if (xDistance < 0)
        xDistance *= -1;

    yDistance = p.getposY() - y;
    if (yDistance < 0)
        yDistance *= -1;

    float distance = xDistance + yDistance;
    return distance;
}

template<typename u, typename c, typename d, typename s>
bool checkEnemyPositions(float &x, float &y, u Object1 = nullptr,
                         c Object2 = nullptr, d Object3 = nullptr, s Object4 = nullptr) {

    if (Object1 != nullptr) {

        for (auto &gc: *Object1) {

            if (gc->getHp() > 0) {

                if (abs(gc->getposY() - y) < 1 && abs(gc->getposX() - x) < 1) {

                    if (!gc->isChecked()) {
                        return false;
                    }

                }

            }

        }

    }

    if (Object2 != nullptr) {

        for (auto &gc: *Object2) {

            if (gc->isTaken() == false) {

                if (abs(gc->getposY() - y) < 1 && abs(gc->getposX() - x) < 1)
                    return false;
            }

        }

    }

    if (Object3 != nullptr) {

        for (auto &gc: *Object3) {

            if (gc->getHp() > 0) {

                if ((abs(gc->getposY() - y) < 1 && abs(gc->getposX() - x) < 1)) {

                    if (!gc->isChecked()) {
                        return false;
                    }

                }

            }

        }

    }

    if (Object4 != nullptr) {

        for (auto &gc: *Object4) {

            if (gc->isActivated()) {

                if (abs(gc->getposY() - y) <= 0 && abs(gc->getposX() - x) <= 0)
                    return false;
            }

        }

    }

    return true;
}

template<typename T, typename u, typename c, typename d, typename s, typename f>
bool isLegalMove(const T &object, float dX, float dY, f &map, u *Object1 = nullptr,
                 c *Object2 = nullptr, d *Object3 = nullptr, s *Object4 = nullptr) {

    float newX = object.getposX() + dX;
    float newY = object.getposY() + dY;
    return (checkEnemyPositions(newX, newY, Object1, Object2, Object3, Object4) && map.getPassable(newX, newY));
}

template<typename T, typename u, typename c, typename d, typename s>
bool findFreeMapTile(float &x, float &y, T &map, u *Object1 = nullptr,
                     c *Object2 = nullptr, d *Object3 = nullptr, s *Object4 = nullptr) {

    bool found = false;

    for (int i = x; i < map.getWidth(); i++) {

        for (int j = y; j < map.getHeight(); j++) {

            if (map.getPassable(i, j) == true) {

                if (map.getSpawnPlace(i, j) == true) {

                    found = true;
                    x = i;
                    y = j;

                    if (Object1 != nullptr) {

                        for (auto &gc: *Object1) {

                            if (l2Distance(*gc, x, y) < 45)
                                found = false;

                        }

                    }

                    if (Object2 != nullptr) {

                        for (auto &gc: *Object2) {

                            if (l2Distance(*gc, x, y) < 15)
                                found = false;

                        }

                    }

                    if (Object3 != nullptr) {

                        for (auto &gc: *Object3) {

                            if (l2Distance(*gc, x, y) < 20)
                                found = false;

                        }

                    }

                    if (Object4 != nullptr) {

                        for (auto &gc: *Object4) {

                            if (l2Distance(*gc, x, y) < 15)
                                found = false;

                        }

                    }

                    if (found) {
                        return true;
                    }

                }

            }

        }

    }

    return false;
}

template<typename T, typename u, typename c, typename d>
int legalDamage(const T &object, u *Object1 = nullptr, c *Object2 = nullptr, d *Object3 = nullptr) {
    bool erased = false;
    int index = 0;

    if (Object1 != nullptr && !(typeid(Object1[0]) == typeid(object) || typeid(Object2[0]) == typeid(object))) {

        for (auto &gc: *Object1) {

            if (l2Distance(*gc, object->getposX(), object->getposY()) <= 1.5 && gc->getHp() > 0 && !(gc->isChecked())) {

                if (object->getTimeSinceDamage() >= object->getInvulnerabilityFrame() && (!gc->isFixed())) {
                    object->receiveDamage(gc->getContactDamage());
                    object->setTimeSinceDamage(0);
                }

            }

        }

    }

    if (Object2 != nullptr && !(typeid(Object1[0]) == typeid(object) || typeid(Object2[0]) == typeid(object))) {

        for (auto &gc: *Object2) {

            if (l2Distance(*gc, object->getposX(), object->getposY()) <= 3.5 && gc->getHp() > 0) {

                if (object->getTimeSinceDamage() >= object->getInvulnerabilityFrame()) {
                    object->receiveDamage(gc->getContactDamage());
                    object->setTimeSinceDamage(0);
                }

            }

        }

    }

    return 0;
}

#endif //MAIN_UTILITIES_H
