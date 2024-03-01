//
// Created by backo on 29/2/2024.
//

#include "Range.h"
#include "Arduino.h"
Range::Range(const int _range[], int _size, bool _cycle) : range(_range), size(_size), cycle(_cycle) {}

// Obtenir posició de n dins el rang.
// cycle fa que comenci i acabi en 0:
// 0 1 2 3 4 vs 0 1 2 1 0
int Range::getLevel(int n) {
    for (int i = 0; i <= this->size; ++i) {
        if (i == this->size || n < this->range[i]) {
            if (this->cycle && i > this->size/2) {
                return this->size - i;
            } else return i;
        }
    }

    Serial.println("Range getLevel() -1");

    return -1;
}
