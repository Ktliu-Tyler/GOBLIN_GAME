//
// Created by Liu KT on 2024/9/9.
//

#include "../include/engine.h"

SDL_Window *mywindow = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *background = nullptr;


GameRecorder *game_recorder = nullptr;
menu *MenuPage = nullptr;
playground *PlayPage = nullptr;
MusicPlayer *BGMmusic = nullptr;

std::vector<std::string> playbg = PLAYGROUND_BACKGROUND;
std::vector<std::string> playbgMove = PLAYGROUND_BACKGROUND_MOVE;
const Uint8* keystate = (SDL_GetKeyboardState(NULL));
int PAGE_ID = 0;
int gametype = 1;
int prePage_ID = 0;
int last_frame_time = 0;
float delta_time = 0;

int initialize_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Init Error: %s\n", SDL_GetError());
        return FALSE;
    }
    mywindow = SDL_CreateWindow("Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
        );
    if (!mywindow) {
        fprintf(stderr, "Window Error: %s\n", SDL_GetError());
        SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return FALSE;
    }
    renderer = SDL_CreateRenderer(mywindow, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer Error: %s\n", SDL_GetError());
        SDL_Log("Renderer Error: %s\n", SDL_GetError());
        return FALSE;
    }
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF Error: %s\n", SDL_GetError());
        SDL_Log("TTF Error: %s\n", SDL_GetError());
        return FALSE;
    }
    TTF_Font* font = TTF_OpenFont(FONT, 24);
    if (!font) {
        fprintf(stderr, "Font Error: %s\n", TTF_GetError());
        SDL_Log("Font Error: %s\n", TTF_GetError());
        return FALSE;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    SDL_Log("Engine Fine!");
    return TRUE;
}

void setup() {
    SDL_Log("test1");
    const std::vector<std::string> BGMpath = {MENUBGM, PLAYGROUNDBGM, GAMEOVERBGM, PLAYGROUNDBGM2};
    BGMmusic = new MusicPlayer(BGMpath);
    SDL_Log("test2");
    game_recorder = new GameRecorder(GAMERECORD_FILE, renderer);
    SDL_Log("test3");
    PlayPage = new playground(playbg[1], playbgMove[1], renderer, game_recorder, BGMmusic);
    SDL_Log("test4");
    MenuPage = new menu(MENU_BACKGROUND, renderer, game_recorder, BGMmusic);
    SDL_Log("Init Fine");
}

// 在迴圈裡
void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type==SDL_QUIT) game_is_running = FALSE;
    if (PAGE_ID == MENUID) {
        PAGE_ID = MenuPage->process_input(&event);
    }else if (PAGE_ID == PLAYGROUNDID) {
        PAGE_ID = PlayPage->process_input(&event, keystate);
    }
    change_page();
}

int update() {
    if(!game_is_running) return FALSE;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (PAGE_ID == MENUID) {
        PAGE_ID = MenuPage->update(delta_time);
    }else if (PAGE_ID == PLAYGROUNDID) {
        PAGE_ID = PlayPage->update(delta_time);
    }
    change_page();
    return game_is_running;
}

void render() {
    if (PAGE_ID == MENUID) {
        MenuPage->render(renderer);
    }else if (PAGE_ID == PLAYGROUNDID) {
        PlayPage->render(renderer);
    }
}

void change_page() {
    if (PAGE_ID != prePage_ID) {
        prePage_ID = PAGE_ID;
        if(PAGE_ID == PLAYGROUNDID2) {
            PAGE_ID = PLAYGROUNDID;
            gametype =2;
        }else if(PAGE_ID == PLAYGROUNDID){
            gametype = 1;
        }
        if (PAGE_ID == PLAYGROUNDID || PAGE_ID == PLAYGROUNDID_RESTART) {
            prePage_ID = PLAYGROUNDID;
            PAGE_ID = PLAYGROUNDID;
            SDL_Log("Play Game 1");
            if(gametype == 1){
                PlayPage = new playground(playbg[1], playbgMove[1], renderer, game_recorder, BGMmusic);
            }else if (gametype == 2) {
                PlayPage = new playground2(playbg[0], playbgMove[0], renderer, game_recorder, BGMmusic);
            }
        }else if (PAGE_ID == MENUID) {
            SDL_Log("MENU");
            MenuPage = new menu(MENU_BACKGROUND, renderer, game_recorder, BGMmusic);

        }
    }
}

void destroy_window() {
    SDL_Log("Engine TURN OFF!");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mywindow);
    Mix_Quit();
    SDL_Quit();
}
