#include "play_card.h"

// function for creating a playing card
PCard* pcard_create_play_card(Suit suit, Rank rank, Enhancement enhancement, Seal seal, EditionT edition) {
    PCard* card = (PCard *) malloc(sizeof(PCard));

    card->suit = suit;
    card->rank = rank;
    card->enhancement = enhancement;
    card->seal = seal;
    card->edition = edition;
    
    return card;
}

// function for determining whether card is a face card
bool pcard_is_face_card(PCard* card) {
    return (card->rank == JACK || card->rank == QUEEN || card->rank == KING);
}

// function for determining chip value of card
int pcard_chip_value(PCard* card) {
    if (card->enhancement == STONE) {
        return 50;
    }
    else {
        assert(card->rank != NONE_RANK); // only way this is possible is if card is stone
        return card->rank;
    }
}

// function for determining mult value of card
int pcard_get_mult_value_when_scored(PCard* card) {
    int mult_value = 0;
    if (card->enhancement == MULT) {
        mult_value += 4;
    } else if (card->enhancement == LUCKY) {
        // 1 in 5 chance of adding 20
        int chance = rand() % 5;
        if (chance == 0) {
            mult_value += 20;
        }
    }

    if (card->edition == HOLOGRAPHIC_EDITION) {
        mult_value += 10; // holographic edition gives +10 mult value when scored
    }

    return mult_value;
}

double pcard_get_mult_multiplier_when_scored(PCard* card) {
    double mult_multiplier = 1.0;

    if (card->enhancement == GLASS) {
        mult_multiplier *=2.0; // glass doubles mult when scored
    } 
    if (card->edition == POLYCHROME_EDITION) {
        mult_multiplier *= 1.5; // polychrome edition gives 1.5x mult when scored
    }

    return mult_multiplier;
} // + steel; if held in hand

double pcard_get_mult_multiplier_when_held(PCard* card) {
    if (card->enhancement == STEEL) {
        return 1.5;
    }
    else {
        return 1.0;
    }
}

// function for cards to do with balance: cards can give money at end of game or when played
int pcard_get_balance_change_on_end(PCard* card) {
    if (card->enhancement == GOLD) {
        return 3; // gold gives $3 at end of round
    }
    else {
        return 0;
    }
}
int pcard_get_balance_change_on_play(PCard* card) {
    if (card->seal == GOLD_SEAL) {
        return 3; // gold seal gives $3 when played and scored
    }
    else {
        return 0;
    }
}

// function for checking retrigger
bool pcard_has_retrigger(PCard* card) {
    // only on red seal
    return (card->seal == RED_SEAL);
}

// function for checking if card is destroyed
bool pcard_is_destroyed_after_scoring(PCard* card); {
    if (card->enhancement == GLASS) {
        // 1 in 4 chance of being destroyed
        int chance = rand() % 4;
        return (chance == 0);
    }
    else {
        return false;
    }
}