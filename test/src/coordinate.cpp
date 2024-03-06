#include <iostream>
#include <vector>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;
    r |= assert(LevelZ::Coordinate2D() == LevelZ::Coordinate2D(0, 0));
    r |= assert(LevelZ::Coordinate2D(1, 2) == LevelZ::Coordinate2D(1, 2));
    r |= assert(LevelZ::Coordinate2D(1, 2) != LevelZ::Coordinate2D(2, 1));

    std::vector<int> xy = {1, 2};
    r |= assert(LevelZ::Coordinate2D(xy) == LevelZ::Coordinate2D(1, 2));

    r |= assert(LevelZ::Coordinate3D() == LevelZ::Coordinate3D(0, 0, 0));
    r |= assert(LevelZ::Coordinate3D(1, 2, 3) == LevelZ::Coordinate3D(1, 2, 3));
    r |= assert(LevelZ::Coordinate3D(1, 2, 3) != LevelZ::Coordinate3D(2, 1, 3));

    std::vector<int> xyz = {1, 2, 3};
    r |= assert(LevelZ::Coordinate3D(xyz) == LevelZ::Coordinate3D(1, 2, 3));

    // #getMagnitude
    r |= assert(LevelZ::Coordinate2D(3, 4).getMagnitude() == 25);
    r |= assert(LevelZ::Coordinate3D(3, 4, 5).getMagnitude() == 50);

    return r;
}