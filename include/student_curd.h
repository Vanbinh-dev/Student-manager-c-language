#ifndef STUDENT_CURD_H
#define STUDENT_CURD_H

#include "../include/student.h"

Student *getStudentList();
int getStudentListSize();

void setup();
void endCURD();

void addStudent();
void printStudentList();

#endif