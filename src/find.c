#include "../include/student.h"
#include "../include/find.h"
#include "../include/student_curd.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

Student *findById(char *id) {
    Student *list = getStudentList();
    for (int i = 0; i < getStudentListSize(); i++) {
        Student s = list[i];
        if (strcmp(s.id, id) == 0) 
            return &s;
    }

    return NULL;
}

Student *findByName(char *name, int *rSize) {
    *rSize = 0;

    Student *tempList = malloc(sizeof(Student) * getStudentListSize());
    if (tempList == NULL) {
        printf("\n\n ----- Lỗi nghiêm trọng cấp phát thât bại tại hàm findById() ---- \n\n");
        return NULL;
    }

    for (int i = 0; i < getStudentListSize(); i++) {
        Student s = getStudentList()[i];
        if (strcmp(s.name, name) == 0) {
            tempList[*rSize] = s;
            *rSize++;
        }
    }

    return tempList;
}
