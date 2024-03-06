#pragma once

#include <vector>

namespace LevelZ {
    class Coordinate2D {
        public:
            int x;
            int y;

            Coordinate2D() : x(0), y(0) {}
            Coordinate2D(int x, int y) : x(x), y(y) {}
            Coordinate2D(std::vector<int> xy) : x(xy.at(0)), y(xy.at(0)) {}

            int getMagnitude() const {
                return x * x + y * y;
            }

            bool operator==(const Coordinate2D& other) const {
                return x == other.x && y == other.y;
            }
            bool operator!=(const Coordinate2D& other) const {
                return x != other.x || y != other.y;
            }
    };

    class Coordinate3D {
        public:
            int x;
            int y;
            int z;

            Coordinate3D() : x(0), y(0), z(0) {}
            Coordinate3D(int x, int y, int z) : x(x), y(y), z(z) {}
            Coordinate3D(std::vector<int> xyz) : x(xyz.at(0)), y(xyz.at(0)), z(xyz.at(0)) {}

            int getMagnitude() const {
                return x * x + y * y + z * z;
            }

            bool operator==(const Coordinate3D& other) const {
                return x == other.x && y == other.y && z == other.z;
            }
            bool operator!=(const Coordinate3D& other) const {
                return x != other.x || y != other.y || z != other.z;
            }
    };
}