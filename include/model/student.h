#ifndef STUDENT_H
#define STUDENT_H

#include "gender.h"
#include "major.h"
#include "study_status.h"

char *newId();
char *getGenderName(int value);
char *getStudyStatusName(int value);
char *getMajorName(int value);

typedef struct {
    char *id;
    char *name;
    short age;
    Gender gender;
    float gpa;
    Major major;
    StudyStatus status;
} Student;

#define STUDENT_DEFINED_FIELDS 7

#endif