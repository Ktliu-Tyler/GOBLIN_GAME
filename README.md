
#### exe 檔在cmake-build-release資料夾中

## 哥布林任務【致命清算】 ##
在這款哥布林遊戲中
# 你! 就是哥布林
現實就是戰爭，失敗即死亡，玩家需要在新冠蝙蝠、百合、特瓦林的夾擊下，生存於這殘酷的現實中，活出最高分的冒險。
### 打開遊戲開啟主畫面
## 可以按 S 或是 N 開啟遊戲 分別對應到不同的模式
### 模式一  
基礎模式 會有boss關 
### 模式二  
NTU 模式 會有無盡模式的NTU帥潮來擊垮哥布林的心靈防線
### 玩家可利用 W 和 S 控制腳色上下，並且可以用1 2 3 4 數字鍵切換武器模式，按空白鍵可以發射，有基礎箭、加速箭、減速箭和增強箭，每種箭消耗的 NP 也不一樣，玩家要注意自己的 NP 量是否足夠，並且要提防BOSS的出現，如果沒有預留足夠的 NP 可能就打不過BOSS。最後你也可以利用分數紀錄的功能來查看自己的最高得分!

## 哥布林們 快來挑戰吧!
# 你 是否能存活?

#   
#  
# 專案介紹
# Goblin game
## 專案架構
# 計算機程式專題
## 個人分工 B12502166 劉昆泰
我個人主要是負責遊戲整體架構的程式以及遊戲邏輯、運行功能設計，主要寫了整體的遊戲框架、環境的建置，以及遊戲的整體邏輯與角色邏輯，這邊可以提一下，因為我們是使用clion在windows上進行編輯，不是像課程中教學使用code block或是vscode，在環境建置的時候，也是花費了不少心思在編輯cmakeList以及抓取動態函式庫，最後也有成功將環境建置出來並且公開倒github上給大家使用。
在這裡附上環境連結: https://github.com/Ktliu-Tyler/SDL_env_clion
遊戲連結: https://github.com/Ktliu-Tyler/GOBLIN_GAME

### 程式架構設計
關於程式的架構設計，我要求必須將檔案分類於include和src這兩個與main位於相同根目鱸的資料夾中，裡面放置我們的.h和.c檔案，方便後續進行debug時的程式跳轉，架構如下:
```
Goblin_game
├── cmake_modules, CMakeLists.txt, SDL_lib<span style="color:blue"># CMake 配置文件</span>
├── imgs, musics, myFont, record <span style="color:blue"># 資料存放</span>
├── include
│ ├── constants.h <span style="color:blue"># 定義常量</span>
│ ├── Enemy.h <span style="color:blue"># 定義敵人相關的類和方法</span>
│ ├── engine.h <span style="color:blue"># 定義遊戲引擎相關的類和方法</span>
│ ├── menu.h <span style="color:blue"># 定義菜單相關的類和方法</span>
│ ├── Player.h <span style="color:blue"># 定義玩家相關的類和方法</span>
│ ├── playground.h <span style="color:blue"># 定義遊戲場景相關的類和方法</span>
│ ├── test.h <span style="color:blue"># 定義測試相關的類和方法</span>
│ └── tool.h <span style="color:blue"># 定義工具類和方法</span>
├── src
│ ├── Enemy.cpp <span style="color:blue"># 實現敵人相關的功能</span>
│ ├── engine.cpp <span style="color:blue"># 實現遊戲引擎相關的功能</span>
│ ├── menu.cpp <span style="color:blue"># 實現菜單相關的功能</span>
│ ├── Player.cpp <span style="color:blue"># 實現玩家相關的功能</span>
│ ├── playground.cpp <span style="color:blue"># 實現遊戲場景相關的功能</span>
│ ├── test.cpp <span style="color:blue"># 實現測試相關的功能 主要是我在除錯exe無法運行的問題</span>
│ └── tool.cpp <span style="color:blue"># 實現工具相關的功能</span>
└── main.cpp <span style="color:blue"># 主程序文件</span>
<div style="page-break-after:always"></div>
```

### 遊戲參數設置
我將所有我們會用到的常數，包含會需要引用到的路徑名稱、圖片音訊位置都放在一個constant.h中，這樣使我們在進行debug的時候可以透過簡單的更改參數來進行調整，甚至是在更改角色圖片或式音效時都能透過這裡快速進行更改，不過這也是造成我們使用const和static較少的原因，因為我的程式習慣會將不更動的參數用define的方式寫成宏，並且可以當作全域變數使用，這樣在書寫時選字顏色比較容易區分，基本上所有的程式都會引用constant.h的常數，方便們進行管理，以下為constant.h的宣告程式以及其代表意義(圖片的話因為太長我就不全放了):

