#include "game.h"

int play_turn(int player_id) {
    int brains = 0;
    int shotguns = 0;
    int footsteps = 0;
    
    printf("\n%s's turn:\n", get_player_name(player_id));
    
    while (shotguns < 3) {
        // Always roll exactly 3 dice
        printf("Rolling 3 dice... ");
        
        int new_brains = 0;
        int new_shotguns = 0;
        int new_footsteps = 0;
        
        for (int i = 0; i < 3; i++) {
            int face = roll_die();
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
