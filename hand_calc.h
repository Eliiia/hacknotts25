#include "poker_hand.h"
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
int calculate_poker_hand_value(PCard **played_cards, int num_played_cards);

// determine which poker hand type is present in the played cards
PokerHandType determine_poker_hand_type(PCard** played_cards, int num_played_cards);
