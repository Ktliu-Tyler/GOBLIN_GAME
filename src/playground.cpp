//
// Created by Liu KT on 2024/11/20.
//

#include "../include/playground.h"

#include "../SDL_lib/SDL_bgi.h"


playground::playground(std::string path, SDL_Renderer *renderer) {
    SDL_Log("Creating playground...");
    this -> background = loadTexture(path, renderer);
    this -> renderer = renderer;
    this->backgroundX = 0;
    srand( time(NULL) );
    player = new Player(PLAYER_W, 40, PLAYER_W, PLAYER_H, PLAYER_SPEED, renderer);
}

int playground::process_input(SDL_Event *event, const Uint8 *keystate) {
    // SDL_Log("Processing input...%d", keystate[SDL_SCANCODE_UP]);
    int ifmove = FALSE;
    if (keystate[SDL_SCANCODE_W]) {
        SDL_Log("SDL_w");
        player->move('u');
        ifmove = TRUE;
    }
    if (keystate[SDL_SCANCODE_S]) {
        SDL_Log("SDL_s");
        player->move('d');
        ifmove = TRUE;
    }
    if(!ifmove) {
        player->move('s');
    }
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_q) {
                SDL_Log("SDL_q");
                return MENUID;
            }
            if (event->key.keysym.sym == SDLK_1) {
                player->changeArrow('N');
            }
            if (event->key.keysym.sym == SDLK_2) {
                player->changeArrow('F');
            }
            if (event->key.keysym.sym == SDLK_3) {
                player->changeArrow('p');
            }
            if (event->key.keysym.sym == SDLK_4) {
                player->changeArrow('P');
            }
            if(event->key.keysym.sym == SDLK_SPACE && player->animS->finish) {
                SDL_Log("SDL_space");
                player->state = 'S';
                player->animS->init();
                bullets.push_back(new Bullet(player->x+player->width/2, player->y+player->height/2, player->type, renderer));
            }
        break;
    }
    return PLAYGROUNDID;
}

int playground::update(float deltatime) {
    new_Enemy();
    player->kinetic(deltatime);
    enemy_update(deltatime);
    bullet_update(deltatime);
    movebd(deltatime);
    return TRUE;
}

void playground::bullet_update(float deltatime) {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        Bullet* bullet = *it;
        bullet->kinetic(deltatime);
        if (bullet->destroyed) {
            bullet->destroy();
            delete bullet; // 释放内存
            it = bullets.erase(it); // 移除子弹
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
        enemy->ifdied();
        if (enemy->destroyed) {
            enemy->destroy();
            delete enemy; // 释放内存
            enemyNUM--;
            it = enemys.erase(it); // 移除子弹
        } else {
            ++it;
        }
    }
}

void playground::render(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    bdrender();
    player->render(renderer);
    for (auto& bullet : bullets) {
        bullet->render(renderer);
    }
    for (auto& enemy : enemys) {
        enemy->render(renderer);
    }
    SDL_RenderPresent(renderer);
}

void playground::movebd(float dt) {
    if (backgroundX < -WINDOW_WIDTH) {
        backgroundX = 0;
    }
    backgroundX+=BDSPEED*dt;
    // SDL_Log("Updating background...%f", backgroundX);
}

void playground::bdrender() {
    SDL_Rect renderQuad = { (int)backgroundX, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, this->background, nullptr, &renderQuad);
    SDL_Rect renderQuad2 = { (int)backgroundX+WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, this->background, nullptr, &renderQuad2);
}

void playground::new_Enemy() {
    int n = ENEMYNUMMAX-enemyNUM;
    for (int i = 0; i < n; i++) {
        enemys.push_back(new Enemy(rand()%WINDOW_WIDTH+WINDOW_WIDTH, rand()%WINDOW_HEIGHT, rand()%200, rand()%10));
        // SDL_Log("Enemy born at %f, %f", enemys[i]->x, enemys[i]->y);
        enemyNUM++;
    }

}

playground::~playground() {
    delete this;
}

