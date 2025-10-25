#include "hand_calc.h"

// calculating total value with given playing cards
// the main function of this!!!!!
int calculate_poker_hand_value(PCard** played_cards, int num_played_cards, PokerHandTableState* hand_table_state) {
    PokerHandEvaluation hand_type = evaluate_poker_hand(played_cards, num_played_cards);
    
    // TODO calculate value based on hand type and cards involved

    /*for(int i = 0; i < hand_type.num_cards; i++) {
                value += hand_type.cards[i]->chip_value;
            }*/

    PokerHand poker_hand = get_poker_hand_state(hand_type.hand_type, hand_table_state);

    int base_chips = poker_hand.chips;
    int base_mult = poker_hand_type_multiplier(hand_type.hand_type);

    for (int i = 0; i < hand_type.num_cards; i++) {
        base_chips += pcard_chip_value(hand_type.cards[i]);
        base_mult += pcard_get_mult_value_when_scored(hand_type.cards[i]);
        base_mult *= pcard_get_mult_multiplier_when_scored(hand_type.cards[i]);
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
        case FLUSH_FIVE: return hand_table_state->flush_five;
        case FLUSH_HOUSE: return hand_table_state->flush_house;
        case FIVE_OF_A_KIND: return hand_table_state->five_of_a_kind;
        default: return hand_table_state->high_card;
    }
}

// determine which poker hand type is present in the played cards
// TODO CONSIDER we also need to return the cards themselves that make up the hand
typedef struct {
    PokerHandType hand_type;
    PCard* cards[5]; // max 5 cards in a poker hand
    int num_cards; // number of cards which are RELEVANT to the hand
} PokerHandEvaluation;

