//
// Created by Liu KT on 2024/11/26.
//

#include "../include/Enemy.h"


Enemy::Enemy(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):hBar(Hp, width, height, renderer) {
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
    delete this->rect;
    this->rect = nullptr;
    rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
    };
    delete this->hitrect;
    this->hitrect = nullptr;
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


    if(!destroyed) {
        hBar.render(x, y, width, hp, renderer);
    }


}

int Enemy::getAttack() {
    return hpMAX;
}


void Enemy::destroy() {
    // animD->playSound(3);
    // SDL_Log("Enemy::destroy");
}

Enemy::~Enemy() {
    if (animW) {
        delete animW;
        animW = nullptr;
    }
    if (animS) {
        delete animS;
        animS = nullptr;
    }
    if (animD) {
        delete animD;
        animD = nullptr;
    }
    if (rect) {
        delete rect;
        rect = nullptr;
    }
    if (hitrect) {
        delete hitrect;
        hitrect = nullptr;
    }
}
//

Monster::Monster(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = MONSTER_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 80, this->Wimages, renderer);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer, BOMB_SOUND);
}
void Monster::kinetic(float dt) {
    static int s = 60;
    this->x += this->speed * dt;
    this->y += s *dt;
    if (this->y > WINDOW_HEIGHT) {
        s = -s;
        this->y = WINDOW_HEIGHT;
    }else if (this->y < WINDOW_M_HEIGHT) {
        s = -s;
        this->y = WINDOW_M_HEIGHT;
    }
}


Human::Human(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = HUMAN_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 80, this->Wimages, renderer, GIRL_SOUND);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer, BOMB_SOUND);
}

Human1::Human1(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = HUMAN1_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 60, this->Wimages, renderer, CLASSMATE_SOUND);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer, BOMB_SOUND);
}


Human2::Human2(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = HUMAN2_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 50, this->Wimages, renderer, CLASSMATE_SOUND);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer, BOMB_SOUND);
}


Human3::Human3(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = HUMAN3_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    animW = new Animation('w', 30, this->Wimages, renderer, CLASSMATE_SOUND);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer, BOMB_SOUND);
}

Shake::Shake(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer):Enemy(posx, posy, speed, Hp, renderer) {
    Wimages = PLAYER_WALK_IMAGES;
    Simages = PLAYER_SHOOT_IMAGES;
    Dimages = EXPLODE_IMAGES;
    rectRATE = 0.7;
    speed = 0;
    animW = new Animation('w', 40, this->Wimages, renderer);
    animS = new Animation('s', 50, this->Simages, renderer);
    animD = new Animation('D', 30, this->Dimages, renderer, BOMB_SOUND);
}

