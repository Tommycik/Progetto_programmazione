//
// Created by tommy on 30/06/2022.
//

#include "Loader.h"

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    if (loaded) {

        for (auto &gl: figures) {
            target.draw(*gl);
        }

    } else {
        states.transform *= getTransform();
        // apply the tileset texture
        states.texture = &m_tileset;
        // draw the vertex array
        target.draw(m_vertices, states);
    }

}

bool TileMap::loadSafezone(sf::Vector2u tileSize, int numItem, Spawner &creator) {
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(numItem * 4);
    count = 0;

    for (auto &gl: creator.getSafezones()) {
        this->loading(tileSize, gl->getTileNumber(), false, false, gl->getposY(), gl->getposX());
    }

    return true;
}

bool TileMap::loadTeleport(sf::Vector2u tileSize, int numItem, Spawner &creator) {
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(numItem * 4);
    count = 0;

    for (auto &gl: creator.getTeleports()) {

        if (gl->isActivated()) {
            this->loading(tileSize, gl->getTileNumber(), false, true, gl->getposY(), gl->getposX());
        }

    }

    return true;
}

bool TileMap::loaditem(sf::Vector2u tileSize, int numItem, Spawner &creator) {
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(numItem * 4);
    count = 0;

    for (auto &gl: creator.getItems()) {

        if (!(gl->isTaken())) {
            this->loading(tileSize, gl->getTileNumber(), false, false, gl->getposY(), gl->getposX());
        }

    }

    return true;
}

bool TileMap::loadMap(const std::string &tileset, sf::Vector2u tileSize, Dungeonarea &map, unsigned int width,
                      unsigned int height) {
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    tv = 0;
    tu = 0;
    count = 0;

    for (unsigned int i = 0; i < width; ++i) {

        for (unsigned int j = 0; j < height; ++j) {
            this->loading(tileSize, map.getTileNumber(i, j), true, false, j, i);
        }

    }

    return true;
}

const sf::Texture &TileMap::getMTileset() const {
    return m_tileset;
}

bool TileMap::loading(sf::Vector2u tileSize, int tileNumber, bool map, bool teleport, float j, float i) {
    float posX = i;
    float posY = j;
    int offset = 1;
    if (teleport)
        offset = 2;

    tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
    tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
    sf::Vertex *quad = &m_vertices[(count) * 4];
    count++;

    quad[0].position = sf::Vector2f(posX * tileSize.x, posY * tileSize.y);
    quad[1].position = sf::Vector2f((posX + 1) * tileSize.x, posY * tileSize.y);
    quad[2].position = sf::Vector2f((posX + 1) * tileSize.x, (posY + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(posX * tileSize.x, (posY + 1) * tileSize.y);

    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + offset) * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + offset) * tileSize.x, (tv + offset) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + offset) * tileSize.y);
    return true;
}

bool TileMap::loadEnemy(sf::Vector2u tileSize, int numItem, Spawner &creator, bool change) {
    count = 0;

    if (loaded == false || change) {
        this->loadingChange(numItem);
        int found = false;
        std::string pass = "0";
        count = 0;

        for (auto &gl: creator.getEnemies()) {
            found = false;
            pass = gl->getTextureFile();

            for (auto &gc: textureFile) {

                if (*gc == pass) {
                    found = true;
                    break;
                }

            }

            if (!found) {
                differentTextures++;
                *textureFile[count] = pass;
                count++;
            }

        }

        this->textureLoaded();
    }

    if (activeEntity != numItem || !loaded || change) {
        count = 0;
        textureIndex = 0;

        if (!(this->figures.empty())) {
            figures.clear();
        }

        figures.reserve(numItem);
        for (auto &gl: creator.getEnemies()) {
            textureIndex = 0;

            for (auto &gc: textureFile) {

                if (*gc == gl->getTextureFile()) {
                    break;
                } else {
                    textureIndex++;
                }

            }

            this->figureCreation(*gl, tileSize, false);
        }

    } else {
        count = 0;

        if (numItem != 0) {

            for (auto &gl: creator.getEnemies()) {

                if (gl->getHp() != 0) {
                    figures[count]->setPosition(sf::Vector2f(gl->getposX() * 16, gl->getposY() * 16));
                }

                count++;
            }

        }

    }

    activeEntity = numItem;
    loaded = true;
    return true;
}

bool TileMap::loadTexture(const std::string &tileset) {
    if (!m_tileset.loadFromFile(tileset))
        return false;
    return true;
}

