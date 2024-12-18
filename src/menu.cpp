//
// Created by Liu KT on 2024/11/20.
//

#include "../include/menu.h"


inline TTF_Font* fontMENU;

menu::menu(std::string path, SDL_Renderer *renderer, GameRecorder *recorder)  {
    SDL_Log("Creating menu...");
    this -> background = loadTexture(path, renderer);
    this -> renderer = renderer;
    this -> recorder = recorder;
    // player = new Player(PLAYER_W+30, WINDOW_HEIGHT-WINDOW_M_HEIGHT, PLAYER_W, PLAYER_H, PLAYER_SPEED, renderer, WINDOW_HEIGHT,WINDOW_HEIGHT-WINDOW_M_HEIGHT);

    fontMENU =  TTF_OpenFont(FONT, 35);

}

int menu::process_input(SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_q) {
                SDL_Log("SDL_q");

            }
            if (event->key.keysym.sym == SDLK_s) {
                SDL_Log("SDL_s");
                SDL_Log("game");
                return PLAYGROUNDID;
            }
            if (event->key.keysym.sym == SDLK_w) {
                SDL_Log("SDL_w");

            }
            if (event->key.keysym.sym == SDLK_DOWN) {
                SDL_Log("SDL_d");
            }
        break;
    }
    return MENUID;
}

int menu::update(float deltatime) {
    return MENUID;
}

void menu::render(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, this->background, nullptr, nullptr);
    renderText(std::to_string(recorder->HIGHSCORE()), WINDOW_WIDTH/2+20, WINDOW_HEIGHT/2-32 ,myWHITE,fontMENU, renderer, 'l');
    renderText(std::to_string(recorder->LASTSCORE()), WINDOW_WIDTH/2+20, WINDOW_HEIGHT/2+13, myWHITE,fontMENU, renderer, 'l');
    SDL_RenderPresent(renderer);
}

// void changebd() {
//     SDL_Rect renderQuad = { chbgX, -60, WINDOW_WIDTH+600, WINDOW_HEIGHT+90 };
//     SDL_RenderCopy(renderer, backgroundChange, nullptr, &renderQuad);
//     chbgX -=2;
// }


menu::~menu() {
    delete this;
}
