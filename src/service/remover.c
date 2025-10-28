#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/model/student.h"

#include "../../include/service/remover.h"
#include "../../include/service/student_curd.h"
#include "../../include/service/finder.h"

#include "../../include/helper/input_helper.h"

int removeStudent(Student *studentList, int *listSize, char *studentId) {
    int index;

    Student *removeStudent = findStudentById(studentId, &index);
    if (index == -1) 
        return 1;

    free(studentList[*listSize].name);
    free(studentList[*listSize].id);
    
    for (int i = index; i < *listSize - 1;  i++) 
        studentList[i] = studentList[i + 1];

    printf("Student with ID %s has been removed successfully.\n", studentId);
    *listSize = *listSize - 1;

    return 1;
}