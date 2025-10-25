#include <stdio.h>
#include "hand_calc.h"
#include "poker_hand.h"
#include "game_state.h"
#include "card.h"
#include "play_card.h"

int main() {
    PokerHandTableState hand_table_state = DEFAULT_POKER_HAND_STATE;

    // PokerHand poker_hand = get_poker_hand_state(hand_type.hand_type, hand_table_state);

    /* int base_chips = poker_hand.chips;
    int base_mult = poker_hand_type_multiplier(hand_type.hand_type);
    for (int i = 0; i < hand_type.num_cards; i++) {
        base_chips += pcard_chip_value(hand_type.cards[i]);
    }

    int total_value = base_chips * base_mult;
    printf("Total Poker Hand Value: %d\n", total_value); */

    PCard card1 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, EditionT = BASE_EDITION};
    PCard card2 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, EditionT = BASE_EDITION};
    printf("Card 1 Chip Value: %d\n", pcard_chip_value(&card1));
    printf("Card 2 Chip Value: %d\n", pcard_chip_value(&card2));

    return 0;
}