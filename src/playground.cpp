//
// Created by Liu KT on 2024/11/20.
//

#include "../include/playground.h"

#include "../SDL_lib/SDL_bgi.h"


// TTF_Font* font;
inline TTF_Font* font;
inline TTF_Font* fontBIG;
playground::playground(std::string path, std::string pathMove, SDL_Renderer *renderer, GameRecorder *recorder) {
    SDL_Log("Creating playground...");
    this -> background = loadTexture(path, renderer);
    this -> backgroundMove = loadTexture(pathMove, renderer);
    this -> backgroundChange = loadTexture(CHANGE_BACKGROUND, renderer);
    this -> renderer = renderer;
    this -> recorder = recorder;
    this -> backgroundX = 0;
    this -> chbgX = -300;
    srand( time(NULL) );
    font =  TTF_OpenFont(FONT, 24);
    fontBIG =  TTF_OpenFont(FONT, 100);


    player = new Player(PLAYER_W+30, WINDOW_HEIGHT-WINDOW_M_HEIGHT, PLAYER_W, PLAYER_H, PLAYER_SPEED, renderer, WINDOW_HEIGHT,WINDOW_HEIGHT-WINDOW_M_HEIGHT);
    scoreboard = new Scoreboard(renderer, font);
    scoreboard->setHealth(PLAYER_HP_MAX);
    scoreboard->setScore(0);
    scoreboard->setLevel(0);
}


int playground::process_input(SDL_Event *event, const Uint8 *keystate) {
    // SDL_Log("Processing input...%d", keystate[SDL_SCANCODE_UP]);
    int ifmove = FALSE;
    if( !scoreboard->game_over) {
        if (keystate[SDL_SCANCODE_W]) {
            // SDL_Log("SDL_w");
            player->move('u');
            ifmove = TRUE;
        }
        if (keystate[SDL_SCANCODE_S]) {
            // SDL_Log("SDL_s");
            player->move('d');
            ifmove = TRUE;
        }
    }
    if(!ifmove) {
        player->move('s');
    }
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_q) {
                // SDL_Log("SDL_q");
                // return MENUID;
            }
            if (event->key.keysym.sym == SDLK_1 && !scoreboard->game_over) {
                player->changeArrow('N');
            }
            if (event->key.keysym.sym == SDLK_2&& !scoreboard->game_over) {
                player->changeArrow('F');
            }
            if (event->key.keysym.sym == SDLK_3&& !scoreboard->game_over) {
                player->changeArrow('p');
            }
            if (event->key.keysym.sym == SDLK_4&& !scoreboard->game_over) {
                player->changeArrow('P');
            }
            if(event->key.keysym.sym == SDLK_SPACE && player->animS->finish&& !scoreboard->game_over) {
                // SDL_Log("SDL_space");
                player->state = 'S';
                player->animS->init();
                bullets.push_back(new Bullet(player->x+player->width/2, player->y+player->height/2, player->type, renderer));
            }
        break;
    }
    return PLAYGROUNDID;
}

int playground::update(float deltatime) {
    if (!scoreboard->game_over && gameStart) {
        new_Enemy();
    }
    player->kinetic(deltatime);
    enemy_update(deltatime);
    bullet_update(deltatime);
    movebd(deltatime);
    if(chbgX < -300 && scoreboard->game_over) {
        return gameOVER_ANIME();
    }
    return PLAYGROUNDID;
}

void playground::render(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    bdrender();
    for (auto& bullet : bullets) {
        bullet->render(renderer);
    }
    for (auto& enemy : enemys) {
        enemy->render(renderer);
    }
    player->render(renderer);
    scoreboard->render();
    if(scoreboard->Health() <= 0 && !scoreboard->game_over) {
        scoreboard->game_over = true;
        player->state = 'D';
        player->animD->finish = false;
    }
    if (!gameStart) {
        changebd();
        if (chbgX < -(WINDOW_WIDTH+600)) {
            gameStart = true;
            chbgX = WINDOW_WIDTH;
        }
    }
    if(scoreboard->game_over && player->animD->finish) {
        changebd();
    }
    SDL_RenderPresent(renderer);
}