```cpp=
// constant.h
#ifndef CONSTANTS
#define CONSTANTS
#define TRUE 1 // 沒什麼用的宣告 只是比較習慣python的樣子
#define FALSE 0 // 
#define WINDOW_HEIGHT 720 // 螢幕高
#define WINDOW_WIDTH 1280 // 螢幕寬
#define WINDOW_M_HEIGHT 336 // 地面移動背景的高度x
#define SCOREBOARD_X 20 // 記分板位置
#define SCOREBOARD_Y 10 
#define SCOREBOARD_BET 50 // 記分板的間隔
#define FPS (16 * 60) // 幀率 單位有點錯，但這是目前運行最順暢的情況，詳細可見engine
#define FRAME_TARGET_TIME (1000 / FPS) //寫在engine的update地方，計算deltatime
#define PLAYER_W 100 //玩家大小
#define PLAYER_h 100 //玩家大小
// #define PLAYER_HIT_W 80 玩家碰撞大小
const int PLAYER_HIT_W =  80;
// #define PLAYER_HIT_H 80 玩家碰撞大小
const int PLAYER_HIT_H =  80;
// #define ENEMY_HIT_RATE 0.8 //原本define寫法也是互通的
const float ENEMY_HIT_RATE =  0.8; //這邊是因為我們都沒甚麼用到const所以在這裡用
#define PLAYER_SHOOT_T 30 // 玩家基礎射擊間隔
#define PLAYER_HP_MAX 20 // 玩家基礎血量
#define PLAYER_NP_MAX 40 // 玩家基礎能量
#define LEVEL_MAX 50 // 進度條最大值
#define PLAYER_SPEED 300 //玩家速度
#define BULLET_SPEED 300 //子彈速度
#define ENEMYNUMMAX 5 // 最大場上存在敵人數
#define ENEMYHP_MAX 10 // 敵人最高血量
#define ENEMPTYPE 3 // 敵人總類，每個遊戲模式各三個，其實後續會隨意更動
#define MENUID 0 // Menu編號
#define PLAYGROUNDID 1 // 遊戲編號
#define PLAYGROUNDID_RESTART 2 // 切換畫面的癲號
#define PLAYGROUNDID2 3 // 特殊遊戲模式編號
#define PLAYGROUNDID_RESTART2 4 // 切換特殊遊戲模式編號
#define BDSPEED -200 // 背景移動速度
#define BDTIME 10 // 背景移動週期
#define MENUBGM "../musics/BGM1.mp3" // 背景音樂
#define PLAYGROUNDBGM "../musics/bg.mp3"// 遊戲背景音樂
#define PLAYGROUNDBGM2 "../musics/GAMEOVER.mp3" // 遊戲背景音樂2
#define GAMEOVERBGM "../musics/BGM2.mp3" // 遊戲結束音樂
```
```cpp=
#define SHOOT_SOUND "../musics/goblin/shoot.wav" //攻擊音樂
#define SHOOT1_SOUND "../musics/goblin/shoot1.wav" // 備用攻擊音樂
#define WALK_SOUND "../musics/goblin/walk.wav" // 走路聲音
#define HURT_SOUND "../musics/goblin/hurt.wav" // 受傷的聲音
#define GIRL_SOUND "../musics/girl.wav" // 女生受傷的聲音(百合)
#define CLASSMATE_SOUND "../musics/classmate.wav" // 帥潮受傷聲音
#define BOMB_SOUND "../music/bomb.wav" //爆炸聲
#define GAMERECORD_FILE "../record/Gamerecoder.txt"// 遊戲紀錄的檔案位置
#define FONT "../myFont/Conther/Conther-2.ttf" // 字體位置
#define PLAYER_WALK_IMAGES {"../im...//哥布林走路
#define PLAYER_SHOOT_IMAGES { "... //射擊圖片
#define ARROW_NORM {"../imgs/arrow/arrow.png"}// 弓箭1圖片
#define ARROW_FAST {"../imgs/arrow/fastarrow.png"}//弓箭2圖片
#define ARROW_POISON {"../imgs/arrow/poisonarrow.png"}//弓箭3圖片
#define ARROW_POWER {"../imgs/arrow/powerarrow.png"}//弓箭4圖片
#define ENEMY1_IMAGES {"...//敵人圖片
#define ENEMY1_DIE {"...//敵人死亡圖片
#define MONSTER_IMAGES {"...//怪獸特瓦林塗圖片
#define HUMAN_IMAGES {"...//學生圖片
#define HUMAN2_IMAGES {"...//徐生圖片
#define HUMAN3_IMAGES {"...//學生圖片
#define EXPLODE_IMAGES {"...//爆炸圖片
#define SKAKE_HEAD {"...// 搖頭女孩圖片
#define STOP_PIC "../imgs/stop.png"// 停止圖片
#define CHANGE_BACKGROUND "../imgs/backgrounds/bg_change.png"// 黑幕位置
#define MENU_BACKGROUND "../imgs/backgrounds/menu.png" // Menu 介面背景
#define MENU_ANIME {"...//MENU的動畫圖片
#define PLAYGROUND_BACKGROUND {"... // 遊戲背景"../imgs/backgrounds/bg_1.jpg",
#define PLAYGROUND_BACKGROUND_MOVE {"...// 移動地板圖片

// 這邊的圖片和音檔路徑引用，因為太多了就先省略
// 基本上就是名稱對應到的圖片或音訊路徑
#endif
```
在這邊的常數設置基本上都跟const的用法類似，如果捨去掉改成設置一般的常數，很容易在編寫程式時不小心改動到定值而造成debug困難，其實define和const還是有很大的差別，一個是用預處理器先編好，但我這邊使用的功能比較類似而已，本來是有打算用define去做一些寫程式上的變化，像是把重複使用的function直接用define寫成段落貼入，不過最後時間不太夠就沒有額外的增加功能了。
下面的 static和 const 宣告在很多地方較分散，使用如下:

| 宣告                             |  功能  | 存放位置                       |
|-------------------------------------|-----|--------------------------------|
| static GameRecorder *game_recorder |計分器 | engine.cpp, line 12       |
| static int s = 60;                       |單次位移| Enemy.cpp, line 151       |
| static menu *MenuPage = nullptr;        |主畫面 | engine.cpp, line 14       |
| static playground *PlayPage = nullptr;  |遊戲畫面 | engine.cpp, line 15       |
| static MusicPlayer *BGMmusic = nullptr; |音樂播放器 | SDL_bgi.cpp, line 42      |
| static int fgWidth = static_cast<int>((static_cast<float>(value) / max_value) * w);|文字框寬度 | tool.cpp, line 31         |
| static int n = ENEMYNUMMAX;             | 敵人計數| playground.cpp, line 410  |
| static int PAGE_ID = 0;                  |當前頁面紀錄| engine.cpp, line 21       |

