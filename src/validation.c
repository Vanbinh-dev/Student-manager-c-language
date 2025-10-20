#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../include/validation.h"

bool intNumFormatable(char *numStr) {
    int i = (numStr[0] == '-') ? 1 : 0;
    while (i < strlen(numStr)) {
        if (numStr[i] < 48 || numStr[i] > 57)
            return false;
        i++;
    }

    return true;
}

bool doubleNumFormatable(char *numStr) {
    short dots = 0;
    int i = (numStr[0] == '-') ? 1 : 0;

    while (i < strlen(numStr)) {
        if (numStr[i] == '.') {
            dots++;
            continue;
        }

        if (dots >= 2 || numStr[i] < 48 || numStr[i] > 57)
            return false;

        i++;
    }

    return true;
}