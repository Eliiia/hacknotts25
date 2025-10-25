
/*

Card of some kind!!!

*/

typedef enum { 
    BASE_EDITION, 
    FOIL_EDITION, // playing card: +50 chips when scored 
                  // joker: +50 chips just before this joker is reached during scoring
    HOLOGRAPHIC_EDITION, // playing card: +10 mult value when scored
                         // joker: +10 mult value just before joker is reached during scoring
    POLYCHROME_EDITION, // playing card: 1.5x Mult
                        // joker: 1.5x Mult just before joker is reached during scoring 
    NEGATIVE_EDITION // playing card: N/A SHOULD NOT BE POSSIBLE
                     // joker: +1 joker slot
} EditionT;