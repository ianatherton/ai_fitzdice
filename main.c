#include "game.h"

int main() {
    // Initialize random seed
    srand(time(NULL));
    
    // Game state
    int scores[NUM_PLAYERS];
    
    // Get player settings
    get_player_settings();
    
    // Play one complete game
    play_game(scores);
    
    // Display final results
    print_game_results(scores);
    
    return 0;
}
