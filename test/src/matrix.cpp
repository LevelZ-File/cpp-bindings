#include <iostream>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;
    r |= assert(LevelZ::CoordinateMatrix2D(2, 2, LevelZ::Coordinate2D()) == LevelZ::CoordinateMatrix2D(0, 2, 0, 2, LevelZ::Coordinate2D()));

    // coordinate size
    LevelZ::CoordinateMatrix2D matrix2d = LevelZ::CoordinateMatrix2D(2, 2, LevelZ::Coordinate2D());
    r |= assert(matrix2d.getCoordinates().size() == 9);
    r |= assert(matrix2d.start == LevelZ::Coordinate2D());

    LevelZ::CoordinateMatrix3D matrix3d = LevelZ::CoordinateMatrix3D(2, 2, 2, LevelZ::Coordinate3D());
    r |= assert(matrix3d.getCoordinates().size() == 27);
    r |= assert(matrix3d.start == LevelZ::Coordinate3D());

    // #from_string
    r |= assert(LevelZ::CoordinateMatrix2D::from_string("(0, 3, 0, 3)^[-1, 2]") == LevelZ::CoordinateMatrix2D(0, 3, 0, 3, LevelZ::Coordinate2D(-1, 2)));
    r |= assert(LevelZ::CoordinateMatrix3D::from_string("(0, 3, 0, 3, 0, 3)^[-1, 2, 3]") == LevelZ::CoordinateMatrix3D(0, 3, 0, 3, 0, 3, LevelZ::Coordinate3D(-1, 2, 3)));

    return r;
}