//
// Created by tommy on 16/06/2022.
//

#include "World.h"
#include <fstream>


void World::savePlayer(int map, Mario &player,bool tutorialItem,bool tutorialSafezone,bool tutorialTeleport/*, int littleStatus*/) {
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    // try {
    out.open("../playerSave/save.txt",std::ios_base::trunc);
    out << map << std::endl;
    //out << littleStatus << std::endl;
    out << player.getHp() << std::endl;
    out <<player.getStamina()<< std::endl;
    out <<player.getPotionNum()<< std::endl;
    out <<player.getMaxHp()<< std::endl;
    out <<player.getMaxStam()<< std::endl;
    out <<player.getMovements()<< std::endl;
    out <<player.getposX()<< std::endl;
    out <<player.getposY()<< std::endl;
    out <<tutorialItem<< std::endl;
    out <<tutorialSafezone<< std::endl;
    out <<tutorialTeleport<< std::endl;
    out.close();

}


bool World::loadPlayer(int &mapIndex,Mario &player,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport) {

    std::ifstream in;

    in.exceptions(std::ifstream::failbit);
    try {
        in.open("../playerSave/save.txt");
    } catch (std::ios_base::failure& e) {

        return false;
    }
    std::string fileLine;
    std::getline(in, fileLine);
    try {




    mapIndex=(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.setHp(std::stoi(fileLine));//fixme non riporta la vita corretta,la vita massima sì
    std::getline(in, fileLine);
    player.setStamina(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.potionNumSave(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.maxHpSave(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.maxStamSave(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.setMovements(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.setposX(std::stoi(fileLine));
    std::getline(in, fileLine);
    player.setposY(std::stoi(fileLine));
    std::getline(in, fileLine);
    tutorialItem=(std::stoi(fileLine));
    std::getline(in, fileLine);
    tutorialSafezone=(std::stoi(fileLine));
    std::getline(in, fileLine);
    tutorialTeleport=(std::stoi(fileLine));

    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }




    in.close();
    return true;


}
