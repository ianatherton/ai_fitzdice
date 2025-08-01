#ifndef GAME_H
#define GAME_H

#include "constants.h"

// Function declarations
int play_turn(int player_id);
void get_player_settings();
void play_game(int scores[]);
void print_game_results(int scores[]);
int find_winner(int scores[]);

#endif // GAME_H
