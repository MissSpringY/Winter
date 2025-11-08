// Name: <Your Name Here>
// Student ID: <Your Student ID Here>
// Email: <your.email@domain>
// cramgrid.h
// Prototypes for Cram assignment functions.

#ifndef CRAMGRID_H
#define CRAMGRID_H

// Print the grid to screen. Provided function (do not modify in grading).
void printGrid(long long grid);

// Return state at position pos (1..16): 0 empty, 1 player1, 2 player2.
int gridState(long long grid, int pos);

// Return true if a domino can be placed at pos along direction d ('V'/'v' or 'H'/'h').
bool isPlaceable(long long grid, char d, int pos);

// Put a domino of player p (1 or 2) at pos along direction d into grid (by reference).
void putToGrid(long long &grid, char d, int pos, int p);

#endif // CRAMGRID_H