這些static的變數能確保區域變數不受到外部存取的影響而改變其值，並且在重複呼叫該區塊時能保有其值，作為計數器使用，裡如上面倒數第二個static int n，若是拿掉static，會導致程式每次進入都重新宣告並賦值，而無法計算每次的當前敵人數而造成錯誤。

| 宣告方式                 |功能                                                                                     | 存放位置                         |
|---------|---------------|---------|
| const std::vector\<std::string> *playbg = PLAYGROUND_BACKGROUND;  |遊戲背景路徑                                             | engine.cpp, line 17              |
| const std::vector\<std::string> Wimages = PLAYER_WALK_IMAGES;      |角色圖片路徑                                  | Player.h, line 28                |
| const std::vector\<std::string> playbgMove = PLAYGROUND_BACKGROUND_MOVE; |移動背景路徑                                      | engine.cpp, line 18              
| const Uint8* keystate = (SDL_GetKeyboardState(NULL)); |讀取keyboard狀態                                                        | engine.cpp, line 19              |
| const std::vector\<std::string> Simages = PLAYER_SHOOT_IMAGES;|射擊圖片路徑                                                 | Player.h, line 29                |
| const int PLAYER_HIT_W = 80;                                             |角色碰撞rect                                     | constants.h, line 23             |
| const std::vector\<std::string> Dimages = PLAYER_DIED_IMAGES;              |角色死亡圖片路徑                     | Player.h, line 30                |
| const int PLAYER_HIT_H = 80;                |角色碰撞rect                                                                  | constants.h, line 25             |
| const float ENEMY_HIT_RATE = 0.8;                |敵人碰撞rect                                                             | constants.h, line 28             |

    
const 的宣告能夠固定數值而不被他者更動，對於程式中的一些常數，用const宣告能避免錯誤更動，或是const指標，讓指標固定指向某一位址，如上面的keyboard輸入只能使用const，因為該function會回傳數值固定到該指標，因此必須用紙const指標來儲存，否則的話會因指標指向錯誤而無法讀取或是報錯。
    
<div style="page-break-after:always"></div>
    
### main.cpp / engine.cpp
這次遊戲引擎的架構我有用了一些小巧思，由於在剛開始設計的時候，考量到我們會有多個視窗切換，並且要讓組員之間容易分工，因此我思考可以利用模組化的方式，將每個介面分類成一個class，並且透過我們的engine程式來進行呼叫，這樣容易將各個頁面分配給組員進行編輯，也容易整合在一起。
首先，我們將整個程式運行的主架構分成以下部分，寫成engine的幾個function。而main.cpp程式只需要寫簡單的迴圈，並且呼叫engine的程式便可以運行。

```cpp=
//main.cpp
int main(int argc, char *argv[]) {
    game_is_running = initialize_window();
    setup();
    while (game_is_running) {
        // SDL_Log("Game is running...");
        process_input();
        game_is_running = update();
        render();
    }
    destroy_window();
    return 0;
}
```
可以注意到這邊有一個蠻重要的全域變數game_is_running，我們會持續監控此變數的狀態，以作為程式是否關閉的運行判斷。

```cpp=
//engine.h
extern SDL_Window *mywindow; // 視窗指標
extern SDL_Renderer *renderer; // 選染器
extern int game_is_running;

int initialize_window(); // 初始化
void setup();  // 設定各class
void process_input(); // 處理輸入
int update(); // 更新角色資料
void render(); // 渲染
void change_page(); // 畫面切換
void destroy_window(); //清除視窗
```
initialize_window()中會初始化SDL環境，和set_up差別在於一個是環境的初始化，一個是物件的初始化。並且分別都用SDL_Log對偵錯進行輸出，方便我們進行debug。還有這裡的destroy_window也有對所有建立好的指標進行記憶體釋放，優化我們的程式。

<div style="page-break-after:always"></div>

接下來這裡提一下我們的change_page以及一些engine邏輯

```cpp= 
// engine.cpp 的宣告
static GameRecorder *game_recorder = nullptr; // 遊戲紀錄存檔模組
static menu *MenuPage = nullptr; // 菜單介面
static playground *PlayPage = nullptr; // 遊戲介面
static MusicPlayer *BGMmusic = nullptr; // 背景音樂播放器
const std::vector<std::string> playbg = PLAYGROUND_BACKGROUND; //背景圖的路徑
const std::vector<std::string> playbgMove = PLAYGROUND_BACKGROUND_MOVE;
const Uint8* keystate = (SDL_GetKeyboardState(NULL)); //用來獲取鍵盤狀態
static int  PAGE_ID = 0; // 用來判斷當前畫面
static int gametype = 1; //判斷遊戲模式
static int prePage_ID = 0; //跟PAGE_ID比較判斷畫面是否更改
static int last_frame_time = 0; //幀數紀錄時前一次的時間
static float delta_time = 0; // 用來存幀率對應的時間
```
上面介紹了這些參數的用途，應該很容易理解到，我主要想解釋的是我們切換畫面的方法，我使用Page_ID來進行頁面切換的判斷，對應執行該狀態介面的update、render、input_proccess，這樣有一個很大的優勢是，如果我今天想要新增新的介面，我只要確保此介面的class中，包含了我所需的render、input_proccess，和update，便可以直接在ID添加此介面，快速更新整個程式，並且，我也能透過這樣同時指運行一種介面的方式，來減少當前正在運行的資料量，達到更通順的運行。
```cpp=
void change_page() {
    if (PAGE_ID != prePage_ID) {
        prePage_ID = PAGE_ID;
        if(PAGE_ID == PLAYGROUNDID2) {
            PAGE_ID = PLAYGROUNDID;
            gametype =2;
        }else if(PAGE_ID == PLAYGROUNDID){
            gametype = 1;
        }
        if (PAGE_ID == PLAYGROUNDID || PAGE_ID == PLAYGROUNDID_RESTART) {
            prePage_ID = PLAYGROUNDID;
            PAGE_ID = PLAYGROUNDID;
            SDL_Log("Play Game 1");
            if(gametype == 1){
                PlayPage = new playground(playbg[1], playbgMove[1]
                                          , renderer, game_recorder, BGMmusic);
            }else if (gametype == 2) {
                PlayPage = new playground2(playbg[0], playbgMove[0]
                                           , renderer, game_recorder, BGMmusic);
            }
        }else if (PAGE_ID == MENUID) {
            SDL_Log("MENU");
            MenuPage = new menu(MENU_BACKGROUND, renderer
                                , game_recorder, BGMmusic);}}}
```
可以注意到我在裡面有兩個static變數，讓我判斷切換畫面，成功切換後直接更新playground或是menu物件，便能成功刷新或是切換畫面了。

