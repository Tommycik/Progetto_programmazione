//
// Created by tommy on 16/06/2022.
//

#include "Spawner.h"

Spawner::Spawner(bool loading, Dungeonarea &map, int monsterNumber, int objectNumber, int safezoneNumber,
                 int bossNumber) : monsterNumber(monsterNumber), objectNumber(objectNumber), safezoneNumber(safezoneNumber), bossNumber(bossNumber) {

    this->create(loading, map);
}

std::vector<std::unique_ptr<Obstacle>> &Spawner::getEnemies() {
    return enemies;
}

std::vector<std::unique_ptr<Item>> &Spawner::getItems() {
    return items;
}

std::vector<std::unique_ptr<Safezone>> &Spawner::getSafezones() {
    return safezones;
}

std::vector<std::unique_ptr<Teleport>> &Spawner::getTeleports() {
    return teleports;
}

std::vector<std::unique_ptr<Boss>> &Spawner::getBosses() {
    return bosses;
}

void Spawner::create(bool loading, Dungeonarea &map) {
    if (!(this->bosses.empty())) {
        bosses.clear();
    }

    if (!(this->items.empty())) {
        items.clear();
    }

    if (!(this->safezones.empty())) {
        safezones.clear();
    }

    if (!(this->teleports.empty())) {
        teleports.clear();
    }

    enemies.reserve(monsterNumber);
    safezones.reserve(safezoneNumber);
    items.reserve(objectNumber);
    bosses.reserve(bossNumber);
    teleports.reserve(bossNumber);

    Dice itemTypeDice(3);
    for (int i = 0; i < objectNumber; i++) {

        int effect = itemTypeDice.roll(1);
        auto newItem = std::make_unique<Item>(1, 1, effect);

        if (!loading) {
            float startX = map.getRand(0, (map.getWidth() - 2));
            float startY = map.getRand(0, (map.getHeight() - 2));

            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }

            newItem->setposX(startX);
            newItem->setposY(startY);
        }

        items.emplace_back(std::move(newItem));
    }

    if (loading) {
        bossNumber = std::stoi(fileLine);

        if (!(this->bosses.empty())) {
            bosses.clear();
        }

        bosses.reserve(bossNumber);
        std::getline(op, fileLine);
    }

    Dice BossTypeDice(3);//numero tipi di boss
    for (int i = 0; i < bossNumber; i++) {
        int effect = 1;

        if (!loading) {
            effect = BossTypeDice.roll(1);
            float startX = map.getRand(0, (map.getWidth() - 2));
            float startY = map.getRand(0, (map.getHeight() - 2));

            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }

            if (effect == 1) {
                auto newBoss = std::make_unique<Dreadgen>(8, 2, map.getDungeonType());
                newBoss->setposX(startX);
                newBoss->setposY(startY);
                auto newTeleport = std::make_unique<Teleport>(newBoss->getposX(), newBoss->getposY());
                teleports.emplace_back(std::move(newTeleport));
                bosses.emplace_back(std::move(newBoss));

            } else if (effect == 2) {
                auto newBoss = std::make_unique<Dreadgen>(8, 2, map.getDungeonType());
                newBoss->setposX(startX);
                newBoss->setposY(startY);
                auto newTeleport = std::make_unique<Teleport>(newBoss->getposX(), newBoss->getposY());
                teleports.emplace_back(std::move(newTeleport));
                bosses.emplace_back(std::move(newBoss));

            } else if (effect == 3) {
                auto newBoss = std::make_unique<Dreadgen>(8, 2, map.getDungeonType());
                newBoss->setposX(startX);
                newBoss->setposY(startY);
                auto newTeleport = std::make_unique<Teleport>(newBoss->getposX(), newBoss->getposY());
                teleports.emplace_back(std::move(newTeleport));
                bosses.emplace_back(std::move(newBoss));
            }

        } else {
            if (std::stoi(fileLine) != -1) {
                effect = std::stoi(fileLine);
                std::getline(op, fileLine);
            }

            if (effect == 1) {
                auto newBoss = std::make_unique<Dreadgen>(8, 2, map.getDungeonType());
                auto newTeleport = std::make_unique<Teleport>(newBoss->getposX(), newBoss->getposY());
                teleports.emplace_back(std::move(newTeleport));
                bosses.emplace_back(std::move(newBoss));

            } else if (effect == 2) {
                auto newBoss = std::make_unique<Dreadgen>(8, 2, map.getDungeonType());
                auto newTeleport = std::make_unique<Teleport>(newBoss->getposX(), newBoss->getposY());
                teleports.emplace_back(std::move(newTeleport));
                bosses.emplace_back(std::move(newBoss));

            } else if (effect == 3) {
                auto newBoss = std::make_unique<Dreadgen>(8, 2, map.getDungeonType());
                auto newTeleport = std::make_unique<Teleport>(newBoss->getposX(), newBoss->getposY());
                teleports.emplace_back(std::move(newTeleport));
                bosses.emplace_back(std::move(newBoss));
            }

        }

    }

    for (int i = 0; i < safezoneNumber; i++) {
        auto newSafezone = std::make_unique<Safezone>(4, 4);

        if (!loading) {
            float startX = map.getRand(0, (map.getWidth() - 2));
            float startY = map.getRand(0, (map.getHeight() - 2));

            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }

            newSafezone->setposX(startX);
            newSafezone->setposY(startY);
        }

        safezones.emplace_back(std::move(newSafezone));
    }

    if (loading) {

        while (std::stoi(fileLine) != -1) {
            std::getline(op, fileLine);
        }

        std::getline(op, fileLine);
        monsterNumber = std::stoi(fileLine);

        if (!(this->enemies.empty())) {
            enemies.clear();
        }

        enemies.reserve(monsterNumber);
        std::getline(op, fileLine);
    }

    Dice enemyTypeDice(2);
    for (int i = 0; i < monsterNumber; i++) {
        int effect = 1;

        if (!loading) {
            effect = enemyTypeDice.roll(1);
            float startX = map.getRand(0, (map.getWidth() - 2));
            float startY = map.getRand(0, (map.getHeight() - 2));

            while (!(findFreeMapTile(startX, startY, map, &bosses, &items, &enemies, &safezones))) {
                startX = map.getRand(0, (map.getWidth() - 2));
                startY = map.getRand(0, (map.getHeight() - 2));
            }

            if (effect == 1) {
                auto newEnemy = std::make_unique<StaticDanger>(8, 2, map.getDungeonType());
                newEnemy->setposX(startX);
                newEnemy->setposY(startY);
                enemies.emplace_back(std::move(newEnemy));

            } else if (effect == 2) {
                auto newEnemy = std::make_unique<FollowingEnemies>(8, 2, map.getDungeonType());
                newEnemy->setposX(startX);
                newEnemy->setposY(startY);
                enemies.emplace_back(std::move(newEnemy));
            }

        } else {
            if (std::stoi(fileLine) != -1) {
                effect = std::stoi(fileLine);
                std::getline(op, fileLine);
            }

            if (effect == 1) {
                auto newEnemy = std::make_unique<StaticDanger>(8, 2, map.getDungeonType());
                enemies.emplace_back(std::move(newEnemy));

            } else if (effect == 2) {
                auto newEnemy = std::make_unique<FollowingEnemies>(8, 2, map.getDungeonType());
                enemies.emplace_back(std::move(newEnemy));
            }

        }

    }

}

