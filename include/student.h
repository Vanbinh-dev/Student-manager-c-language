#ifndef STUDENT_H
#define STUDENT_H

typedef enum {MALE, FEMALE} Gender;

typedef enum {
    AI, SE, IC, NET, DA, DS, TE
} Major;

typedef enum {
    ENROLLED,      // Đang học
    ON_LEAVE,      // Bảo lưu
    WITHDRAWN,     // Nghỉ học
    GRADUATED,     // Tốt nghiệp
    SUSPENDED,     // Tạm ngưng
    TRANSFERRED    // Chuyển trường
} StudyStatus;

typedef struct {
    char *id;
    char *name;
    short age;
    Gender gender;
    char *birthday;
    char *phoneNum;
    float gpa;
    Major major;
    StudyStatus status;
} Student;

#endif