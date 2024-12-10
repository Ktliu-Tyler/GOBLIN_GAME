//
// Created by Liu KT on 2024/11/20.
//
#include "../include/tool.h"

#include "../include/engine.h"

// SDL_Color WHITE = { 255, 255, 255, 255 };
// SDL_Color BLACK = { 0, 0, 0, 255 };
// SDL_Color RED = { 255, 0, 0, 255 };
// SDL_Color GREEN = { 0, 255, 0, 255 };
// SDL_Color BLUE = { 0, 0, 255, 255 };
// SDL_Color YELLOW = { 255, 255, 0, 255 };
// SDL_Color MAGENTA = { 255, 0, 255, 255 };
// SDL_Color CYAN = { 0, 255, 255, 255 };
// SDL_Color GREY = { 128, 128, 128, 255 };


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



Scoreboard::Scoreboard(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font), score(0), health(100), level(1), scoreTexture(nullptr), healthTexture(nullptr), levelTexture(nullptr) {}

Scoreboard::~Scoreboard() {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (healthTexture) SDL_DestroyTexture(healthTexture);
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

int Scoreboard::Score() {
    return score;
}

int Scoreboard::Health() {
    return health;
}

void Scoreboard::getHurt(int att) {
    this->health -= att;
    if(health <= 0) {
        health = 0;
    }
    // updateTextures();
}

void Scoreboard::getScore(int score) {
    this->score += score;
    // updateTextures();
}

void Scoreboard::updateTextures() {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (healthTexture) SDL_DestroyTexture(healthTexture);
    if (levelTexture) SDL_DestroyTexture(levelTexture);

    scoreTexture = createTextTexture("Score: " + std::to_string(score), myWHITE, font);
    healthTexture = createTextTexture("HP: " + std::to_string(health), myWHITE, font);
    levelTexture = createTextTexture("Level: " + std::to_string(level), myWHITE, font);
}

void Scoreboard::render() {

    renderText("Score: " + std::to_string(score), SCOREBOARD_X, SCOREBOARD_Y, myWHITE, font, renderer, 'l');

    SDL_Color fgColor = myRED;
    SDL_Color bgColor = myGREY;
    renderText("HP " , SCOREBOARD_X, SCOREBOARD_Y+SCOREBOARD_BET, myWHITE, font, renderer, 'l');
    renderProgressBar(SCOREBOARD_X+100, SCOREBOARD_Y+SCOREBOARD_BET, 200, 30, health, PLAYER_HP_MAX, fgColor, bgColor, renderer);

    fgColor = myBLUE;
    bgColor  = myGREY;
    renderText("LEVEL " , SCOREBOARD_X, SCOREBOARD_Y+2*SCOREBOARD_BET, myWHITE, font, renderer, 'l');
    renderProgressBar(SCOREBOARD_X+100, SCOREBOARD_Y+2*SCOREBOARD_BET, 200, 30, level, 100, fgColor, bgColor, renderer); // Assuming max level is 10
}

GameRecorder::GameRecorder(const std::string& filename) : filename(filename) {
    // 构造函数
    highscore = loadScore();
    SDL_Log("Highscore load: %d", highscore);
}

void GameRecorder::saveScore(int score) {
    lastScore = score;
    if (score > highscore) {
        highscore = score;
        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file << score;
            file.close();
            std::cout << "Score saved to " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file for saving score." << std::endl;
        }
    }
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
    } else {
        std::cerr << "Unable to open file for loading score." << std::endl;
    }
    return score;
}



void renderProgressBar(int x, int y, int w, int h, int value, int max_value, SDL_Color fgColor, SDL_Color bgColor, SDL_Renderer *renderer) {
    // Render background bar
    SDL_Rect bgRect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &bgRect);

    // Render foreground bar
    int fgWidth = static_cast<int>((static_cast<float>(value) / max_value) * w);
    SDL_Rect fgRect = { x, y, fgWidth, h };
    SDL_SetRenderDrawColor(renderer, fgColor.r, fgColor.g, fgColor.b, fgColor.a);
    SDL_RenderFillRect(renderer, &fgRect);
}

SDL_Texture* createTextTexture(const std::string& text, SDL_Color color, TTF_Font* font) {
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
    SDL_Texture* texture = createTextTexture(text, color, font);
    if (texture) {
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        SDL_Rect dstRect;
        if (type=='l') {
            dstRect = { x, y, width, height };
        }else if (type=='m') {
            dstRect = { x-width/2, y-height/2, width, height };
        }
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_DestroyTexture(texture);
    }
}

