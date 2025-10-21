#include "../include/student.h"
#include "../include/student_curd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Student *studentList;
int capacity = 100;

void setup() {
    if (studentList == NULL)
        studentList = malloc(sizeof(Student) * capacity);
    if (studentList != NULL)
        printf("Complete setup!");
}

void endCURD() {
    if (studentList != NULL)
        free(studentList);
}