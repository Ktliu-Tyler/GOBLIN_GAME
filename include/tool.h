//
// Created by Liu KT on 2024/11/20.
//

#ifndef TOOL_H
#define TOOL_H
#include "SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "vector"
#include "iostream"
#include "fstream"
#include "constants.h"
#include <string.h>

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
inline SDL_Color myBLUE2 = { 51, 255, 251, 255 };
//一些遊戲工具
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);// 載入圖片

class Animation {
    std::vector<SDL_Texture*> frames;
    int currentFrameIndex = 0;
    int frameMax = 0;
    int timeCounter = 0;
    Mix_Chunk* sound = nullptr;
    void addAnimationFrame(const std::string& path, SDL_Renderer* renderer);
    public:
    bool stop = false;
    int updateTime = 0;
    int finish = false;
    char id;
    void init();
    void playSound(int channel);
    Animation(char id, int updateTime, const std::vector<std::string>& imagePaths, SDL_Renderer* renderer,const std::string& path="");
    SDL_Texture* getCurrentFrame();
    ~Animation();
    bool update(SDL_Renderer* renderer, SDL_Rect *rect);
};


class Scoreboard {
public:
    Scoreboard(SDL_Renderer* renderer, TTF_Font* font);
    ~Scoreboard();

    void setScore(int score);
    void setHealth(int health);
    void setLevel(int level);
    void setNP(int NP);
    void getHurt(int att);
    void getScore(int score);
    void getNP(int NP);
    void getLevel(int level);
    int Score();
    int Health();
    int NP();
    void render();
    int game_over = false;
    int state = 'n';

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    int score;
    int health;
    int level = 0;
    int np;

    // void renderProgressBar(int x, int y, int w, int h, int value, int max_value, SDL_Color fgColor, SDL_Color bgColor);

    void updateTextures();

    SDL_Texture* scoreTexture;
    SDL_Texture* healthTexture;
    SDL_Texture* levelTexture;
    SDL_Texture* npTexture;
};


class GameRecorder {
public:
    GameRecorder(const std::string& filename, SDL_Renderer* renderer);
    ~GameRecorder();
    void updateScore(int score);
    void saveScore(int score);
    int loadScore();
    int LASTSCORE();
    int HIGHSCORE();

private:
    SDL_Renderer* renderer;
    std::string filename;
    int highscore=0;
    int lastScore=0;
};


class MusicPlayer {
public:
    MusicPlayer(const std::vector<std::string>& Paths);
    Mix_Music *musicMenu = nullptr;
    Mix_Music *musicPlayground = nullptr;
    Mix_Music *musicPlayground2 = nullptr;
    Mix_Music *musicGameOver = nullptr;
    void playMenu();
    void playGamining(int type=1);
    void playGameOver();
    void stop();
    ~MusicPlayer();
};

void renderProgressBar(int x, int y, int w, int h, int value, int max_value, SDL_Color fgColor, SDL_Color bgColor, SDL_Renderer *renderer);

SDL_Texture* createTextTexture(const std::string& text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);

void renderText(const std::string& text, int x, int y, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer, char type);

#endif //TOOL_H