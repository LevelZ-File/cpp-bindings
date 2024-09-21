#pragma once

#include <vector>
#include <array>
#include <regex>

#include "coordinate.h"

namespace LevelZ {

    /**
     * Represents a coordinate matrix.
     */
    struct CoordinateMatrix {
        /**
         * Converts this coordinate matrix to a string.
         * @return The string representation of the coordinate.
         */
        virtual std::string to_string() const = 0;
    };

    /**
     * Represents a 2D matrix of coordinates.
     */
    struct CoordinateMatrix2D : CoordinateMatrix {
        public:
            /**
             * The minimum x coordinate of the matrix.
             */
            int minX;

            /**
             * The maximum x coordinate of the matrix.
             */
            int maxX;

            /**
             * The minimum y coordinate of the matrix.
             */
            int minY;

            /**
             * The maximum y coordinate of the matrix.
             */
            int maxY;

            /**
             * The starting coordinate of the matrix.
             */
            LevelZ::Coordinate2D start;

            /**
             * Constructs a new CoordinateMatrix2D object with the minimum coordinates at 0. 
             * @param x The maximum x coordinate of the matrix.
             * @param y The maximum y coordinate of the matrix.
             * @param start The starting coordinate of the matrix.
             */
            CoordinateMatrix2D(int x, int y, LevelZ::Coordinate2D start) : minX(0), maxX(x), minY(0), maxY(y), start(start) {}

            /**
             * Constructs a new CoordinateMatrix2D object with the specified minimum and maximum coordinates.
             * @param minX The minimum x coordinate of the matrix.
             * @param maxX The maximum x coordinate of the matrix.
             * @param minY The minimum y coordinate of the matrix.
             * @param maxY The maximum y coordinate of the matrix.
             * @param start The starting coordinate of the matrix.
             */
            CoordinateMatrix2D(int minX, int maxX, int minY, int maxY, LevelZ::Coordinate2D start) : minX(minX), maxX(maxX), minY(minY), maxY(maxY), start(start) {}

