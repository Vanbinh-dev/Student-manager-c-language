#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/helper/input_validation.h"

#include "../../include/error_code.h"

short isAlpha(char c) {
    if (c >= 'a' && c <= 'z')
        return true;
    else if (c >= 'A' && c <= 'Z')
        return true;

    return false;
}

short isNumeric(char c) {
    if (c >= '0' && c <= '9')
        return true;

    return false;
}

short isBlankOrEndl(char c) {
    if (c == ' ' || c == '\n')
        return true;
    return false;
}


short canBeFormatToInt(char* num) {
    for (int i = 0; i < strlen(num); i++)
        if (!isNumeric(num[i]))
            return false;
    return true;
}

short canBeFormatToDouble(char* num) {
    short hasDot = false;

    for (int i = 0; i < strlen(num); i++) {
        if (num[i] == '.' && !hasDot) {
            hasDot = true;
            continue;
        }

        else if (!isNumeric(num[i]))
            return false;
    }

    return true;
}