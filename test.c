#include <stdio.h>
#include <assert.h>

#include "hand_calc.h" 
#include "game_state.h"

int main() {
    PokerHandTableState hand_table_state = DEFAULT_POKER_HAND_STATE;

    PCard card1 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FLUSH_FIVE);

    // Test for flush house 
    PCard card6 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card7 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card8 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card9 = {.rank = QUEEN, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card10 = {.rank = QUEEN, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards2[5] = {&card6, &card7, &card8, &card9, &card10};
    num_played_cards = 5;

    evaluation = evaluate_poker_hand_type(played_cards2, num_played_cards);
    assert(evaluation.hand_type == FLUSH_HOUSE);

    return 0;
}