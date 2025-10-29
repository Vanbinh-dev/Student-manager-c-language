#ifndef STRING_HELPER_H
#define STRING_HELPER_H

/**
 * Tách chuỗi thành mảng các chuỗi con dựa trên delimiter
 * @param str: Chuỗi gốc cần tách
 * @param delimiter: Ký tự phân tách
 * @param getSize: Con trỏ để lưu số lượng chuỗi con được tách ra
 * @return: Mảng các chuỗi con (cần free sau khi dùng). Có thể xuất hiện giá trị null!
 */
char** stringSplit(const char *str, char delimiter, int *getSize) ;

/**
 * Giải phóng bộ nhớ sau khi sử dụng mảng con trỏ
 * @param array: Mảng con chuỗi
 * @param size: Kích thước của mảng chuỗi
 */
void freeStringArr(char **array, int size);

/**
 * Trả về một mảng chuỗi, không tồn tại giá trị null trong mảng chuỗi
 */
char **notNullStringSplit(const char *baseString, char delimiter, int *getSize);

#endif