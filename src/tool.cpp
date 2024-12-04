//
// Created by Liu KT on 2024/11/20.
//
#include "../include/tool.h"

#include "../include/engine.h"


SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
         SDL_Log("Unable to load image %s", IMG_GetError);
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            SDL_Log("Unable to create texture from %s", IMG_GetError);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

Animation::Animation(char id,int t, const std::vector<std::string>& imagePaths, SDL_Renderer* renderer){
    this->id = id;
    this->updateTime = t;
    this->finish = true;
    for (const std::string& path : imagePaths) {
        addAnimationFrame(path ,renderer);
    }

}

void Animation::addAnimationFrame(const std::string &path, SDL_Renderer* renderer) {
    SDL_Texture* frame = loadTexture(path.c_str(), renderer);
    this->frames.push_back(frame);
    this->frameMax++;
}

SDL_Texture *Animation::getCurrentFrame() {
    timeCounter++;
    if (timeCounter >= updateTime) {
        currentFrameIndex++;
        if (currentFrameIndex == frameMax) {
            currentFrameIndex = 0;
            finish = true;
        }
        timeCounter = 0;

    }
    return frames[currentFrameIndex];
}

bool Animation::update(SDL_Renderer* renderer, SDL_Rect *rect) {
    SDL_RenderCopy(renderer, getCurrentFrame(), nullptr, rect);
    return (this->currentFrameIndex>=this->frameMax-1);
}

void Animation::init() {
    currentFrameIndex = 0;
    finish = false;
}


