#include <iostream>
#include "SDL.h"
#include "SDL_lib/graphics.h"
#include "SDL_lib/SDL_bgi.h"
#include "include/engine.h"
// #include "include/test.h"


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