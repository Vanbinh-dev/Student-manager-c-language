#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/validation.h"

short isAlpha(char c) {
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

short isNumeric(char c) {
    return c >= '0' && c <= '9';
}

short isBlankOrEndline(char c) {
    if (c == ' ' || c == '\n')
        return 1;

    return 0;
}

short nameValidated(char *name) {
    if (name == NULL) 
        return 0;
        
    for (int i = 0; i < strlen(name); i++) 
        if (!isAlpha(name[i]) && !isBlankOrEndline(name[i])) 
            return 0;
    return 1;
}

short intNumFormatable(char *numStr) {
    if (numStr == NULL)
        return 0;

    int i = (numStr[0] == '-') ? 1 : 0;
    while (i < strlen(numStr) && numStr[i] != '\n') {
        if (numStr[i] < 48 || numStr[i] > 57)
            return 0;
        i++;
    }

    return 1;
}

short doubleNumFormatable(char *numStr) {
    if (numStr == NULL)
        return 0;

    short dots = 0;
    int i = (numStr[0] == '-') ? 1 : 0;

    // Check if string is empty or just a minus sign
    if (numStr[i] == '\0')
        return 0;

    while (numStr[i] != '\0') {
        if (numStr[i] == '.') {
            dots++;
            if (dots > 1) {
                printf("Trả về 0 do dư dấu .\n");
                return 0;
            } // More than one decimal point
            i++;
            continue;
        }

        if (numStr[i] == ' ')
            continue;

        if (
            (numStr[i] < '0' || numStr[i] > '9') && numStr[i] != 10) {
            printf("Trả về 0 do không phải số! Kí tự %c số giá trị %d\n", numStr[i], numStr[i]);
            return 0;
        }
        i++;
    }

    return 1;
}

short ageValidated(char *age) {
    if (!intNumFormatable(age))
        return 0;
    int a = atoi(age);
    if (a < 18 || a > 90)   
        return 0;
    return 1;
}