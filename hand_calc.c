#include "hand_calc.h"
#include <stdlib.h>
#include <stdio.h>

// calculating total value with given playing cards
// the main function of this!!!!!
int calculate_poker_hand_value(PCard** played_cards, int num_played_cards, PokerHandTableState* hand_table_state) {
    PokerHandEvaluation played_hand_evaluated = evaluate_poker_hand_type(played_cards, num_played_cards);

    PokerHand poker_hand = get_poker_hand_state(played_hand_evaluated.hand_type, hand_table_state);

    // Get default chips and mult for the poker hand, from the table
    int base_chips = poker_hand.chips;
    int base_mult = poker_hand.mult;

    // For each card in the evaluated hand, add chip value and mult value/mult multiplier
    for (int i = 0; i < played_hand_evaluated.num_cards; i++) {
        base_chips += pcard_chip_value(played_hand_evaluated.cards[i]);
        base_mult += pcard_get_mult_value_when_scored(played_hand_evaluated.cards[i]);
        base_mult *= pcard_get_mult_multiplier_when_scored(played_hand_evaluated.cards[i]);
    }

    // TODO joker logic if we want to add that later
    
    return base_chips * base_mult;
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
        case ROYAL_FLUSH: return hand_table_state->royal_flush;
        case FIVE_OF_A_KIND: return hand_table_state->five_of_a_kind;
        case FLUSH_HOUSE: return hand_table_state->flush_house;
        case FLUSH_FIVE: return hand_table_state->flush_five;
        default: return hand_table_state->high_card;
    }
}

bool hand_is_flush(PCard** played_cards, int num_played_cards) {
    if (num_played_cards != 5) {
        return false; // can't be flush if not exactly 5 cards
    }
    // check whether all cards have same suit
    for (int i = 1; i < num_played_cards; i++) {
        if (played_cards[0]->suit != played_cards[i]->suit) {
            return false; // found countexample
        }
    }
    return true;
}
bool hand_is_five_of_a_kind(PCard** played_cards, int num_played_cards) {
    if (num_played_cards != 5) {
        return false; // can't be five of a kind if not exactly 5 cards
    }

    // check whether all cards have same rank
    for (int i = 1; i < num_played_cards; i++) {
        if (played_cards[0]->rank != played_cards[i]->rank) {
            return false;
        }
    }
    return true;
}
bool hand_is_three_of_a_kind(PCard** played_cards, int num_played_cards) {
    if (num_played_cards < 3) return false; // can't be three of a kind if less than 3 cards

    // count occurrences of each rank
    int rank_counts[14] = {0}; // 14 ranks in the deck; NONE, 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 3 occurrences
    for (int i = 0; i < 14; i++) {
        if (rank_counts[i] >= 3) {
            return true;
        }
    }
    return false;
}
bool hand_is_two_pair(PCard** played_cards, int num_played_cards) {
    if (num_played_cards < 4) return false; // can't be two pair if less than 4 cards

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check for two pairs
    int pair_count = 0;
    for (int i = 0; i < 14; i++) {
        if (rank_counts[i] >= 2) {
            pair_count++;
        }
    }
    return pair_count >= 2;
}
bool hand_is_straight(PCard** played_cards, int num_played_cards) {
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
bool hand_is_four_of_a_kind(PCard** played_cards, int num_played_cards) {
    if (num_played_cards != 4 && num_played_cards != 5) {
        return false; // can't be four of a kind if not exactly 4 or 5 cards
    }

    // count occurrences of each rank
    int rank_counts[14] = {0}; // 14 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 4 occurrences
    for (int i = 0; i < 14; i++) {
        if (rank_counts[i] >= 4) {
            return true;
        }
    }
    return false;
}
bool hand_is_full_house(PCard** played_cards, int num_played_cards) {
    return num_played_cards == 5 
        && hand_is_two_pair(played_cards, num_played_cards) 
        && hand_is_three_of_a_kind(played_cards, num_played_cards);
}
bool hand_is_one_pair(PCard** played_cards, int num_played_cards) {
    if (num_played_cards < 2) return false; // can't be one pair if less than 2 cards

    // count occurrences of each rank
    int rank_counts[13] = {0}; // 13 ranks in the deck; 2-10, J, Q, K, A
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++;
    }

    // check if any rank has 2 occurrences
    for (int i = 0; i < 14; i++) {
        if (rank_counts[i] >= 2) {
            return true;
        }
    }
    return false;
}
bool hand_is_royal_flush(PCard** played_cards, int num_played_cards) {
    if (num_played_cards != 5) {
        return false; // can't be royal flush if not exactly 5 cards
    }

    // Check if all cards are same suit
    if (!hand_is_flush(played_cards, num_played_cards)) {
        return false;
    }

    // Check for TEN, JACK, QUEEN, KING, ACE
    bool has_ten = false;
    bool has_jack = false;
    bool has_queen = false;
    bool has_king = false;
    bool has_ace = false;

    for (int i = 0; i < num_played_cards; i++) {
        switch (played_cards[i]->rank) {
            case TEN:
                has_ten = true;
                break;
            case JACK:
                has_jack = true;
                break;
            case QUEEN:
                has_queen = true;
                break;
            case KING:
                has_king = true;
                break;
            case ACE:
                has_ace = true;
                break;
            default:
                break;
        }
    }

    return has_ten && has_jack && has_queen && has_king && has_ace;
}


