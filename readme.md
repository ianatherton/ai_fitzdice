### Zombie Dice Simulator ###

This is a simulator for the board game "Zombie Dice". It can simulate a number of games with a given number of players of a given strategy.

### work notes / ideas / plans ###

Player profiles: could be a struct with name, score, turn state, strategy(stopping_point ie after how many shotguns to stop + considering footstep dice difficulty(this is the important decision moment))

*player number will be assigned automatically with initialization*

typedef struct 
{
    char name[MAX_NAME_LENGTH]
    int turn_order;
    int score;
}player_t;

struct Game
{
    float game_number; *could use float to track game/turn_number*
}

player_t for players[player_count];

bool playerAdamStrategy(int)

### Game Rules ###

13 dice and a cup
2 or more can play
On your turn, shake the cup, draw 3 dice without looking and roll them. Each one is a human victim. The red dice are the toughest. Green are easiest, and yellow are medium tough.


The dice have 3 symbols:
*Brain* - you ate your victims brain. Set your brain dice ot your left.

*Shotgun* - they fought back! Set your shotgun dice to your right.

*Footprints* - they escaped. Keep your feet dice in front of you. If you 
choose to roll again, you will re-roll these along with enough new ones to bring the total to 3.

*green dice* [brain, brain, brain, footstep, footstep, shotgun]
*yellow dice* [brain, brain, footstep, footstep, shotgun, shotgun]
*red dice* [brain, footstep, footstep, shotgun, shotgun, shotgun]

If you rolled 3 shotguns, your turn is over. Otherwise, you can choose to stop and score, or continue.

If you decice to STOP, score 1 for each Brain you have, and put all the dice back into the cup.

If you choose to KEEP GOING, leave all your footsteps dice on the table. Unless all three of your dice are footprints, take enough random new dice from the cup to total 3, and roll again. Whenever you roll, you will roll 3 dice at a time.

After you take new dice, you can't decide to stop...you have to roll. Set aside Brains and Shotguns as above. If you are up to 3 shotguns, your turn is over and you score nothing.

13 dice are used; 6 green (easy), 4 yellow (medium), and 3 red (hard).
easy_dice["Brain", "Brain", "Brain", "Footsteps", "Footsteps", "Shotgun"]

### Random Numbers ###

We need: Dice roll 1-6, Cup draw 1-13, 