<div style="page-break-after:always"></div>

## **class playground & playground2**
### 程式架構 *這區講的程式都在playgrdoun.h 和 playground.cpp中
此程式主要用於建立遊戲中的遊戲畫面page，這個class 用到了繼承、組合、複製建構子、解構子等功能，其中scoreboard為其子物件，而playground2又由他進行繼承並設置virtual函式調整了新增敵人的方法，player、enemy和bullet將其設為friend，可以取用這些class的private宣告。

```cpp=
// playground.h
class playground { // 遊戲介面 class
public:
    int update(float deltatime);
    int process_input(SDL_Event *event, const Uint8* keystate);
    void render(SDL_Renderer *renderer); 
    void movebd(float deltatime);// 移動背景
    void bdrender(); // 背景渲染
    int gameSTOP(); // 遊戲結束時的判斷
    void changebd(); //畫面切換的黑幕
    playground(std::string path,std::string pathMove, SDL_Renderer* renderer,
               GameRecorder *recorder, MusicPlayer *music_player); // 物件建構子
    playground(const playground & p); // 複製建構子 
    ~playground(); // 物件解構子
    virtual void new_Enemy(); //新增敵人的程式
    virtual void bullet_update(float deltatime); // 子彈更新程式
    virtual void enemy_update(float deltatime); //敵人更新程式
    virtual int gameOVER_ANIME(); // gameover的while迴圈  
protected:
    float backgroundX;
    int timecounter = 0; // 痾好這個後來沒用到
    int enemyNUM = 0; // 敵人當前數量
    int chbgX = -300; // chang background的黑幕座標
    int gameStart = false; // 判斷黑幕跑完沒
    int gametype = 1; //判斷遊戲模式
    SDL_Texture *background = nullptr; //背景圖
    SDL_Texture *backgroundMove = nullptr;//背景圖
    SDL_Texture *backgroundChange = nullptr;//黑幕圖 我用小畫家塗的
    SDL_Renderer *renderer = nullptr; // 渲染氣 來自engine
    GameRecorder *recorder = nullptr; // 分數紀錄器 來自engine
    MusicPlayer *musicPlayer = nullptr; // 背景音樂 來自engine
    Player *player; // 玩家
    Scoreboard scoreboard; // 子物件 記分板
    std::vector<Bullet *> bullets; // 子彈指標陣列
    std::vector<Enemy *> enemys; // 敵人指標陣列
};
```
<div style="page-break-after:always"></div>

### 參數宣告
變數我主要都用 protected 進行宣告，以防不當的編寫意外更改導致難以除錯，同時也讓繼承其的 playground2 容易調整參數，而其他會被engine調用的程式我放在public，以利撰寫時直接調用。
* virtual的使用是因為後面繼承的特殊遊戲介面playground2 會需要更新不同的角色生成方式或是角色攻擊方式，這樣可以使後續程式能夠覆蓋這裡的函式內容。

### 程式運行邏輯
運行程式時，由其上游的 engine 對應到這些 page 的基礎程式:
進入 playground -> process_input -> update -> render 而其中又分別對應
|程式|      process_input     | update         | render         |
|----|--------------|--------------|---------------|
|功能| 進行輸入讀取，有角色移動操作的輸入，子彈發射的輸入。遊戲畫面切換的輸入。| 遊戲資料更新，包含碰撞判斷、角色死亡判斷，以及分數紀錄更新等等    |   最重要的畫面渲染，會呼叫playground中，各個物件進行渲染，像是enemy、player、scoreboard等等 |
|程式| 主要處理物件內的程式 | new_Enemy() bullet_update() enemy_update() movebd()  |   bdrender() 和一些角色 render()|

結構都依循著主架構的 engine，主要特別的是，遊戲有一個過場畫面的黑幕，因此設定了參數 gamestart 為 false ，待黑幕移動到指定位置後，將 gamestart 設為 true 才開始，還有在遊戲結束的畫面是於engine之中的while迴圈，自成一個架構的 gameOVER_ANIME() 其中等待使用者輸入後才決定跳轉至何畫面。接下來將根據個 function 依序介紹功能:

#### 建構子 & 複製建構子
此 class 初始化需要提供 
| path          | pathMove         | renderer         | recorder    |music_player |
|---------------|--------------|---------------|-----|-----|
| string  | string     |    SDL_Renderer*   |GameRecorder*  (tool.h)| MusicPlayer* (tool.h)  |
| 背景圖片路徑  |   移動背景    |    渲染器       |分數紀錄器|  背景音樂播放器  |

