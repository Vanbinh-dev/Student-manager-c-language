#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/error_code.h"

#include "../../include/helper/input_helper.h"
#include "../../include/helper/input_validation.h"

static void removeExtraBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safeInput(char** buffer, size_t maxLen, const char* message) {
    char* tempBuffer = malloc(sizeof(char) * (maxLen + 1));
    
    if (tempBuffer == NULL)
        return MALLOC_ERROR;
    
    if (message != NULL)
        printf("%s", message);
    
    if (fgets(tempBuffer, maxLen + 1, stdin) == NULL) {
        free(tempBuffer);
        return READ_ERROR;
    }
    
    size_t len = strlen(tempBuffer);
    
    // Kiểm tra buffer đầy: không có \n và độ dài = maxLen
    if (len == maxLen && tempBuffer[len - 1] != '\n') {
        removeExtraBuffer();
        free(tempBuffer);
        return EXTRA_INPUT;
    }
    
    // Xóa \n nếu có
    if (len > 0 && tempBuffer[len - 1] == '\n')
        tempBuffer[len - 1] = '\0';
    
    // Kiểm tra chuỗi rỗng
    if (strlen(tempBuffer) == 0) {
        free(tempBuffer);
        return EMPTY_INPUT;
    }
    
    // Giải phóng buffer cũ
    if (*buffer != NULL)
        free(*buffer);
    
    *buffer = tempBuffer;
    return SUCCESS;
}

int safeIntInput(int* value, const char* message) {
    char* buffer = NULL;
    char* endptr;
    long temp;
    
    if (message != NULL)
        printf("%s", message);
    
    if (fgets(buffer = malloc(100), 100, stdin) == NULL) {
        free(buffer);
        return READ_ERROR;
    }
    
    size_t len = strlen(buffer);
    
    // Kiểm tra buffer đầy
    if (len == 99 && buffer[len - 1] != '\n') {
        removeExtraBuffer();
        free(buffer);
        return EXTRA_INPUT;
    }
    
    // Xóa \n
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    
    // Kiểm tra rỗng
    if (strlen(buffer) == 0) {
        free(buffer);
        return EMPTY_INPUT;
    }
    
    // Chuyển đổi sang số
    errno = 0;
    temp = strtol(buffer, &endptr, 10);
    
    // Kiểm tra lỗi chuyển đổi
    if (errno == ERANGE || temp > INT_MAX || temp < INT_MIN) {
        free(buffer);
        return OVERFLOW_ERROR;
    }
    
    if (*endptr != '\0') {
        free(buffer);
        return INVALID_INPUT;
    }
    
    *value = (int)temp;
    free(buffer);
    return SUCCESS;
}

int safeDoubleInput(double* value, const char* message) {
    char* buffer = NULL;
    char* endptr;
    double temp;
    
    if (message != NULL)
        printf("%s", message);
    
    if (fgets(buffer = malloc(100), 100, stdin) == NULL) {
        free(buffer);
        return READ_ERROR;
    }
    
    size_t len = strlen(buffer);
    
    // Kiểm tra buffer đầy
    if (len == 99 && buffer[len - 1] != '\n') {
        removeExtraBuffer();
        free(buffer);
        return EXTRA_INPUT;
    }
    
    // Xóa \n
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    
    // Kiểm tra rỗng
    if (strlen(buffer) == 0) {
        free(buffer);
        return EMPTY_INPUT;
    }
    
    // Chuyển đổi sang số
    errno = 0;
    temp = strtod(buffer, &endptr);
    
    // Kiểm tra lỗi chuyển đổi
    if (errno == ERANGE) {
        free(buffer);
        return OVERFLOW_ERROR;
    }
    
    if (*endptr != '\0') {
        free(buffer);
        return INVALID_INPUT;
    }
    
    *value = temp;
    free(buffer);
    return SUCCESS;
}

char* completeInput(size_t maxLen, const char* message) {
    char* buffer = NULL;
    int result;
    
    do {
        result = safeInput(&buffer, maxLen, message);
        
        switch (result) {
            case MALLOC_ERROR:
                printf("Lỗi: Không đủ bộ nhớ!\n");
                return NULL;
            case READ_ERROR:
                printf("Lỗi: Không thể đọc dữ liệu!\n");
                break;
            case EXTRA_INPUT:
                printf("Lỗi: Nhập quá dài! Tối đa %zu ký tự. Vui lòng nhập lại.\n", maxLen);
                break;
            case EMPTY_INPUT:
                printf("Lỗi: Không được để trống! Vui lòng nhập lại.\n");
                break;
            case SUCCESS:
                return buffer;
        }
    } while (result != SUCCESS);
    
    return buffer;
}

int completeIntInput(const char* message) {
    int value = 0;
    int result;
    
    do {
        result = safeIntInput(&value, message);
        
        switch (result) {
            case READ_ERROR:
                printf("Lỗi: Không thể đọc dữ liệu!\n");
                break;
            case EXTRA_INPUT:
                printf("Lỗi: Nhập quá dài! Vui lòng nhập lại.\n");
                break;
            case EMPTY_INPUT:
                printf("Lỗi: Không được để trống! Vui lòng nhập lại.\n");
                break;
            case INVALID_INPUT:
                printf("Lỗi: Không phải số nguyên hợp lệ! Vui lòng nhập lại.\n");
                break;
            case OVERFLOW_ERROR:
                printf("Lỗi: Số quá lớn hoặc quá nhỏ! Vui lòng nhập lại.\n");
                break;
            case SUCCESS:
                return value;
        }
    } while (result != SUCCESS);
    
    return value;
}

double completeDoubleInput(const char* message) {
    double value = 0.0;
    int result;
    
    do {
        result = safeDoubleInput(&value, message);
        
        switch (result) {
            case READ_ERROR:
                printf("Lỗi: Không thể đọc dữ liệu!\n");
                break;
            case EXTRA_INPUT:
                printf("Lỗi: Nhập quá dài! Vui lòng nhập lại.\n");
                break;
            case EMPTY_INPUT:
                printf("Lỗi: Không được để trống! Vui lòng nhập lại.\n");
                break;
            case INVALID_INPUT:
                printf("Lỗi: Không phải số thực hợp lệ! Vui lòng nhập lại.\n");
                break;
            case OVERFLOW_ERROR:
                printf("Lỗi: Số quá lớn hoặc quá nhỏ! Vui lòng nhập lại.\n");
                break;
            case SUCCESS:
                return value;
        }
    } while (result != SUCCESS);
    
    return value;
}