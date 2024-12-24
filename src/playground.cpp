//
// Created by Liu KT on 2024/11/20.
//

#include "../include/playground.h"

#include "../SDL_lib/SDL_bgi.h"


// TTF_Font* font;
inline TTF_Font* font;
inline TTF_Font* fontBIG;


playground::playground(std::string path, std::string pathMove, SDL_Renderer *renderer, GameRecorder *recorder, MusicPlayer *music_player): scoreboard(renderer, font) {
    SDL_Log("Creating playground...");
    this -> background = loadTexture(path, renderer);
    this -> backgroundMove = loadTexture(pathMove, renderer);
    this -> backgroundChange = loadTexture(CHANGE_BACKGROUND, renderer);
    this -> renderer = renderer;
    this -> recorder = recorder;
    this -> musicPlayer = music_player;
    this -> backgroundX = 0;
    this -> chbgX = -300;
    srand( time(NULL) );
    font =  TTF_OpenFont(FONT, 24);
    fontBIG =  TTF_OpenFont(FONT, 100);
    this->musicPlayer->stop();
    player = new Player(PLAYER_W+30, WINDOW_HEIGHT-WINDOW_M_HEIGHT, PLAYER_W, PLAYER_h, PLAYER_SPEED, renderer, WINDOW_HEIGHT,WINDOW_HEIGHT-WINDOW_M_HEIGHT);
    // scoreboard = Scoreboard(renderer, font);
    scoreboard.setHealth(PLAYER_HP_MAX);
    scoreboard.setNP(PLAYER_NP_MAX);
    scoreboard.setScore(0);
    scoreboard.setLevel(0);
}


int playground::process_input(SDL_Event *event, const Uint8 *keystate) {
    // SDL_Log("Processing input...%d", keystate[SDL_SCANCODE_UP]);
    int ifmove = FALSE;
    if( !scoreboard.game_over) {
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
        // player->animW->playSound(-1);
    }
    switch (event->type) {
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_q) {
                // SDL_Log("SDL_q");
                // return MENUID;
            }
            if (event->key.keysym.sym == SDLK_1 && !scoreboard.game_over) {
                player->changeArrow('N');
            }
            if (event->key.keysym.sym == SDLK_2&& !scoreboard.game_over) {
                player->changeArrow('F');
            }
            if (event->key.keysym.sym == SDLK_3&& !scoreboard.game_over) {
                player->changeArrow('p');
            }
            if (event->key.keysym.sym == SDLK_4&& !scoreboard.game_over) {
                player->changeArrow('P');
            }
            if(event->key.keysym.sym == SDLK_SPACE && player->animS->finish&& !scoreboard.game_over) {
                // SDL_Log("SDL_space");
                player->state = 'S';
                player->animS->init();

                Bullet *b = new Bullet(player->x+player->width/2, player->y+player->height/2, player->type, renderer);
                if (scoreboard.NP()-b->np >0 || player->type == 'N') {
                    player->animS->playSound(2);
                    scoreboard.getNP(-1*b->np);
                    bullets.push_back(b);
                }
            }
        break;
    }
    return PLAYGROUNDID;
}

int playground::update(float deltatime) {
    if (!scoreboard.game_over && gameStart) {
        new_Enemy();
    }
    player->kinetic(deltatime);
    enemy_update(deltatime);
    bullet_update(deltatime);
    movebd(deltatime);
    if(chbgX < -300 && scoreboard.game_over) {
        return gameOVER_ANIME();
    }
    return PLAYGROUNDID;
}

void playground::render(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    bdrender();

    for (auto& enemy : enemys) {
        enemy->render(renderer);
    }
    for (auto& bullet : bullets) {
        bullet->render(renderer);
    }
    if(!player->animD->stop) {
        player->render(renderer);
    }
    scoreboard.render();
    if(scoreboard.Health() <= 0 && !scoreboard.game_over) {
        scoreboard.game_over = true;
        player->state = 'D';
        player->animD->finish = false;
        musicPlayer->playGameOver();
    }
    if (!gameStart) {
        changebd();
        if (chbgX < -(WINDOW_WIDTH+600)) {
            gameStart = true;
            this->musicPlayer->playGamining(gametype);
            chbgX = WINDOW_WIDTH;
        }
    }
    if(scoreboard.game_over && player->animD->finish) {
        player->animD->stop = true;
        changebd();

    }
    SDL_RenderPresent(renderer);
}

