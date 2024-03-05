#pragma once
namespace LevelZ {
    class Coordinate2D {
        public:
            Coordinate2D(int x, int y) : x(x), y(y) {}
            int x;
            int y;
    };

    class Coordinate3D {
        public:
            Coordinate3D(int x, int y, int z) : x(x), y(y), z(z) {}
            int x;
            int y;
            int z;
    };
}