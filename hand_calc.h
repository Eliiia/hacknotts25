#ifndef POKER_HAND_H
#include "poker_hand.h"
#define POKER_HAND_H
#endif 
#ifndef PLAY_CARD_H
#include "play_card.h"
#define PLAY_CARD_H
#endif

/*
whenever a hand is calculated, the general steps we take are:
1. Get the type of the hand
2. Get the default chips and mult for the hand
3. Figure it out what cards are being played
4. For each card (if retrigger, repeat that amount of times for that card):
    - Get chip value (...etc)
    - Get mult value (...etc)
    - Apply enhancements, seals, editions as needed
    - Call all jokers' "each card" function
5. For each unplayed card:
    - Call all of their functions based on "if held in hand" status
6. Calculate the final hand value based on all the above
7. Call all jokers' "end of hand" function
8. Destroy any cards that need destroying
*/

// calculating total value with given playing cards
// the main function of this!!!!!
int calculate_poker_hand_value(PCard** played_cards, int num_played_cards, PokerHandTableState* hand_table_state);

// get the PokerHand struct from the state table; for the specific hand type (see state table)
PokerHand get_poker_hand_state(PokerHandType hand_type, PokerHandTableState* hand_table_state);

// struct for returning evaluate_poker_hand_type
typedef struct {
    PokerHandType hand_type;
    PCard* cards[5]; // max 5 cards in a poker hand
    int num_cards; // number of cards which are RELEVANT to the hand
} PokerHandEvaluation;
// determine which poker hand type is present in the played cards
PokerHandEvaluation evaluate_poker_hand_type(PCard** played_cards, int num_played_cards);

// functions to check for specific hand types based on played cards
bool hand_is_flush_five(PCard** played_cards, int num_played_cards);
bool hand_is_flush_house(PCard** played_cards, int num_played_cards);
bool hand_is_five_of_a_kind(PCard** played_cards, int num_played_cards);
bool hand_is_royal_flush(PCard** played_cards, int num_played_cards);
bool hand_is_straight_flush(PCard** played_cards, int num_played_cards);
bool hand_is_four_of_a_kind(PCard** played_cards, int num_played_cards);
bool hand_is_full_house(PCard** played_cards, int num_played_cards);
bool hand_is_flush(PCard** played_cards, int num_played_cards);
bool hand_is_straight(PCard** played_cards, int num_played_cards);
bool hand_is_three_of_a_kind(PCard** played_cards, int num_played_cards);
bool hand_is_two_pair(PCard** played_cards, int num_played_cards);
bool hand_is_one_pair(PCard** played_cards, int num_played_cards);