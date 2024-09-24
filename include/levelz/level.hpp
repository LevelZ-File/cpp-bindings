#pragma once

#include <vector>
#include <unordered_map>

#include "block.hpp"
#include "coordinate.hpp"

namespace LevelZ {

    /**
     * Represents a LevelZ level.
     */
    struct Level {
        protected:
            std::unordered_map<std::string, std::string> _headers = {};
            std::vector<LevelZ::LevelObject> _blocks = {};

            Level() {}

        public:
            /**
             * Gets the headers in the level.
             * @return The headers in the level.
             */
            inline std::unordered_map<std::string, std::string> headers() const {
                return _headers;
            }

            /**
             * Gets the blocks in the level.
             * @return The blocks in the level.
             */
            inline std::vector<LevelObject> blocks() const {
                return _blocks;
            }

            /**
             * Compares two levels for equality.
             * @param other The other level to compare.
             * @return true if the levels are equal, false if the levels are not equal
             */
            bool operator==(const Level& other) const {
                return _headers == other._headers && _blocks == other._blocks;
            }

            /**
             * Compares two levels for inequality.
             * @param other The other level to compare.
             * @return true if the levels are not equal, false if the levels are equal
             */
            bool operator!=(const Level& other) const {
                return _headers != other._headers || _blocks != other._blocks;
            }
    };

    /**
     * Represents a scroll direction in a 2D level.
     */
    enum Scroll {
        /**
         * No Scrolling
         */
        NONE,
        
        /**
         * Horizontal Scrolling moving left
         */
        HORIZONTAL_LEFT,

        /**
         * Horizontal Scrolling moving right
         */
        HORIZONTAL_RIGHT,

        /**
         * Vertical Scrolling moving up
         */
        VERTICAL_UP,

        /**
         * Vertical Scrolling moving down
         */
        VERTICAL_DOWN
    };

    /**
     * Represents a 2D Level.
     */
    struct Level2D : Level {
        public:
            /**
             * The spawnpoint of the level.
             */
            Coordinate2D spawn = Coordinate2D(0, 0);

            /**
             * Constructs a new, empty 2D Level.
             */
            Level2D() {}

            /**
             * Constructs a new 2D Level with the specified headers.
             * @param headers The headers of the level.
             */
            explicit Level2D(const std::unordered_map<std::string, std::string>& headers) : Level2D(headers, {}) {}

            /**
             * Constructs a new 2D Level with the specified headers and blocks.
             * @param headers The headers of the level.
             * @param blocks The blocks of the level.
             */
            Level2D(const std::unordered_map<std::string, std::string>& headers, const std::vector<LevelObject>& blocks) {
                _headers = headers;
                _blocks = blocks;

                if (headers.find("type") == headers.end())
                    _headers["type"] = "2";

                spawn = Coordinate2D(0, 0);
                if (headers.find("spawn") != headers.end()) {
                    spawn = Coordinate2D::from_string(headers.at("spawn"));
                }
            }

            /**
             * Clones a 2D Level from an Abstract Level.
             * @param level The level to clone.
             */
            explicit Level2D(const Level& level) : Level2D(level.headers(), level.blocks()) {};

            /**
             * Gets the scroll direction of the level.
             * @return Scroll Direction
             */
            inline Scroll scroll() {
                if (_headers.find("scroll") == _headers.end())
                    return Scroll::NONE;

                std::string scroll = _headers.at("scroll");

                if (scroll == "none") return Scroll::NONE;
                if (scroll == "horizontal-left") return Scroll::HORIZONTAL_LEFT;
                if (scroll == "horizontal-right") return Scroll::HORIZONTAL_RIGHT;
                if (scroll == "vertical-up") return Scroll::VERTICAL_UP;
                if (scroll == "vertical-down") return Scroll::VERTICAL_DOWN;

                return Scroll::NONE;
            }
    };

    /**
     * Represents a 3D Level.
     */
    struct Level3D : Level {
        public:
            /**
             * The spawnpoint of the level.
             */
            Coordinate3D spawn = Coordinate3D(0, 0, 0);

            /**
             * Constructs a new, empty 3D Level.
             */
            Level3D() {}

            /**
             * Constructs a new 3D Level with the specified headers.
             * @param headers The headers of the level.
             */
            explicit Level3D(const std::unordered_map<std::string, std::string>& headers) : Level3D(headers, {}) {}

            /**
             * Constructs a new 3D Level with the specified headers and blocks.
             * @param headers The headers of the level.
             * @param blocks The blocks of the level.
             */
            Level3D(const std::unordered_map<std::string, std::string>& headers, const std::vector<LevelObject>& blocks) {
                _headers = headers;
                _blocks = blocks;

                if (headers.find("type") == headers.end())
                    _headers["type"] = "3";

                spawn = Coordinate3D(0, 0, 0);
                if (headers.find("spawn") != headers.end()) {
                    spawn = Coordinate3D::from_string(headers.at("spawn"));
                }
            }

            /**
             * Clones a 3D Level from an Abstract Level.
             * @param level The level to clone.
             */
            explicit Level3D(const Level& level) : Level3D(level.headers(), level.blocks()) {};
    };

}