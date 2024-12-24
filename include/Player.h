//
// Created by Liu KT on 2024/11/21.
//

#ifndef PLAYER_H

#include <SDL.h>
#include "constants.h"
#include "tool.h"
// #include "SDL.h"
// #define PLAYER_H
#define PLAYER_H

class Player {
// 玩家 class
public:
    friend class playground;
    Player(float x, float y, float width ,float height, float speed, SDL_Renderer* renderer,float yMax=WINDOW_HEIGHT,float yMin=0);
    ~Player();
    void init(float x, float y);
    void render(SDL_Renderer* renderer);
    void move(char dir);
    void kinetic(float dt);
    void changeArrow(char type);
private:
    SDL_Rect *rect = nullptr;
    SDL_Rect *hitrect = nullptr;
    const std::vector<std::string> Wimages = PLAYER_WALK_IMAGES;
    const std::vector<std::string> Simages = PLAYER_SHOOT_IMAGES;
    const std::vector<std::string> Dimages = PLAYER_DIED_IMAGES;
    Animation* animW = nullptr;
    Animation* animS = nullptr;
    Animation* animD = nullptr;
    float x, y, vx=100, vy=100;
    float speed;
    float width;
    float height;
    float yMax;
    float yMin;
    char direction = 's';
    char state = 'W';
    char type = 'N';
};

class Bullet {
    friend class Player;
    friend class playground;
public:
    Bullet(float posx, float posy, char type, SDL_Renderer* renderer);
    ~Bullet();
    void init(float x, float y);
    void render(SDL_Renderer* renderer);
    void kinetic(float dt);
    void destroy();
    void set_arrow(char t, SDL_Renderer* renderer);
private:
    Animation* anim = nullptr;
    float x, y;
    bool destroyed = false;
    int att = 1;
    char type = 'N';
    int np = 0;
    SDL_Rect *rect;
    const std::vector<std::string> Nimages = ARROW_NORM;
    const std::vector<std::string> Fimages = ARROW_FAST;
    const std::vector<std::string> PNimages = ARROW_POISON;
    const std::vector<std::string> PRimages = ARROW_POWER;
    float vx=100, vy=100;
    float speed=BULLET_SPEED;
    float width=40, height=40;
};

#endif //PLAYER_H