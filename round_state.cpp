#include "round_state.h"
#include "poker_hand.h"
#include <vector>

// new round state
RoundState round_state_initialise_new_round_state(PlayerDeck* player_deck, PokerHandTableState* hand_table_state, int round_number) {
    RoundState state;
    state.hands = 0;
    state.discards = 0;
    state.score = 0;
    state.required_score = 300 + (round_number - 1) * 150; 
    state.player_deck = player_deck;
    state.hand_table_state = hand_table_state;
    return state;
}

// play hand
void round_state_play_hand(RoundState* state, PCard** hand_played, int num_cards) {
    // Sanity check: player has hands available
    assert(state->hands > 0); // can't play hand if none available
    state->hands--;

    // Evaluate hand
    int hand_value = calculate_poker_hand_value(hand_played, num_cards, &DEFAULT_POKER_HAND_STATE);
}

// play discard
void round_state_play_discard(RoundState* state, PCard** discard_played, int num_cards) {
    assert(state->discards > 0); // can't play discard if none available
    state->discards = state->discards - 1;

    for(int i; i < num_cards; i++) {
        
    }
}

// end round
void round_state_end_round(RoundState* state) {
    free(state);
}