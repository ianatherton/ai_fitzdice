#include "game.h"

// Global dice cup (shared across all turns)
static DiceCup game_cup;
static int cup_initialized = 0;

int play_turn(int player_id) {
    int brains = 0;
    int shotguns = 0;
    int footsteps = 0;
    
    // Initialize cup on first use
    if (!cup_initialized) {
        init_dice_cup(&game_cup);
        cup_initialized = 1;
        printf("\n=== DICE CUP INITIALIZED ===\n");
        printf("Cup contains: %d Green, %d Yellow, %d Red dice\n", 
               TOTAL_GREEN_DICE, TOTAL_YELLOW_DICE, TOTAL_RED_DICE);
    }
    
    printf("\n%s's turn:\n", get_player_name(player_id));
    printf("Cup status: %d Green, %d Yellow, %d Red dice remaining\n",
           game_cup.green_dice, game_cup.yellow_dice, game_cup.red_dice);
    
    while (shotguns < 3) {
        // Draw 3 dice from the cup
        int drawn_dice[DICE_PER_ROLL];
        draw_dice_from_cup(&game_cup, drawn_dice);
        
        printf("\nDrew dice: ");
        for (int i = 0; i < DICE_PER_ROLL; i++) {
            printf("%s ", get_dice_color_name(drawn_dice[i]));
        }
        printf("\nRolling... ");
        
        int new_brains = 0;
        int new_shotguns = 0;
        int new_footsteps = 0;
        
        for (int i = 0; i < DICE_PER_ROLL; i++) {
            int face = roll_specific_die(drawn_dice[i]);
            printf("%s ", get_face_symbol(face));
            
            switch (face) {
                case BRAIN:
                    new_brains++;
                    break;
                case SHOTGUN:
                    new_shotguns++;
                    break;
                case FOOTSTEPS:
                    new_footsteps++;
                    break;
            }
        }
        
        brains += new_brains;
        shotguns += new_shotguns;
        footsteps += new_footsteps;
        
        printf("\n");
        printf("This roll: Brains: %d, Shotguns: %d, Footsteps: %d\n", 
               new_brains, new_shotguns, new_footsteps);
        printf("Total: Brains: %d, Shotguns: %d, Footsteps: %d\n", 
               brains, shotguns, footsteps);
        
        // Check if busted (3 shotguns)
        if (shotguns >= 3) {
            printf("%s got 3 shotguns and is BUSTED! No points this turn.\n", 
                   get_player_name(player_id));
            return 0;
        }
        
        // Check if player should stop based on brains collected
        if (should_stop(brains, player_id)) {
            printf("%s stops rolling with %d brains (stopping point: %d brains)\n", 
                   get_player_name(player_id), brains, PLAYER_AGGRESSIVENESS[player_id]);
            break;
        }
        
        // Player can also choose to stop if they have 1 or 2 shotguns (risk management)
        if (shotguns > 0) {
            printf("%s has %d shotgun(s) but continues rolling (needs %d brains to stop)\n",
                   get_player_name(player_id), shotguns, PLAYER_AGGRESSIVENESS[player_id]);
        }
    }
    
    printf("%s scores %d brains this turn!\n", get_player_name(player_id), brains);
    return brains;
}
