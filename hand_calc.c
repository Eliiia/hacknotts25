#include "hand_calc.h"
#include <stdlib.h>
#include <stdio.h>

// calculating total value with given playing cards
// the main function of this!!!!!
int calculate_poker_hand_value(PCard** played_cards, int num_played_cards, PokerHandTableState* hand_table_state) {
    PokerHandEvaluation played_hand_evaluated = evaluate_poker_hand_type(played_cards, num_played_cards);

    PokerHand poker_hand = get_poker_hand_state(played_hand_evaluated.hand_type, hand_table_state);

    int base_chips = poker_hand.chips;
    int base_mult = poker_hand.mult;

    for (int i = 0; i < played_hand_evaluated.num_cards; i++) {
        base_chips += pcard_chip_value(played_hand_evaluated.cards[i]);
        base_mult += pcard_get_mult_value_when_scored(played_hand_evaluated.cards[i]);
        base_mult *= pcard_get_mult_multiplier_when_scored(played_hand_evaluated.cards[i]);
    }
    
    int total_value = base_chips * base_mult;
}

PokerHand get_poker_hand_state(PokerHandType hand_type, PokerHandTableState* hand_table_state) {
    // map poker hand enum to struct
    switch(hand_type) {
        case HIGH_CARD: return hand_table_state->high_card;
        case ONE_PAIR: return hand_table_state->one_pair;
        case TWO_PAIR: return hand_table_state->two_pair;
        case THREE_OF_A_KIND: return hand_table_state->three_of_a_kind;
        case STRAIGHT: return hand_table_state->straight;
        case FLUSH: return hand_table_state->flush;
        case FULL_HOUSE: return hand_table_state->full_house;
        case FOUR_OF_A_KIND: return hand_table_state->four_of_a_kind;
        case STRAIGHT_FLUSH: return hand_table_state->straight_flush;
        case FIVE_OF_A_KIND: return hand_table_state->five_of_a_kind;
        case FLUSH_HOUSE: return hand_table_state->flush_house;
        case FLUSH_FIVE: return hand_table_state->flush_five;
        default: return hand_table_state->high_card;
    }
}

bool hand_is_flush(int num_played_cards, PCard** played_cards) {
    // TODO MAYBE REMOVE THIS BIT:
    if (num_played_cards < 5) {
        return false; // can't be flush if less than 5 cards
    }

    bool all_same_suit = true; // assume until found counterexample
    for (int i = 1; i < num_played_cards; i++) {
        if (played_cards[i]->suit != played_cards[0]->suit) {
            all_same_suit = false; // found counterexample
            break;
        } else {
            all_same_suit = true;
        }
    }
    return all_same_suit;
}

bool hand_is_five_of_a_kind(int num_played_cards, PCard** played_cards) {
    if (num_played_cards < 5) {
        return false; // can't be five of a kind if less than 5 cards
    }

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 5 occurrences
    for (int i = 0; i < 13; i++) {
        if (rank_counts[i] >= 5) {
            return true;
        }
    }
    return false;
}

bool hand_is_three_of_a_kind(int num_played_cards, PCard** played_cards) {
    if (num_played_cards < 3) return false; // can't be three of a kind if less than 3 cards

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 3 occurrences
    for (int i = 0; i < 13; i++) {
        if (rank_counts[i] >= 3) {
            return true;
        }
    }
    return false;
}

bool hand_is_two_pair(int num_played_cards, PCard** played_cards) {
    if (num_played_cards < 4) return false; // can't be two pair if less than 4 cards

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check for two pairs
    int pair_count = 0;
    for (int i = 0; i < 13; i++) {
        if (rank_counts[i] >= 2) {
            pair_count++;
        }
    }
    return pair_count >= 2;
}

bool hand_is_straight(int num_played_cards, PCard** played_cards) {
    if (num_played_cards < 5) return false; // can't be straight if less than 5 cards

    // loop through first 4 (played_cards-1) cards
    // check if each card's rank + 1 == another card's rank
    for (int i = 0; i < (num_played_cards - 1); i++) {
        bool found_next_rank = false;
        for (int j = 0; j < num_played_cards; j++) {
            if (j == i) { continue; } // skip self
            else if (played_cards[j]->rank == played_cards[i]->rank + 1) {
                found_next_rank = true;
                break;
            }
        }
        if (!found_next_rank) {
            // if we haven't been able to find a card that would go after played_cards[i], this isn't a straight
            return false;
        }
    }
    return true;
}