void playground::movebd(float dt) {
    if (backgroundX < -WINDOW_WIDTH) {
        backgroundX = 0;
    }
    if(!scoreboard.game_over) {
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
    chbgX -=3;
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
            if(SDL_HasIntersection(bullet->rect, enemy->hitrect)&& !enemy->destroyed) {
                enemy->hurted(bullet->att);
                bullet->destroyed = true;
                scoreboard.getLevel(1);
                enemy->animW->playSound(4);
                if (bullet->type == 'p') {
                    enemy->speed =BDSPEED+10;
                    if(enemy->type == 'B') {
                        enemy->speed = BDSPEED+120;
                        SDL_Log("slow %d", enemy->speed);
                    }

                }
            }
        }
        if(SDL_HasIntersection(enemy->hitrect, player->hitrect) && !enemy->attacked && !enemy->destroyed) {
            scoreboard.getHurt(enemy->getAttack());
            enemy->attacked = true;
            player->animD->playSound(5);
            SDL_Log("Hurt");
        }
        int test = enemy->ifdied();

        if (enemy->destroyed && enemy->animD->finish) {
            enemy->destroy();
            if(test == 1 && enemy->dieANIMcount == 0) {
                scoreboard.getScore(enemy->getAttack());
                scoreboard.getNP(enemy->getAttack()/3+2);
                scoreboard.getLevel(enemy->getAttack());
                enemy->animD->finish = false;
                enemy->state = 'D';

                enemy->speed = BDSPEED;
                enemy->dieANIMcount++;

            }
            if(enemy->animD->finish) {
                delete enemy;
                enemyNUM--;
                if(enemy->type=='B') {
                    scoreboard.state = 'n';
                    scoreboard.setLevel(0);
                    enemyNUM = 0;
                }
                it = enemys.erase(it);
            }

        } else {
            ++it;
        }
    }
}

void playground::new_Enemy() {
    int n = ENEMYNUMMAX-enemyNUM;
    if (scoreboard.state == 'n') {
        for (int i = 0; i < n; i++) {
            int enemyType = rand()%ENEMPTYPE;
            int hp = rand()%6+3;
            if(enemyType == 0) {
                enemys.push_back(new Enemy(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), rand()%200,hp, renderer));
            }else if (enemyType == 1) {
                // if(hp <6) {
                //     hp = 6;
                // }
                // hp = 20;
                enemys.push_back(new Human(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), rand()%200, hp, renderer));
            }else if (enemyType == 2) {
                enemys.push_back(new Human(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), rand()%200, hp, renderer));
            }
            // SDL_Log("Enemy born at %f, %f", enemys[i]->x, enemys[i]->y);
            enemyNUM++;
        }
    }else  if (scoreboard.state == 'g'){
        Monster *e = new Monster(rand()%WINDOW_WIDTH+WINDOW_WIDTH, WINDOW_HEIGHT/4+30, -100, 30, renderer);
        e->type = 'B';
        enemys.push_back(e);
        enemyNUM = 0;
        scoreboard.state = 'B';
    }


}

int playground::gameOVER_ANIME() {
    int animeEnd = false;
    // Shake s1(WINDOW_WIDTH/2-100,WINDOW_HEIGHT/2,0, 10, renderer);
    recorder->saveScore(scoreboard.Score());
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
        // s1.render(renderer);
        SDL_RenderPresent(renderer);
    }
    return PageID;
}

int playground::gameSTOP() {
    int animeEnd = false;
    recorder->saveScore(scoreboard.Score());
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
        // SDL_RenderClear(renderer);
        renderText("GAME OVER", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, myWHITE,fontBIG, renderer, 'm');
        renderText("Press 'r' to restart, or Press 'm' to back to Menu.", WINDOW_WIDTH/2, WINDOW_HEIGHT/2+60, myWHITE,font, renderer, 'm');
        SDL_RenderPresent(renderer);
    }
    return PageID;
}

playground::~playground() {
    // 先清理 bullets
    for (auto& bullet : bullets) {
        if (bullet) {
            bullet->destroy();
            delete bullet;    // 釋放記憶體
            bullet = nullptr;
        }
    }
    bullets.clear();

    // 再清理 enemys
    for (auto& enemy : enemys) {
        if (enemy) {
            enemy->destroy();
            delete enemy;    // 釋放記憶體
            enemy = nullptr;
        }
    }
    enemys.clear();

    // 刪除玩家
    if (player) {
        delete player;
        player = nullptr;
    }

    // 釋放背景貼圖（若非空）
    if (background) {
        SDL_DestroyTexture(background);
        background = nullptr;
    }
    if (backgroundMove) {
        SDL_DestroyTexture(backgroundMove);
        backgroundMove = nullptr;
    }
    if (backgroundChange) {
        SDL_DestroyTexture(backgroundChange);
        backgroundChange = nullptr;
    }

    // 6) 關閉字型（若非空）
    if (fontBIG) {
        TTF_CloseFont(fontBIG);
        fontBIG = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    delete this;
}




playground2::playground2(std::string path, std::string pathMove, SDL_Renderer *renderer, GameRecorder *recorder, MusicPlayer *music_player):playground(path, pathMove, renderer, recorder, music_player) {
    SDL_Log("playground2()");
    gametype = 2;
}

void playground2::new_Enemy() {
    static int n = ENEMYNUMMAX;
    n = ENEMYNUMMAX-enemyNUM;
    for (int i = 0; i < n; i++) {
        int enemyType = rand()%ENEMPTYPE;
        int hp = rand()%10+1;
        if(enemyType == 0) {
            enemys.push_back(new Human3(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), rand()%200,hp, renderer));
        }else if (enemyType == 1) {
            enemys.push_back(new Human1(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), rand()%200, hp, renderer));
        }else if (enemyType == 2) {
            enemys.push_back(new Human2(rand()%WINDOW_WIDTH+WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)+(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), rand()%200, hp, renderer));
        }
        // SDL_Log("Enemy born at %f, %f", enemys[i]->x, enemys[i]->y);
        enemyNUM++;
    }

}
