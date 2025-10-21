#include "../include/add_update.h"
#include "../include/student.h"
#include "../include/validation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getId()
{
    return "00000000";
}

void printStudyStatusList()
{
    char studyStatusList[][100] = {
        "Enrolled - 1",
        "On leave - 2",
        "Withdraw - 3",
        "Graduated - 4",
        "Suspened - 5",
        "Transfered - 6"
    };

    printf("Chon tinh trang hoc tap!\n");
    
    for (int i = 0; i < 6; i++)
        printf("%s\n", studyStatusList[i]);
}

void printMajorList()
{
    char majorList[][100] = {
        "Artificial Intelligence - 1",
        "Software Engineer - 2",
        "Integrated Circuit - 3",
        "Networking - 4",
        "Data analysis - 5",
        "Data science - 6",
        "Tester - 7"
    };

    printf("Chon chuyen nganh!\n");

    for (int i = 0; i < 7; i++)
        printf("%s\n", majorList[i]);
}
void changeName(char **updateName)
{
    int nameSize = 200;
    char _command = '0';
    char *name = malloc(sizeof(char) * nameSize);

    if (!name)
    {
        printf("\n\nThay doi bat thanh!!!\n\n");
        return;
    }

    do
    {
        printf("Nhap ten sinh vien: ");
        fgets(name, nameSize, stdin);
        if (strlen(name) == nameSize)
        {
            printf("Dat lai ten dai hon khong? Nhap y de tiep tuc: ");
            scanf("%c", &_command);
        }

        if (_command == 'y')
        {
            nameSize *= 2;
            name = realloc(name, sizeof(char) * nameSize);
        }

        if (!nameValidated(name))
        {
            printf("Nhap ten khong hop le");
            continue;
        }

    } while (_command == 'y');

    if (!updateName)
        free(*updateName);
    *updateName = name;
}

int changeAge()
{
    char input[2];
    int age = -1;

    do
    {
        printf("Nhap tuoi sinh vien!");
        printf("Nhap: ");
        fgets(input, 2, stdin);

        if (!intNumFormatable(input) || age < 18 || age > 90)
        {
            printf("\n-------Nhap sai dinh dang hoac so tuoi qua quy dinh!-------\n");
            continue;
        }

        age = atoi(input);
    } while (age >= 18 && age <= 90);

    return age;
}

void changeBirthday(char **birthDay)
{
    char *input = malloc(sizeof(char) * 11);
    if (input == NULL)
        return;

    do
    {
        printf("Nhap ngay thang nam sinh theo dinh dang sau 01 01 2111!\n");
        printf("Nhap: ");
        fgets(input, 11, stdin);

        if (!birthDayValidated(input))
            printf("\nNhap sai dinh dang!Nhap lai!\n");

    } while (!birthDayValidated(input));

    if (*birthDay == NULL)
        free(*birthDay);

    *birthDay = input;
}

void changePhoneNum(char **phoneNum)
{
    char *input = malloc(sizeof(char) * 12);
    do
    {
        printf("Nhap so dien thoai! Nhap so: ");
        fgets(input, 12, stdin);
        if (!intNumFormatable(input))
            printf("\nNhap sai roi! Nhap lai di!\n");
    } while (!intNumFormatable(input));

    if (*phoneNum != NULL)
        free(*phoneNum);
    *phoneNum = input;
}

Gender changeGender(char *str)
{
    if (strcmp(str, "1") == 0)
        return FEMALE;
    return MALE;
}

Major chooseMajor(char *str)
{
    if (strcmp(str, "1") == 0)
        return AI;
    else if (strcmp(str, "2") == 0)
        return SE;
    else if (strcmp(str, "3") == 0)
        return IC;
    else if (strcmp(str, "4") == 0)
        return NET;
    else if (strcmp(str, "5") == 0)
        return DA;
    else if (strcmp(str, "6") == 0)
        return DS;
    else if (strcmp(str, "7") == 0)
        return TE;

    return SE; // Default;
}

StudyStatus changeStudyStatus(char *status)
{
    if (strcmp(status, "0") == 0)
        return ENROLLED;
    else if (strcmp(status, "1") == 0)
        return ON_LEAVE;
    else if (strcmp(status, "2") == 0)
        return WITHDRAWN;
    else if (strcmp(status, "3") == 0)
        return GRADUATED;
    else if (strcmp(status, "4") == 0)
        return SUSPENDED;
    else if (strcmp(status, "5") == 0)
        return TRANSFERRED;

    return ENROLLED; // Default
}

Student newStudent()
{
    Student student;
    char *name;
    student.age = changeAge();
    char input[100];

    changeName(&name);

    printf("Chon gioi tinh.");
    printf("Female - 1\n");
    printf("Male - 2\n");
    printf("Nhap: ");
    fgets(input, 2, stdin);
    student.gender = changeGender(input);

    printMajorList();
    printf("Nhap: ");
    fgets(input, 2, stdin);
    student.major = chooseMajor(input);

    student.id = getId();
    student.name = name;
    student.birthday = "00/00/0000";
    student.phoneNum = "xxxxxxxxxxxx";
    student.major = chooseMajor(input);
    student.gpa = 0.0;

    return student;
}