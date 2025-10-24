#ifndef FIND_H
#define FIND_H

#include "../include/student.h"

Student *findById(char *id);
Student *findByName(char *name, int *rSize); // Return temp student array!

#endif