bool hand_is_four_of_a_kind(int num_played_cards, PCard** played_cards) {
    if (num_played_cards < 4) {
        return false; // can't be four of a kind if less than 4 cards
    }

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 4 occurrences
    for (int i = 0; i < 13; i++) {
        if (rank_counts[i] >= 4) {
            return true;
        }
    }
    return false;
}

PokerHandEvaluation evaluate_poker_hand_type(PCard** played_cards, int num_played_cards) {
    // Check if flush five = flush && five of a kind
    if (hand_is_flush(num_played_cards, played_cards) && hand_is_five_of_a_kind(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FLUSH_FIVE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if flush house = flush && full house
    if (hand_is_flush(num_played_cards, played_cards) && hand_is_full_house(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FLUSH_HOUSE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if five of a kind
    if (hand_is_five_of_a_kind(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FIVE_OF_A_KIND, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
    }

    // Check if full house = two pair && three of a kind
    if (hand_is_two_pair(num_played_cards, played_cards) && hand_is_three_of_a_kind(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FULL_HOUSE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if straight flush = straight && flush
    if (hand_is_straight(num_played_cards, played_cards) && hand_is_flush(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = STRAIGHT_FLUSH, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if four of a kind
    if (hand_is_four_of_a_kind(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FOUR_OF_A_KIND, .num_cards = 4};
        // pick only matching cards
        for (int i = 0; i < num_played_cards; i++) {
            // implement picking only the four matching cards
            for (int j = 0; j < num_played_cards; j++) {
                if (i != j && played_cards[i]->rank == played_cards[j]->rank) {
                    evaluation.cards[i] = played_cards[i];
                }
            }
        }
        return evaluation;
    }

    // Check if full house = two pair && three of a kind
    if (hand_is_two_pair(num_played_cards, played_cards) && hand_is_three_of_a_kind(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FULL_HOUSE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if flush
    if (hand_is_flush(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FLUSH, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if straight
    if (hand_is_straight(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = STRAIGHT, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if three of a kind
    if (hand_is_three_of_a_kind(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = THREE_OF_A_KIND, .num_cards = 3};
        // pick only matching cards
        for (int i = 0; i < num_played_cards; i++) {
            // implement picking only the three matching cards
            for (int j = 0; j < num_played_cards; j++) {
                if (i != j && played_cards[i]->rank == played_cards[j]->rank) {
                    evaluation.cards[i] = played_cards[i];
                }
            }
        }
    }

    // Check if two pair
    if (hand_is_two_pair(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = TWO_PAIR, .num_cards = 4};
        // pick only matching cards
        int pair_index = 0;
        for (int i = 0; i < num_played_cards; i++) {
            // implement picking only the two pairs
            for (int j = 0; j < num_played_cards; j++) {
                if (i != j && played_cards[i]->rank == played_cards[j]->rank) {
                    evaluation.cards[pair_index++] = played_cards[i];
                }
            }
        }
        return evaluation;
    }

    // Check if one pair
    if (hand_is_one_pair(num_played_cards, played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = ONE_PAIR, .num_cards = 2};
        // pick only matching cards
        for (int i = 0; i < num_played_cards; i++) {
            // implement picking only the pair
            for (int j = 0; j < num_played_cards; j++) {
                if (i != j && played_cards[i]->rank == played_cards[j]->rank) {
                    evaluation.cards[0] = played_cards[i];
                    evaluation.cards[1] = played_cards[j];
                }
            }
        }
        return evaluation;
    }

    // Default: high card
    PokerHandEvaluation evaluation = {.hand_type = HIGH_CARD, .num_cards = 1};
    // find highest card
    PCard* highest_card = played_cards[0];
    for (int i = 1; i < num_played_cards; i++) {
        if (played_cards[i]->rank > highest_card->rank) {
            highest_card = played_cards[i];
        }
    }
    evaluation.cards[0] = highest_card;
    return evaluation;
}