            /**
             * Gets the coordinates in the matrix.
             * @return The coordinates in the matrix.
             */
            std::vector<LevelZ::Coordinate2D> getCoordinates() const {
                std::vector<LevelZ::Coordinate2D> coordinates;
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) {
                        coordinates.push_back(LevelZ::Coordinate2D(x, y));
                    }
                }
                return coordinates;
            }

            std::vector<LevelZ::Coordinate2D>::const_iterator begin() const {
                return getCoordinates().begin();
            }

            std::vector<LevelZ::Coordinate2D>::const_iterator end() const {
                return getCoordinates().end();
            }

            /**
             * Checks if two 2D coordinate matrices are equal.
             * @param other The other coordinate matrix to compare to.
             * @return true if the coordinate matrices are equal, false otherwise.
             */
            bool operator==(const CoordinateMatrix2D& other) const {
                return minX == other.minX && maxX == other.maxX && minY == other.minY && maxY == other.maxY && start == other.start;
            }

            /**
             * Checks if two 2D coordinate matrices are not equal.
             * @param other The other coordinate matrix to compare to.
             * @return true if the coordinate matrices are not equal, false otherwise.
             */
            bool operator!=(const CoordinateMatrix2D& other) const {
                return minX != other.minX || maxX != other.maxX || minY != other.minY || maxY != other.maxY || start != other.start;
            }

            /**
             * Converts this coordinate matrix to a string.
             * @return The string representation of the coordinate.
             */
            std::string to_string() const {
                return "(" + std::to_string(minX) + ", " + std::to_string(maxX) + ", " + std::to_string(minY) + ", " + std::to_string(maxY) + ")^" + start.to_string();
            }

            /**
             * Converts a string to a 2D coordinate matrix.
             * @param str The string to convert.
             * @return The 2D coordinate matrix. 
             */
            static LevelZ::CoordinateMatrix2D from_string(const std::string& str) {
                const std::regex matrix("[\\[\\]()]");
                std::string s0 = std::regex_replace(str, matrix, "");
                s0 = s0.replace(s0.find('^'), 1, ", ");

                unsigned int i = 0;
                size_t cpos = 0;
                std::string s1;

                int x1, x2, y1, y2;
                double cx, cy;

                while ((cpos = s0.find(',')) != std::string::npos) {
                    s1 = s0.substr(0, cpos);
                    switch (i) {
                        case 0: x1 = std::stoi(s1); break;
                        case 1: x2 = std::stoi(s1); break;
                        case 2: y1 = std::stoi(s1); break;
                        case 3: y2 = std::stoi(s1); break;
                        case 4: cx = std::stod(s1); break;
                    }
                    
                    s0.erase(0, cpos + 1);
                    i++;
                }
                cy = std::stod(s0);

                return CoordinateMatrix2D(x1, x2, y1, y2, LevelZ::Coordinate2D(cx, cy));
            }
    };

    /**
     * Represents a 3D matrix of coordinates.
     */
    struct CoordinateMatrix3D : CoordinateMatrix {
        public:
            /**
             * The minimum x coordinate of the matrix.
             */
            int minX;

            /**
             * The maximum x coordinate of the matrix.
             */
            int maxX;

            /**
             * The minimum y coordinate of the matrix.
             */
            int minY;

            /**
             * The maximum y coordinate of the matrix.
             */
            int maxY;

            /**
             * The minimum z coordinate of the matrix.
             */
            int minZ;

            /**
             * The maximum z coordinate of the matrix.
             */
            int maxZ;

            /**
             * The starting coordinate of the matrix.
             */
            LevelZ::Coordinate3D start;

            /**
             * Constructs a new CoordinateMatrix3D object with the minimum coordinates at 0. 
             * @param x The maximum x coordinate of the matrix.
             * @param y The maximum y coordinate of the matrix.
             * @param z The maximum z coordinate of the matrix.
             * @param start The starting coordinate of the matrix.
             */
            CoordinateMatrix3D(int x, int y, int z, LevelZ::Coordinate3D start) : minX(0), maxX(x), minY(0), maxY(y), minZ(0), maxZ(z), start(start) {}

            /**
             * Constructs a new CoordinateMatrix3D object with the specified minimum and maximum coordinates.
             * @param minX The minimum x coordinate of the matrix.
             * @param maxX The maximum x coordinate of the matrix.
             * @param minY The minimum y coordinate of the matrix.
             * @param maxY The maximum y coordinate of the matrix.
             * @param minZ The minimum z coordinate of the matrix.
             * @param maxZ The maximum z coordinate of the matrix.
             * @param start The starting coordinate of the matrix.
             */
            CoordinateMatrix3D(int minX, int maxX, int minY, int maxY, int minZ, int maxZ, LevelZ::Coordinate3D start) : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ), start(start) {}

            /**
             * Gets the coordinates in the matrix.
             * @return The coordinates in the matrix.
             */
            std::vector<LevelZ::Coordinate3D> getCoordinates() const {
                std::vector<LevelZ::Coordinate3D> coordinates;
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) {
                        for (int z = minZ; z <= maxZ; z++) {
                            coordinates.push_back(LevelZ::Coordinate3D(x, y, z));
                        }
                    }
                }
                return coordinates;
            }

            std::vector<LevelZ::Coordinate3D>::const_iterator begin() const {
                return getCoordinates().begin();
            }

            std::vector<LevelZ::Coordinate3D>::const_iterator end() const {
                return getCoordinates().end();
            }

            /**
             * Checks if two 2D coordinate matrices are equal.
             * @param other The other coordinate matrix to compare to.
             * @return true if the coordinate matrices are equal, false otherwise.
             */
            bool operator==(const CoordinateMatrix3D& other) const {
                return minX == other.minX && maxX == other.maxX && minY == other.minY && maxY == other.maxY && minZ == other.minZ && maxZ == other.maxZ && start == other.start;
            }

            /**
             * Checks if two 2D coordinate matrices are not equal.
             * @param other The other coordinate matrix to compare to.
             * @return true if the coordinate matrices are not equal, false otherwise.
             */
            bool operator!=(const CoordinateMatrix3D& other) const {
                return minX != other.minX || maxX != other.maxX || minY != other.minY || maxY != other.maxY || minZ != other.minZ || maxZ != other.maxZ || start == other.start;
            }

            /**
             * Converts this coordinate matrix to a string.
             * @return The string representation of the coordinate.
             */
            std::string to_string() const {
                return "(" + std::to_string(minX) + ", " + std::to_string(maxX) + ", " + std::to_string(minY) + ", " + std::to_string(maxY) + ", " + std::to_string(minZ) + ", " + std::to_string(maxZ) + ")^" + start.to_string();
            }

            /**
             * Converts a string to a 3D coordinate matrix.
             * @param str The string to convert.
             * @return The 3D coordinate matrix. 
             */
            static LevelZ::CoordinateMatrix3D from_string(const std::string& str) {
                const std::regex matrix("[\\[\\]()]");
                std::string s0 = std::regex_replace(str, matrix, "");
                s0 = s0.replace(s0.find('^'), 1, ", ");

                unsigned int i = 0;
                size_t cpos = 0;
                std::string s1;

                int x1, x2, y1, y2, z1, z2;
                double cx, cy, cz;

                while ((cpos = s0.find(',')) != std::string::npos) {
                    s1 = s0.substr(0, cpos);
                    switch (i) {
                        case 0: x1 = std::stoi(s1); break;
                        case 1: x2 = std::stoi(s1); break;
                        case 2: y1 = std::stoi(s1); break;
                        case 3: y2 = std::stoi(s1); break;
                        case 4: z1 = std::stoi(s1); break;
                        case 5: z2 = std::stoi(s1); break;
                        case 6: cx = std::stod(s1); break;
                        case 7: cy = std::stod(s1); break;
                    }
                    
                    s0.erase(0, cpos + 1);
                    i++;
                }
                cz = std::stod(s0);

                return CoordinateMatrix3D(x1, x2, y1, y2, z1, z2, LevelZ::Coordinate3D(cx, cy, cz));
            }
    };
}