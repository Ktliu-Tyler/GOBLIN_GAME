//
// Created by Liu KT on 2024/11/26.
//

#include "../include/Enemy.h"


Enemy::Enemy(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer) {
    this->hp = Hp;
    this->hpMAX = Hp;
    this->speed = BDSPEED-speed;
    this->width = 30+Hp*15;
    this->height = 30+Hp*15;
    this->x = posx;
    this->y = posy;
    this->rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
    };
    this->hitrect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) (width*ENEMY_HIT_RATE),
        (int) (height*ENEMY_HIT_RATE)
    };
    animW = new Animation('w', 80, this->Wimages, renderer);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer);
}

void Enemy::init(float x, float y, float speed, int Hp) {
    this->x = x;
    this->y = y;
    this->speed = BDSPEED-speed;
    this->hp = Hp;
    this->width = 30+Hp*15;
    this->height = 30+Hp*15;
}

void Enemy::kinetic(float dt) {
    this->x += this->speed * dt;
}

int Enemy::ifdied() {
    if(x < -width) {
        destroyed = true;
        animD->finish = true;
        animD->stop = true;
        return 2;
    }
    if(hp <= 0) {
        hp = 0;
        state = 'D';
        // SDL_Log("die1");
        // if(destroyed==false) {
        //     animD->finish = false;
        // }
        // if(animD->finish) {
        //     animD->stop = true;
        // }
        destroyed = true;
        return 1;
    }
    return 0;
}

void Enemy::hurted(int att) {
    hp -= att;
}

void Enemy::render(SDL_Renderer *renderer) {
    if(destroyed) {
        destroy();
    }
    rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
    };
    this->hitrect = new SDL_Rect {
        (int) (x+width*(1-rectRATE)/2),
        (int) (y+height*(1-rectRATE)/2),
        (int) (width*rectRATE),
        (int) (height*rectRATE)
    };
    if (state == 'W') {
        animW->update(renderer, rect);
    }else if (state == 'S') {
        animS->update(renderer, rect);
        if(animS->finish) {
            state = 'W';
            animW->init();
        }
    }else if (state == 'D') {
        animD->update(renderer, rect);
    }

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(renderer, rect);
    if(!destroyed) {
        renderProgressBar(x, y-15, width, 13
            , hp, hpMAX, myRED, myGREY, renderer);
    }

}

int Enemy::getAttack() {
    return hpMAX;
}


void Enemy::destroy() {
    // SDL_Log("Enemy::destroy");
}
//

Monster::Monster(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = PLAYER_WALK_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = PLAYER_DIED_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 80, this->Wimages, renderer);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer);
}


Human::Human(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = HUMAN_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 80, this->Wimages, renderer);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer);
}