這裡的 playground 是一個組合，包含了 scoreboard 的物件，在建立 playground 時一起初始化，用來記錄遊戲中的分數、血量、能量等等，並且進行記分板的畫面渲染以及遊戲狀態的紀錄，因此其將 playground 設為 friend 方便進行調用。

複製建構子程式如下
```cpp=
// playground.cpp
playground::playground(const playground & c):scoreboard(c.renderer, font) {
    SDL_Log("Creating playground...");
    this -> background = c.background;
    this -> backgroundMove = c.backgroundMove;
    this -> backgroundChange  = c.backgroundChange;
    this -> renderer = c.renderer;
    this -> recorder = c.recorder;
    this -> musicPlayer = c.musicPlayer;
    this -> backgroundX = 0; // 計算畫面滾動的座標
    this -> chbgX = -300; // 一開始畫面的位置
    srand( time(NULL) );  // 設定random的參數隨機
    font =  TTF_OpenFont(FONT, 24); // 小字體
    fontBIG =  TTF_OpenFont(FONT, 100); // Gameover的字體
    this->musicPlayer->stop(); // 在切換畫面時音樂停止
    player = new Player(PLAYER_W+30, WINDOW_HEIGHT-WINDOW_M_HEIGHT, 
                        PLAYER_W,PLAYER_h, PLAYER_SPEED, renderer, 
                        WINDOW_HEIGHT,WINDOW_HEIGHT-WINDOW_M_HEIGHT);
    scoreboard.setHealth(PLAYER_HP_MAX);// 初始化scoreboard
    scoreboard.setNP(PLAYER_NP_MAX);
    scoreboard.setScore(0);
    scoreboard.setLevel(0);
}
```

#### 繼承 & 組裝
前面有提過了playground 有一個繼承的 playground2 一樣在 playground.cpp中，而 playground 為一個組裝並包含scoreboard的物件，這邊使用組裝是因為scoreboard不需要被傳遞給engine，而是跟著playground一起被創建和delete，因此此直接把他當作playground的子物件來進行初始化也比較方便。而scoreboard又將playground設為friend方便調用，除此之外，內容中使用到的所有Enemy是由最初蝙蝠的enemy的class去進行繼承的，這樣方便我們在加入到enemy* 的 vector 中也能順利運行，並且方便修改整體的創建、判斷程式。

#### 特殊使用 (指標處理)
這邊想補充我在 enemy 和 bullet 新增的方法，也算是指標的使用，因為程式碼蠻長的就不貼上來，內容都在playground,cpp中可以找到new_enemy、enemy_update、bullet_update等，可以注意到我一開始設定的用來儲存的型別為指標陣列 (引用vector)
```cpp=
// playground.h的class中
std::vector<Bullet *> bullets;
std::vector<Enemy *> enemys;
```
<div style="page-break-after:always"></div>
    
不得不說 vector 是個很好用的東西，透過他我可以用 pushback 的方式輕鬆處理動態陣列，還有在 bullet 和 enemy 的碰撞判斷等等，直接調用物件指標，直接存取各物件的 hitrect 來進行判斷，當角色血量判斷死亡時，讓我們播放動畫及音效(這是我花很多心思的功能，後面會提到)，並且可以用 erase 將物件從 vector 中去除，大幅提升了我在程式編寫上的效率，這邊的物件大多是使用指標宣告，方便對物件進行傳遞和取值，在物件被刪除時，我也都有使用delete將物件記憶體釋放。

還有一點是因為我們的敵人角色都是利用繼承的方式進行編寫，所以都能夠放入這邊的enemy指標陣列中，使得在切換不同種敵人生成時很方便。

####  polymorphism & virtual
這邊利用 virtual 達到 polymorphism 在繼承類別的實作，用意是讓特殊模式生成的敵人為其他繼承enemy類別的角色，方便我們對於不同種類的敵人記形客製化或是更改參數。
```cpp=
// 原virtual
void playground::new_Enemy() {
    int n = ENEMYNUMMAX-enemyNUM;
    if (scoreboard.state == 'n') {
        for (int i = 0; i < n; i++) {// 判斷當前場上還缺幾個敵人就直接隨機生成
            int enemyType = rand()%ENEMPTYPE;
            int hp = rand()%6+3;
            if(enemyType == 0) {//辨別隨機敵人對應的生成數字
                enemys.push_back(new Enemy(rand()%WINDOW_WIDTH+WINDOW_WIDTH, 
                   (rand()%WINDOW_M_HEIGHT-30-hp*15)+
                   (WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15),
                   rand()%200,hp, renderer));
            }else if (enemyType == 1) {
                enemys.push_back(new Human(rand()%WINDOW_WIDTH+WINDOW_WIDTH,
                    (rand()%WINDOW_M_HEIGHT-30-hp*15)+
                    (WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15),
                   rand()%200, hp, renderer));
            }else if (enemyType == 2) {
                enemys.push_back(new Human(rand()%WINDOW_WIDTH+WINDOW_WIDTH,
                    (rand()%WINDOW_M_HEIGHT-30-hp*15)+
                    (WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), 
                    rand()%200, hp, renderer));
            }
            enemyNUM++;
        }
    }else  if (scoreboard.state == 'g'){// Boss生成
        Monster *e = new Monster(rand()%WINDOW_WIDTH+WINDOW_WIDTH
                                 , WINDOW_HEIGHT/4+30, -100, 30, renderer);
        e->type = 'B';
        enemys.push_back(e);
        enemyNUM = 0;
        scoreboard.state = 'B';
    }
}
```
可以對比下面的內容，程式中都是使用random的方式來隨機生成敵人的血量，並根據血量去生成角色大小和攻擊力，主要差別就是使用的enemy繼承物件不一樣，而這也就是在初始化時對應到的動畫和音效不一樣。
```cpp=
// playground2 中的 new_Enemy()
void playground2::new_Enemy() {
    static int n = ENEMYNUMMAX;
    n = ENEMYNUMMAX-enemyNUM;//計算要生成的敵人數量
    for (int i = 0; i < n; i++) {
        int enemyType = rand()%ENEMPTYPE;
        int hp = rand()%10+1;
        if(enemyType == 0) {//判斷隨機數字對應
            enemys.push_back(new Human3(rand()%WINDOW_WIDTH+
                    WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)
                    +(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15),
                    rand()%200,hp, renderer));
        }else if (enemyType == 1) {
            enemys.push_back(new Human1(rand()%WINDOW_WIDTH+
                    WINDOW_WIDTH, (rand()%WINDOW_M_HEIGHT-30-hp*15)
                    +(WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), 
                    rand()%200, hp, renderer));
        }else if (enemyType == 2) {
            enemys.push_back(new Human2(rand()%WINDOW_WIDTH+WINDOW_WIDTH, 
                    (rand()%WINDOW_M_HEIGHT-30-hp*15)+
                    (WINDOW_HEIGHT-WINDOW_M_HEIGHT-100+hp*15), 
                    rand()%200, hp, renderer));
        }
        // SDL_Log("Enemy born at %f, %f", enemys[i]->x, enemys[i]->y);
        enemyNUM++;
    }
}
```
    
