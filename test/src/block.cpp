#include <iostream>
#include <unordered_map>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;
    r |= assert(LevelZ::Block("test") == LevelZ::Block("test"));
    r |= assert(LevelZ::Block("test") != LevelZ::Block("test2"));
    r |= assert(LevelZ::Block("test", {{"key", "value"}}) == LevelZ::Block("test", {{"key", "value"}}));

    // #getProperty
    LevelZ::Block block("test", {{"key", "value"}});
    r |= assert(block.getProperty("key") == "value");

    return r;
}