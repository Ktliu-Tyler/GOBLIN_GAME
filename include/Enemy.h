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
    Enemy(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
    SDL_Rect *rect;
    SDL_Rect *hitrect;
    void init(float x, float y, float speed, int Hp);
    void render(SDL_Renderer* renderer);
    void kinetic(float dt);
    void destroy();
    void hurted(int att);
    int ifdied();
    int getAttack();
    std::vector<std::string> Wimages = ENEMY1_IMAGES;
    std::vector<std::string> Simages = ENEMY1_DIE;
    std::vector<std::string> Dimages = ENEMY1_DIE;
    Animation* animW = nullptr;
    Animation* animS = nullptr;
    Animation* animD = nullptr;
    float x, y;
    bool destroyed = false;
    bool attacked = false;
    char state = 'W';
    int dieANIMcount = 0;
    float speed=BDSPEED;
    float rectRATE = 0.6;
    char type = 'E';
protected:
    int hpMAX = 10;
    int hp = 1;
    float width=100, height=100;
};


class Monster: public Enemy {
public:
    Monster(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
};

class Human: public Enemy {
public:
    Human(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
};

class Human1: public Enemy {
public:
    Human1(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
};

class Human2: public Enemy {
public:
    Human2(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
};

class Human3: public Enemy {
public:
    Human3(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
};

class Shake: public Enemy {
public:
    Shake(float posx, float posy, float speed, int Hp, SDL_Renderer* renderer);
};