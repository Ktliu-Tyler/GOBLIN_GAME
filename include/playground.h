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


class playground { // 遊戲介面 class
    protected:
    float backgroundX;
    int timecounter = 0;
    int enemyNUM = 0;
    int chbgX = -300;
    int gameStart = false;
    public:
    SDL_Texture *background = nullptr;
    SDL_Texture *backgroundMove = nullptr;
    SDL_Texture *backgroundChange = nullptr;
    SDL_Renderer *renderer = nullptr;
    GameRecorder *recorder = nullptr;
    MusicPlayer *musicPlayer = nullptr;
    Player *player;
    Scoreboard *scoreboard;
    std::vector<Bullet *> bullets;
    std::vector<Enemy *> enemys;
    int update(float deltatime);
    int process_input(SDL_Event *event, const Uint8* keystate);
    void render(SDL_Renderer *renderer);
    void movebd(float deltatime);// 移動背景
    void bdrender();
    void new_Enemy();
    void bullet_update(float deltatime);
    void enemy_update(float deltatime);
    int gameOVER_ANIME();
    int gameSTOP();
    void changebd();
    playground(std::string path,std::string pathMove, SDL_Renderer* renderer, GameRecorder *recorder, MusicPlayer *music_player);
    ~playground();
};


class playground2:public playground {
public:
    playground2(std::string path,std::string pathMove, SDL_Renderer* renderer, GameRecorder *recorder, MusicPlayer *music_player);

};



