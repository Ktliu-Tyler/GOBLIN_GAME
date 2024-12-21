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
#define PLAYER_h 100 //玩家大小
#define PLAYER_HIT_W 80 //玩家碰撞大小
#define PLAYER_HIT_H 80 //玩家碰撞大小

#define PLAYER_SHOOT_T 30
#define ENEMY_HIT_RATE 0.8
#define PLAYER_HP_MAX 20
#define PLAYER_NP_MAX 40
#define LEVEL_MAX 50
#define PLAYER_SPEED 300 //玩家速度
#define BULLET_SPEED 300
#define ENEMYNUMMAX 5
#define ENEMYHP_MAX 10
#define ENEMPTYPE 3
#define MENUID 0 // Menu編號
#define PLAYGROUNDID 1 // 遊戲編號
#define PLAYGROUNDID_RESTART 2
#define PLAYGROUNDID2 3
#define PLAYGROUNDID_RESTART2 4
#define BDSPEED -200 // 背景移動速度
#define BDTIME 10 // 背景移動週期

#define MENUBGM "../musics/BGM1.mp3"
#define PLAYGROUNDBGM "../musics/bg.mp3"
#define PLAYGROUNDBGM2 "../musics/GAMEOVER.mp3"
#define GAMEOVERBGM "../musics/BGM2.mp3"

#define SHOOT1_SOUND "../musics/goblin/shoot1.wav"
#define WALK_SOUND "../musics/goblin/walk.wav"
#define HURT_SOUND "../musics/goblin/hurt.wav"
#define GIRL_SOUND "../musics/girl.wav"
#define CLASSMATE_SOUND "../musics/classmate.wav"
#define BOMB_SOUND "../music/bomb.wav"

#define GAMERECORD_FILE "../record/Gamerecoder.txt"
#define FONT "../myFont/Conther/Conther-2.ttf"
#define PLAYER_WALK_IMAGES {"../imgs/gob_w/arrowgoblin7.png", "../imgs/gob_w/arrowgoblin8.png", "../imgs/gob_w/arrowgoblin9.png", "../imgs/gob_w/arrowgoblin10.png", "../imgs/gob_w/arrowgoblin11.png", "../imgs/gob_w/arrowgoblin12.png", "../imgs/gob_w/arrowgoblin12.png", "../imgs/gob_w/arrowgoblin12.png", "../imgs/gob_w/arrowgoblin12.png"}//"../imgs/gob_s/arrowgoblin1.png", "../imgs/gob_s/arrowgoblin2.png", "../imgs/gob_s/arrowgoblin3.png", "../imgs/gob_s/arrowgoblin4.png", "../imgs/gob_s/arrowgoblin5.png", "../imgs/gob_s/arrowgoblin6.png",
#define PLAYER_SHOOT_IMAGES { "../imgs/gob_s/arrowgoblin14.png", "../imgs/gob_s/arrowgoblin15.png", "../imgs/gob_s/arrowgoblin16.png", "../imgs/gob_s/arrowgoblin17.png", "../imgs/gob_s/arrowgoblin18.png", "../imgs/gob_s/arrowgoblin18.png", "../imgs/gob_s/arrowgoblin18.png", "../imgs/gob_s/arrowgoblin18.png"}
#define PLAYER_DIED_IMAGES { "../imgs/gob_d/diegoblin20.png", "../imgs/gob_d/diegoblin21.png","../imgs/gob_d/diegoblin22.png","../imgs/gob_d/diegoblin23.png","../imgs/gob_d/diegoblin24.png","../imgs/gob_d/diegoblin25.png","../imgs/gob_d/diegoblin26.png","../imgs/gob_d/diegoblin27.png","../imgs/gob_d/diegoblin28.png","../imgs/gob_d/diegoblin29.png","../imgs/gob_d/diegoblin30.png","../imgs/gob_d/diegoblin31.png","../imgs/gob_d/diegoblin32.png", "../imgs/gob_d/diegoblin32.png", "../imgs/gob_d/diegoblin32.png", "../imgs/gob_d/diegoblin32.png"}
#define ARROW_NORM {"../imgs/arrow/arrow.png"}
#define ARROW_FAST {"../imgs/arrow/fastarrow.png"}
#define ARROW_POISON {"../imgs/arrow/poisonarrow.png"}
#define ARROW_POWER {"../imgs/arrow/powerarrow.png"}