bool TileMap::loadSkill(sf::Vector2u tileSize, int numItem, std::vector<std::unique_ptr<Skills>> &skill, bool change) {
    count = 0;

    if (loaded == false || change) {
        this->loadingChange(numItem);
        count = 0;
        int found = false;
        std::string pass = "0";

        for (auto &gl: skill) {
            found = false;
            pass = gl->getTextureFile();

            for (auto &gc: textureFile) {

                if (*gc == pass) {
                    found = true;
                    break;
                }

            }

            if (!found) {
                differentTextures++;
                *textureFile[count] = pass;
                count++;
            }

        }

        this->textureLoaded();
        activeEntity = numItem;
        loaded = true;
    }

    if (change) {
        count = 0;
        textureIndex = 0;

        if (!(this->figures.empty())) {
            figures.clear();
        }

        figures.reserve(numItem);
        for (auto &gl: skill) {
            textureIndex = 0;

            for (auto &gc: textureFile) {

                if (*gc == gl->getTextureFile()) {
                    break;
                } else {
                    textureIndex++;
                }

            }

            this->figureCreation(*gl, tileSize, true);
        }

    } else {
        count = 0;

        if (numItem != 0) {

            for (auto &gl: skill) {

                if (gl->getHp() != 0) {
                    figures[count]->setPosition(sf::Vector2f(gl->getposX() * 16, gl->getposY() * 16));
                }

                count++;
            }

        }

    }

    return true;
}

void TileMap::loadingChange(int numItem) {
    activeEntity = numItem;

    if (!(this->figuresTexture.empty())) {
        figuresTexture.clear();
    }

    if (!(this->textureFile.empty())) {
        textureFile.clear();
    }

    textureFile.reserve(numItem);
    differentTextures = 0;

    count = 0;
    for (int i = 0; i < numItem; i++) {
        auto newString = std::make_unique<std::string>("0");
        auto itPos = textureFile.begin() + count;
        auto newIt = textureFile.insert(itPos, std::move(newString));
        count++;
    }

}

void TileMap::textureLoaded() {
    figuresTexture.reserve(differentTextures);

    count = 0;
    for (int i = 0; i < differentTextures; i++) {
        auto newTexture = std::make_unique<sf::Texture>();
        auto itPos = figuresTexture.begin() + count;
        auto newIt = figuresTexture.insert(itPos, std::move(newTexture));
        count++;
    }

    count = 0;
    for (auto &gd: figuresTexture) {

        if (*textureFile[count] == "0") {
            gd->loadFromFile("assets/hpBar.png");
        } else {
            gd->loadFromFile(*textureFile[count]);
        }

        count++;
    }

}

void TileMap::figureCreation(Entity &gl, sf::Vector2u tileSize, bool skill) {
    int multiplier = gl.getTextureMultiplier();
    auto newEntity = std::make_unique<sf::RectangleShape>(sf::Vector2f(16.0f, 16.0f));
    newEntity->setPosition(gl.getposX() * 16, gl.getposY() * 16);
    newEntity->setTexture(&*figuresTexture[textureIndex]);
    textureSize = figuresTexture[textureIndex]->getSize();
    textureSize.x /= (figuresTexture[textureIndex]->getSize().x / (tileSize.x * multiplier));
    textureSize.y /= (figuresTexture[textureIndex]->getSize().y / (tileSize.y * multiplier));
    newEntity->setTextureRect(sf::IntRect(textureSize.x * (gl.getTileNumber() %
                                                           (figuresTexture[textureIndex]->getSize().x /
                                                            (tileSize.x * multiplier))), textureSize.y *
                                                                                         (gl.getTileNumber() /
                                                                                          (figuresTexture[textureIndex]->getSize().y /
                                                                                           (tileSize.x * multiplier))),
                                          textureSize.x, textureSize.y));//

    if (!skill) {
        newEntity->setOrigin(1, 7);

        if (boss) {
            newEntity->setScale(3, 3.5);
        } else {
            newEntity->setScale(1.2, 1.5);
        }

    }

    auto itPos = figures.begin() + count;
    auto newIt = figures.insert(itPos, std::move(newEntity));
    count++;
}

bool TileMap::loadBoss(sf::Vector2u tileSize, int numItem, Spawner &creator, bool change) {
    boss = true;
    count = 0;

    if (loaded == false || change) {
        this->loadingChange(numItem);
        int found = false;
        std::string pass = "0";
        count = 0;

        for (auto &gl: creator.getBosses()) {
            found = false;
            pass = gl->getTextureFile();

            for (auto &gc: textureFile) {

                if (*gc == pass) {
                    found = true;
                    break;
                }

            }

            if (!found) {
                differentTextures++;
                *textureFile[count] = pass;
                count++;
            }

        }

        this->textureLoaded();
    }

    if (activeEntity != numItem || !loaded || change) {
        count = 0;
        textureIndex = 0;

        if (!(this->figures.empty())) {
            figures.clear();
        }

        figures.reserve(numItem);
        for (auto &gl: creator.getBosses()) {
            textureIndex = 0;

            for (auto &gc: textureFile) {

                if (*gc == gl->getTextureFile()) {
                    break;
                } else {
                    textureIndex++;
                }

            }

            this->figureCreation(*gl, tileSize, false);
        }

    } else {
        count = 0;

        if (numItem != 0) {

            for (auto &gl: creator.getBosses()) {

                if (gl->getHp() != 0) {
                    figures[count]->setPosition(sf::Vector2f(gl->getposX() * 16, gl->getposY() * 16));
                }

                count++;
            }

        }

    }

    activeEntity = numItem;
    loaded = true;
    return true;
}


