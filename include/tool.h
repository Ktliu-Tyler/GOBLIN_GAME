//
// Created by Liu KT on 2024/11/20.
//

#ifndef TOOL_H
#define TOOL_H
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "vector"
#include "iostream"
#include "fstream"
#include "constants.h"


inline int game_is_running = true;
inline SDL_Color myWHITE = { 255, 255, 255, 255 };
inline SDL_Color myBLACK = { 0, 0, 0, 255 };
inline SDL_Color myRED = { 255, 0, 0, 255 };
inline SDL_Color myGREEN = { 0, 255, 0, 255 };
inline SDL_Color myBLUE = { 0, 0, 255, 255 };
inline SDL_Color myYELLOW = { 255, 255, 0, 255 };
inline SDL_Color myMAGENTA = { 255, 0, 255, 255 };
inline SDL_Color myCYAN = { 0, 255, 255, 255 };
inline SDL_Color myGREY = { 128, 128, 128, 255 };

//一些遊戲工具
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);// 載入圖片

class Animation {
    std::vector<SDL_Texture*> frames;
    int currentFrameIndex = 0;
    int frameMax = 0;
    int timeCounter = 0;
    void addAnimationFrame(const std::string& path, SDL_Renderer* renderer);
    public:
    int updateTime = 0;
    int finish = false;
    void init();
    char id;
    Animation(char id, int updateTime, const std::vector<std::string>& imagePaths, SDL_Renderer* renderer);
    SDL_Texture* getCurrentFrame();
    ~Animation();
    bool update(SDL_Renderer* renderer, SDL_Rect *rect);
};

//
// class Scoreboard {
// public:
//     Scoreboard(SDL_Renderer* renderer, TTF_Font* font);
//     ~Scoreboard();
//
//     void setScore(int score);
//     void setHealth(int health);
//     void setLevel(int level);
//
//     void render();
//
// private:
//     SDL_Renderer* renderer;
//     TTF_Font* font;
//
//     int score;
//     int health;
//     int level;
//
//     SDL_Texture* createTextTexture(const std::string& text, SDL_Color color);
//     void renderText(const std::string& text, int x, int y, SDL_Color color);
//
//     SDL_Texture* scoreTexture;
//     SDL_Texture* healthTexture;
//     SDL_Texture* levelTexture;
//
//     void updateTextures();
// };
class Scoreboard {
public:
    Scoreboard(SDL_Renderer* renderer, TTF_Font* font);
    ~Scoreboard();

    void setScore(int score);
    void setHealth(int health);
    void setLevel(int level);

    void getHurt(int att);
    void getScore(int score);
    int Score();
    int Health();
    void render();
    int game_over = false;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    int score;
    int health;
    int level;

    // void renderProgressBar(int x, int y, int w, int h, int value, int max_value, SDL_Color fgColor, SDL_Color bgColor);

    void updateTextures();

    SDL_Texture* scoreTexture;
    SDL_Texture* healthTexture;
    SDL_Texture* levelTexture;
};

class GameRecorder {
public:
    GameRecorder(const std::string& filename);
    ~GameRecorder();
    void updateScore(int score);
    void saveScore(int score);
    int loadScore();
    int LASTSCORE();
    int HIGHSCORE();

private:
    std::string filename;
    int highscore=0;
    int lastScore=0;
};

void renderProgressBar(int x, int y, int w, int h, int value, int max_value, SDL_Color fgColor, SDL_Color bgColor, SDL_Renderer *renderer);

SDL_Texture* createTextTexture(const std::string& text, SDL_Color color, TTF_Font* font);

void renderText(const std::string& text, int x, int y, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer, char type);

#endif //TOOL_H