<!-- <div style="page-break-after:always"></div> -->
    
#### enemy更新處理(指標處理)
在playground的許多函式中，我都使用到大量的指標來進行物件之間的交互，像是這邊對enemy的更新處理，我利用for迴圈遍歷指標陣列，並取出其記憶體位址針對其物件下的hitrect進行碰撞判斷，以及後續遊戲邏輯更新處理。
```cpp=
void playground::enemy_update(float deltatime) {
    for (auto it = enemys.begin(); it != enemys.end(); ) {//遍歷指標
        Enemy* enemy = *it;
        enemy->kinetic(deltatime);
        for (auto bullet: bullets) {
            if(SDL_HasIntersection(bullet->rect, enemy->hitrect)//碰撞判斷
               && !enemy->destroyed) {
                enemy->hurted(bullet->att);// 敵人受傷
                bullet->destroyed = true; // 子彈消滅
                scoreboard.getLevel(1); // level增加
                enemy->animW->playSound(4);// 播放音效
                if (bullet->type == 'p') { // 子彈種類判斷
                    enemy->speed =BDSPEED+10; // 敵人中毒減速
                    if(enemy->type == 'B') { // 判斷是否為BOSS
                        enemy->speed = BDSPEED+120; //減速
                        SDL_Log("slow %d", enemy->speed);
                    }// nextpage
```
```cpp=

                }
            }
        }//這邊基本上和前面是相同的概念
        if(SDL_HasIntersection(enemy->hitrect, player->hitrect) 
           && !enemy->attacked && !enemy->destroyed) {
            scoreboard.getHurt(enemy->getAttack());
            enemy->attacked = true;
            player->animD->playSound(5);
            SDL_Log("Hurt");
        }
        int test = enemy->ifdied();
        //判斷敵人死亡並進行分數與獎勵計算
        if (enemy->destroyed && enemy->animD->finish) {
            enemy->destroy();
            if(test == 1 && enemy->dieANIMcount == 0) {
                scoreboard.getScore(enemy->getAttack());
                scoreboard.getNP(enemy->getAttack()/3+2);
                scoreboard.getLevel(enemy->getAttack());
                enemy->animD->finish = false;
                enemy->state = 'D';

                enemy->speed = BDSPEED;
                enemy->dieANIMcount++;//這是敵人死亡數的計數
                //可以用來後續判斷是否要生成新敵人

            }
            if(enemy->animD->finish) {//判斷敵人遭擊殺且死亡動畫播放完畢
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
```

#### 其他
其實還有很多內容，像是我的滾動背景設計，場景疊圖，物件碰撞程式(考量兩個rect重疊情況)，角色死亡時的動畫呈現和清除的順序也是我花很多時間修整的地方，但礙於篇幅，這邊就不多贅述。
(程式碼一樣都位於playground中)

<div style="page-break-after:always"></div>

## class Player & Bullet
接戲來就是遊戲的核心角色，我在設計上為了調用的方便，一樣幫只要是會渲染的物件添加move、kinetic、render，在playground中，這兩個式子會被添加到input_progress，update和render中，分別用來處理角色的速度方向控制、位移計算、畫面渲染，這部分的渲染會使用到我寫的Animation class，在動畫顯示上提供很大程度的自由性。
### 程式架構
```cpp=
//player.cpp
class Player {// 玩家 class
public:
    friend class playground; 
    Player(float x, float y, float width ,
           float height, float speed, SDL_Renderer* renderer
           ,float yMax=WINDOW_HEIGHT,float yMin=0);//建構子
    ~Player();//解構子
    void init(float x, float y); //初始化，其實沒用到 因為角色遊戲結束會刪除
    void render(SDL_Renderer* renderer); // 渲染
    void move(char dir); // 改變移動方向
    void kinetic(float dt); // 計算位置
    void changeArrow(char type); //改變弓箭
private:
    SDL_Rect *rect = nullptr;//圖片rect
    SDL_Rect *hitrect = nullptr;//碰撞rect
    const std::vector<std::string> Wimages = PLAYER_WALK_IMAGES;// 走路圖片路徑
    const std::vector<std::string> Simages = PLAYER_SHOOT_IMAGES;// 射擊圖片路徑
    const std::vector<std::string> Dimages = PLAYER_DIED_IMAGES;// 死亡圖片路徑
    Animation* animW = nullptr;//動畫
    Animation* animS = nullptr;//動畫
    Animation* animD = nullptr;//動畫
    float x, y, vx=100, vy=100;//位置和速度
    float speed;//速度
    float width;//寬度
    float height;//高度
    float yMax;//向下最大位置
    float yMin;//向上最大位置
    char direction = 's'; // 角色方向 有's'靜止'u'向上'd'向下
    char state = 'W'; // 角色狀態
    char type = 'N'; // 角色弓箭模式
};
```
#### 參數宣告
private主要是儲存player自己本身的動畫，碰撞位置、大小、方向等等，public主要為會被調用的函式，而將playgraound設為friend，讓其可以調用角色狀態，來判斷當前遊戲是否結束，還有scoreboard要如何顯示。

