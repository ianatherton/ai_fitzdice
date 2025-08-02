#include "constants.h"

// Dice probability distributions (out of 6 faces per die)
// Green (Easy): More brains, fewer shotguns
const int GREEN_DICE_FACES[6] = {BRAIN, BRAIN, BRAIN, SHOTGUN, FOOTSTEPS, FOOTSTEPS};
// Yellow (Medium): Balanced distribution
const int YELLOW_DICE_FACES[6] = {BRAIN, BRAIN, SHOTGUN, SHOTGUN, FOOTSTEPS, FOOTSTEPS};
// Red (Hard): More shotguns, fewer brains
const int RED_DICE_FACES[6] = {BRAIN, SHOTGUN, SHOTGUN, SHOTGUN, FOOTSTEPS, FOOTSTEPS};

// Array of dice face arrays for easy access
const int* DICE_DISTRIBUTIONS[3] = {GREEN_DICE_FACES, YELLOW_DICE_FACES, RED_DICE_FACES};

// Player names for output
const char* PLAYER_NAMES[NUM_PLAYERS] = {"Alice", "Bob", "Charlie"};

// Player aggressiveness settings (defined in gamerunner.c)

// Dice face symbols for display
const char* FACE_SYMBOLS[3] = {"🧠", "💥", "👣"};
const char* FACE_NAMES[3] = {"Brain", "Shotgun", "Footsteps"};

// Utility function to get player name
const char* get_player_name(int player_id) {
    if (player_id >= 0 && player_id < NUM_PLAYERS) {
        return PLAYER_NAMES[player_id];
    }
    return "Unknown";
}

// Utility function to get face symbol
const char* get_face_symbol(int face) {
    if (face >= 0 && face < 3) {
        return FACE_SYMBOLS[face];
    }
    return "?";
}

// Utility function to get face name
const char* get_face_name(int face) {
    if (face >= 0 && face < 3) {
        return FACE_NAMES[face];
    }
    return "Unknown";
}

// Utility function to get dice color name
const char* get_dice_color_name(int dice_color) {
    switch (dice_color) {
        case GREEN_EASY: return "Green";
        case YELLOW_MEDIUM: return "Yellow";
        case RED_HARD: return "Red";
        default: return "Unknown";
    }
}

// Dice Cup Functions
void init_dice_cup(DiceCup* cup) {
    cup->green_dice = TOTAL_GREEN_DICE;
    cup->yellow_dice = TOTAL_YELLOW_DICE;
    cup->red_dice = TOTAL_RED_DICE;
}

void refill_dice_cup(DiceCup* cup) {
    cup->green_dice = TOTAL_GREEN_DICE;
    cup->yellow_dice = TOTAL_YELLOW_DICE;
    cup->red_dice = TOTAL_RED_DICE;
}

int get_total_dice_in_cup(const DiceCup* cup) {
    return cup->green_dice + cup->yellow_dice + cup->red_dice;
}

int draw_dice_from_cup(DiceCup* cup, int drawn_dice[DICE_PER_ROLL]) {
    // Check if we need to refill the cup
    if (get_total_dice_in_cup(cup) < DICE_PER_ROLL) {
        printf("Cup is running low, refilling...\n");
        refill_dice_cup(cup);
    }
    
    // Create array of available dice types
    int available_dice[TOTAL_DICE];
    int dice_count = 0;
    
    // Add green dice to available pool
    for (int i = 0; i < cup->green_dice; i++) {
        available_dice[dice_count++] = GREEN_EASY;
    }
    
    // Add yellow dice to available pool
    for (int i = 0; i < cup->yellow_dice; i++) {
        available_dice[dice_count++] = YELLOW_MEDIUM;
    }
    
    // Add red dice to available pool
    for (int i = 0; i < cup->red_dice; i++) {
        available_dice[dice_count++] = RED_HARD;
    }
    
    // Draw 3 dice randomly
    for (int i = 0; i < DICE_PER_ROLL; i++) {
        int random_index = rand() % dice_count;
        int selected_dice = available_dice[random_index];
        drawn_dice[i] = selected_dice;
        
        // Remove the selected die from the cup
        switch (selected_dice) {
            case GREEN_EASY:
                cup->green_dice--;
                break;
            case YELLOW_MEDIUM:
                cup->yellow_dice--;
                break;
            case RED_HARD:
                cup->red_dice--;
                break;
        }
        
        // Remove the selected die from available array
        for (int j = random_index; j < dice_count - 1; j++) {
            available_dice[j] = available_dice[j + 1];
        }
        dice_count--;
    }
    
    return DICE_PER_ROLL;
}

// Game Logic Functions
int roll_die() {
    // Use the green dice distribution by default (for backward compatibility)
    return GREEN_DICE_FACES[rand() % 6];
}

int roll_specific_die(int dice_color) {
    const int* dice_faces;
    
    switch (dice_color) {
        case GREEN_EASY:
            dice_faces = GREEN_DICE_FACES;
            break;
        case YELLOW_MEDIUM:
            dice_faces = YELLOW_DICE_FACES;
            break;
        case RED_HARD:
            dice_faces = RED_DICE_FACES;
            break;
        default:
            dice_faces = GREEN_DICE_FACES; // Default to green
            break;
    }
    
    return dice_faces[rand() % 6];
}

int is_busted(int shotguns) {
    return shotguns >= 3;
}

int should_stop(int brains, int player_id) {
    if (player_id >= 0 && player_id < NUM_PLAYERS) {
        return brains >= PLAYER_AGGRESSIVENESS[player_id];
    }
    return 1; // Default to stopping if invalid player_id
}

int has_won(int score) {
    return score >= WINNING_SCORE;
}
