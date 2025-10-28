#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/model/student.h"

#include "../../include/service/finder.h"
#include "../../include/service/student_curd.h"

#include "../../include/helper/input_helper.h"
#include "../../include/helper/printer.h"

void printFindMenu() {
    printf("\n");
    printf("Find Student Menu:\n");
    printf("1. Find by ID\n");
    printf("2. Find by Name\n");
    printf("0. Return to Main Menu\n");
    printf("\n");
}

void findStudent() {
    int command = -1;
    do {
        printFindMenu();
        command = completeIntInput("Enter command: ");
        
        switch (command) {
        case 0:
            printf("Returning to main menu...\n");
            break;
        case 1:
            char *id = completeInput(10, "Enter student ID to find: ");
            int index;
            Student *student = findStudentById(id, &index);

            if (student == NULL)
                printf("Can not find studnet with id %s: ", id);
            else 
                printStudent(*student);
            break;
        case 2:
            char *name = completeInput(35, "Enter student name to find: ");
            int resultSize = 0;
            Student *foundStudents = findStudentByName(name, &resultSize);

            if (resultSize == 0) {
                printf("Can not find student with name %s\n", name);
            } else {
                printStudentList(foundStudents, resultSize);
            }

            free(foundStudents);
            break;
        default:
            printf("Function not implemented yet!\n");
            break;
        }
    } while (command != 0);
}

Student *findStudentById(char *id, int *index) {
    Student *list = getStudentList();
    for (int i = 0; i < getStudentListSize(); i++) {
        Student s = list[i];
        if (strcmp(s.id, id) == 0) {
            *index = i;
            return &(list[i]);
        }
    }

    *index = -1;
    printf("\n Can not find student with id %s", id);
    return NULL;
}

Student *findStudentByName(char *name, int *rSize) {
    int listSize = getStudentListSize(), size = 0;
    Student *tempList = malloc(sizeof(Student));

    if (tempList == NULL) {
        printf("Malloc error in findByName function\n");
        return NULL;
    }

    for (int i = 0; i < listSize; i++) {
        Student s = getStudentList()[i];
        if (strcmp(s.name, name) == 0)
            tempList[size++] = s;
    }

    *rSize = size;
    return tempList;
}