#define ENEMY1_IMAGES {"../imgs/enemy1/Bat1.png","../imgs/enemy1/Bat2.png","../imgs/enemy1/Bat3.png","../imgs/enemy1/Bat4.png","../imgs/enemy1/Bat5.png","../imgs/enemy1/Bat6.png","../imgs/enemy1/Bat7.png","../imgs/enemy1/Bat8.png"}
#define ENEMY1_DIE {"../imgs/enemy1/Bat-Die.png","../imgs/enemy1/Bat-Die2.png","../imgs/enemy1/Bat-Die3.png","../imgs/enemy1/Bat-Die4.png","../imgs/enemy1/Bat-Die5.png","../imgs/enemy1/Bat-Die6.png","../imgs/enemy1/Bat-Die7.png","../imgs/enemy1/Bat-Die8.png","../imgs/enemy1/Bat-Die.png","../imgs/enemy1/Bat-Die9.png"}

#define MONSTER_IMAGES {"../imgs/dragon/gragon-0_0.png", "../imgs/dragon/gragon-1_0.png", "../imgs/dragon/gragon-2_0.png", "../imgs/dragon/gragon-3_0.png", "../imgs/dragon/gragon-4_0.png", "../imgs/dragon/gragon-5_0.png", "../imgs/dragon/gragon-6_0.png", "../imgs/dragon/gragon-7_0.png", "../imgs/dragon/gragon-8_0.png", "../imgs/dragon/gragon-9_0.png", "../imgs/dragon/gragon-10_0.png", "../imgs/dragon/gragon-11_0.png"}
#define HUMAN_IMAGES {"../imgs/lily/lily0.png","../imgs/lily/lily1.png","../imgs/lily/lily2.png","../imgs/lily/lily3.png","../imgs/lily/lily4.png","../imgs/lily/lily5.png","../imgs/lily/lily6.png","../imgs/lily/lily7.png"}
#define HUMAN1_IMAGES {"../imgs/human1/1-1_0.png", "../imgs/human1/1-2_0.png", "../imgs/human1/1-3_0.png", "../imgs/human1/1-4_0.png", "../imgs/human1/1-5_0.png", "../imgs/human1/1-6_0.png", "../imgs/human1/1-7_0.png"}
#define HUMAN2_IMAGES {"../imgs/human2/2-1_0.png", "../imgs/human2/2-2_0.png", "../imgs/human2/2-3_0.png", "../imgs/human2/2-4_0.png", "../imgs/human2/2-5_0.png", "../imgs/human2/2-6_0.png"}
#define HUMAN3_IMAGES {"../imgs/human3/3-1_0.png", "../imgs/human3/3-2_0.png", "../imgs/human3/3-3_0.png", "../imgs/human3/3-4_0.png", "../imgs/human3/3-5_0.png", "../imgs/human3/3-6_0.png", "../imgs/human3/3-7_0.png", "../imgs/human3/3-8_0.png", "../imgs/human3/3-9_0.png", "../imgs/human3/3-10_0.png", "../imgs/human3/3-11_0.png", "../imgs/human3/3-12_0.png", "../imgs/human3/3-13_0.png", "../imgs/human3/3-14_0.png", "../imgs/human3/3-15_0.png", "../imgs/human3/3-16_0.png", "../imgs/human3/3-17_0.png", "../imgs/human3/3-18_0.png", "../imgs/human3/3-19_0.png"}

