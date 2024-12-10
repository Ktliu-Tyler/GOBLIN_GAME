// Created by Liu KT on 2024/11/26.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "tool.h"
#include "SDL.h"
#include "constants.h"
#endif //ENEMY_H


class Enemy {
public:
    Enemy(float posx, float posy, float speed, int Hp);
    SDL_Rect *rect;
    void init(float x, float y, float speed, int Hp);
    void render(SDL_Renderer* renderer);
    void kinetic(float dt);
    void destroy();
    void hurted(int att);
    int ifdied();
    int getAttack();
    float x, y;
    bool destroyed = false;
    bool attacked = false;
private:
    int hpMAX = 10;
    int hp = 1;
    float vx=100, vy=100;
    float speed=BDSPEED;
    float width=100, height=100;
};


