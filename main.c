#include "game.h"

int main() {
    // Initialize random seed
    srand(time(NULL));
    
    // Run the main game loop with menu system
    run_game_loop();
    
    return 0;
}
