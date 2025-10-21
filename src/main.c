#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/validation.h"

int main() {
    char name[] = "Nguyen Van A";
    char not_Name[] = "N23 ";
    printf("%d\n", nameValidated(name));
    printf("%d", nameValidated(not_Name));

    return 0;
}