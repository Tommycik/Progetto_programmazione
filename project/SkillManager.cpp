//
// Created by tommy on 13/08/2022.
//

#include "SkillManager.h"

SkillManager::~SkillManager() {
    _subject->detach(this);
}

SkillManager::SkillManager(World &game, TileMap &skills) {

    this->skills = &skills;
    _subject = &game;
    _subject->attach(this);

}

void SkillManager::update(Subject *theChangedSubject) {

    if (theChangedSubject == _subject)
        draw();
}

void SkillManager::draw() {

    if (_subject->isNewSkillCreated() == true) {
        skills->loadSkill(sf::Vector2u(16, 16), _subject->getSkillNumber(), _subject->getSkill(), true);
    } else {
        skills->loadSkill(sf::Vector2u(16, 16), _subject->getSkillNumber(), _subject->getSkill(), false);
    }
}
