#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/validation.h"

short nameValidated(char *name) {
    if (name == NULL)
        return 0;
        
    for (int i = 0; name[i] != '\0'; i++)
       if (!isalpha(name[i]) || !isspace(name[i]))  
        return 0;
    return 1;
}

short intNumFormatable(char *numStr) {
    if (numStr == NULL)
        return 0;

    int i = (numStr[0] == '-') ? 1 : 0;
    while (i < strlen(numStr)) {
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

short ageValidated(char *age) {
    return 1;
}

short phoneNumberValidated(char *phoneNum) {
    return 1;
} 

short birthDayValidated(char *birthDay) {
    return 1;
}