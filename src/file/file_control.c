#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/file/file_control.h"

#include "../../include/model/student.h"

#include "../../include/helper/string_helper.h"

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