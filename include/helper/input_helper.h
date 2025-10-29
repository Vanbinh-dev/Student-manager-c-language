#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#define SUCCESS 0
#define MALLOC_ERROR -1
#define READ_ERROR -2
#define EXTRA_INPUT -3
#define EMPTY_INPUT -4
#define INVALID_INPUT -5
#define OVERFLOW_ERROR -6

/**
 * @return: Gọi ngay sau khi sử dụng fgets để loại bỏ buffer thửa.
 */
void removeExtraBuffer();

/**
 * Đọc chuỗi an toàn từ stdin
 * @param buffer: Con trỏ tới con trỏ chuỗi (sẽ được cấp phát bộ nhớ)
 * @param maxLen: Độ dài tối đa (không bao gồm '\0')
 * @param message: Thông báo hiển thị trước khi nhập (có thể NULL)
 * @return: SUCCESS hoặc mã lỗi
 */
int safeInput(char** buffer, size_t maxLen, const char* message);

/**
 * Đọc số nguyên an toàn từ stdin
 * @param value: Con trỏ tới biến chứa kết quả
 * @param message: Thông báo hiển thị trước khi nhập (có thể NULL)
 * @return: SUCCESS hoặc mã lỗi
 */
int safeIntInput(int* value, const char* message);

/**
 * Đọc số thực an toàn từ stdin
 * @param value: Con trỏ tới biến chứa kết quả
 * @param message: Thông báo hiển thị trước khi nhập (có thể NULL)
 * @return: SUCCESS hoặc mã lỗi
 */
int safeDoubleInput(double* value, const char* message);

/**
 * Đọc chuỗi liên tục cho đến khi thành công
 * @param maxLen: Độ dài tối đa (không bao gồm '\0')
 * @param message: Thông báo hiển thị trước khi nhập (có thể NULL)
 * @return: Con trỏ tới chuỗi đã đọc (cần free sau khi dùng), hoặc NULL nếu lỗi nghiêm trọng
 */
char* completeInput(size_t maxLen, const char* message);

/**
 * Đọc số nguyên liên tục cho đến khi thành công
 * @param message: Thông báo hiển thị trước khi nhập (có thể NULL)
 * @return: Số nguyên đã đọc
 */
int completeIntInput(const char* message);

/**
 * Đọc số thực liên tục cho đến khi thành công
 * @param message: Thông báo hiển thị trước khi nhập (có thể NULL)
 * @return: Số thực đã đọc
 */
double completeDoubleInput(const char* message);

#endif // INPUT_HELPER_H