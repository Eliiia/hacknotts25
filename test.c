#include <stdio.h>
#include <assert.h>

#include "hand_calc.h" 
#include "game_state.h"
#include "player_deck.h"

void test_flush_five();
void test_flush_house();
void test_five_of_a_kind();
void test_royal_flush();
void test_straight_flush();
void test_four_of_a_kind();
void test_full_house();
void test_full_house_2();
void test_flush();
void test_straight();
void test_three_of_a_kind();
void test_two_pair();
void test_two_pair_2();
void test_one_pair();
void test_one_pair_2();


int main() {
    PokerHandTableState hand_table_state = DEFAULT_POKER_HAND_STATE;

    // test card hand evaluations
    test_flush_five();
    test_flush_house();
    test_five_of_a_kind();
    test_royal_flush();
    test_straight_flush();
    test_four_of_a_kind();
    test_full_house();
    test_full_house_2();
    test_flush();
    test_straight();
    test_three_of_a_kind();
    test_two_pair();
    test_two_pair_2();
    test_one_pair();
    test_one_pair_2();

    // generate random deck and print values of cards
    PlayerDeck* deck = player_deck_initialise_new_deck();
    
    for (int i = 0; i < deck->draw_pile_size; i++) {
        PCard* card = deck->draw_pile[i];
        printf("Card %d\tRank %d\tSuit %d\tEnhancement %d\tSeal %d\tEdition %d\n", 
            i+1, card->rank, card->suit, card->enhancement, card->seal, card->edition);
    }

    return 0;
}

void test_flush_five() {

    PCard card1 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FLUSH_FIVE);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_flush_house(){
    PCard card6 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card7 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card8 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card9 = {.rank = QUEEN, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card10 = {.rank = QUEEN, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card6, &card7, &card8, &card9, &card10};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FLUSH_HOUSE); 
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }   
}

void test_five_of_a_kind() {
    PCard card1 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = ACE, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = ACE, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FIVE_OF_A_KIND);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_royal_flush() {
    PCard card1 = {.rank = TEN, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = JACK, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = QUEEN, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = KING, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = ACE, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == ROYAL_FLUSH);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_straight_flush() {
    PCard card1 = {.rank = NINE, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = TEN, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = JACK, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = QUEEN, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = KING, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == STRAIGHT_FLUSH);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_four_of_a_kind() {
    PCard card1 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = ACE, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = ACE, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FOUR_OF_A_KIND);
    assert(evaluation.num_cards == 4);
    for (int i = 0; i < 4; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_full_house() {
    PCard card1 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = KING, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = KING, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = QUEEN, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = QUEEN, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FULL_HOUSE);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_full_house_2() {
    PCard card1 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = QUEEN, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = KING, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = KING, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = QUEEN, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FULL_HOUSE);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_flush() {
    PCard card1 = {.rank = TWO, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = FIVE, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = NINE, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = JACK, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = KING, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == FLUSH);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_straight() {
    PCard card1 = {.rank = FOUR, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = FIVE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = SIX, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = SEVEN, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = EIGHT, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == STRAIGHT);
    assert(evaluation.num_cards == 5);
    for (int i = 0; i < 5; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_three_of_a_kind() {
    PCard card1 = {.rank = KING, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = ACE, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[4] = {&card1, &card2, &card3, &card4};
    int num_played_cards = 4;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == THREE_OF_A_KIND);
    assert(evaluation.num_cards == 3);
    for (int i = 0; i < 3; i++) {
        assert(evaluation.cards[i]->rank == played_cards[i+1]->rank);
    }
}

void test_two_pair() {
    PCard card1 = {.rank = KING, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = QUEEN, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = QUEEN, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = JACK, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == TWO_PAIR);
    assert(evaluation.num_cards == 4);
    for (int i = 0; i < 4; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_two_pair_2() {
    PCard card1 = {.rank = KING, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = QUEEN, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = KING, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card5 = {.rank = JACK, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = QUEEN, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[5] = {&card1, &card2, &card3, &card4, &card5};
    int num_played_cards = 5;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == TWO_PAIR);
    assert(evaluation.num_cards == 4);
    for (int i = 0; i < 4; i++) {
        assert(evaluation.cards[i] == played_cards[i]);
    }
}

void test_one_pair() {
    PCard card1 = {.rank = KING, .suit = CLUBS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card4 = {.rank = QUEEN, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[4] = {&card1, &card2, &card3, &card4};
    int num_played_cards = 4;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == ONE_PAIR);
    assert(evaluation.num_cards == 2);
    for (int i = 0; i < 2; i++) {
        assert(evaluation.cards[i] == played_cards[i + 1]); 
    }
}

void test_one_pair_2() {
    PCard card1 = {.rank = ACE, .suit = SPADES, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card2 = {.rank = QUEEN, .suit = DIAMONDS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};
    PCard card3 = {.rank = ACE, .suit = HEARTS, .enhancement = NONE_ENHANCEMENT, .seal = NONE_SEAL, .edition = BASE_EDITION};

    PCard* played_cards[3] = {&card1, &card2, &card3};
    int num_played_cards = 3;

    PokerHandEvaluation evaluation = evaluate_poker_hand_type(played_cards, num_played_cards);
    assert(evaluation.hand_type == ONE_PAIR);
    assert(evaluation.num_cards == 2);
    assert(evaluation.cards[0] == played_cards[0]);
    assert(evaluation.cards[1] == played_cards[2]);
}