void Spawner::saveVectors(std::string fileName, std::string name, int Bosses, int Items, int Enemies, int Safezones) {
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    out.open(fileName, std::ios_base::trunc);
    out << name << std::endl;
    out << Items << std::endl;
    out << Safezones << std::endl;
    out << Bosses << std::endl;

    out << bosses.size() << std::endl;
    for (auto &gc: this->bosses) {
        out << gc->getType();
        out << std::endl;
    }
    out << -1 << "\n";

    out << enemies.size() << std::endl;
    for (auto &gc: this->enemies) {
        out << gc->getType();
        out << std::endl;
    }
    out << -1 << "\n";

    for (auto &gc: this->bosses) {
        out << gc->getHp() << "\n" << gc->getMovements() << "\n" << gc->getposX() << "\n" << gc->getposY() << "\n"
            << gc->getStatIncrease() << "\n" << gc->getTileNumber();
        out << std::endl;
    }
    out << -1 << "\n";

    for (auto &gc: this->items) {
        out << gc->getMovements() << "\n" << gc->getposX() << "\n" << gc->getposY() << "\n" << gc->getEffect() << "\n"
            << gc->isTaken();
        out << std::endl;
    }
    out << -1 << "\n";

    for (auto &gc: this->enemies) {
        out << gc->getHp() << "\n" << gc->getMovements() << "\n" << gc->getposX() << "\n" << gc->getposY() << "\n"
            << gc->isFixed() << "\n" << gc->getTileNumber() << "\n" << gc->getTextureFile();
        out << std::endl;
    }
    out << -1 << "\n";

    for (auto &gc: this->safezones) {
        out << gc->getMovements() << "\n" << gc->getposX() << "\n" << gc->getposY();
        out << std::endl;
    }
    out << -1 << "\n";

    for (auto &gc: this->teleports) {
        out << gc->getposX() << "\n" << gc->getposY() << "\n" << gc->isActivated();
        out << std::endl;
    }
    out << -1 << "\n";

    out << std::endl;
    out.close();
}

