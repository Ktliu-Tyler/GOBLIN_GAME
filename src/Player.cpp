#include "../include/player.h"


Player::Player(float posx, float posy, float w, float h, float sp, SDL_Renderer* renderer, float yM,float ym) {
    x = posx;
    y = posy;
    width = w;
    height = h;
    speed = sp;
    yMax = yM;
    yMin = ym;
    animW = new Animation('w', 80, this->Wimages, renderer, WALK_SOUND);
    animS = new Animation('s', PLAYER_SHOOT_T, this->Simages, renderer, SHOOT_SOUND);
    animD = new Animation('D', 50, this->Dimages, renderer, HURT_SOUND);
    rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
    };
    hitrect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) PLAYER_HIT_W,
        (int) PLAYER_HIT_H
    };
}

void Player::init(float x, float y) {
    this->x = x;
    this->y = y;
}

void Player::render( SDL_Renderer* renderer) {
    rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
    };
    hitrect = new SDL_Rect {
        (int) x+(PLAYER_h-PLAYER_HIT_H)/2,
        (int) y+(PLAYER_h-PLAYER_HIT_H)/2,
        (int) PLAYER_HIT_W,
        (int) PLAYER_HIT_H
    };
    if (state == 'W') {
        animW->update(renderer, rect);
    }else if (state == 'S') {
        animS->update(renderer, rect);
        if(animS->finish) {
            state = 'W';
            animW->init();
        }
    }else if (state == 'D') {
        animD->update(renderer, rect);
    }
}

void Player::move(char dir) {
    direction = dir;
}

void Player::kinetic(float dt) {
    if(direction=='u') {
        y -= speed * vy/abs(vy)*dt;
    }else if(direction=='d') {
        y += speed * vy/abs(vy)*dt;
    }
    if (y >= yMax-height) {
        y = yMax-height;
    } else if (y <= yMin-height) {
        y = yMin-height;
    }
}

void Player::changeArrow(char type) {
    this->type = type;
    if(type == 'F') {
        animS->updateTime = PLAYER_SHOOT_T/2;
    }else if(type == 'P') {
        animS->updateTime = PLAYER_SHOOT_T*2;
    }
    else {
        animS->updateTime = PLAYER_SHOOT_T;
    }
    SDL_Log("Changing arrow state to %c", type);
}

Player::~Player() {
    // 1) 釋放三個動畫指標
    if (animW) {
        delete animW;
        animW = nullptr;
    }
    if (animS) {
        delete animS;
        animS = nullptr;
    }
    if (animD) {
        delete animD;
        animD = nullptr;
    }

    // 2) 釋放 rect、hitrect
    if (rect) {
        delete rect;
        rect = nullptr;
    }
    if (hitrect) {
        delete hitrect;
        hitrect = nullptr;
    }
}


Bullet::Bullet(float posx, float posy, char type, SDL_Renderer* renderer) {
    this->x = posx;
    this->y = posy;
    this->type = type;
    destroyed = false;
    set_arrow(type, renderer);
    // anims = {animN, animF, animPN, animPR};

    rect = new SDL_Rect {
        (int) x,
        (int) (y-width/2),
        (int) width,
        (int) height
    };

}

void Bullet::kinetic(float dt) {
    x += speed * dt;
    if(x > WINDOW_WIDTH) {
        destroyed = true;
    }
}

void Bullet::render(SDL_Renderer* renderer) {
    if(destroyed) {
        destroy();
    }
    rect = new SDL_Rect {
        (int) x,
        (int) (y-width/4),
        (int) width,
        (int) height
    };
    anim->update(renderer, rect);
}

void Bullet::set_arrow(char t,  SDL_Renderer* renderer) {
    switch(t) {
        case 'N':
            anim = new Animation(t, 100, this->Nimages, renderer);
        break;
        case 'F':
            speed = speed * 2;
            np = 1;
            anim = new Animation(t, 100, this->Fimages, renderer);
        break;
        case 'p':
            att = 3;
            np = 3;
            anim = new Animation(t, 100, this->PNimages, renderer);
        break;
        case 'P':
            width = 2*width;
            height = 2*height;
            att = 6;
            np = 6;

            anim = new Animation(t, 100, this->PRimages, renderer);
        break;
    }

}

void Bullet::destroy() {
    // SDL_Log("Bullet::destroy");
}

Bullet::~Bullet() {
    // 1) 釋放 anim
    if (anim) {
        delete anim;
        anim = nullptr;
    }

    // 2) 釋放 rect
    if (rect) {
        delete rect;
        rect = nullptr;
    }
}



