#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace LevelZ {

    /**
     * Represents a block in a game level.
     */
    struct Block {
        public:
            /**
             * The name of the block.
             */
            std::string name;

            /**
             * The properties of the block.
             */
            std::unordered_map<std::string, std::string> properties;

            /**
             * Constructs a new block with the specified name and empty properties.
             */
            explicit Block(std::string name) : name(name) {}

            /**
             * Constructs a new block with the specified name and properties.
             * @param name The name of the block.
             * @param properties The properties of the block.
             */
            Block(std::string name, std::unordered_map<std::string, std::string> properties) : name(name), properties(properties) {}

            /**
             * Gets the property of the block with the specified key.
             * @param key The key of the property.
             * @return The value of the property.
             */
            std::string getProperty(std::string key) const {
                return properties.at(key);
            }

            /**
             * Gets the property of the block with the specified key, or a default value if the property does not exist.
             * @param key The key of the property.
             * @param defaultValue The default value to return if the property does not exist.
             * @return The value of the property, or the default value if the property does not exist.
             */
            std::string getProperty(std::string key, std::string defaultValue) const {
                return properties.find(key) != properties.end() ? properties.at(key) : defaultValue;
            }

            /**
             * Sets the value of a property.
             * @param key The key of the property.
             * @return true if the property was set, false if the property was not set
             */
            bool hasProperty(std::string key) const {
                return properties.find(key) != properties.end();
            }

            /**
             * Compares two blocks for equality.
             * @param other The other block to compare to.
             * @return True if the blocks are equal, false otherwise.
             */
            bool operator==(const Block& other) const {
                return name == other.name && properties == other.properties;
            }

            /**
             * Compares two blocks for inequality.
             * @param other The other block to compare to.
             * @return True if the blocks are not equal, false otherwise.
             */
            bool operator!=(const Block& other) const {
                return name != other.name || properties != other.properties;
            }

            /**
             * Converts this Block into a string.
             * @return The string representation of this Block.
             */
            std::string to_string() const {
                std::string str;
                str += name + "<";

                for (auto const& [k, v] : properties) {
                    str += k + "=" + v;
                }

                str += ">";

                return str;
            }
    };

    /**
     * Utility Object for representing a Level Block and its Coordinate.
     */
    struct LevelObject {
        private:
            Coordinate* _coordinate;
            Block _block;
        public:
            /**
             * Constructs a new LevelObject with the specified block and coordinate.
             * @param block The block of the object.
             * @param coordinate The coordinate of the object.
             */
            LevelObject(Block block, Coordinate2D coordinate) : _block(block), _coordinate(&coordinate) {}

            /**
             * Constructs a new LevelObject with the specified block and coordinate.
             * @param block The block of the object.
             * @param coordinate The coordinate of the object.
             */
            LevelObject(Block block, Coordinate3D coordinate) : _block(block), _coordinate(&coordinate) {}

            /**
             * Gets the block of the object.
             * @return Block of the object.
             */
            inline Block block() {
                return _block;
            }
            
            /**
             * Gets the coordinate of the object.
             * @return Coordinate of the object.
             */
            Coordinate* coordinate() {
                return _coordinate;
            }

            /**
             * Compares two LevelObjects for equality.
             * @param other The other LevelObject to compare to.
             * @return True if the LevelObjects are equal, false otherwise.
             */
            bool operator==(const LevelObject& other) const {
                return _block == other._block && _coordinate->getMagnitude() == other._coordinate->getMagnitude();
            }

            /**
             * Compares two LevelObjects for inequality.
             * @param other The other LevelObject to compare to.
             * @return True if the LevelObjects are not equal, false otherwise.
             */
            bool operator!=(const LevelObject& other) const {
                return _block != other._block || _coordinate->getMagnitude() != other._coordinate->getMagnitude();
            }

            /**
             * Converts this LevelObject into a string.
             * @return The string representation of this LevelObject.
             */
            std::string to_string() const {
                return _block.to_string() + ": " + _coordinate->to_string();
            }
    };

}