bool Spawner::loadVectors(std::string fileName, std::string name, Dungeonarea &map) {
    op.exceptions(std::ifstream::failbit);

    try {
        op.open(fileName);
    } catch (std::ios_base::failure &e) {
        return false;
    }

    std::getline(op, fileLine);
    if (fileLine.compare(name) != 0)
        throw GameFileException("Vectors file is wrong format", fileName, true);

    std::getline(op, fileLine);
    std::getline(op, fileLine);
    std::getline(op, fileLine);
    std::getline(op, fileLine);
    this->create(true, map);

    try {

        while (std::stoi(fileLine) != -1) {
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);

        for (auto &gc: this->bosses) {

            if (std::stoi(fileLine) != -1) {
                gc->setHp(std::stod(fileLine));
                std::getline(op, fileLine);
                gc->setMovements(std::stod(fileLine));
                std::getline(op, fileLine);
                gc->setposX(std::stod(fileLine));
                std::getline(op, fileLine);
                gc->setposY(std::stod(fileLine));
                std::getline(op, fileLine);
                gc->setStatIncrease(std::stoi(fileLine));
                std::getline(op, fileLine);
                gc->setTileNumber(std::stoi(fileLine));
                std::getline(op, fileLine);
            }

        }

        while (std::stoi(fileLine) != -1) {
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);

        for (auto &gd: this->items) {

            if (std::stoi(fileLine) != -1) {
                gd->setMovements(std::stod(fileLine));
                std::getline(op, fileLine);
                gd->setposX(std::stod(fileLine));
                std::getline(op, fileLine);
                gd->setposY(std::stod(fileLine));
                std::getline(op, fileLine);
                gd->setEffect(std::stoi(fileLine));
                std::getline(op, fileLine);
                gd->setTaken(std::stoi(fileLine));
                std::getline(op, fileLine);
            }

        }

        while (std::stoi(fileLine) != -1) {
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);

        for (auto &gb: this->enemies) {

            if (std::stoi(fileLine) != -1) {
                gb->setHp(std::stod(fileLine));
                std::getline(op, fileLine);
                gb->setMovements(std::stod(fileLine));
                std::getline(op, fileLine);
                gb->setposX(std::stod(fileLine));
                std::getline(op, fileLine);
                gb->setposY(std::stod(fileLine));
                std::getline(op, fileLine);
                gb->setFixed(std::stoi(fileLine));
                std::getline(op, fileLine);
                gb->setTileNumber(std::stoi(fileLine));
                std::getline(op, fileLine);
                gb->setTextureFile(fileLine);
                std::getline(op, fileLine);
            }

        }

        while (std::stoi(fileLine) != -1) {
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);

        for (auto &gv: this->safezones) {

            if (std::stoi(fileLine) != -1) {
                gv->setMovements(std::stod(fileLine));
                std::getline(op, fileLine);
                gv->setposX(std::stod(fileLine));
                std::getline(op, fileLine);
                gv->setposY(std::stod(fileLine));
                std::getline(op, fileLine);
            }

        }

        while (std::stoi(fileLine) != -1) {
            std::getline(op, fileLine);
        }
        std::getline(op, fileLine);

        for (auto &gm: this->teleports) {

            if (std::stoi(fileLine) != -1) {
                gm->setposX(std::stod(fileLine));
                std::getline(op, fileLine);
                gm->setposY(std::stod(fileLine));
                std::getline(op, fileLine);
                gm->setActivated(std::stoi(fileLine));
                std::getline(op, fileLine);
            }

        }

        while (std::stoi(fileLine) != -1) {
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
        bosses.clear();
    }

    if (!(this->items.empty())) {
        items.clear();
    }

    if (!(this->enemies.empty())) {
        enemies.clear();
    }

    if (!(this->safezones.empty())) {
        safezones.clear();
    }

    if (!(this->teleports.empty())) {
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

void Spawner::setMonsterNumber(int monsterNumber) {
    Spawner::monsterNumber += monsterNumber;
}

void Spawner::setBossNumber(int bossNumber) {
    Spawner::bossNumber += bossNumber;
}


