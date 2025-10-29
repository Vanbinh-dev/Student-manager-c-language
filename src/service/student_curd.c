#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/model/student.h"
#include "../../include/model/gender.h"
#include "../../include/model/major.h"
#include "../../include/model/study_status.h"

#include "../../include/service/student_curd.h"
#include "../../include/service/student_validation.h"
#include "../../include/service/finder.h"
#include "../../include/service/updater.h"
#include "../../include/service/remover.h"

#include "../../include/error_code.h"

#include "../../include/helper/input_helper.h"
#include "../../include/helper/printer.h"

#include "../../include/file/file_control.h"

Student *studentList = NULL;
int listSize = 0;
int capacity = 100;
char datasource[] = "resource/data.txt";

Student *getStudentList() { return studentList; }
int getStudentListSize() { return listSize; }

char *simpleIdInput(int id) {
    char *getId = malloc(sizeof(char) * 9);
    sprintf(getId, "%08d", id);
    return getId;
}

void addRawData() {
    Student students[10] = {
        {"00000001", "Alice",   20, 1, 3.8, 0, 0},
        {"00000002", "Bob",     21, 0, 3.2, 1, 0},
        {"00000003", "Charlie", 22, 0, 2.7, 2, 2},
        {"00000004", "Diana",   19, 1, 3.9, 3, 0},
        {"00000005", "Eve",     23, 1, 3.5, 4, 1},
        {"00000006", "Frank",   24, 0, 2.9, 0, 0},
        {"00000007", "Grace",   20, 1, 3.6, 1, 1},
        {"00000008", "Henry",   22, 0, 3.0, 2, 0},
        {"00000009", "Ivy",     21, 1, 3.7, 3, 0},
        {"00000010", "Jack",    25, 0, 2.4, 4, 2}
    };

    Student *s;
    for (int i = 0; i < 10; i++) {
        s = malloc(sizeof(Student));
        s->name = malloc(sizeof(char) * (strlen(students[i].name) + 1));
        s->id = newId();
        strcpy(s->name, students[i].name);
        s->age = students[i].age;
        s->gpa = students[i].gpa;
        s->gender = students[i].gender;
        s->major = students[i].major;
        s->status = students[i].status;

        addStudentToList(s);
    }
}

void init() {
    if (studentList == NULL)
        studentList = malloc(sizeof(Student) * capacity);
    
    // addRawData();
    loadData("resource/data.txt", &listSize);
    printf("Initialized student list with capacity %d\n", capacity);
}

void endCURD() {
    printf("Cleaning up student list...\n");
    saveData("resource/data.txt", studentList, listSize);

    if (studentList != NULL) {
        for (int i = 0; i < listSize; i++) {
            printf("Var i: %d\n ", i);
            
            if (studentList[i].id != NULL) {
                printf("Freeing student %d with ID: %s\n", i, studentList[i].id);
                free(studentList[i].id);
            }

            if (studentList[i].name != NULL) {
                printf("Freeing student %d with Name: %s\n", i, studentList[i].name);
                free(studentList[i].name);
            }
        }

        if (studentList != NULL) {
            printf("Freeing student list memory...\n");
            free(studentList);
            printf("Student list memory freed.\n");
        }
        studentList = NULL;
        listSize = 0;
    }
}

void printStudentList(Student *list, size_t listSize) {
    printLine();
    printf("| %-9s | %-35s | %3s | %-5s | %7s | %-23s | %-13s|\n", "ID", "Name", "Age", "Gender", "GPA", "Major", "Status"); 
    for (int i = 0; i < listSize; i++) 
        printStudent(list[i]);

    printLine();
}

void run() {
    init();

    int command = -1;
    char *studentId = NULL;
    do {
        printChoice();
        command = completeIntInput("Enter your choice: ");

        switch (command) {
        case 0:
            printf("Exiting program...\n");
            break;
        case 1:
            printStudentList(studentList, listSize);
            command = completeIntInput("Press any number to continue:  ");
            break;
        case 2:
            addStudent();
            break;
        case 3:
            printf("Edit student function!\n");
            studentId = simpleIdInput(completeIntInput("Enter student id only number: "));
            updateStudent(studentList, listSize, studentId);
            free(studentId);
            studentId = NULL;
            break;
        case 4:
            printf("Remove student function!\n");
            studentId = simpleIdInput(completeIntInput("Enter student id only number: "));
            removeStudent(studentList, &listSize, studentId);
            free(studentId);
            studentId = NULL;
            break;
        case 5:
            printf("Find student function\n");
            findStudent();
            break;
        default:
            printf("Function not implemented yet!\n");
        }

    } while (command != 0);

    endCURD();
}

void addStudentToList(Student *student) {
    if (listSize >= capacity) {
        Student *tempList = realloc(studentList, sizeof(Student) * capacity);
        if (tempList == NULL) {
            printf("Lỗi: Không thể mở rộng danh sách sinh viên!\n");
            return;
        }

        free(studentList);
        studentList = tempList;
        capacity *= 2;
    }

    studentList[listSize++] = *student;
    free(student);
}

void addStudent() {
    char *name = NULL;
    int age, genderInput, majorInput, statusInput;
    double gpa;

    do {
        int code = safeInput(&name, 35, "Nhập tên sinh viên: ");
        if (nameValidated(name) == 0 || code != SUCCESS) {
            printf("Tên không hợp lệ. Vui lòng chỉ sử dụng chữ cái và khoảng trắng.\n");
            free(name);
            name = NULL;
        }

    } while (name == NULL);

    do {
        age = completeIntInput("Nhập tuổi sinh viên (18-50): ");
        if (age < 18 || age > 50) {
            printf("Tuổi không hợp lệ. Vui lòng nhập tuổi trong khoảng 18 đến 50.\n");
        }
    } while (age < 18 || age > 50);

    printGenderList();
    printf("Nhập giá trị giới tính (0-1). Mặc định là 1: ");
    genderInput = completeDoubleInput("Nhập giá trị giới tính (0-1). Mặc định là 1: ");

    do {
        gpa = completeDoubleInput("Nhập GPA sinh viên (0.0-10.0): ");
        if (gpa < 0.0 || gpa > 10.0) {
            printf("GPA không hợp lệ. Vui lòng nhập GPA trong khoảng 0.0 đến 10.0.\n");
        }
    } while (gpa < 0.0 || gpa > 10.0);

    printMajorList();
    printf("Nhập giá trị chuyên ngành (0-6). Mặc định là SE: ");
    majorInput = completeIntInput("Nhập giá trị chuyên ngành (0-6). Mặc định là SE: ");

    printf("\n--- Code chạy đến đâu nhận ok ---\n");

    printf("\n--- Thông tin sinh viên nhận được ---\n");
    printf("Tên: %s\n", name);
    printf("Tuổi: %d\n", age);
    printf("Giới tính: %d\n", genderInput);
    printf("GPA: %.2f\n", gpa);
    printf("Chuyên ngành: %d\n", majorInput);
    printf("-------------------------------\n");

    Student *newStudent = malloc(sizeof(Student));

    printf("Trước copy!\n");
    newStudent->id = newId();
    newStudent->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(newStudent->name, name);

    printf("Copy thành công\n!");

    newStudent->id = newId();
    newStudent->age = age;
    newStudent->gender = genderInput;
    newStudent->gpa = gpa;
    newStudent->major = majorInput;
    newStudent->status = ENROLLED;


    addStudentToList(newStudent);
}