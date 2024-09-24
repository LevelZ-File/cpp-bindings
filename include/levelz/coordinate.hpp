#pragma once

#include <vector>
#include <array>

namespace LevelZ {

    /**
     * Represents a LevelZ Coordinate.
     */
    struct Coordinate {
        /**
         * Converts this coordinate to a string.
         * @return The string representation of the coordinate.
         */
        virtual std::string to_string() const = 0;

        /**
         * Gets the magnitude of the coordinate.
         * @return Coordinate Magnitude
         */
        virtual double getMagnitude() const = 0;
    };

    /**
     * Represents a 2D coordinate.
     */
    struct Coordinate2D : Coordinate {
        public:
            /**
             * The X coordinate.
             */
            double x;

            /**
             * The Y coordinate.
             */
            double y;

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
             * @param x The X coordinate.
             * @param y The Y coordinate.
             */
            Coordinate2D(double x, double y) : x(x), y(y) {}

            /**
             * Initializes a new instance of the Coordinate2D class at the specified coordinates.
             * @param xy The X and Y coordinates in a vector.
             */
            Coordinate2D(std::vector<int> xy) : x(xy.at(0)), y(xy.at(1)) {}

            /**
             * Initializes a new instance of the Coordinate2D class at the specified coordinates.
             * @param xy The X and Y coordinates in an array.
             */
            Coordinate2D(std::array<int, 2> xy) : x(xy.at(0)), y(xy.at(1)) {}

            /**
             * Initializes a new instance of the Coordinate2D class at the specified coordinates.
             * @param xy The X and Y coordinates in a vector.
             */
            Coordinate2D(std::vector<double> xy) : x(xy.at(0)), y(xy.at(1)) {}

            /**
             * Initializes a new instance of the Coordinate2D class at the specified coordinates.
             * @param xy The X and Y coordinates in an array.
             */
            Coordinate2D(std::array<double, 2> xy) : x(xy.at(0)), y(xy.at(1)) {}

            /**
             * Gets the magnitude of the coordinate.
             * @return The magnitude of the coordinate.
             */
            double getMagnitude() const {
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

            /**
             * Converts this 2D coordinate to a string.
             * @return The string representation of the coordinate.
             */
            std::string to_string() const {
                return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
            }

            /**
             * Overloads the << operator to allow for easy printing of a Coordinate2D.
             * @param strm The output stream to write to.
             * @return The output stream.
             */
            std::ostream& operator<<(std::ostream &strm) {
                return strm << to_string();
            }

            /**
             * Converts a string to a 2D coordinate.
             * @param str The string to convert.
             * @return Coordinate2D The 2D coordinate.
             */
            static Coordinate2D from_string(const std::string& str) {
                std::string x = str.substr(1, str.find(",") - 1);
                std::string y = str.substr(str.find(",") + 1, str.find("]") - str.find(",") - 1);
                return Coordinate2D(std::stod(x), std::stod(y));
            }
    };

    /**
     * Represents a 3D coordinate.
     */
    struct Coordinate3D : Coordinate {
        public:
            /**
             * The X coordinate.
             */
            double x;

            /**
             * The Y coordinate.
             */
            double y;

            /**
             * The Z coordinate.
             */
            double z;

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
             * @param x The X coordinate.
             * @param y The Y coordinate.
             * @param z The Z coordinate.
             */
            Coordinate3D(double x, double y, double z) : x(x), y(y), z(z) {}

            /**
             * Initializes a new instance of the Coordinate3D class at the specified coordinates.
             * @param xyz The X, Y, and Z coordinates in a vector.
             */
            explicit Coordinate3D(std::vector<int> xyz) : x(xyz.at(0)), y(xyz.at(1)), z(xyz.at(2)) {}

            /**
             * Initializes a new instance of the Coordinate3D class at the specified coordinates.
             * @param xyz The X, Y, and Z coordinates in an array.
             */
            explicit Coordinate3D(std::array<int, 3> xyz) : x(xyz.at(0)), y(xyz.at(1)), z(xyz.at(2)) {}

            /**
             * Initializes a new instance of the Coordinate3D class at the specified coordinates.
             * @param xyz The X, Y, and Z coordinates in a vector.
             */
            explicit Coordinate3D(std::vector<double> xyz) : x(xyz.at(0)), y(xyz.at(1)), z(xyz.at(2)) {}

            /**
             * Initializes a new instance of the Coordinate3D class at the specified coordinates.
             * @param xyz The X, Y, and Z coordinates in an array.
             */
            explicit Coordinate3D(std::array<double, 3> xyz) : x(xyz.at(0)), y(xyz.at(1)), z(xyz.at(2)) {}

            /**
             * Gets the magnitude of the coordinate.
             * @return Coordinate Magnitude
             */
            double getMagnitude() const {
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

            /**
             * Converts this 3D coordinate to a string.
             * @return The string representation of the coordinate.
             */
            std::string to_string() const {
                return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
            }

            /**
             * Overloads the << operator to allow for easy printing of a Coordinate3D.
             * @param strm The output stream to write to.
             * @return The output stream.
             */
            std::ostream& operator<<(std::ostream &strm) {
                return strm << to_string();
            }

            /**
             * Converts a string to a 3D coordinate.
             * @param str The string to convert.
             * @return Coordinate3D The 3D coordinate.
             */
            static Coordinate3D from_string(const std::string& str) {
                std::string x = str.substr(1, str.find(",") - 1);
                std::string y = str.substr(str.find(",") + 1, str.rfind(",") - str.find(",") - 1);
                std::string z = str.substr(str.rfind(",") + 1, str.find("]") - str.rfind(",") - 1);
                return Coordinate3D(std::stod(x), std::stod(y), std::stod(z));
            }
    };
}