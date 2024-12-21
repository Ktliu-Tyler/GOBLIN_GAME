//
// Created by Liu KT on 2024/11/21.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include "constants.h"
#include "tool.h"
// #include "SDL.h"
// #define PLAYER_H
#endif //PLAYER_H

class Player {
// 玩家 class
public:
    Player(float x, float y, float width ,float height, float speed, SDL_Renderer* renderer,float yMax=WINDOW_HEIGHT,float yMin=0);
    SDL_Rect *rect = nullptr;
    SDL_Rect *hitrect = nullptr;
    void init(float x, float y);
    void render(SDL_Renderer* renderer);
    void move(char dir);
    void kinetic(float dt);
    void shoot();
    void changeArrow(char type);
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
    public:
    Bullet(float posx, float posy, char type, SDL_Renderer* renderer);
    SDL_Rect *rect;
    void init(float x, float y);
    void render(SDL_Renderer* renderer);
    void kinetic(float dt);
    void destroy();
    void set_arrow(char t, SDL_Renderer* renderer);
    const std::vector<std::string> Nimages = ARROW_NORM;
    const std::vector<std::string> Fimages = ARROW_FAST;
    const std::vector<std::string> PNimages = ARROW_POISON;
    const std::vector<std::string> PRimages = ARROW_POWER;
    // Animation* animN = nullptr;
    // Animation* animF = nullptr;
    // Animation* animPN = nullptr;
    // Animation* animPR = nullptr;
    // std::vector<Animation*> anims = {animN, animF, animPN, animPR};
    Animation* anim = nullptr;
    float x, y;
    bool destroyed = false;
    int att = 1;
    char type = 'N';
    int np = 0;
private:
    float vx=100, vy=100;
    float speed=BULLET_SPEED;
    float width=40, height=40;
};

