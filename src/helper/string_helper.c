#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/helper/string_helper.h"

char** stringSplit(const char *str, char delimiter, int *getSize) {
    if (str == NULL || getSize == NULL) {
        return NULL;
    }

    // Đếm số lượng delimiter để tính số phần tử
    int delimiterCount = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delimiter) {
            delimiterCount++;
        }
    }
    
    // Số phần tử = số delimiter + 1
    *getSize = delimiterCount + 1;
    
    // Cấp phát mảng con trỏ
    char **result = (char**)malloc((*getSize) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }
    
    // Tạo bản sao của chuỗi gốc để xử lý
    char *strCopy = (char*)malloc((strlen(str) + 1) * sizeof(char));
    if (strCopy == NULL) {
        free(result);
        return NULL;
    }
    strcpy(strCopy, str);
    
    // Tách chuỗi
    int index = 0;
    char *token = strtok(strCopy, &delimiter);
    
    while (token != NULL) {
        result[index] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (result[index] == NULL) {
            // Giải phóng bộ nhớ đã cấp phát nếu lỗi
            for (int i = 0; i < index; i++) {
                free(result[i]);
            }
            free(result);
            free(strCopy);
            return NULL;
        }
        strcpy(result[index], token);
        index++;
        token = strtok(NULL, &delimiter);
    }
    
    free(strCopy);
    return result;
}

// Hàm giải phóng bộ nhớ cho kết quả của stringSplit
void freeStringSplit(char **array, int size) {
    if (array == NULL) return;
    
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}