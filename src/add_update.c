#include "../include/add_update.h"
#include "../include/student.h"
#include "../include/validation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student *newStudent()
{
    return NULL;
}

void doiTen(char **updateName)
{
    int nameSize = 200;
    char _command = '0';
    char *name = malloc(sizeof(char) * nameSize);

    if (!name) {
        printf("\n\nThay doi bat thanh!!!\n\n");
        return;
    }

    do
    {
        printf("Nhap ten sinh vien: ");
        fgets(name, nameSize, stdin);
        if (strlen(name) == nameSize)
        {
            printf("Dat lai ten dai hon khong? Nhap y de tiep tuc: ");
            scanf("%c", &_command);
        }

        if (_command == 'y')
        {
            nameSize *= 2;
            name = realloc(name, sizeof(char) * nameSize);
        }
    } while (_command == 'y');

    *updateName = name;
}

int nhapTuoi()
{
    char prompt[2];
    int age = -1;

    do
    {
        printf("Nhap tuoi sinh vien!");
        printf("Nhap: ");
        fgets(prompt, 2, stdin);

        if (!intNumFormatable(prompt) || age < 18 || age > 90)
        {
            printf("\n-------Nhap sai dinh dang hoac so tuoi qua quy dinh!-------\n");
            continue;
        }

        age = atoi(prompt);
    } while (age >= 18 && age <= 90);

    return age;
}

Gender nhapGioiTinh()
{
    Gender g = MALE;
    return g;
}

Major chonChuyenNganh() {
    return  SE;
}

StudyStatus thayDoiTinhTrangHoc() {
    return ENROLLED;
}