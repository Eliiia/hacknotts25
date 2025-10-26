#include "player_deck.h"

PlayerDeck* player_deck_initialise_new_deck() {
    PlayerDeck* deck = (PlayerDeck*) malloc(sizeof(PlayerDeck));

    deck->draw_pile = (PCard**) malloc(sizeof(PCard*) * 52);
    deck->discard_pile = (PCard**) malloc(sizeof(PCard*) * 52);

    // generate all the cards,, yay,,,
    for (int i = 0; i < 14; i++) { // loop through ranks
        for (int j = 0; j < 4; j++) { // loop through suits
            // use bases, unless...
            Enhancement enhancement = NONE_ENHANCEMENT;
            Seal seal = NONE_SEAL;
            EditionT edition = BASE_EDITION;
            // ...the randomiser works
            if (random_num(100) < 20) { // 20% chance of enhancement
                int enh_index = random_num(7); // 0-7
                enhancement = (Enhancement) enh_index;
            }
            if (random_num(100) < 5) { // 5% chance of seal
                int seal_index = random_num(3) + 1; // 1-4
                seal = (Seal) seal_index;
            }
            if (random_num(100) < 5) { // 5% chance of edition
                int edition_index = random_num(3) + 1; // 1-4
                edition = (EditionT) edition_index;
            }

            // create card
            PCard* card = pcard_create_play_card((Suit) j, (Rank) i, enhancement, seal, edition);
            deck->draw_pile[i * 4 + j] = card;
        }
    }

    deck->draw_pile_size = 52;
    deck->discard_pile_size = 0;

    return deck;
}

void player_deck_shuffle_draw_pile(PlayerDeck* deck) {
    for (int i = deck->draw_pile_size - 1; i > 0; i--) {
        int j = random_num(i); // random index from 0 to i
        // swap deck->draw_pile[i] and deck->draw_pile[j]
        PCard* temp = deck->draw_pile[i];
        deck->draw_pile[i] = deck->draw_pile[j];
        deck->draw_pile[j] = temp;
    }
}

void player_deck_free_deck(PlayerDeck* deck) {
    free(deck->draw_pile);
    free(deck->discard_pile);
    free(deck);
}

int random_num(int upto) {
    // output random number between 0 and upto inclusive
    return rand() % (upto + 1);
}