```cpp=
class Bullet {
    friend class Player;
    friend class playground;
public:
    Bullet(float posx, float posy, char type, SDL_Renderer* renderer);
    ~Bullet();
    void init(float x, float y);//初始化
    void render(SDL_Renderer* renderer);//渲染
    void kinetic(float dt);//計算位置
    void destroy();// 子彈銷毀
    void set_arrow(char t, SDL_Renderer* renderer); // 設定弓箭
private:
    Animation* anim = nullptr;//動畫
    float x, y;// 位置
    bool destroyed = false;//是否被摧毀
    int att = 1; // 攻擊力
    char type = 'N'; // 種類 有四種弓箭
    int np = 0;//消耗的np
    SDL_Rect *rect;//圖片、碰撞
    const std::vector<std::string> Nimages = ARROW_NORM;// 弓箭圖片 種類1
    const std::vector<std::string> Fimages = ARROW_FAST;// 2
    const std::vector<std::string> PNimages = ARROW_POISON;// 3
    const std::vector<std::string> PRimages = ARROW_POWER;// 4
    float vx=100, vy=100;// 速度
    float speed=BULLET_SPEED; // 子彈速度
    float width=40, height=40;// 大小
};
```
#### 參數宣告
private主要是儲存Bullet自己本身的動畫，碰撞位置、大小等等，public主要為會被調用的函式，將playgraound和player設為friend，讓其可以調用弓箭狀態，來判斷敵人的扣血狀態和碰撞情況，還有角色的NP扣取量。

#### 建構子
對player和bullet進行初始化，都要提供位置大小等參數和速度，以定位腳色於我們的畫面上，而bullet發射的判斷是依附於player身上的座標進行移動。

#### Player 的移動
Player的移動主要要考慮當前動畫的幀率，透過在engine寄宿的delta time 去計算我們真正的位移量是多少，在加回原本的位置，能達到較順暢的移動。
```cpp
void Player::move(char dir) {
    direction = dir;// 更改當前的方向
}
void Player::kinetic(float dt) {
    if(direction=='u') {
        y -= speed * vy/abs(vy)*dt;//考慮方向和deltatime
    }else if(direction=='d') {
        y += speed * vy/abs(vy)*dt;
    }
    if (y >= yMax-height) {//防止角色跑出陸地
        y = yMax-height;
    } else if (y <= yMin-height) {
        y = yMin-height;
    }
}
```
在engine有時間的計算:並且把未達到deltatime的時間用while迴圈補齊，以達到每一幀都能等速的目的，不至於畫面忽快忽慢。
```cpp=
while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
```


    
## tool.cpp中的其他class和模組
在我的分類中，除了遊戲角色外的特舒功能，我都歸類到tool.cpp和tool.h中，包含Animation、Scoreboard、GameRecorder、MusicPlayer、healthbar之類的，以及一些非class的工具函式，例如:loadTexture、enderProgressBar、createTextTexture、renderText，還有顏色常數宣告(雖然大部分都沒用到)
                               
```cpp=
                               
void renderProgressBar(int x, int y, int w, int h, int value, 
    int max_value,SDL_Color fgColor, SDL_Color bgColor, SDL_Renderer *renderer);

SDL_Texture* createTextTexture(const std::string& text, SDL_Color color,
               TTF_Font* font, SDL_Renderer* renderer);

void renderText(const std::string& text, int x, int y, SDL_Color color,
                TTF_Font* font, SDL_Renderer* renderer, char type); 
```
                               
例如這邊這邊的三個函式，主要都是在 tool 內部被調用，屬於最基層的工作函式，負責直接對介面或式檔案進行處理及渲染，邏輯的概念比較少。
                               
<div style="page-break-after:always"></div>

## Animation 
這是我寫得泛用性最廣的class，在整個程式裡，所有的動畫和音樂特效都是利用這個class進行操作的，基本上每個角色和敵人都有初始化自己的Animtion物件指標，用起來也很方便，還能彈性的調整動畫長度，算是我這裡面最得意的class之一。也是我花費很多時間進行編寫的成果。
### 程式架構
```cpp=
class Animation {
private:
    std::vector<SDL_Texture*> frames;// 用來儲存已經轉成texture的圖檔
    int currentFrameIndex = 0;// 當前的圖片id
    int frameMax = 0;//最大圖片數
    int timeCounter = 0; //計算每張圖的間隔時間
    Mix_Chunk* sound = nullptr;//引入音效
    void addAnimationFrame(const std::string& path, SDL_Renderer* renderer);
    //用來添加圖片
public:
    bool stop = false;//動畫是否暫停
    int updateTime = 0;//更新時間
    int finish = false;//動畫是否播完一輪了
    char id;// 動畫名稱
    void init(); // 動畫初始化
    void playSound(int channel); //播放音效
    Animation(char id, int updateTime, 
              const std::vector<std::string>& imagePaths,
              SDL_Renderer* renderer,const std::string& path="");//建構子
    SDL_Texture* getCurrentFrame();//讓外部獲取當前的動畫圖
    ~Animation();//解構子
    bool update(SDL_Renderer* renderer, SDL_Rect *rect);//更新動畫
};
```
### 參數宣告
pruvate將內建的時間計算、圖片列表、圖片讀取等包裝，使其不被外在class調用更改，同時public提供能夠調整更新時間、暫停動畫等等的參數，讓我們能對動畫的播放進行調整，像是弓箭在切換時射速改變，在player.cpp77行的change arrow就有使用updateTime的改變來讓快速弓箭發射變快。

