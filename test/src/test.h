#pragma once

int assert(bool condition) {
    if (!condition) return 1;

    return 0;
}