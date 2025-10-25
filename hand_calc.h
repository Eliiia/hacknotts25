#ifndef POKER_HAND_H
#include "poker_hand.h"
#define POKER_HAND_H
#endif 
#include "play_card.h"

/*
whenever a hand is calculated, we:
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

// todo write this comment lol
PokerHand get_poker_hand_state(PokerHandType hand_type, PokerHandTableState* hand_table_state);

// determine which poker hand type is present in the played cards
typedef struct {
    PokerHandType hand_type;
    PCard** cards[5]; // max 5 cards in a poker hand
    int num_cards; // number of cards which are RELEVANT to the hand
} PokerHandEvaluation;
PokerHandEvaluation evaluate_poker_hand_type(PCard** played_cards, int num_played_cards);

// functions to check for specific hand types
bool hand_is_flush_five(int num_played_cards, PCard** played_cards);
bool hand_is_flush_house(int num_played_cards, PCard** played_cards);
bool hand_is_five_of_a_kind(int num_played_cards, PCard** played_cards);
bool hand_is_full_house(int num_played_cards, PCard** played_cards);
bool hand_is_straight_flush(int num_played_cards, PCard** played_cards);
bool hand_is_four_of_a_kind(int num_played_cards, PCard** played_cards);
bool hand_is_three_of_a_kind(int num_played_cards, PCard** played_cards);
bool hand_is_one_pair(int num_played_cards, PCard** played_cards);
bool hand_is_two_pair(int num_played_cards, PCard** played_cards);
bool hand_is_flush(int num_played_cards, PCard** played_cards);
bool hand_is_straight(int num_played_cards, PCard** played_cards);
