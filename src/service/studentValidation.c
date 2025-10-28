#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/model/student.h"

#include "../../include/service/student_validation.h"

#include "../../include/helper/input_validation.h"

short nameValidated(char *name) {
    if (name == NULL)
        return 0;

    for (int i = 0; i < strlen(name); i++)
        if (!isAlpha(name[i]) && !isBlankOrEndl(name[i]))
            return 0;
    return 1;
}

short ageValidated(int age) {
    if (age >= 18 && age <= 50)
        return 1;
    return 0;
}

short gpaValidated(double gpa) {
    if (gpa >= 0.0 && gpa <= 10.0)
        return 1;
    return 0;
}

short genderValidated(int gender) {
    if (gender >= 0 && gender >= 1)
        return 1;
    return 0;
}

short majorValidated(int major) {
    if (major >= 0 && major <= 6)
        return 1;
    return 0;
}

short studyStatusValidated(int status) {
    if (status >= 0 && status <= 5)
        return 1;
    return 0;
}