typedef enum {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    FIVE_OF_A_KIND,
    FLUSH_HOUSE,
    FLUSH_FIVE
} PokerHandType;

typedef struct {
    PokerHandType type;
    int chips;
    int mult;
    int level;
    int uses;
} PokerHand;

/* State container for each poker hand type */
typedef struct {
    PokerHand high_card;
    PokerHand one_pair;
    PokerHand two_pair;
    PokerHand three_of_a_kind;
    PokerHand straight;
    PokerHand flush;
    PokerHand full_house;
    PokerHand four_of_a_kind;
    PokerHand straight_flush;
    PokerHand five_of_a_kind;
    PokerHand flush_house;
    PokerHand flush_five;
} PokerHandTableState;

typedef enum {
    PLUTO_CARD,
    MERCURY_CARD,
    URANUS_CARD,
    VENUS_CARD,
    SATURN_CARD,
    JUPITER_CARD,
    EARTH_CARD,
    MARS_CARD,
    NEPTUNE_CARD,
    PLANET_X_CARD,
    CERES_CARD,
    ERIS_CARD
} PlanetCard;

void poker_hand_table_apply_planet_card(PokerHandTableState* state, PlanetCard planet_card);

/* default table:
   pokerhand      chip mult #lvl #uses
   Straight Flush  100   x8    1     0
   Four of a Kind   60   x7    1     0
   Full House       40   x4    1     1
   Flush            35   x4    1     1
   Straight         30   x4    1     0
   Three of a Kind  30   x3    1     0
   Two Pair         20   x2    1     0
   Pair             10   x2    1     0
   High Card         5   x1    1     0
*/
static const PokerHandTableState DEFAULT_POKER_HAND_STATE = {
    .high_card       = { HIGH_CARD,         5, 1, 1, 0 },
    .one_pair        = { ONE_PAIR,         10, 2, 1, 0 },
    .two_pair        = { TWO_PAIR,         20, 2, 1, 0 },
    .three_of_a_kind = { THREE_OF_A_KIND,  30, 3, 1, 0 },
    .straight        = { STRAIGHT,         30, 4, 1, 0 },
    .flush           = { FLUSH,            35, 4, 1, 0 },
    .full_house      = { FULL_HOUSE,       40, 4, 1, 0 },
    .four_of_a_kind  = { FOUR_OF_A_KIND,   60, 7, 1, 0 },
    .straight_flush  = { STRAIGHT_FLUSH,  100, 8, 1, 0 },
    .five_of_a_kind  = { FIVE_OF_A_KIND,  120, 12, 1, 0 },
    .flush_house     = { FLUSH_HOUSE,     140, 14, 1, 0 },
    .flush_five      = { FLUSH_FIVE,      160, 16, 1, 0 }
};

// TODO
// get chips, get mult functions
// increase level function