PokerHandEvaluation evaluate_poker_hand_type(PCard** played_cards, int num_played_cards) {
    // rank frequency scan
    int rank_counts[14] = {0};
    for (int i = 0; i < num_played_cards; i++) {
        rank_counts[played_cards[i]->rank]++; // ->rank goes from 0 to 13
    }

    // Check if flush five; flush && five of a kind
    if (hand_is_flush(played_cards, num_played_cards) && hand_is_five_of_a_kind(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FLUSH_FIVE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
            
        }
        return evaluation;
    }

    // Check if flush house; flush && full house
    if (hand_is_flush(played_cards, num_played_cards) && hand_is_full_house(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FLUSH_HOUSE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if five of a kind
    if (hand_is_five_of_a_kind(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FIVE_OF_A_KIND, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    if (hand_is_royal_flush(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = ROYAL_FLUSH, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if full house
    if (hand_is_full_house(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FULL_HOUSE, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if straight flush = straight && flush
    if (hand_is_straight(played_cards, num_played_cards) && hand_is_flush(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = STRAIGHT_FLUSH, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if four of a kind
    if (hand_is_four_of_a_kind(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FOUR_OF_A_KIND, .num_cards = 4};
        
        // loop through rank counter and find something with 4 occurences
        for (int rank = 0; rank < 15; rank++) {
            if (rank_counts[rank] >= 4) {
                // pick the 4 cards with this rank
                int card_index = 0;
                for (int i = 0; i < num_played_cards; i++) {
                    if (played_cards[i]->rank == rank) {
                        evaluation.cards[card_index++] = played_cards[i];
                        if (card_index == 4) break; // got all 4 cards
                    }
                }
                break; // found the rank with 4 occurences, no need to check further
            }
        }

        return evaluation;
    }

    // Check if full house = two pair && three of a kind
    if (hand_is_two_pair(played_cards, num_played_cards) && hand_is_three_of_a_kind(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = TWO_PAIR, .num_cards = 4};
        
        // loop through rank counter and find something with 4 occurences
        int rank1_chosen;
        int card_index = 0;
        for (int rank = 0; rank < 15; rank++) {
            if (rank_counts[rank] >= 2) {
                // pick the 2 cards with this rank
                rank1_chosen = rank;
                for (int i = 0; i < num_played_cards; i++) {
                    if (played_cards[i]->rank == rank) {
                        evaluation.cards[card_index++] = played_cards[i];
                        if (card_index == 2) break; // got both cards
                    }
                }
                break; // found the rank with 4 occurences, no need to check further
            }
        }
        // do the same thing again, but with a different rank
        // note that card_index was not reset, so we continue from where we left off in the index
        for (int rank = 0; rank < 15; rank++) {
            if (rank_counts[rank] >= 2 && rank != rank1_chosen) {
                // pick the 2 cards with this rank
                rank1_chosen = rank;
                for (int i = 0; i < num_played_cards; i++) {
                    if (played_cards[i]->rank == rank) {
                        evaluation.cards[card_index++] = played_cards[i];
                        if (card_index == 4) break; // got all 4 cards now
                    }
                }
                break; // found the rank with 4 occurences, no need to check further
            }
        }

        return evaluation;
    }

    // Check if flush
    if (hand_is_flush(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = FLUSH, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if straight
    if (hand_is_straight(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = STRAIGHT, .num_cards = 5};
        for (int i = 0; i < 5; i++) {
            evaluation.cards[i] = played_cards[i];
        }
        return evaluation;
    }

    // Check if three of a kind
    if (hand_is_three_of_a_kind(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = THREE_OF_A_KIND, .num_cards = 3};

        // loop through rank counter and find something with 3 occurences
        for (int rank = 0; rank < 15; rank++) {
            if (rank_counts[rank] >= 3) {
                // pick the 3 cards with this rank
                int card_index = 0;
                for (int i = 0; i < num_played_cards; i++) {
                    if (played_cards[i]->rank == rank) {
                        evaluation.cards[card_index++] = played_cards[i];
                        if (card_index == 3) break; // got all 3 cards
                    }
                }
                break; // found the rank with 3 occurences, no need to check further
            }
        }

        return evaluation;

    }

    // Check if two pair
    if (hand_is_two_pair(played_cards, num_played_cards)) {
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
    if (hand_is_one_pair(played_cards, num_played_cards)) {
        PokerHandEvaluation evaluation = {.hand_type = ONE_PAIR, .num_cards = 2};

        // note here: this does not find optimal one pair if multiple exist; just finds first it sees

        // loop through rank counter and find something with 2 occurences
        for (int rank = 0; rank < 15; rank++) {
            if (rank_counts[rank] >= 2) {
                // pick the 2 cards with this rank
                int card_index = 0;
                for (int i = 0; i < num_played_cards; i++) {
                    if (played_cards[i]->rank == rank) {
                        evaluation.cards[card_index++] = played_cards[i];
                        if (card_index == 2) break; // got all 2 cards
                    }
                }
                break; // found the rank with 2 occurences, no need to check further
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