PokerHandEvaluation evaluate_poker_hand(PCard** played_cards, int num_played_cards) {
    PokerHandEvaluation evaluation;

    // do we have the basic ones, that we can use to construct the rest?
    // store the specific examples for later use
    // assign NULL if not
    // TODO this should not necessarily assume 5 cards for straight/flush
    PCard* contains_flush[5]; // assume must be 5
    PCard* contains_straight[5]; // assume must be 5
    PCard* contains_pair[2];
    PCard* contains_two_pair[4]; // NOTE this MUST also detect four of a kind and five of a kind
    PCard* contains_three_of_a_kind[3];

    bool all_same_rank = true;
    bool all_same_suit = true;

    // assign them
    for (int i = 0; i < 4; i++) {
        if (contains_two_pair[i]->rank != contains_two_pair[0]->rank) {
            all_same_rank = false;
            
        }
        if (contains_flush[i]->suit != contains_flush[0]->suit) {
            all_same_suit = false;
        }
    }

    // Check for flush five
    if (all_same_rank && all_same_suit) {
        evaluation.hand_type = FLUSH_FIVE;
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = contains_flush[i];
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for flush house
    if (contains_flush && contains_three_of_a_kind && contains_two_pair) {
        evaluation.hand_type = FLUSH_HOUSE;
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = contains_flush[i];
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for five of a kind
    if (num_played_cards == 5 && all_same_rank) {
        evaluation.hand_type = FIVE_OF_A_KIND;
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for straight flush
    if (contains_straight && contains_flush) {
        evaluation.hand_type = STRAIGHT_FLUSH;
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = contains_straight[i];
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for four of a kind
    if (contains_two_pair && all_same_rank) {
        // contains_two_pair will be triggered for two_pair
        evaluation.hand_type = FOUR_OF_A_KIND;
        for (int i = 0; i < 4; i++) {
            evaluation.cards[i] = contains_two_pair[i];
        }
        evaluation.num_cards = 4;
        return evaluation;
    }
    // Check for full house using contains_three_of_a_kind and contains_two_pair
    if (contains_three_of_a_kind && contains_two_pair) {
        evaluation.hand_type = FULL_HOUSE;
        for (int i = 0; i < 3; i++) {
            evaluation.cards[i] = contains_three_of_a_kind[i];
        }
        for (int i = 0; i < 4; i++) {
            // add only the pair cards that aren't already in the three of a kind
            bool is_in_three_of_a_kind = false;
            for (int j = 0; j < 3; j++) {
                if (contains_two_pair[i]->rank == contains_three_of_a_kind[j]->rank) {
                    is_in_three_of_a_kind = true;
                }
            }
            if (!is_in_three_of_a_kind) {
                evaluation.cards[3] = contains_two_pair[i];
                evaluation.cards[4] = contains_two_pair[
                    i == 0 ? 1 : // if i is 0, get 1; it is the first of first pair 
                        i == 1 ? 0 : // if i is 1, get 0; it is the second of first pair
                            i == 2 ? 3 : // if i is 2, get 3; it is the first of second pair
                                4 // else here means i is 3, so get 4; it is the second of second pair
                ]; // get the other card of the pair
                break;
            }
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for flush using contains_flush
    if (contains_flush) {
        evaluation.hand_type = FLUSH;
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = contains_flush[i];
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for straight using contains_straight
    if (contains_straight) {
        evaluation.hand_type = STRAIGHT;
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = contains_straight[i];
        }
        evaluation.num_cards = 5;
        return evaluation;
    }
    // Check for three of a kind using contains_three_of_a_kind
    if (contains_three_of_a_kind) {
        evaluation.hand_type = ONE_PAIR;
        evaluation.cards[0] = contains_pair[0];
        evaluation.cards[1] = contains_pair[1];
        evaluation.num_cards = 2;
        return evaluation;
    }
    // Check for two pair using contains_two_pair
    if (contains_two_pair) {
        evaluation.hand_type = ONE_PAIR;
        evaluation.cards[0] = contains_pair[0];
        evaluation.cards[1] = contains_pair[1];
        evaluation.num_cards = 2;
        return evaluation;
    }
    // Check for one pair using contains_pair
    if (contains_pair) {
        evaluation.hand_type = ONE_PAIR;
        evaluation.cards[0] = contains_pair[0];
        evaluation.cards[1] = contains_pair[1];
        evaluation.num_cards = 2;
        return evaluation;
    }

    // If nothing found, default to high card
    evaluation.hand_type = HIGH_CARD;
    // TODO find highest card

    // return
    return evaluation;
}

// Below are stub implementations for hand type checks

bool hand_is_flush_five(int num_played_cards, PCard** played_cards) {
    // detect both a flush and five of a kind
    return hand_is_flush(num_played_cards, played_cards) && hand_is_five_of_a_kind(num_played_cards, played_cards);
}
bool hand_is_flush_house(int num_played_cards, PCard** played_cards) {
    // detect both a full house and a flush
    return hand_is_full_house(num_played_cards, played_cards) && hand_is_flush(num_played_cards, played_cards);
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
bool hand_is_full_house(int num_played_cards, PCard** played_cards) {
    // detect both a two pair and a three of a kind
    return hand_is_two_pair(num_played_cards, played_cards) && hand_is_three_of_a_kind(num_played_cards, played_cards);
    
}
bool hand_is_straight_flush(int num_played_cards, PCard** played_cards) {
    return hand_is_flush(num_played_cards, played_cards) && hand_is_straight(num_played_cards, played_cards);
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
bool hand_is_three_of_a_kind(int num_played_cards, PCard** played_cards) {
    if (num_played_cards < 3) {
        return false; // can't be three of a kind if less than 3 cards
    }

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
bool hand_is_one_pair(int num_played_cards, PCard** played_cards) {
    // one pair is just a two of a kind

    if (num_played_cards < 2) {
        return false; // can't be one pair if less than 2 cards
    }

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 2 occurrences
    for (int i = 0; i < 13; i++) {
        if (rank_counts[i] >= 2) {
            return true;
        }
    }
    return false;
}
bool hand_is_two_pair(int num_played_cards, PCard** played_cards) {
    // two of a kind (one pair) but,,, twice!!!
    if (num_played_cards < 4) {
        return false; // can't be two pair if less than 4 cards
    }

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
bool hand_is_flush(int num_played_cards, PCard** played_cards) {
    // TODO MAYBE REMOVE THIS BIT:
    if (num_played_cards < 5) {
        return false; // can't be flush if less than 5 cards
    }

    bool all_same_suit = true; // assume until found counterexample
    for (int i = 1; i < num_played_cards; i++)
    {
        if (played_cards[i]->suit != played_cards[0]->suit)
        {
            all_same_suit = false; // found counterexample
            break;
        }
        else
        {
            all_same_suit = true;
        }
    }
    return all_same_suit;
}
bool hand_is_straight(int num_played_cards, PCard** played_cards) {
    // TODO MAYBE REMOVE THIS BIT:
    if (num_played_cards < 5) {
        return false; // can't be straight if less than 5 cards
    }

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

// TODO 4-card flush/straight joker
// current impl of stuff assumes 4 card flushes/straights arent possible
// this includes flush/straight detection, re-ordering of cards in case of flush/straight, 

// TODO current impl doesn't account for stone cards

// TODO evaluate_poker_hand is so incredibly janky pls fix