void playground::movebd(float dt) {
    if (backgroundX < -WINDOW_WIDTH) {
        backgroundX = 0;
    }
    if(!scoreboard->game_over) {
        backgroundX+=BDSPEED*dt;
    }
    // SDL_Log("Updating background...%f", backgroundX);
}

void playground::bdrender() {
    SDL_RenderCopy(renderer, this->background, nullptr, nullptr);
    SDL_Rect renderQuad = { (int)backgroundX, WINDOW_HEIGHT-WINDOW_M_HEIGHT, WINDOW_WIDTH, WINDOW_M_HEIGHT };
    SDL_RenderCopy(renderer, this->backgroundMove, nullptr, &renderQuad);
    SDL_Rect renderQuad2 = { (int)backgroundX+WINDOW_WIDTH, WINDOW_HEIGHT-WINDOW_M_HEIGHT, WINDOW_WIDTH, WINDOW_M_HEIGHT };
    SDL_RenderCopy(renderer, this->backgroundMove, nullptr, &renderQuad2);
}

void playground::changebd() {
    SDL_Rect renderQuad = { chbgX, -60, WINDOW_WIDTH+600, WINDOW_HEIGHT+90 };
    SDL_RenderCopy(renderer, this->backgroundChange, nullptr, &renderQuad);
    chbgX -=2;
}

void playground::bullet_update(float deltatime) {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        Bullet* bullet = *it;
        bullet->kinetic(deltatime);
        if (bullet->destroyed) {
            bullet->destroy();
            delete bullet; // 释放内存
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void playground::enemy_update(float deltatime) {
    for (auto it = enemys.begin(); it != enemys.end(); ) {
        Enemy* enemy = *it;
        enemy->kinetic(deltatime);
        for (auto bullet: bullets) {
            if(SDL_HasIntersection(bullet->rect, enemy->rect)) {
                enemy->hurted(bullet->att);
                bullet->destroyed = true;
            }
        }
        if(SDL_HasIntersection(enemy->rect, player->rect) && !enemy->attacked) {
            scoreboard->getHurt(enemy->getAttack());
            enemy->attacked = true;
            SDL_Log("Hurt");
        }
        int test = enemy->ifdied();
        if (enemy->destroyed) {
            enemy->destroy();
            if(test == 1) {
                scoreboard->getScore(enemy->getAttack());
            }
            delete enemy;
            enemyNUM--;
            it = enemys.erase(it);
        } else {
            ++it;
        }
    }
}

void playground::new_Enemy() {
    int n = ENEMYNUMMAX-enemyNUM;
    for (int i = 0; i < n; i++) {
        enemys.push_back(new Enemy(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100), rand()%200, rand()%10));
        // SDL_Log("Enemy born at %f, %f", enemys[i]->x, enemys[i]->y);
        enemyNUM++;
    }

}

int playground::gameOVER_ANIME() {
    int animeEnd = false;
    recorder->saveScore(scoreboard->Score());
    int PageID = 0;
    while (!animeEnd) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type==SDL_QUIT) {
            game_is_running = false;
            break;
        }else if (event.type==SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_m) {
                PageID = MENUID;
                return PageID;
                break;
            }
            if (event.key.keysym.sym == SDLK_r) {
                PageID = PLAYGROUNDID_RESTART;
                return PageID;
                break;
            }
        }
        renderText("GAME OVER", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, myWHITE,fontBIG, renderer, 'm');
        renderText("Press 'r' to restart, or Press 'm' to back to Menu.", WINDOW_WIDTH/2, WINDOW_HEIGHT/2+60, myWHITE,font, renderer, 'm');
        SDL_RenderPresent(renderer);
    }
    return PageID;
}

playground::~playground() {
    delete this;
}

