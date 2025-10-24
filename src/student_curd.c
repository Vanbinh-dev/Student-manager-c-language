#include "../include/student.h"
#include "../include/student_curd.h"
#include "../include/print.h"
#include "../include/validation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student *studentList;
char datasource[] = "resource/data.txt";

int listSize;
int capacity = 100;

Student *getStudentList() {
    return studentList;
}

int getStudentListSize() {
    return listSize;
}

void addStudentToList(Student s) {
    if (listSize + 1 == capacity) {
        Student *tempList = realloc(studentList, capacity * 2);
        if (tempList == NULL) {
            printf("\n\n----------Lỗi nghiêm trọng. Không thể nới rộng nơi lưu trữ!-------\n\n");
            return;
        }

        capacity *= 2;
        free(studentList);
        studentList = tempList;
    }

    studentList[listSize] = s;
    listSize++;
}

void createFile()
{
    FILE *f = fopen(datasource, "a+");
    fclose(f);
}

short getData()
{
    FILE *f = fopen(datasource, "r");
    if (f == NULL)
        return 0;

    char id[10], name[50];
    double gpa;
    int age, gender, major, status;

    while (fscanf(f, "%[^;];%[^;];%d;%d;%lf;%d;%d\n",
                  id,
                  name,
                  &age,
                  &gender,
                  &gpa,
                  &major,
                  &status) != EOF) {
        Student s;
        s.id = malloc(sizeof(char) * strlen(id) + 1);
        strcpy(s.id, id);
        s.name = malloc(sizeof(char) * strlen(name) + 1);
        strcpy(s.name, name);   

        s.age = age;
        s.gender = gender;
        s.gpa = gpa;
        s.major = major;
        s.status = status;

        addStudentToList(s);
    }   

    fclose(f);
    return 1;
}

void saveData()
{
    FILE *f = fopen(datasource, "w+");
    if (f == NULL)
    {
        printf("Không tìm được file!");
        return;
    }

    for (int i = 0; i < listSize; i++)
    {
        Student s = studentList[i];
        fprintf(f, "%s;%s;%d;%d;%.2f;%d;%d\n",
                s.id,
                s.name,
                s.age,
                s.gender,
                s.gpa,
                s.major,
                s.status);
    }

    fclose(f);
}

void setup()
{
    if (studentList == NULL)
        studentList = malloc(sizeof(Student) * capacity);

    if (studentList != NULL)
    {
        printf("Complete setup!\n");
        if (getData())
        {
            printf("Lấy dữ liệu thành công!\n");
            return;
        }
        else
            printf("Lấy dữ liệu thất bại. Tạo lại file!\n");

        createFile();

        if (getData() == 0)
            printf("Thất bại lần 2! Kết thúc chương trình thủ công bằng cách nhấn ctrl + c\n");
        else
            printf("Tạo file thành công. Tiếp tục chương trình. Tuy nhiên chương trình không có dữ liệu!\n");
    }
}

void endCURD()
{
    printf("\nKết thúc chương trình");
    saveData();
    free(studentList);
}

void printStudentList(Student *list) {
    if (list == NULL)
        return;

    printf("\n");
    printLine();
    printf("| %-9s | %-35s | %-3s | %-4s | %-5s | %-23s | %-13s |\n",
           "ID",
           "Name",
           "Age",
           "Gender",
           "GPA",
           "Major",
           "Status");

    for (int i = 0; i < listSize; i++)
        printStudent(list[i]);
    printLine();
}

void formatableIntNumInput(int *num, int maxSizeNum, char *mess) {
    char *input = malloc(sizeof(char) * maxSizeNum);

    do {
        printf("%s", mess);
        fgets(input, maxSizeNum, stdin);
        if (intNumFormatable(input))
            break;

        printf("Hãy nhập đúng định dạng\n");
    } while (1);

    *num = atoi(input);
}

void formatableDoubleNumInput(double *num, int maxSizeNum, char *mess) {
    char *input = malloc(sizeof(char) * maxSizeNum);

    do {
        printf("%s", mess);
        fgets(input, maxSizeNum, stdin);
        printf("%s %d \n", input, doubleNumFormatable(input));
        if (doubleNumFormatable(input) == 1)
            break;

        printf("Hãy nhập đúng định dạng\n");
    } while (1);

    *num = atof(input);
}

void addStudent()
{
    int nameSize = 35;
    char *name = malloc(sizeof(char) * nameSize);

    if (name == NULL)
    {
        printf("\n ----- Cấp phát bộ nhớ thất bại ----- \n");
        return;
    }

    do {
        printf("Nhập tên không dấu: ");
        fgets(name, nameSize, stdin);

        if (nameValidated(name))
            break;

        printf("Hãy nhập tên đúng định dạng!\n");
    } while (1);


    for (int i = 0; i < strlen(name); i++)
        if (name[i] == '\n')
            name[i] = ' ';
    
    int age;
    formatableIntNumInput(&age, 3, "Nhập số tuổi: ");
    
    while (age < 18 || age > 30)  {
        printf("Số tuổi không thể quá 30 hay nhỏ hơn 18!\n");
        formatableIntNumInput(&age, 3, "Nhập số tuổi: ");
    }

    int gender;
    printGenderList();
    scanf("%d", &gender);

    double gpa;
    formatableDoubleNumInput(&gpa, 8, "Nhập giá trị gpa: ");
    
    while (gpa >= 10 || gpa <= 0)   {
        printf("Gpa không thể quá 10 hoặc bé hơn 0\n");
        formatableDoubleNumInput(&gpa, 8, "Nhập giá trị gpa: ");
    }

    int major;
    printMajorList();
    formatableIntNumInput(&major, 3, "Nhập chọn chuyên ngành. Nếu nhập sai mặc định là SE: ");

    Student s;

    s.id = newId();
    s.name = name;
    s.age = age;
    s.gender = gender;
    s.gpa = gpa;
    s.major = major;
    s.status = ENROLLED;

    addStudentToList(s);
}