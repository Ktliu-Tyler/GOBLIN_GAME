#include "../include/player.h"


Player::Player(float posx, float posy, float w, float h, float sp, SDL_Renderer* renderer) {
    x = posx;
    y = posy;
    width = w;
    height = h;
    speed = sp;
    animW = new Animation('w', 100, this->Wimages, renderer);
    animS = new Animation('s', 50, this->Simages, renderer);
    rect = new SDL_Rect {
        (int) x,
        (int) y,
        (int) width,
        (int) height
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
    if (state == 'W') {
        animW->update(renderer, rect);
    }else if (state == 'S') {
        animS->update(renderer, rect);
        if(animS->finish) {
            state = 'W';
            animW->init();
        }
    }

    // std::cout << x <<" "<< y << std::endl;
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // SDL_RenderFillRect(renderer, rect);
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
}

void Player::changeArrow(char type) {
    this->type = type;
    if(type == 'F') {
        animS->updateTime = 20;
    }else if(type == 'P') {
        animS->updateTime = 100;
    }
    else {
        animS->updateTime = 50;
    }
    SDL_Log("Changing arrow state to %c", type);
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
    // for (Animation* anim : anims) {
    //     if (type == anim->id) {
    //         anim->update(renderer, rect);
    //         break;
    //     }
    // }


    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(renderer, rect);
}

void Bullet::set_arrow(char t,  SDL_Renderer* renderer) {
    switch(t) {
        case 'N':
            anim = new Animation(t, 100, this->Nimages, renderer);
        break;
        case 'F':
            speed = speed * 2;
            anim = new Animation(t, 100, this->Fimages, renderer);
        break;
        case 'p':
            att = 2;
            anim = new Animation(t, 100, this->PNimages, renderer);
        break;
        case 'P':
            width = 2*width;
            height = 2*height;
        att = 4;
            anim = new Animation(t, 100, this->PRimages, renderer);
        break;
    }

}

void Bullet::destroy() {
    // SDL_Log("Bullet::destroy");
}




