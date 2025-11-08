// Name: <Your Name Here>
// Student ID: <Your Student ID Here>
// Email: <your.email@domain>
// cramgrid.cpp
// Implementations of required functions for Cram assignment.

#include <iostream>
#include "cramgrid.h"

// Helper: compute 10^(exp) as long long (exp >= 0).
static long long pow10_int(int exp) {
    long long res = 1;
    for (int i = 0; i < exp; ++i) res *= 10LL;
    return res;
}

// Provided function - prints the 4x4 grid. Keep output format consistent with sample.
void printGrid(long long grid) {
    for (int r = 0; r < 4; ++r) {
        for (int c = 1; c <= 4; ++c) {
            int pos = r * 4 + c; // 1..16
            int st = gridState(grid, pos);
            if (st == 0) {
                std::cout << ".";
            } else {
                std::cout << st;
            }
            if (c < 4) std::cout << " ";
        }
        std::cout << std::endl;
    }
    // print an extra newline to match sample interaction spacing
    std::cout << std::endl;
}

// Return the digit value at position pos (1..16), where pos=1 is the leftmost (most significant) digit.
int gridState(long long grid, int pos) {
    // position pos corresponds to digit index pos in a 16-digit number d1 d2 ... d16
    // We need to extract digit d_pos where d1 is the 10^(15) place.
    // Compute divisor = 10^(16-pos)
    if (pos < 1 || pos > 16) return 0; // defensive, though caller assumes 1..16
    int exp = 16 - pos;
    long long div = pow10_int(exp);
    long long v = grid / div; // integer division handles leading zeros
    int digit = (int)(v % 10LL);
    return digit;
}

// Check if placing a domino at pos along direction d is valid (not actually placing).
bool isPlaceable(long long grid, char d, int pos) {
    // check pos range
    if (pos < 1 || pos > 16) return false;
    // check direction char
    if (!(d == 'V' || d == 'v' || d == 'H' || d == 'h')) return false;
    if (d == 'V' || d == 'v') {
        // vertical: pos and pos+4 must be within grid and empty; pos must not be in bottom row (13..16)
        if (pos >= 13) return false;
        if (gridState(grid, pos) != 0) return false;
        if (gridState(grid, pos + 4) != 0) return false;
        return true;
    } else {
        // horizontal: pos and pos+1 must be within same row; pos must not be at rightmost column (4,8,12,16)
        if (pos % 4 == 0) return false;
        if (gridState(grid, pos) != 0) return false;
        if (gridState(grid, pos + 1) != 0) return false;
        return true;
    }
}

// Put a domino into grid by updating the digits for pos and pos+4 or pos+1 to p.
// Assumptions per spec: pos in 1..16, d is valid char, and the two spaces are currently empty.
void putToGrid(long long &grid, char d, int pos, int p) {
    // compute power for pos: 10^(16-pos)
    int exp1 = 16 - pos;
    long long pow1 = pow10_int(exp1);
    int old1 = gridState(grid, pos);
    long long delta1 = (long long)(p - old1) * pow1;
    grid += delta1;
    if (d == 'V' || d == 'v') {
        int pos2 = pos + 4;
        int exp2 = 16 - pos2;
        long long pow2 = pow10_int(exp2);
        int old2 = gridState(grid, pos2); // should be 0 per assumption
        long long delta2 = (long long)(p - old2) * pow2;
        grid += delta2;
    } else {
        int pos2 = pos + 1;
        int exp2 = 16 - pos2;
        long long pow2 = pow10_int(exp2);
        int old2 = gridState(grid, pos2);
        long long delta2 = (long long)(p - old2) * pow2;
        grid += delta2;
    }
}
