#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Game Constants
#define NUM_PLAYERS 3
#define DICE_PER_ROLL 3
#define WINNING_SCORE 13
#define MAX_TURNS 100

// Dice Face Types
#define BRAIN 0
#define SHOTGUN 1
#define FOOTSTEPS 2

// Dice Colors/Difficulties
#define GREEN_EASY 0
#define YELLOW_MEDIUM 1
#define RED_HARD 2

// Dice probability distributions (out of 6 faces per die)
// Green (Easy): More brains, fewer shotguns
extern const int GREEN_DICE_FACES[6];
// Yellow (Medium): Balanced distribution
extern const int YELLOW_DICE_FACES[6];
// Red (Hard): More shotguns, fewer brains
extern const int RED_DICE_FACES[6];

// Array of dice face arrays for easy access
extern const int* DICE_DISTRIBUTIONS[3];

// Player names for output
extern const char* PLAYER_NAMES[NUM_PLAYERS];

// Player aggressiveness settings (shared between files)
extern int PLAYER_AGGRESSIVENESS[NUM_PLAYERS];

// Dice face symbols for display
extern const char* FACE_SYMBOLS[3];
extern const char* FACE_NAMES[3];

// Function declarations (implementations moved to appropriate .c files)
int roll_die();
int is_busted(int shotguns);
int should_stop(int brains, int player_id);
int has_won(int score);
const char* get_player_name(int player_id);
const char* get_face_symbol(int face);
const char* get_face_name(int face);

#endif // CONSTANTS_H
