//
// Created by Liu KT on 2024/11/20.
//

#ifndef TOOL_H
#define TOOL_H
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "vector"
#include "iostream"

//一些遊戲工具
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);// 載入圖片

class Animation {
    std::vector<SDL_Texture*> frames;
    int currentFrameIndex = 0;
    int frameMax = 0;
    int timeCounter = 0;
    void addAnimationFrame(const std::string& path, SDL_Renderer* renderer);
    public:
    int updateTime = 0;
    int finish = false;
    void init();
    char id;
    Animation(char id, int updateTime, const std::vector<std::string>& imagePaths, SDL_Renderer* renderer);
    SDL_Texture* getCurrentFrame();
    ~Animation();
    bool update(SDL_Renderer* renderer, SDL_Rect *rect);
};

#endif //TOOL_H