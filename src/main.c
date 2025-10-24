#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/student_curd.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    setup();
    addStudent();
    printStudentList();
    endCURD();
    return 0;
}