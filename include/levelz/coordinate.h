#pragma once

#include <vector>

namespace LevelZ {

    /**
     * Represents a 2D coordinate.
     */
    class Coordinate2D {
        public:
            /**
             * The X coordinate.
             */
            int x;

            /**
             * The Y coordinate.
             */
            int y;

            /**
             * Initializes a new instance of the Coordinate2D class at [0, 0].
             */
            Coordinate2D() : x(0), y(0) {}

            /**
             * Initializes a new instance of the Coordinate2D class at the specified coordinates.
             * @param x The X coordinate.
             * @param y The Y coordinate.
             */
            Coordinate2D(int x, int y) : x(x), y(y) {}

            /**
             * Initializes a new instance of the Coordinate2D class at the specified coordinates.
             * @param xy The X and Y coordinates in a vector.
             */
            Coordinate2D(std::vector<int> xy) : x(xy.at(0)), y(xy.at(1)) {}

            /**
             * Gets the magnitude of the coordinate.
             * @return The magnitude of the coordinate.
             */
            int getMagnitude() const {
                return x * x + y * y;
            }

            /**
             * Compares two coordinates for equality.
             * @param other The other coordinate to compare to.
             * @return True if the coordinates are equal, false otherwise.
             */
            bool operator==(const Coordinate2D& other) const {
                return x == other.x && y == other.y;
            }

            /**
             * Compares two coordinates for inequality.
             * @param other The other coordinate to compare to.
             * @return True if the coordinates are not equal, false otherwise.
             */
            bool operator!=(const Coordinate2D& other) const {
                return x != other.x || y != other.y;
            }

            /**
             * Adds two coordinates together.
             * @param other The other coordinate to add.
             * @return The sum of the two coordinates.
             */
            Coordinate2D operator+(const Coordinate2D& other) const {
                return Coordinate2D(x + other.x, y + other.y);
            }

            /**
             * Subtracts one coordinate from another.
             * @param other The other coordinate to subtract.
             * @return The difference of the two coordinates.
             */
            Coordinate2D operator-(const Coordinate2D& other) const {
                return Coordinate2D(x - other.x, y - other.y);
            }

            /**
             * Multiplies the coordinate by a scalar.
             * @param scalar The scalar to multiply by.
             * @return The product of the coordinate and the scalar.
             */
            Coordinate2D operator*(int scalar) const {
                return Coordinate2D(x * scalar, y * scalar);
            }

            /**
             * Divides the coordinate by a scalar.
             * @param scalar The scalar to divide by.
             * @return The quotient of the coordinate and the scalar.
             */
            Coordinate2D operator/(int scalar) const {
                return Coordinate2D(x / scalar, y / scalar);
            }
    };

    /**
     * Represents a 3D coordinate.
     */
    class Coordinate3D {
        public:
            /**
             * The X coordinate.
             */
            int x;

            /**
             * The Y coordinate.
             */
            int y;

            /**
             * The Z coordinate.
             */
            int z;

            /**
             * Initializes a new instance of the Coordinate3D class at [0, 0, 0].
             */
            Coordinate3D() : x(0), y(0), z(0) {}

            /**
             * Initializes a new instance of the Coordinate3D class at the specified coordinates.
             * @param x The X coordinate.
             * @param y The Y coordinate.
             * @param z The Z coordinate.
             */
            Coordinate3D(int x, int y, int z) : x(x), y(y), z(z) {}

            /**
             * Initializes a new instance of the Coordinate3D class at the specified coordinates.
             * @param xyz The X, Y, and Z coordinates in a vector.
             */
            explicit Coordinate3D(std::vector<int> xyz) : x(xyz.at(0)), y(xyz.at(1)), z(xyz.at(2)) {}

            /**
             * Gets the magnitude of the coordinate.
             * @return Coordinate Magnitude
             */
            int getMagnitude() const {
                return x * x + y * y + z * z;
            }

            /**
             * Compares two coordinates for equality.
             * @param other The other coordinate to compare to.
             * @return True if the coordinates are equal, false otherwise.
             */
            bool operator==(const Coordinate3D& other) const {
                return x == other.x && y == other.y && z == other.z;
            }

            /**
             * Compares two coordinates for inequality.
             * @param other The other coordinate to compare to.
             * @return True if the coordinates are not equal, false otherwise.
             */
            bool operator!=(const Coordinate3D& other) const {
                return x != other.x || y != other.y || z != other.z;
            }

            /**
             * Adds two coordinates together.
             * @param other The other coordinate to add.
             * @return The sum of the two coordinates.
             */
            Coordinate3D operator+(const Coordinate3D& other) const {
                return Coordinate3D(x + other.x, y + other.y, z + other.z);
            }

            /**
             * Subtracts one coordinate from another.
             * @param other The other coordinate to subtract.
             * @return The difference of the two coordinates.
             */
            Coordinate3D operator-(const Coordinate3D& other) const {
                return Coordinate3D(x - other.x, y - other.y, z - other.z);
            }

            /**
             * Multiplies the coordinate by a scalar.
             * @param scalar The scalar to multiply by.
             * @return The product of the coordinate and the scalar.
             */
            Coordinate3D operator*(int scalar) const {
                return Coordinate3D(x * scalar, y * scalar, z * scalar);
            }

            /**
             * Divides the coordinate by a scalar.
             * @param scalar The scalar to divide by.
             * @return The quotient of the coordinate and the scalar.
             */
            Coordinate3D operator/(int scalar) const {
                return Coordinate3D(x / scalar, y / scalar, z / scalar);
            }
    };
}