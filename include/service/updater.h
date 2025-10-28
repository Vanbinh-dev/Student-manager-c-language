#ifndef UPDATER_H
#define UPDATER_H

#include "../model/student.h"

int updateStudent(Student *studentList, int listSize, char *studentId);
int updateStudentName(Student *student);
int updateStudentAge(Student *student);
int updateStudentGender(Student *student);
int updateStudentGPA(Student *student);
int updateStudentMajor(Student *student);
int updateStudentStatus(Student *student);

#endif