/* 

struct representing the state of a round 

these go in the game state TODO:
- round numbr and ante 

*/

typedef struct {
    int round_number;
    int hand_size;
    int hands;
    int discards;
    int score;
    //BlindType blind; // type of blind, IF its a custom one // TODO
    int required_score; // e.g. 300 for ante 1 round 1
} RoundState;

