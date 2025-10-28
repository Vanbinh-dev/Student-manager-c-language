#include <math.h>

#include "../../include/helper/num_helper.h"

int countDigits(long long num) {
    int count = 0;  
    num = abs(num);

    do {
        count++;
        num /= 10;
    } while(num != 0);

    return count;
}