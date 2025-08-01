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

// Game Logic Functions
int roll_die() {
    // Use the green dice distribution by default (can be modified later for different difficulty levels)
    return GREEN_DICE_FACES[rand() % 6];
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
