//
// Created by Liu KT on 2024/11/26.
//

#include "../include/Enemy.h"

Enemy::Enemy(float posx, float posy, float speed, int Hp) {
    this->x = posx;
    this->y = posy;
    this->hp = Hp;
    this->speed = BDSPEED-speed;
    this->width = 30+Hp*15;
    this->height = 30+Hp*15;
    this->rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
    };
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

void Enemy::ifdied() {
    if(x < -width) {
        destroyed = true;
    }
    if(hp <= 0) {
        destroyed = true;
    }
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, rect);
}

void Enemy::destroy() {
    // SDL_Log("Enemy::destroy");
}



