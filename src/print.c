#include "../include/print.h"

#include <stdio.h>
#include <stdlib.h>

void printLine() {
    printf("+-----------+-------------------------------------+-----+--------+-------+----------------------------------------+\n");
}

void printStudent(Student s) {
    printf("| %-8s | %-35s | %3d | %-5s | %5.2lf | %-23s | %-13s |\n", 
       s.id, 
       s.name, 
       s.age, 
       getGenderName(s.gender),
       s.gpa,
       getMajorName(s.major),
       getStudyStatusName(s.status)
    );
}

void printGenderList() {
    printf("\n========== CHỌN GIỚI TÍNH ==========\n");
    printf("  [0] Male (Nam)\n");
    printf("  [1] Female (Nữ)\n");
    printf("====================================\n");
    printf("Nhập: ");
}

void printMajorList() {
    printf("\n========== CHỌN CHUYÊN NGÀNH ==========\n");
    printf("  [0] AI  - Artificial Intelligence\n");
    printf("  [1] SE  - Software Engineering\n");
    printf("  [2] IC  - Information Communication\n");
    printf("  [3] NET - Network Engineering\n");
    printf("  [4] DA  - Data Analytics\n");
    printf("  [5] DS  - Data Science\n");
    printf("  [6] TE  - Technology Entrepreneurship\n");
    printf("=======================================\n");
    printf("Nhập: ");
}

void printStudyStatusList() {
    printf("\n========== CHỌN TRẠNG THÁI HỌC TẬP ==========\n");
    printf("  [0] Enrolled    - Đang học\n");
    printf("  [1] On Leave    - Bảo lưu\n");
    printf("  [2] Withdrawn   - Nghỉ học\n");
    printf("  [3] Graduated   - Tốt nghiệp\n");
    printf("  [4] Suspended   - Tạm ngưng\n");
    printf("  [5] Transferred - Chuyển trường\n");
    printf("=============================================\n");
    printf("Nhập: ");
}
