#ifndef FIND_H
#define FIND_H

#include "../model/student.h"

void printFindMenu();

void findStudent();
Student *findStudentById(char *id, int *index);
Student *findStudentByName(char *name, int *rSize); // Return temp student array!

#endif