#include <iostream>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;
    r |= assert(LevelZ::Coordinate2D(1, 2) == LevelZ::Coordinate2D(1, 2));
    r |= assert(LevelZ::Coordinate2D(1, 2) != LevelZ::Coordinate2D(2, 1));

    r |= assert(LevelZ::Coordinate3D(1, 2, 3) == LevelZ::Coordinate3D(1, 2, 3));
    r |= assert(LevelZ::Coordinate3D(1, 2, 3) != LevelZ::Coordinate3D(2, 1, 3));
    
    return r;
}