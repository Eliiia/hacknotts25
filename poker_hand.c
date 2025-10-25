#ifndef POKER_HAND_H
#include "poker_hand.h"
#define POKER_HAND_H
#endif

void poker_hand_table_apply_planet_card(PokerHandTableState* state, PlanetCard planet_card) {
    if (!state) return;

    switch (planet_card) {
        case PLUTO_CARD:
            state->high_card.mult += 1;
            state->high_card.chips += 10;
            break;
        case MERCURY_CARD:
            state->one_pair.mult += 1;
            state->one_pair.chips += 15;
            break;
        case URANUS_CARD:
            state->two_pair.mult += 1;
            state->two_pair.chips += 20;
            break;
        case VENUS_CARD:
            state->three_of_a_kind.mult += 2;
            state->three_of_a_kind.chips += 20;
            break;
        case SATURN_CARD:
            state->straight.mult += 3;
            state->straight.chips += 30;
            break;
        case JUPITER_CARD:
            state->flush.mult += 2;
            state->flush.chips += 15;
            break;
        case EARTH_CARD:
            state->full_house.mult += 2;
            state->full_house.chips += 25;
            break;
        case MARS_CARD:
            state->four_of_a_kind.mult += 3;
            state->four_of_a_kind.chips += 30;
            break;
        case NEPTUNE_CARD:
            state->straight_flush.mult += 4;
            state->straight_flush.chips += 40;
            break;
        case PLANET_X_CARD:
            state->five_of_a_kind.mult += 3;
            state->five_of_a_kind.chips += 35;
            break;
        case CERES_CARD:
            state->flush_house.mult += 4;
            state->flush_house.chips += 40;
            break;
        case ERIS_CARD:
            state->flush_five.mult += 3;
            state->flush_five.chips += 50;
            break;
        default:
            break;
    }
}
