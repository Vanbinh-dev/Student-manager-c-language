#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/model/student.h"
#include "../../include/model/gender.h"
#include "../../include/model/major.h"
#include "../../include/model/study_status.h"

#include "../../include/service/updater.h"
#include "../../include/service/student_curd.h"
#include "../../include/service/student_validation.h"
#include "../../include/service/finder.h"

#include "../../include/helper/input_helper.h"

void printChoiceTable() {
    printf("\n");
    printf("Choose field to update:\n");
    printf("1. Name\n");
    printf("2. Age\n");
    printf("3. Gender\n");
    printf("4. GPA\n");
    printf("5. Major\n");
    printf("6. Status\n");
    printf("0. Exit\n");
    printf("\n");
}

int updateStudentName(Student *student) {
    char *newName = NULL;

    do {
        newName = completeInput(35, "Enter new name: ");
        if (nameValidated(newName) == 0) {
            printf("Validating name: %s\n", newName);
            printf("Please enter a valid name.\n");
        }
    } while(nameValidated(newName) == 0);

    free(student->name);
    student->name = malloc(sizeof(char) * (strlen(newName) + 1));
    strcpy(student->name, newName);
    free(newName);
    printf("Name updated successfully!\n");

    return 1;
}

int updateStudentAge(Student *student) {
    int newAge;
    do {
        newAge = completeIntInput("Enter new age: ");
        if (ageValidated(newAge) == 0) {
            printf("Validating age: %d\n", newAge);
            printf("Enter a valid age (18-50).\n");
        }
    } while(ageValidated(newAge) == 0);

    student->age = newAge;
    printf("Age updated successfully!\n");

    return 1;
}

int updateStudentGender(Student *student) {
    int newGender;
    do {
        newGender = completeIntInput("Enter new gender (0: Male, 1: Female");
        if (newGender != 0 || newGender != 1) 
            printf("Invalid gender!\n");
        }  while (newGender!= 0 || newGender != 1);

    student->gender = newGender;
    printf("Gender updated successfully!\n");
    return 1;
}

int updateStudentGPA(Student *student) {
    float newGPA;
    do {
        newGPA = completeDoubleInput("Enter new GPA: ");
        if (gpaValidated(newGPA) == 0) {
            printf("Validating GPA: %.2f\n", newGPA);
            printf("Enter a valid GPA (0.0 - 4.0).\n");
        }
    } while(gpaValidated(newGPA) == 0);

    student->gpa = newGPA;
    printf("GPA updated successfully!\n");

    return 1;
}

int updateStudentMajor(Student *student) {
    int newMajor;
    do {
        newMajor = completeIntInput("Enter new major code: ");
        if (majorValidated(newMajor) == 0) {
            printf("Validating major: %d\n", newMajor);
            printf("Enter a valid major (0-4).\n");
        }
    } while(majorValidated(newMajor) == 0);

    student->major = newMajor;
    printf("Major updated successfully!\n");

    return 1;
}

int updateStudentStatus(Student *student) {
    int newStatus;
    do {
        newStatus = completeIntInput("Enter study status code: ");
        if (studyStatusValidated(newStatus) == 0) {
            printf("Validating status: %d\n", newStatus);
            printf("Enter a valid status (0-2).\n");
        }
    } while(studyStatusValidated(newStatus) == 0);

    student->status = newStatus;
    printf("Status updated successfully!\n");

    return 1;
}

int updateStudent(Student *studetnList, int listSize, char *studentId) {
    int index;
    Student *student = findStudentById(studentId, &index);
    if (student == NULL)  {
        printf("Cannot find student with ID %s\n", studentId);
        free(studentId);

        return -1;
    }
    else 
        printf("Found student with ID %s. Proceeding to update.\n", studentId);


    int command;
    do {
        printChoiceTable();
        command = completeIntInput("Enter field number to update (0 to exit): ");

        switch (command) {
            case 0:
                printf("Exiting update menu...\n");
                break;
            case 1:
                updateStudentName(student);
                break;
            case 2:
                updateStudentAge(student);
                break;
            case 3:
                updateStudentGender(student);
                break;
            case 4:
                updateStudentGPA(student);
                break;
            case 5:
                updateStudentMajor(student);
                break;
            case 6:
                updateStudentStatus(student);
                break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

    } while (command != 0);
}