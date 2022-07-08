//
// Created by tommy on 16/06/2022.
//

#include "Spawner.h"



Spawner::Spawner(int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber) : monsterNumber(
        monsterNumber), objectNumber(objectNumber), safezoneNumber(safezoneNumber), bossNumber(bossNumber) {

    this->create();
}

 std::vector<Obstacle *> &Spawner::getEnemies()  {
    return enemies;
}



 std::vector<Item *> &Spawner::getItems()  {
    return items;
}




 std::vector<Object *> &Spawner::getSafezones() {
    return safezones;
}



 std::vector<Teleport *> &Spawner::getTeleports()  {
    return teleports;
}



 std::vector<Boss *> &Spawner::getBosses()  {
    return bosses;
}




void Spawner::create() {
    enemies.reserve(monsterNumber);
    safezones.reserve(safezoneNumber);
    items.reserve(objectNumber);
    bosses.reserve(bossNumber);
    teleports.reserve(bossNumber);

    Dice itemTypeDice(3);

    for(int i=0; i<objectNumber; i++) {
        Item* item;
        int effect=itemTypeDice.roll(1);
        if(effect==1) {
            item = new Item(1,1,1,1);
        } else if(effect==2) {
            item = new Item(1,1,1,2);
        }else{
            item = new Item(1,1,1,3);
        }
        items.push_back(item);
    }

    Dice BossTypeDice(3);

    for(int i=0; i<bossNumber; i++) {
        Boss* boss;
        Teleport* teleport;
        int effect=BossTypeDice.roll(1);
        if(effect==1) {
            boss = new Boss(2,1,2,2,1);
        } else if(effect==2) {
            boss = new Boss(2,1,2,2,1);
        }else{
            boss = new Boss(2,1,2,2,1);
        }


        teleport=new Teleport(3,3);
        bosses.push_back(boss);
        teleports.push_back(teleport);
    }

    for(int i=0; i<safezoneNumber; i++) {
        Object* safezone;
        safezone = new Object(1,4,4);


        safezones.push_back(safezone);
    }

    Dice enemyTypeDice(3);//todo fare in modo che i nemici peggio abbiano meno possibilità

    for(int i=0; i<monsterNumber; i++) {
        Obstacle* enemy;
        int effect=enemyTypeDice.roll(1);
        if(effect==1) {
            enemy = new Obstacle(5,1,8,2,true);
        } else if(effect==2) {
            enemy = new Obstacle(5,1,8,2,true);
        }else{
            enemy = new Obstacle(5,1,8,2,true);
        }
        enemies.push_back(enemy);
    }
}
void Spawner::saveVectors(std::string fileName,std::string name,int Bosses,int Items,int Enemies,int Safezones){
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    // try {
    out.open(fileName,std::ios_base::trunc);
    out << name << std::endl;
    out <<Bosses<< std::endl;
    out <<Items<< std::endl;
    out <<Enemies<< std::endl;
    out <<Safezones<< std::endl;


    for(auto gc:this->bosses){
        out << gc->getHp() << "\n" << gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->getStatIncrease();
        out << std::endl;
    }
    for(auto gc:this->items){
        out << gc->getMovements() << "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->getEffect()<< "\n" << gc->isTaken();
        out << std::endl;
    }
    for(auto gc:this->enemies){

        out << gc->getHp() << "\n" << gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" <<gc->isFixed();
        out << std::endl;
    }

    for(auto gc:this->safezones){
        out <<gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY();
        out << std::endl;
    }

    for(auto gc:this->teleports){
        out << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->isActivated();
        out << std::endl;
    }
    out << std::endl;
    out.close();
    //}
}
bool Spawner::loadVectors(std::string fileName,std::string name){
    std::ifstream in;

    in.exceptions(std::ifstream::failbit);
    try {
        in.open(fileName);
    } catch (std::ios_base::failure& e) {

        return false;
    }
    std::string fileLine;
    std::getline(in, fileLine);
    if (fileLine.compare(name) != 0)
        throw GameFileException("Map file is in wrong format", "../vectors/vector.txt", true);
    std::getline(in, fileLine);
    this->bosses.reserve(std::stoi(fileLine));
    this->teleports.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    this->items.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    this->enemies.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    this->safezones.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);


    try {
        for(auto gc:this->bosses){
            gc->setHp(std::stoi(fileLine));
            std::getline(in, fileLine);
            gc->setMovements(std::stoi(fileLine));
            std::getline(in, fileLine);
            gc->setposX(std::stoi(fileLine));
            std::getline(in, fileLine);
            gc->setposY(std::stoi(fileLine));
            std::getline(in, fileLine);
            gc->setStatIncrease(std::stoi(fileLine));
            std::getline(in, fileLine);
        }
        for(auto gd:this->items){
            gd->setMovements(std::stoi(fileLine));
            std::getline(in, fileLine);
            gd->setposX(std::stoi(fileLine));
            std::getline(in, fileLine);
            gd->setposY(std::stoi(fileLine));
            std::getline(in, fileLine);
            gd->setEffect(std::stoi(fileLine));
            std::getline(in, fileLine);
            gd->setTaken(std::stoi(fileLine));
            std::getline(in, fileLine);
        }
        for(auto gb:this->enemies){
            gb->setHp(std::stoi(fileLine));
            std::getline(in, fileLine);
            gb->setMovements(std::stoi(fileLine));
            std::getline(in, fileLine);
            gb->setposX(std::stoi(fileLine));
            std::getline(in, fileLine);

            gb->setposY(std::stoi(fileLine));
            std::getline(in, fileLine);
            gb->setFixed(std::stoi(fileLine));
            std::getline(in, fileLine);
        }

        for(auto gv:this->safezones){
            gv->setMovements(std::stoi(fileLine));
            std::getline(in, fileLine);
            gv->setposX(std::stoi(fileLine));
            std::getline(in, fileLine);
            gv->setposY(std::stoi(fileLine));
            std::getline(in, fileLine);

        }

        for(auto gm:this->teleports){
            gm->setposX(std::stoi(fileLine));
            std::getline(in, fileLine);
            gm->setposY(std::stoi(fileLine));
            std::getline(in, fileLine);
            gm->setActivated(std::stoi(fileLine));
            std::getline(in, fileLine);
        }
    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }




    in.close();
    return true;





}