#ifndef engine
#define engine
#include <iostream>
#include "SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "tool.h"
#include "menu.h"
#include "playground.h"
//#include "object.h"
#endif

extern SDL_Window *mywindow; // 視窗指標
extern SDL_Renderer *renderer; // 選染器

extern int game_is_running;

int initialize_window(); // 初始化
void setup();  // 設定各class
void process_input(); // 處理輸入
int update(); // 更新角色資料
void render(); // 渲染
void change_page();
void destroy_window(); //清除視窗

