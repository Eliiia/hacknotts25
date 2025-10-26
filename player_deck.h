#include <stdlib.h>

#ifndef PLAY_CARD_H
#include "play_card.h"
#define PLAY_CARD_H
#endif

// structure to hold all cards
// NEED to have a draw pile and a discard pile, maybe a function to shuffle them back in together
// remember: if draw pile runs out, game over
// remember: need to be able to implement screen that shows what cards are available: need functions to see how much of each type of card is avaiable

// use static array!!!
// stretch goal: dynamic array that can grow/shrink as needed so that can implement tarot/etc

typedef struct  {
    // dynamic arrays for piles (allocated in initialise)
    PCard** draw_pile; // pointer to array of PCard* (max 52)
    int draw_pile_size;
    PCard** discard_pile; // pointer to array of PCard* (max 52)
    int discard_pile_size;
} PlayerDeck;

PlayerDeck* player_deck_initialise_new_deck();

void player_deck_shuffle_draw_pile(PlayerDeck* deck);

void player_deck_free_deck(PlayerDeck* deck);

int random_num(int upto);