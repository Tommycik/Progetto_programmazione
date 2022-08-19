//
// Created by tommy on 10/07/2022.
//

#include "Events.h"

int Events::event(sf::RenderWindow *window,std::string *names,std::string *savesVec,Mario &hero,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport,
                  int &mapIndex,int numberMap,World &game,sf::Music &Game,TileMap &map,TileMap &object,
                  TileMap &teleport,TileMap &safezone,std::unique_ptr<Spawner> *vectors) {

    game.setNewSkillCreated(false);
    while (window->pollEvent(Happen))
    {
        cancel=false;
        switch (Happen.type){

            case sf::Event::Closed:
                cancel =true;
                break;

            case sf::Event::KeyPressed:
                if (Happen.key.code == sf::Keyboard::Escape){
                    cancel =true;
                    break;
                }

                if (Happen.key.code == sf::Keyboard::B){
                    if(hero.getPotionNum()!=0)
                        hero.recoverHp(1);}
                break;

            case sf::Event::KeyReleased:
                if (Happen.key.code == sf::Keyboard::R){
                    for(auto &gc:vectors[mapIndex]->getItems()){
                        if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1&&!(gc->isTaken())){


                            switch (gc->getEffect()) {
                                case 1:
                                    hero.setPotionNum(1) ;
                                    gc->setTaken(true);

                                    break;
                                case 2:
                                    hero.setMaxHp(hero.getMaxHp()/10);
                                    hero.setHp(hero.getMaxHp());
                                    gc->setTaken(true);
                                    break;
                                case 3:
                                    hero.setMaxStam(hero.getMaxStam()/10);
                                    gc->setTaken(true);
                                    break;

                                default:
                                    break;
                            }

                            tutorialItem=true;
                            hero.setPotionTaken(hero.getPotionTaken()+1);
                        }
                    }
                }
                if (Happen.key.code == sf::Keyboard::T){
                    for(auto &gc:vectors[mapIndex]->getSafezones()){
                        if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1){

                            hero.recoverHp(0);
                            gc->setUsed(true);
                            tutorialSafezone=true;
                            hero.setSafezoneUsed(hero.getSafezoneUsed()+1);
                        }
                    }
                }
                if (Happen.key.code == sf::Keyboard::V){
                    auto skillCreated=hero.skillUse();
                    if(skillCreated!= nullptr){
                        game.getSkill().reserve(game.getSkillNumber()+1);
                        auto newSkill = game.getSkill().insert(game.getSkill().end(), std::move(skillCreated));
                        game.setSkillNumber(1);
                        game.setNewSkillCreated(true);
                    }
                }
                if (Happen.key.code == sf::Keyboard::O||Happen.key.code == sf::Keyboard::P){
                    for(auto &gc:vectors[mapIndex]->getTeleports()){
                        if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1.5&&gc->isActivated()){

                            if (Happen.key.code == sf::Keyboard::O){
                                if(mapIndex>=numberMap-1) {
                                    mapIndex=0;
                                }else{
                                    mapIndex++;
                                }
                            }else if (Happen.key.code == sf::Keyboard::P){
                                if(mapIndex==0) {
                                    return 0;
                                }else{
                                    mapIndex--;
                                }
                            }
                            hero.setTeleported(hero.getTeleported()+1);
                            return 2;
                        }
                    }
                }
                break;

            default:
                break;
        }
        if (cancel){
            try {
                is.open("playerSave/save.txt");
                is.close();
                remove("playerSave/save.txt");
            } catch (std::ios_base::failure& e) {}

            game.savePlayer(mapIndex,hero,tutorialItem,tutorialSafezone,tutorialTeleport);
            for(int i=0;i<numberMap;i++) {
                try {
                    is.open(savesVec[i].c_str());
                    is.close();
                    remove(savesVec[i].c_str());
                } catch (std::ios_base::failure& e) {}

                vectors[i]->saveVectors(savesVec[i],names[i],vectors[i]->getBossNumber(), vectors[i]->getObjectNumber(), vectors[i]->getMonsterNumber(), vectors[i]->getSafezoneNumber());
            }
            window->close();
            Game.stop();
            return 1;
        }
    }
    return 0;
}
