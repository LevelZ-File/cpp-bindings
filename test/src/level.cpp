#include <iostream>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;
    
    Level2D l1 = Level2D({{"scroll", "none"}, {"spawn", "[0, 0]"}}, {});
    r |= assert(l1.scroll() == Scroll::NONE);
    r |= assert(l1.spawn == Coordinate2D(0, 0));

    Level2D l2 = Level2D({{"scroll", "horizontal-right"}, {"spawn", "[-2, 4]"}}, {});
    r |= assert(l2.scroll() == Scroll::HORIZONTAL_RIGHT);
    r |= assert(l2.spawn == Coordinate2D(-2, 4));

    Level3D l3 = Level3D({{"spawn", "[2, 3, 4]"}}, {});
    r |= assert(l3.spawn == Coordinate3D(2, 3, 4));

    // File Parsing
    std::vector<std::string> l4v = {
        "@type 2",
        "@scroll horizontal-right",
        "@spawn [-2, 4]",
        "---",
        "grass: [0, 0]",
        "stone: [0, 1]*[0, 2]"
    };
    Level2D l4 = static_cast<Level2D>(LevelZ::parseLines(l4v));
    r |= assert(l4.scroll() == Scroll::HORIZONTAL_RIGHT);
    r |= assert(l4.spawn == Coordinate2D(-2, 4));
    r |= assert(l4.blocks().size() == 3);

    return r;
}