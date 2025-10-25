

/*

whenever a hand is calculated, we:
1. Get the type of the hand
2. Get the default chips and mult for the hand
3. For each card (if retrigger, repeat that amount of times for that card):
    - Get chip value (...etc)
    - Get mult value (...etc)
    - Apply enhancements, seals, editions as needed
    - Call all jokers' "each card" function
4. Calculate the final hand value based on all the above
5. Call all jokers' "end of hand" function

*/