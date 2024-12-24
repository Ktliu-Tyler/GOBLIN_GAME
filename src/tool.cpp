//
// Created by Liu KT on 2024/11/20.
//
#include "../include/tool.h"


SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
         SDL_Log("Unable to load image %s", path.c_str());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            SDL_Log("Unable to create texture from %s", IMG_GetError);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void renderProgressBar(int x, int y, int w, int h, int value, int max_value, SDL_Color fgColor, SDL_Color bgColor, SDL_Renderer *renderer) {
    SDL_Rect outRect = { x-2, y-2, w+4, h+4 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &outRect);

    SDL_Rect bgRect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &bgRect);

    int fgWidth = static_cast<int>((static_cast<float>(value) / max_value) * w);
    SDL_Rect fgRect = { x, y, fgWidth, h };
    SDL_SetRenderDrawColor(renderer, fgColor.r, fgColor.g, fgColor.b, fgColor.a);
    SDL_RenderFillRect(renderer, &fgRect);
}

SDL_Texture* createTextTexture(const std::string& text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        SDL_Log("TTF_RenderText_Solid Error: %s", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void renderText(const std::string& text, int x, int y, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer, char type) {
    SDL_Texture* texture = createTextTexture(text, color, font, renderer);
    if (texture) {
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        SDL_Rect dstRect;
        if (type=='l') {
            dstRect = { x, y, width, height };
        }else if (type=='m') {
            dstRect = { x-width/2, y-height/2, width, height };
        }else if (type=='r') {
            dstRect = { x-width, y, width, height };
        }
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_DestroyTexture(texture);
    }
}



Animation::Animation(char id,int t, const std::vector<std::string>& imagePaths, SDL_Renderer* renderer, const std::string& soundPath){
    this->id = id;
    this->updateTime = t;
    this->finish = true;
    if(soundPath !="") {
        this->sound = Mix_LoadWAV(soundPath.c_str());
    }
    for (const std::string& path : imagePaths) {
        addAnimationFrame(path ,renderer);
    }

}

Animation::~Animation() {
    for (auto& frame : frames) {
        if (frame) {
            SDL_DestroyTexture(frame);
            frame = nullptr;
        }
    }

    if (sound) {
        Mix_FreeChunk(sound);
        sound = nullptr;
    }
}


void Animation::addAnimationFrame(const std::string &path, SDL_Renderer* renderer) {
    SDL_Texture* frame = loadTexture(path.c_str(), renderer);
    this->frames.push_back(frame);
    this->frameMax++;
}

SDL_Texture *Animation::getCurrentFrame() {
    timeCounter++;
    if (timeCounter >= updateTime && !stop) {
        currentFrameIndex++;
        if (currentFrameIndex >= frameMax-3) {
            currentFrameIndex = 0;
            finish = true;
        }
        timeCounter = 0;

    }
    return frames[currentFrameIndex];
}

bool Animation::update(SDL_Renderer* renderer, SDL_Rect *rect) {
    SDL_RenderCopy(renderer, getCurrentFrame(), nullptr, rect);
    // SDL_Log("SHAKE");
    return 0;
}

void Animation::init() {
    currentFrameIndex = 0;
    finish = false;
}

void Animation::playSound(int channel) {
    Mix_PlayChannel(channel, sound, 0);
}



Scoreboard::Scoreboard(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font), score(0), health(100), level(1), np(30), scoreTexture(nullptr), healthTexture(nullptr),npTexture(nullptr), levelTexture(nullptr) {}

Scoreboard::~Scoreboard() {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (healthTexture) SDL_DestroyTexture(healthTexture);
    if (npTexture) SDL_DestroyTexture(npTexture);
    if (levelTexture) SDL_DestroyTexture(levelTexture);
}

void Scoreboard::setScore(int score) {
    this->score = score;
    updateTextures();
}

void Scoreboard::setHealth(int health) {
    this->health = health;
    updateTextures();
}

void Scoreboard::setLevel(int level) {
    this->level = level;
    updateTextures();
}

void Scoreboard::setNP(int NP) {
    this->np = NP;
    updateTextures();
}

int Scoreboard::Score() {
    return score;
}

int Scoreboard::Health() {
    return health;
}

int Scoreboard::NP() {
    return np;
}

void Scoreboard::getHurt(int att) {
    this->health -= att;
    if(health <= 0) {
        health = 0;
    }
    else if (health  > PLAYER_HP_MAX){
    health = PLAYER_HP_MAX;
    }

    // updateTextures();
}

void Scoreboard::getScore(int score) {
    this->score += score;
    // updateTextures();
}

void Scoreboard::getNP(int NP) {
    this->np += NP;
    if(np > PLAYER_NP_MAX) {
        np = PLAYER_NP_MAX;
    }
}

void Scoreboard::getLevel(int level) {
    this->level += level;
    if(this->level > LEVEL_MAX) {
        if(this->state == 'n') {
            this->state = 'g';
        }
        this->level = LEVEL_MAX;
    }
}



void Scoreboard::updateTextures() {
    if (this->scoreTexture) SDL_DestroyTexture(this->scoreTexture);
    if (this->healthTexture) SDL_DestroyTexture(this->healthTexture);
    if (this->npTexture) SDL_DestroyTexture(this->npTexture);
    if (this->levelTexture) SDL_DestroyTexture(this->levelTexture);

    std::string t1 = "Score: ";
    t1.append(std::to_string(score));
    std::string t2 = "HP: ";
    t2.append(std::to_string(health));
    std::string t3 = "NP: ";
    t3.append(std::to_string(np));
    this->scoreTexture = createTextTexture(t1, myWHITE, this->font, this->renderer);
    this->healthTexture = createTextTexture(t2, myWHITE, this->font, this->renderer);
    this->levelTexture = createTextTexture(t3, myWHITE, this->font, this->renderer);
}

void Scoreboard::render() {
    SDL_Color fgColor = myGREEN;
    SDL_Color bgColor = myGREY;
    renderText("LV " , SCOREBOARD_X, SCOREBOARD_Y, myWHITE, font, this->renderer, 'l');
    renderProgressBar(SCOREBOARD_X+60, SCOREBOARD_Y, WINDOW_WIDTH-100, 30, level, LEVEL_MAX, fgColor, bgColor, this->renderer);


    std::string t1 = "Score: ";
    t1.append(std::to_string(score));
    renderText(t1, WINDOW_WIDTH-40, SCOREBOARD_Y+SCOREBOARD_BET, myWHITE, font, this->renderer, 'r');

    fgColor = myRED;
    bgColor = myGREY;
    renderText("HP " , SCOREBOARD_X, SCOREBOARD_Y+SCOREBOARD_BET, myWHITE, font, this->renderer, 'l');
    renderProgressBar(SCOREBOARD_X+60, SCOREBOARD_Y+SCOREBOARD_BET, 200, 30, health, PLAYER_HP_MAX, fgColor, bgColor, this->renderer);

    fgColor = myBLUE2;
    bgColor  = myGREY;
    renderText("NP " , SCOREBOARD_X, SCOREBOARD_Y+2*SCOREBOARD_BET, myWHITE, font, this->renderer, 'l');
    renderProgressBar(SCOREBOARD_X+60, SCOREBOARD_Y+2*SCOREBOARD_BET, 200, 30, np, PLAYER_NP_MAX, fgColor, bgColor, this->renderer);
}



GameRecorder::GameRecorder(const std::string& filename, SDL_Renderer* renderer) : filename(filename), renderer(renderer) {
    highscore = 0;
    // highscore = loadScore();
    SDL_Log("Highscore load: %d", highscore);
}

GameRecorder::~GameRecorder() {

}


void GameRecorder::saveScore(int score) {
    lastScore = score;
    // if (score > highscore) {
    //     highscore = score;
    //     std::ofstream file(filename, std::ios::out | std::ios::trunc);
    //     if (file.is_open()) {
    //         file << score;
    //         file.close();
    //         std::cout << "Score saved to " << filename << std::endl;
    //     } else {
    //         std::cerr << "Unable to open file for saving score." << std::endl;
    //     }
    // }
}

int GameRecorder::LASTSCORE() {
    return lastScore;
}

int GameRecorder::HIGHSCORE() {
    return highscore;
}

int GameRecorder::loadScore() {
    std::ifstream file(filename, std::ios::in);
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
        std::cout << "Score loaded from " << filename << std::endl;
        SDL_Log("Score loaded from %s", filename.c_str());
    } else {
        std::cerr << "Unable to open file for loading score." << std::endl;
        SDL_Log("Unable to open file %s", filename.c_str());
    }
    return score;
}


MusicPlayer::MusicPlayer(const std::vector<std::string>& paths) {
    this->musicMenu = Mix_LoadMUS(paths[0].c_str());
    this->musicPlayground = Mix_LoadMUS(paths[1].c_str());
    this->musicGameOver = Mix_LoadMUS(paths[2].c_str());
    this->musicPlayground2 = Mix_LoadMUS(paths[3].c_str());
    if ( musicMenu== nullptr) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    if ( musicPlayground== nullptr) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    if ( musicGameOver== nullptr) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    if ( musicGameOver== nullptr) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void MusicPlayer::playMenu() {
    Mix_PlayMusic(this->musicMenu, -1);
}



void MusicPlayer::playGamining(int type) {
    if (type == 1) {
        Mix_PlayMusic(this->musicPlayground, -1);
    }else if (type == 2) {
        Mix_PlayMusic(this->musicPlayground2, -1);
    }
}

void MusicPlayer::playGameOver() {
    Mix_PlayMusic(this->musicGameOver, -1);
}

void MusicPlayer::stop() {
    Mix_HaltMusic();
}

MusicPlayer::~MusicPlayer() {
    Mix_FreeMusic(this->musicMenu);
    Mix_FreeMusic(this->musicPlayground);
    Mix_FreeMusic(this->musicGameOver);
    if (musicMenu) {
        Mix_FreeMusic(musicMenu);
        musicMenu = nullptr;
    }
    if (musicPlayground) {
        Mix_FreeMusic(musicPlayground);
        musicPlayground = nullptr;
    }
    if (musicGameOver) {
        Mix_FreeMusic(musicGameOver);
        musicGameOver = nullptr;
    }


    if (musicPlayground2) {
        Mix_FreeMusic(musicPlayground2);
        musicPlayground2 = nullptr;
    }

    if (bombsound) {
        Mix_FreeChunk(bombsound);
        bombsound = nullptr;
    }
}

healthBar::healthBar(int max_hp, int w, int h, SDL_Renderer *renderer) {
    this->max_health = max_hp;
    this->width = w;
    this->height = h;
    this->renderer = renderer;
}

void healthBar::render(int x, int y,int width, int health, SDL_Renderer *renderer) {
    renderProgressBar(x, y-15, width, 13, health, max_health, myRED, myGREY, renderer);
}

