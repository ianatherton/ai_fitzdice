#include "game.h"

// Define the global player aggressiveness array
int PLAYER_AGGRESSIVENESS[NUM_PLAYERS] = {3, 5, 7};

void get_player_settings() {
    printf("=== ZDICE PLAYER SETUP ===\n");
    printf("Enter the brain stopping point for each player (1-10):\n");
    printf("(Higher numbers = more aggressive play)\n\n");
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        int stopping_point;
        do {
            printf("Enter stopping point for %s: ", get_player_name(i));
            if (scanf("%d", &stopping_point) != 1) {
                // Clear invalid input
                while (getchar() != '\n');
                printf("Invalid input! Please enter a number.\n");
                stopping_point = 0; // Force retry
            } else if (stopping_point < 1 || stopping_point > 10) {
                printf("Please enter a number between 1 and 10.\n");
            }
        } while (stopping_point < 1 || stopping_point > 10);
        
        PLAYER_AGGRESSIVENESS[i] = stopping_point;
    }
    
    printf("\nPlayer settings confirmed:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("- %s will stop at %d brains\n", 
               get_player_name(i), PLAYER_AGGRESSIVENESS[i]);
    }
    printf("\n");
}

void play_game(int scores[]) {
    // Initialize scores
    for (int i = 0; i < NUM_PLAYERS; i++) {
        scores[i] = 0;
    }
    
    printf("=== ZDICE SIMULATION ===\n");
    printf("Players: ");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%s (stops at %d brains)%s", 
               get_player_name(i), 
               PLAYER_AGGRESSIVENESS[i],
               i < NUM_PLAYERS - 1 ? ", " : "\n");
    }
    printf("First to %d brains wins!\n", WINNING_SCORE);
    
    int turn = 0;
    while (turn < MAX_TURNS) {
        printf("\n--- Turn %d ---\n", turn + 1);
        
        for (int player = 0; player < NUM_PLAYERS; player++) {
            // Skip if player already won
            if (has_won(scores[player])) {
                continue;
            }
            
            int turn_score = play_turn(player);
            scores[player] += turn_score;
            
            printf("Total score for %s: %d\n", 
                   get_player_name(player), scores[player]);
            
            // Check for winner
            if (has_won(scores[player])) {
                printf("\n🎉 %s WINS with %d brains! 🎉\n", 
                       get_player_name(player), scores[player]);
                return;
            }
        }
        
        turn++;
    }
    
    printf("\nGame ended after %d turns (max limit reached)\n", MAX_TURNS);
}

void print_game_results(int scores[]) {
    int winner = find_winner(scores);
    
    printf("\n=== FINAL RESULTS ===\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%s: %d brains%s\n", 
               get_player_name(i), 
               scores[i],
               i == winner ? " 🏆 WINNER!" : "");
    }
}

int find_winner(int scores[]) {
    int winner = 0;
    int max_score = scores[0];
    
    for (int i = 1; i < NUM_PLAYERS; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
            winner = i;
        }
    }
    
    return winner;
}

int show_menu() {
    int choice;
    
    printf("\n" COLOR_CYAN COLOR_BOLD "=== GAME MENU ===" COLOR_RESET "\n");
    printf("1. " COLOR_GREEN "Play Again" COLOR_RESET "\n");
    printf("2. " COLOR_YELLOW "Change Strategy" COLOR_RESET " (reset player settings)\n");
    printf("3. " COLOR_RED "Exit" COLOR_RESET "\n");
    printf("\nEnter your choice (1-3): ");
    
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        // Clear invalid input
        while (getchar() != '\n');
        printf("Invalid choice! Please enter 1, 2, or 3: ");
    }
    
    return choice;
}

void run_game_loop() {
    int continue_playing = 1;
    int settings_initialized = 0;
    
    printf(COLOR_BOLD COLOR_CYAN "Welcome to ZDICE - Zombie Dice Simulator!" COLOR_RESET "\n\n");
    
    while (continue_playing) {
        // Get player settings if not initialized or if user chose to change strategy
        if (!settings_initialized) {
            get_player_settings();
            settings_initialized = 1;
        }
        
        // Game state
        int scores[NUM_PLAYERS];
        
        // Play one complete game
        play_game(scores);
        
        // Display final results
        print_game_results(scores);
        
        // Show menu and handle user choice
        int choice = show_menu();
        
        switch (choice) {
            case MENU_PLAY_AGAIN:
                printf("\n" COLOR_GREEN "Starting new game with same settings..." COLOR_RESET "\n");
                break;
            case MENU_CHANGE_STRATEGY:
                printf("\n" COLOR_YELLOW "Resetting player settings..." COLOR_RESET "\n");
                settings_initialized = 0;
                break;
            case MENU_EXIT:
                printf("\n" COLOR_CYAN "Thanks for playing ZDICE!" COLOR_RESET "\n");
                continue_playing = 0;
                break;
        }
    }
}
