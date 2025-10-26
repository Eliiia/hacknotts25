#include "round_state.h"
#include "player_deck.h"

/*

core gameplay loop:

- round_state_initialise_new_round_state
- one of the following, whatever user selects:
    - round_state_play_hand
    - round_state_play_discard
- repeat this loop until one of the following: draw pile empty, score reached required score, hand value is 0
- round_state_end_round
- put round_number up AND re-shuffle decks

mvp: just round play with fixed ante and hand size

*/

typedef struct {
    int round_number;
    int ante_number;
    RoundState round;
    PlayerDeck* player_deck;
} GameState;

GameState* game_state_initialise_new_game();

void game_state_start_new_round(GameState* state);

void game_state_free_game(GameState* state);