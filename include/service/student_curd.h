#ifndef STUDENT_CURD_H
#define STUDENT_CURD_H

#include "../model/student.h"

Student *getStudentList();
int getStudentListSize();

void init();
void endCURD();

void addStudent();
void printStudentList(Student *studentList, size_t listSize);
void addStudentToList(Student *student);
void run();

#endif