// Name: <Your Name Here>
// Student ID: <Your Student ID Here>
// Email: <your.email@domain>
// cram.cpp
// Main program implementing the game flow for Cram.

#include <iostream>
#include "cramgrid.h"

// Helper: check whether there exists any legal placeable move (V or H at any pos).
static bool anyPlaceable(long long grid) {
    for (int pos = 1; pos <= 16; ++pos) {
        if (isPlaceable(grid, 'V', pos)) return true;
        if (isPlaceable(grid, 'H', pos)) return true;
    }
    return false;
}

int main() {
    long long grid = 0; // empty grid
    int player = 1; // Player 1 starts

    // initial grid print
    printGrid(grid);

    while (true) {
        // before asking current player, check whether they have any move
        if (!anyPlaceable(grid)) {
            int winner = 3 - player; // other player wins
            std::cout << "Player " << winner << " wins!" << std::endl;
            break;
        }

        // prompt and read input
        std::cout << "Player " << player << " moves: ";
        char d;
        int pos;
        if (!(std::cin >> d >> pos)) {
            // input failed (EOF or invalid), terminate gracefully
            return 0;
        }

        // validate placeability
        if (!isPlaceable(grid, d, pos)) {
            std::cout << "Invalid! Try again." << std::endl;
            continue; // same player's turn
        }

        // perform move and print grid
        putToGrid(grid, d, pos, player);
        printGrid(grid);

        // swap player
        player = 3 - player;
    }

    return 0;
}
