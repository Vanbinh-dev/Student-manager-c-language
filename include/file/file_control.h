#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "../model/student.h"

int createFile();

Student *loadData(char *datasource, int *rSize);
void saveData(char *datasource, Student *studentList, int listSize);

#endif