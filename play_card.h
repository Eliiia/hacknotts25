#include <stdbool.h>

#include "card.h"

/*

playing card from the deck, based on balatro deck

*/

// suit,,,
typedef enum {
    NONE_SUIT,
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

// rank,,,
typedef enum {
    NONE_RANK,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 10,
    QUEEN = 10,
    KING = 10,
    ACE = 11
} Rank;

// enhancements,,,
typedef enum {
    NONE_ENHANCEMENT,
    BONUS, // additional 30 chips when scored
    MULT, // +4 mult value
    WILD, // can be used as any suit
    GLASS, // x2 mult when scored, BUT 1 in 4 chance to destroy card
    STEEL, // x1.5 mult while held in hand
    STONE, // 50 chip value but no rank or suit; ALWAYS SCORES even when not played!!!
    GOLD, // $3 if held in hand at end of round
    LUCKY // 1 in 5 chance of +20 Mult, 1 in 15 chance to give $20 (rolled separately)
} Enhancement;

// seals,,,
typedef enum {
    NONE_SEAL, 
    GOLD_SEAL, // $3 when played and scored
    RED_SEAL, // retrigger 1 time, incl joker ability
    BLUE_SEAL, // creates last played planet card
    PURPLE_SEAL // creates tarot card when this card is discarded
} Seal;

// editions are in card.h

// the actual card!!!
typedef struct {
    Suit suit;
    Rank rank;
    Enhancement enhancement;
    Seal seal;
    EditionT edition;
} PCard;

// function for creating a playing card
PCard* pcard_create_play_card(Suit suit, Rank rank, Enhancement enhancement, Seal seal, EditionT edition);

// function for determining whether card is a face card
bool pcard_is_face_card(PCard* card);

// function for determining chip value of card
int pcard_chip_value(PCard* card);

// function for determining mult value of card
int pcard_get_mult_value(PCard* card); // mult given on top
double pcard_get_mult_multiplier_when_scored(PCard* card);
double pcard_get_mult_multiplier_when_held(PCard* card);

// function for cards to do with balance: cards can give money at end of game or when played
int pcard_get_balance_change_on_end(PCard* card);
int pcard_get_balance_change_on_play(PCard* card);

// function for checking retrigger
bool pcard_has_retrigger(PCard* card); // only when red seal

// function for checking if card is destroyed
bool pcard_is_destroyed_after_scoring(PCard* card); // by chance, only when glass
