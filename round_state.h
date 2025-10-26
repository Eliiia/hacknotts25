#include "player_deck.h"
#include <vector>

/* 

struct representing the state of a round 

these go in the game state TODO:
- round numbr and ante 

*/

// The state of a round in the game!!!
typedef struct {
    int hands;
    int discards;
    int score;
    int required_score; // e.g. 300 for ante 1 round 1
    vector<PCard*> player_hand;
    PlayerDeck* player_deck;
    PokerHandTableState* hand_table_state;
} RoundState;

// new round state
RoundState round_state_initialise_new_round_state(PlayerDeck* player_deck, int round_number);

// play hand
void round_state_play_hand(RoundState* state, PCard** hand_played, int num_cards);

// play discard
void round_state_play_discard(RoundState* state, PCard** discard_played, int num_cards);

// end round
void round_state_end_round(RoundState* state);