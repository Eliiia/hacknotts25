#include "game_state.h"

GameState* game_state_initialise_new_game() {
    GameState* state = (GameState*) malloc(sizeof(GameState));

    state->round_number = 1;
    state->ante_number = 1;
    state->round.hands = 0;
    state->round.discards = 0;
    state->round.score = 0;
    state->round.required_score = 300; // ante 1 round 1 default

    state->player_deck = player_deck_initialise_new_deck();

    return state;
}

void game_state_start_new_round(GameState* state) {
    state->round_number += 1;
    // state->ante_number .......
    state->round.hands = 0;
    state->round.discards = 0;
    state->round.score = 0;
    state->round.required_score = 300 + (state->round_number * 150);
}

void game_state_free_game(GameState* state) {
    free(state->player_deck);
    free(state);
}