#define EXPLODE_IMAGES {"../imgs/explode/Bomb0.png","../imgs/explode/Bomb1.png","../imgs/explode/Bomb2.png","../imgs/explode/Bomb3.png","../imgs/explode/Bomb6.png","../imgs/explode/Bomb7.png","../imgs/explode/Bomb8.png","../imgs/explode/Bomb9.png","../imgs/explode/Bomb10.png","../imgs/explode/Bomb11.png","../imgs/explode/Bomb12.png","../imgs/explode/Bomb13.png","../imgs/explode/Bomb14.png","../imgs/explode/Bomb15.png","../imgs/explode/Bomb16.png","../imgs/explode/Bomb17.png","../imgs/explode/Bomb18.png","../imgs/explode/Bomb19.png","../imgs/explode/Bomb20.png","../imgs/explode/Bomb21.png","../imgs/explode/Bomb22.png","../imgs/explode/Bomb23.png","../imgs/explode/Bomb24.png","../imgs/explode/Bomb25.png","../imgs/explode/Bomb26.png"}
#define SKAKE_HEAD {"../imgs/shakeing/ryo-0_0.png","../imgs/shakeing/ryo-1_0.png","../imgs/shakeing/ryo-2_0.png","../imgs/shakeing/ryo-3_0.png"}



#define STOP_PIC "../imgs/stop.png"
#define CHANGE_BACKGROUND "../imgs/backgrounds/bg_change.png"
#define MENU_BACKGROUND "../imgs/backgrounds/menu.png" // Menu 介面背景
#define MENU_ANIME {"../imgs/backgrounds/MenuANIME/bg0_0.png", "../imgs/backgrounds/MenuANIME/bg1_0.png", "../imgs/backgrounds/MenuANIME/bg2_0.png", "../imgs/backgrounds/MenuANIME/bg3_0.png", "../imgs/backgrounds/MenuANIME/bg4_0.png", "../imgs/backgrounds/MenuANIME/bg5_0.png", "../imgs/backgrounds/MenuANIME/bg6_0.png", "../imgs/backgrounds/MenuANIME/bg7_0.png", "../imgs/backgrounds/MenuANIME/bg8_0.png", "../imgs/backgrounds/MenuANIME/bg9_0.png", "../imgs/backgrounds/MenuANIME/bg10_0.png", "../imgs/backgrounds/MenuANIME/bg11_0.png", "../imgs/backgrounds/MenuANIME/bg12_0.png", "../imgs/backgrounds/MenuANIME/bg13_0.png", "../imgs/backgrounds/MenuANIME/bg14_0.png", "../imgs/backgrounds/MenuANIME/bg15_0.png", "../imgs/backgrounds/MenuANIME/bg16_0.png", "../imgs/backgrounds/MenuANIME/bg17_0.png", "../imgs/backgrounds/MenuANIME/bg18_0.png", "../imgs/backgrounds/MenuANIME/bg19_0.png", "../imgs/backgrounds/MenuANIME/bg20_0.png", "../imgs/backgrounds/MenuANIME/bg21_0.png", "../imgs/backgrounds/MenuANIME/bg22_0.png", "../imgs/backgrounds/MenuANIME/bg23_0.png", "../imgs/backgrounds/MenuANIME/bg24_0.png", "../imgs/backgrounds/MenuANIME/bg25_0.png", "../imgs/backgrounds/MenuANIME/bg26_0.png", "../imgs/backgrounds/MenuANIME/bg27_0.png", "../imgs/backgrounds/MenuANIME/bg28_0.png", "../imgs/backgrounds/MenuANIME/bg29_0.png"}
#define PLAYGROUND_BACKGROUND {"../imgs/backgrounds/ntubg_0.jpg","../imgs/backgrounds/bg_2.jpg"} // 遊戲背景"../imgs/backgrounds/bg_1.jpg",
#define PLAYGROUND_BACKGROUND_MOVE {"../imgs/backgrounds/ntubg1_0.jpg", "../imgs/backgrounds/bg_2_Move3.png"} //"../imgs/backgrounds/bg_1_Move.jpg"


#endif

