//
// Created by tommy on 30/07/2022.
//

#include "StaticDanger.h"


StaticDanger::StaticDanger(int posX, int posY, int dungeonType){
int n=0;
int i=0;
int random=1;
    switch (dungeonType) {

        case 0://

            n = 5 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*66+4;//32*66+4;
            }else if(random==2){
                this->tileNumber=32*66+3;//32*66+3;
            }else if(random==3){
                this->tileNumber=32*68+2;//32*68+2
            }else if(random==4){
                this->tileNumber=32*66+6;//32*62+4
            }else if(random==5){
                this->tileNumber=32*86+4;
            }
             break;
        case 1:
            n = 4 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*62+7;//32*66+4;
            }else if(random==2){
                this->tileNumber=32*64+7;//32*66+3;
            }else if(random==3){
                this->tileNumber=32*62+2;//32*68+2
            }else if(random==4){
                this->tileNumber=32*62+3;
            }
            break;
        case 2://todo aggiungere cristalli
            n = 4 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*90+12;//32*90+12;
            }else if(random==2){
                this->tileNumber=32*98+8;;//32*98+8;
            }else if(random==3){
                this->tileNumber=32*80+8;;//32*80+8
            }else if(random==4){
                this->tileNumber=32*68+21;//32*68+21
            }
            break;
        case 3:
            n = 3 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*100+30;//32*100+30;
            }else if(random==2){
                this->tileNumber=32*102+30;//32*102+30;
            }else if(random==3){
                this->tileNumber=32*96+29;//32*96+29
            }
            break;
        case 4:
            n = 3 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*118+26;//32*118+26;
            }else if(random==2){
                this->tileNumber=32*122+20;//32*122+20;
            }else if(random==3){
                this->tileNumber=32*122+17;//32*122+17
            }
            break;
        case 5:
            n = 3 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*118+15;;//32*118+15;
            }else if(random==2){
                this->tileNumber=32*112+13;//32*112+13;
            }else if(random==3){
                this->tileNumber=32*110+3;//32*110+3
            }
            break;
        default :
            n = 5 - 1 + 1;
            i = rand() % n;
            if (i < 0)
                i = -i;

            random=1 + i;
            if(random==1){
                this->tileNumber=32*66+4;//32*66+4;
            }else if(random==2){
                this->tileNumber=32*66+3;//32*66+3;
            }else if(random==3){
                this->tileNumber=32*68+2;//32*68+2
            }else if(random==4){
                this->tileNumber=32*66+6;//32*62+4
            }else if(random==5){
                this->tileNumber=32*86+4;
            }
            break;

    }
    this->activated=false;
    this->fixed=true;
    this->hp=1;
    this->movements=0;
    this->posX=posX;
    this->posY=posY;
    this->killable=true;
    this->type=1;
    this->textureFile="assets/TileSet.png";
    this->textureMultiplier=2;
}

void StaticDanger::behaviour(Entity &target) {

}

void StaticDanger::tracking(Entity &target) {

}

void StaticDanger::move(float x, float y) {

}
