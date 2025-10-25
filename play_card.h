

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
} SuitT;

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
} RankT;

// enhancements,,,
typedef enum {
    NONE_ENHANCEMENT,
    BONUS,
    MULT,
    WILD,
    GLASS,
    STEEL,
    STONE,
    GOLD,
    LUCKY
} EnhancementT;

// seals,,,
typedef enum {
    NONE_SEAL,
    GOLD_SEAL,
    RED_SEAL,
    BLUE_SEAL,
    PURPLE_SEAL
} SealT;

// editions,,,
typedef enum {
    BASE_EDITION,
    FOIL_EDITION,
    HOLOGRAPHIC_EDITION,
    POLYCHROME_EDITION,
    NEGATIVE_EDITION
} EditionT;

// the actual card!!!
typedef struct {
    SuitT suit;
    RankT rank;
    EnhancementT enhancement;
    SealT seal;
    EditionT edition;
} PCardT;

// function for creating a playing card
PCardT pcard_create_play_card(SuitT suit, RankT rank, EnhancementT enhancement);

// function for determining whether card is a face card
bool pcard_is_face_card(PCardT card);

// function for determining chip value of card
int pcard_chip_value(PCardT card);

// function for determining mult value of card
int pcard_get_mult_value(PCardT card); // mult given on top
float pcard_get_mult_multiplier(PCardT card); // 

// function for cards to do with balance: cards can give money at end of game or when played
int get_balance_change_on_end(PCardT card);
int get_balance_change_on_play(PCardT card);