### 圖片動畫處理
為了讓新增動畫時更方便，不需要考慮圖片數量都能製成動畫，這裡的圖片輸入我特別用vector來進行圖片路徑的讀取，這樣可以讓多張圖片被讀取並轉成SDL_Texture* 的形別，並存入我們的frames中，同時還能計算最大圖片數，以利後續的動畫處理。
```cpp=
void Animation::addAnimationFrame(const std::string &path,
                                  SDL_Renderer* renderer) {
    SDL_Texture* frame = loadTexture(path.c_str(), renderer);
    this->frames.push_back(frame);
    this->frameMax++;
}
```
載入圖片是用以下程式讀入: (加上SDL_Log()有助於圖片錯誤時進行debug) 
```cpp=
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
```
在建構式的地方將所有圖片讀入，以及讀入音訊:
```cpp=
Animation::Animation(char id,int t, 
                    const std::vector<std::string>& imagePaths,
                    SDL_Renderer* renderer, const std::string& soundPath){
    this->id = id;
    this->updateTime = t;
    this->finish = true;
    if(soundPath !="") {
        this->sound = Mix_LoadWAV(soundPath.c_str());
    }
    for (const std::string& path : imagePaths) {
        addAnimationFrame(path ,renderer);
    }//對圖片陣列遍歷並添加
}
```
在使用時，利用getCurrentFrame()抓取圖片並回傳，同時對圖片的counter進行更新，counter是根據我一開始初始化時給的updateTime來進行判斷，因此updateTime愈高，這動畫就會播放得越慢可以和幀率之間進行配合調整。
```cpp=
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
```
在我們的遊戲中，各個物件中都可以看到Animation的存在，從MENU的封面動畫到角色的射擊、移動、死亡動畫等等都是。只要呼叫 anim->update() 就能對rect的位置進行部分渲染。
```cpp=
bool Animation::update(SDL_Renderer* renderer, SDL_Rect *rect) {
    SDL_RenderCopy(renderer, getCurrentFrame(), nullptr, rect);
    return 0;
}
```

## Musicplayer
這個就比較簡單了，主要是用來處理背景音樂的程式，至於為甚麼音效和背景音樂要分開呢，主要是因為背景音樂讀入的是mp3檔案，而且使用背景音樂是不能進行混音的，他同時只能播放同一種音檔並循環播放，音次我將它和需要有即時性的音效分開，把音效加入Animation中配合動畫播出，而背景音樂主要在engine就被宣告，因為他是一個跨越頁面的音樂，需要考量到轉場間的音效不同。
而即時性的音效需要能夠堆疊混音，並且還要選擇分配channel，因此寫在Animation中，可以固定每個角色的channel。
### 程式架構
```cpp=
class MusicPlayer {
public:
    MusicPlayer(const std::vector<std::string>& Paths);
    void playMenu();//播主畫面聲音
    void playGamining(int type=1);//播遊戲場景聲音
    void playGameOver();//播遊戲結束聲音
    void stop();
    ~MusicPlayer();
private:
    Mix_Music *musicMenu = nullptr;//音檔
    Mix_Music *musicPlayground = nullptr;
    Mix_Music *musicPlayground2 = nullptr;
    Mix_Music *musicGameOver = nullptr;
    Mix_Chunk *bombsound = nullptr;
};
```
### 參數宣告
音檔都以指標型式儲存於class的private中，而會被外部調用的直接設為public

## healthBar
一個簡單的渲染功能，用來為敵人的血條分配大小與血量，並根據敵人當前血量反映出扣血的狀態，主要是由三個不同顏色的長方體堆疊渲染，行程外框底色以及血條，並控制血條部分的寬度。
### 程式架構
```cpp=
class healthBar {
public:
    healthBar(int max_hp,int w, int h, SDL_Renderer* renderer);
    void render(int x, int y,int width,  int health, SDL_Renderer* renderer);
private:
    int width, height;
    int max_health;
    SDL_Renderer *renderer;
};
```

## 報告後額外心得分享
我自己一直都是很喜歡寫遊戲的人，過去也寫過pygame、godot、unity和一些c\++的小遊戲，這次期末專題剛好能夠有機會自由發揮，並讓我對於 c\++程式更加熟悉，這次花了相當多的時間投入在遊戲製作上，再加上我們組員人數只有兩個，即使早早就開始進行程式編寫，也一直調適到期末前才完成，很高興最後能看到在報告時大家有熱烈的反饋，讓我成就感十足。不過這次有點感覺奇怪的是，評分標準給的蠻晚的，其實最後趕工的時間，很多都是為了把原本設計的程式修出符合分數要求的程式，變得有點心煩意亂，畢竟原本完成的程式，又要更改很多地方，或又出現原本沒有的報錯之類的，不過所幸最後也是順利的完成了。還有報告編寫好麻煩呵呵，比起寫遊戲，報告對我來說根本就是一大負擔，不過把它上傳到hackmd和github上後又是另一種心情了啦，這學期真的收穫很多在c、c++中的特殊用法，課程的內容是真的紮實，很慶幸自己能選上這堂課。
P.S. 希望期末報告能高分!
附上hackmd連結: https://hackmd.io/@B-m0H4fLQ6WdHC924pQUYw/rk3EBw_Skl
