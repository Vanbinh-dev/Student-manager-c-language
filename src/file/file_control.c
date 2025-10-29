#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/file/file_control.h"

#include "../../include/model/student.h"

#include "../../include/helper/string_helper.h"
#include "../../include/helper/input_helper.h"
#include "../../include/helper/input_validation.h"

#include "../../include/service/student_curd.h"

int createFile() {
    FILE *f = fopen("resource/data.txt", "w+");
    if (f == NULL) {
        printf("Lỗi: Không thể tạo file dữ liệu!\n");
        return 0;
    }
    fclose(f);
    printf("File dữ liệu đã được tạo thành công.\n");

    return 1;
}

Student *loadData(char *datasource, int *rSize) {
    FILE *f = fopen(datasource, "r");
    int length = 0;

    if (f == NULL) {
        printf("Error: can not open file!\n");
        printf("Creating new file...\n");
        if (createFile() == 1)
            printf("Create new file succussfully! No data!\n");
        else 
            return NULL;
    }

    int maxSize = 255, arrSize;
    char *line = malloc(sizeof(char) * 255);
    char ** data;

    while (1) {
        if (fgets(line, maxSize, f) == NULL) {
            if (feof(f)) {
                break;
                printf("Đọc hết file!\n");
            }
            else {
                perror("Lỗi khi đọc file!\n");
                break;
            }
        }

        int len = 0;
        while (line[len] != '\0') 
            len++; 
    
        if (line[len - 1] != '\n')
            removeExtraBuffer();
        else if (line[len - 1] == '\n')  line[len - 1] = '\0';
        data = notNullStringSplit(line, ';', &arrSize);
        if (arrSize != STUDENT_DEFINED_FIELDS)
            continue;
        
        if (!isLegalContent(data[0]) || !isLegalContent(data[1])) {
            printf("Giá trị không hợp lệ: %s, %s", data[0], data[1]);
            continue;
        }

        Student *s = malloc(sizeof(Student));
        char *id = data[0], *name = data[1];
        int age = atoi(data[2]), gender = atoi(data[3]), major = atoi(data[5]), status = atoi(data[6]);
        double gpa = atof(data[4]);

        s->name = malloc(sizeof(char) * (strlen(name) + 1));
        s->id = malloc(sizeof(char) * (strlen(id) + 1));

        strcpy(s->name, name);
        strcpy(s->id, id);
        s->age = age;
        s->gender = gender;
        s->major = major;
        s->status = status;

        addStudentToList(s);

        printf("Giải phóng phần dư thừa!\n");
        freeStringArr(data, arrSize);
        data = NULL;
    } 

    free(line);

    printf("Get data successfully from file!\n");
    fclose(f);
}

void saveData(char *datasource, Student *studentList, int listSize) {
    FILE *f = fopen(datasource, "w+");
    if (f == NULL) {
        printf("Lỗi: Không thể mở file để lưu dữ liệu!\n");
        return;
    }

    for (int i = 0; i < listSize; i++) {
        Student student = studentList[i];
        fprintf(f, "%s;%s;%d;%d;%.2f;%d;%d\n",
                student.id,
                student.name,
                student.age,
                student.gender,
                student.gpa,
                student.major,
                student.status);
        }
    
    fclose(f);
}