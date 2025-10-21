#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/validation.h"

short intNumFormatable(char *numStr) {
    int i = (numStr[0] == '-') ? 1 : 0;
    while (i < strlen(numStr)) {
        if (numStr[i] < 48 || numStr[i] > 57)
            return 0;
        i++;
    }

    return 1;
}

short doubleNumFormatable(char *numStr) {
    short dots = 0;
    int i = (numStr[0] == '-') ? 1 : 0;

    while (i < strlen(numStr)) {
        if (numStr[i] == '.') {
            dots++;
            continue;
        }

        if (dots >= 2 || numStr[i] < 48 || numStr[i] > 57)
            return 0;

        i++;
    }

    return 1;
}

short birthDayValidated(char *birthDay) {
    return 0;
}