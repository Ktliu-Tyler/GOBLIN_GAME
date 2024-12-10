//
// Created by Liu KT on 2024/9/9.
//
// 常數檔案
#ifndef CONSTANTS
#define CONSTANTS
#define TRUE 1
#define FALSE 0
#define WINDOW_HEIGHT 720 // 螢幕高
#define WINDOW_WIDTH 1280 // 螢幕寬
#define WINDOW_M_HEIGHT 336

#define SCOREBOARD_X 20
#define SCOREBOARD_Y 10
#define SCOREBOARD_BET 50

#define FPS (16 * 60)//幀率 目前還沒寫好
#define FRAME_TARGET_TIME (1000 / FPS)

#define PLAYER_W 100 //玩家大小
#define PLAYER_H 100 //玩家大小
#define PLAYER_HP_MAX 10
#define PLAYER_SPEED 300 //玩家速度
#define BULLET_SPEED 300
#define ENEMYNUMMAX 5
#define ENEMYHP_MAX 10
#define MENUID 0 // Menu編號
#define PLAYGROUNDID 1 // 遊戲編號
#define PLAYGROUNDID_RESTART 2
#define BDSPEED -200 // 背景移動速度
#define BDTIME 10 // 背景移動週期

#define GAMERECORD_FILE "../record/Gamerecoder.txt"
#define FONT "../myFont/arial.ttf"
#define PLAYER_WALK_IMAGES {"../imgs/gob_w/arrowgoblin7.png", "../imgs/gob_w/arrowgoblin8.png", "../imgs/gob_w/arrowgoblin9.png", "../imgs/gob_w/arrowgoblin10.png", "../imgs/gob_w/arrowgoblin11.png", "../imgs/gob_w/arrowgoblin12.png"}//"../imgs/gob_s/arrowgoblin1.png", "../imgs/gob_s/arrowgoblin2.png", "../imgs/gob_s/arrowgoblin3.png", "../imgs/gob_s/arrowgoblin4.png", "../imgs/gob_s/arrowgoblin5.png", "../imgs/gob_s/arrowgoblin6.png",
#define PLAYER_SHOOT_IMAGES { "../imgs/gob_s/arrowgoblin14.png", "../imgs/gob_s/arrowgoblin15.png", "../imgs/gob_s/arrowgoblin16.png", "../imgs/gob_s/arrowgoblin17.png", "../imgs/gob_s/arrowgoblin18.png"}
#define PLAYER_DIED_IMAGES { "../imgs/gob_s/arrowgoblin13.png", "../imgs/gob_s/arrowgoblin17.png"}
#define ARROW_NORM {"../imgs/arrow/arrow.png"}
#define ARROW_FAST {"../imgs/arrow/fastarrow.png"}
#define ARROW_POISON {"../imgs/arrow/poisonarrow.png"}
#define ARROW_POWER {"../imgs/arrow/powerarrow.png"}

#define Enemy1_IMAGES {}

#define CHANGE_BACKGROUND "../imgs/backgrounds/bg_change.png"
#define MENU_BACKGROUND "../imgs/background.png" // Menu 介面背景
#define PLAYGROUND_BACKGROUND {"../imgs/backgrounds/bg_1.jpg", "../imgs/backgrounds/bg_2.jpg"} // 遊戲背景
#define PLAYGROUND_BACKGROUND_MOVE {"../imgs/backgrounds/bg_1_Move.jpg", "../imgs/backgrounds/bg_2_Move3.png"}
#endif

