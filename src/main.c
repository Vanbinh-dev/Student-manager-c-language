#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool intNumFormatable(char *numStr) {   
    int i = (numStr[0] == '-') ? 1 : 0;
    for (i; i < strlen(numStr); i++)
        if (numStr[i] < 48 || numStr[i] > 57)
            return false;

    return true;
}

bool doubleNumFormatable(char *numStr) {
    short dots = 0;
    int i = (numStr[0] == '-') ? 1 : 0;

    for (i; i < strlen(numStr); i++) {
        if (numStr[i] == '.') {
            dots++;
            continue;
        }

        if (dots >= 2 || numStr[i] < 48 || numStr[i] > 57)
            return false;
    }

    return true;
}

int main() {
    return 0;
}