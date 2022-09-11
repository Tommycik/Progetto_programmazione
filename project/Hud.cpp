//
// Created by tommy on 19/06/2022.
//

#include "Hud.h"

bool Hud::hudSetter(Mario &player, int tilesetResolution, int &HudBarsHeigth) {
    if (!this->hpBar.loadFromFile("assets/hpBar.png"))
        return false;
    if (!this->staminaBar.loadFromFile("assets/green.png"))
        return false;
    if (!this->potion.loadFromFile("assets/potions.png"))
        return false;

    this->staminaBar.setSmooth(true);
    this->hpBar.setSmooth(true);
    life.setSize(sf::Vector2f(player.getHp() / 10 * tilesetResolution, HudBarsHeigth));
    stamina.setSize(sf::Vector2f(player.getStamina() / 10 * tilesetResolution, HudBarsHeigth));
    this->potionIcon.setSize(sf::Vector2f(tilesetResolution, tilesetResolution));
    this->life.setTexture(&this->hpBar);
    this->stamina.setTexture(&this->staminaBar);
    this->potionIcon.setTexture(&this->potion);
    sf::Vector2u textureSize = this->potion.getSize();
    textureSize.x /= 21;
    textureSize.y /= 15;
    this->potionIcon.setTextureRect(sf::IntRect(textureSize.x * 12, textureSize.y * 0, textureSize.x, textureSize.y));
    this->Potion.setFont(this->myFont);
    this->Potion.setFillColor(sf::Color::White);
    this->Potion.setCharacterSize(128);
    this->Potion.setScale(sf::Vector2f(0.1, 0.1));
    this->Potion.setOutlineColor(sf::Color::Black);
    this->Potion.setOutlineThickness(thickness);

    if (!this->myFont.loadFromFile("assets/arial.ttf")) {
        return false;
    }
    return true;
}

Hud::Hud(int thickness) : thickness(thickness) {}

bool Hud::hudSow(Mario &player, sf::RenderWindow *window, int tilesetResolution, int &HudBarsHeigth, sf::View &view1) {
    stamina.setSize(sf::Vector2f(player.getStamina() / 10 * tilesetResolution, HudBarsHeigth));
    life.setSize(sf::Vector2f(player.getHp() / 10 * tilesetResolution, HudBarsHeigth));
    ss << player.getPotionNum();
    Potion.setString(ss.str().c_str());
    ss.str("");
    life.setPosition(player.getposX() * tilesetResolution - view1.getSize().x / 2,
                     player.getposY() * tilesetResolution - view1.getSize().y / 2);
    stamina.setPosition(life.getPosition().x + 2, life.getPosition().y + 8);
    Potion.setPosition(life.getPosition().x + 3, stamina.getPosition().y + 8);

    if (player.getPotionNum() < 10) {
        potionIcon.setPosition(Potion.getPosition().x + 7, Potion.getPosition().y);
    } else {
        potionIcon.setPosition(Potion.getPosition().x + 14, Potion.getPosition().y);
    }

    window->draw(life);
    window->draw(stamina);
    window->draw(Potion);
    window->draw(potionIcon);
    return true;
}
