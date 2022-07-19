//
// Created by tommy on 16/06/2022.
//

#include "Spawner.h"

Spawner::Spawner(bool loading,Dungeonarea &map,int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber) : monsterNumber(
        monsterNumber), objectNumber(objectNumber), safezoneNumber(safezoneNumber), bossNumber(bossNumber) {

    this->create(loading,map);
}

std::vector<Obstacle *> &Spawner::getEnemies()  {
    return enemies;
}

std::vector<Item *> &Spawner::getItems()  {
    return items;
}

std::vector<Safezone *> &Spawner::getSafezones() {
    return safezones;
}

std::vector<Teleport *> &Spawner::getTeleports()  {
    return teleports;
}

std::vector<Boss *> &Spawner::getBosses()  {
    return bosses;
}

void Spawner::create(bool loading ,Dungeonarea &map) {//todo la creazione dei boss dipende da mapIndex

    if (!(this->bosses.empty())) {
        for (auto p : bosses)
        {
            delete p;
        }
        bosses.clear();
    }
    if (!(this->items.empty())) {
        for (auto p : items)
        {
            delete p;
        }
        items.clear();
    }
    if (!(this->enemies.empty())) {
        for (auto p : enemies)
        {
            delete p;
        }
        enemies.clear();
    }
    if (!(this->safezones.empty())) {
        for (auto p : safezones)
        {
            delete p;
        }
        safezones.clear();
    }
    if (!(this->teleports.empty())) {
        for (auto p : teleports)
        {
            delete p;
        }
        teleports.clear();
    }

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
            item = new Item(1,1,2,2);
        }else{
            item = new Item(1,1,3,3);
        }
        if(loading==false){
            int startX = map.getRand(0, (map.getWidth() - 2));
            int startY = map.getRand(0, (map.getHeight() - 2));
            while(!(findFreeMapTile(startX, startY, map,&bosses,&items,&enemies,&safezones))){
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }
            item->setposX(startX);
            item->setposY(startY);}
        items.push_back(item);
    }

    Dice BossTypeDice(6);

    for(int i=0; i<bossNumber; i++) {
        Boss* boss;
        Teleport* teleport;
        int effect=BossTypeDice.roll(1);
        if(effect==1) {
            boss = new Boss(2,1,2,2,1);
        } else if(effect==2) {
            boss = new Boss(2,1,2,2,1);
        }else if(effect==3){
            boss = new Boss(2,1,2,2,1);
        }else if(effect==4){
            boss = new Boss(2,1,2,2,1);
        }else if(effect==5){
            boss = new Boss(2,1,2,2,1);
        }else if(effect==6){
            boss = new Boss(2,1,2,2,1);
        }
        if(loading==false) {
            int startX = map.getRand(0, (map.getWidth() - 2));
            int startY = map.getRand(0, (map.getHeight() - 2));
            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }
            boss->setposX(startX);
            boss->setposY(startY);
        }
        teleport=new Teleport(boss->getposX(),boss->getposY());
        bosses.push_back(boss);
        teleports.push_back(teleport);
    }

    for(int i=0; i<safezoneNumber; i++) {
        Safezone* safezone;
        safezone = new Safezone(4,4);
        if(loading==false) {
            int startX = map.getRand(0, (map.getWidth() - 2));
            int startY = map.getRand(0, (map.getHeight() - 2));
            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }
            safezone->setposX(startX);
            safezone->setposY(startY);
        }
        safezones.push_back(safezone);
    }

    Dice enemyTypeDice(5);//todo fare op modo che i nemici peggio abbiano meno possibilità

    for(int i=0; i<monsterNumber; i++) {
        Obstacle* enemy;
        int effect=enemyTypeDice.roll(1);
        if(effect==1) {
            enemy = new Obstacle(5,1,8,2,true);
        } else if(effect==2) {
            enemy = new Obstacle(5,1,8,2,true);
        }else if(effect==3){
            enemy = new Obstacle(5,1,8,2,true);
        }else if(effect==4){
            enemy = new Obstacle(5,1,8,2,true);
        }else if(effect==5){
            enemy = new Obstacle(5,1,8,2,true);
        }
        if(loading==false) {
            int startX = map.getRand(0, (map.getWidth() - 2));
            int startY = map.getRand(0, (map.getHeight() - 2));
            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }
            enemy->setposX(startX);
            enemy->setposY(startY);
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
    out <<-1<<"\n";
    for(auto gc:this->items){
        out << gc->getMovements() << "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->getEffect()<< "\n" << gc->isTaken();
        out << std::endl;
    }
    out <<-1<<"\n";
    for(auto gc:this->enemies){

        out << gc->getHp() << "\n" << gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" <<gc->isFixed();
        out << std::endl;
    }
    out <<-1<<"\n";
    for(auto gc:this->safezones){
        out <<gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY();
        out << std::endl;
    }
    out <<-1<<"\n";
    for(auto gc:this->teleports){
        out << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->isActivated();
        out << std::endl;
    }
    out <<-1<<"\n";
    out << std::endl;
    out.close();
    //}
}
bool Spawner::loadVectors(std::string fileName,std::string name,Dungeonarea &map){

    op.exceptions(std::ifstream::failbit);

    try {
        op.open(fileName);
    } catch (std::ios_base::failure& e) {

        return false;
    }
    std::string fileLine;
    std::getline(op, fileLine);

    if (fileLine.compare(name) != 0)
        throw GameFileException("Map file is op wrong format", "../vectors/vector.txt", true);

    std::getline(op, fileLine);

    /* if(std::stoi(fileLine)>this->bossNumber)
         this->bossNumber=std::stoi(fileLine);*/

    std::getline(op, fileLine);
    /* if(std::stoi(fileLine)>this->objectNumber)
         this->objectNumber=std::stoi(fileLine);*/

    std::getline(op, fileLine);
    /*  if(std::stoi(fileLine)>this->monsterNumber)
          this->monsterNumber=std::stoi(fileLine);
*/
    std::getline(op, fileLine);
    /* if(std::stoi(fileLine)>this->safezoneNumber)
         this->safezoneNumber=std::stoi(fileLine);
*/
    std::getline(op, fileLine);
    this->create(true,map);

    try {
        for(auto gc:this->bosses){

            Boss* boss;
            boss = new Boss(5,1,8,2,true);

            if(std::stoi(fileLine)!=-1){
                gc->setHp(std::stoi(fileLine));
                std::getline(op, fileLine);
                gc->setMovements(std::stoi(fileLine));
                std::getline(op, fileLine);
                gc->setposX(std::stoi(fileLine));
                std::getline(op, fileLine);
                gc->setposY(std::stoi(fileLine));
                std::getline(op, fileLine);
                gc->setStatIncrease(std::stoi(fileLine));
                std::getline(op, fileLine);
            }
        }
        while(std::stoi(fileLine)!=-1){
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);
        for(auto gd:this->items){

            Item* item;
            item = new Item(1,1,1,1);

            if(std::stoi(fileLine)!=-1){
                gd->setMovements(std::stoi(fileLine));
                std::getline(op, fileLine);
                gd->setposX(std::stoi(fileLine));
                std::getline(op, fileLine);
                gd->setposY(std::stoi(fileLine));
                std::getline(op, fileLine);
                gd->setEffect(std::stoi(fileLine));
                std::getline(op, fileLine);
                gd->setTaken(std::stoi(fileLine));
                std::getline(op, fileLine);
            }
        }
        while(std::stoi(fileLine)!=-1){
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);
        for(auto gb:this->enemies){

            Obstacle* enemy;
            enemy = new Obstacle(5,1,8,2,true);

            if(std::stoi(fileLine)!=-1){
                gb->setHp(std::stoi(fileLine));
                std::getline(op, fileLine);
                gb->setMovements(std::stoi(fileLine));
                std::getline(op, fileLine);
                gb->setposX(std::stoi(fileLine));
                std::getline(op, fileLine);

                gb->setposY(std::stoi(fileLine));
                std::getline(op, fileLine);
                gb->setFixed(std::stoi(fileLine));
                std::getline(op, fileLine);
            }
        }
        while(std::stoi(fileLine)!=-1){
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);
        for(auto gv:this->safezones){

            Safezone* safezone;
            safezone = new Safezone(4,4);


            if(std::stoi(fileLine)!=-1){
                gv->setMovements(std::stoi(fileLine));
                std::getline(op, fileLine);
                gv->setposX(std::stoi(fileLine));
                std::getline(op, fileLine);
                gv->setposY(std::stoi(fileLine));
                std::getline(op, fileLine);
            }
        }
        while(std::stoi(fileLine)!=-1){
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);
        for(auto gm:this->teleports){

            Teleport* teleport;
            teleport=new Teleport(3,3);

            if(std::stoi(fileLine)!=-1){
                gm->setposX(std::stoi(fileLine));
                std::getline(op, fileLine);
                gm->setposY(std::stoi(fileLine));
                std::getline(op, fileLine);
                gm->setActivated(std::stoi(fileLine));
                std::getline(op, fileLine);
            }
        }
        while(std::stoi(fileLine)!=-1){
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);
    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }

    op.close();
    return true;
}

Spawner::~Spawner() {

    if (!(this->bosses.empty())) {
        for (auto p : bosses)
        {
            delete p;
        }
        bosses.clear();
    }
    if (!(this->items.empty())) {
        for (auto p : items)
        {
            delete p;
        }
        items.clear();
    }
    if (!(this->enemies.empty())) {
        for (auto p : enemies)
        {
            delete p;
        }
        enemies.clear();
    }
    if (!(this->safezones.empty())) {
        for (auto p : safezones)
        {
            delete p;
        }
        safezones.clear();
    }
    if (!(this->teleports.empty())) {
        for (auto p : teleports)
        {
            delete p;
        }
        teleports.clear();
    }
}

int Spawner::getMonsterNumber() const {
    return monsterNumber;
}

int Spawner::getObjectNumber() const {
    return objectNumber;
}

int Spawner::getSafezoneNumber() const {
    return safezoneNumber;
}

int Spawner::getBossNumber() const {
    return bossNumber;
}
