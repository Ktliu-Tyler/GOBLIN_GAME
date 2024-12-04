//
// Created by Liu KT on 2024/11/20.
//

#ifndef PLAYGROUND_H
#include <iostream>
#include "constants.h"
#include "tool.h"
#include <string>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <random>

#define PLAYGROUND_H
#endif //MENU_H

inline Player *player;
inline std::vector<Bullet *> bullets;
inline std::vector<Enemy *> enemys;

class playground { // 遊戲介面 class
    private:
    float backgroundX;
    int timecounter = 0;
    int enemyNUM = 0;
    public:
    SDL_Texture *background = nullptr;
    SDL_Texture *backgroundMove = nullptr;
    SDL_Renderer *renderer = nullptr;
    int update(float deltatime);
    int process_input(SDL_Event *event, const Uint8* keystate);
    void render(SDL_Renderer *renderer);
    void movebd(float deltatime);// 移動背景
    void bdrender();
    void new_Enemy();
    void bullet_update(float deltatime);
    void enemy_update(float deltatime);
    playground(std::string path,std::string pathMove, SDL_Renderer* renderer);
    ~playground();
};




