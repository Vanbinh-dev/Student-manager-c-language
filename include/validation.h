#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>

short intNumFormatable(char *numStr);
short doubleNumFormatable(char *numStr);

short nameValidated(char *name);
short ageValidated(char *age);
short birthDayValidated(char *birhtday);
short phoneNumberValidated(char *phoneNumber);
short gpaValidated(char *gpa);

#endif