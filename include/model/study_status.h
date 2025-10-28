#ifndef STUDY_STATUS_H
#define STUDY_STATUS_H

typedef enum {
    ENROLLED,      // Đang học
    ON_LEAVE,      // Bảo lưu
    WITHDRAWN,     // Nghỉ học
    GRADUATED,     // Tốt nghiệp
    SUSPENDED,     // Tạm ngưng
    TRANSFERRED    // Chuyển trường
} StudyStatus;

#endif
