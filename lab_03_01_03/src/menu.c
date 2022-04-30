#include <stdio.h>
#include "constants.h"
#include "matrix.h"
#include "info.h"

void print_information()
{
    printf("Лабораторная работа №3, ТиСД, Вариант 3. Разреженные матрицы. Умножение матрицы на столбец\n");
}

void print_menu()
{
    printf("Возможные действия: \n");
    printf(" 1 - Ввести данные вручную\n");
    printf(" 2 - Сгенерировать данные\n");
    printf(" 3 - Умножить матрицу на столбец\n");
    printf(" 4 - Изменить размер матрицы и столбца\n");
    printf(" 5 - Исследовать время работы программы и используемый объём памяти\n");
    printf(" 0 - Выйти из программы\n");
}

int get_action_code()
{
    printf("Введите номер действия: ");
    char code = 0;
    int result = INCORRECT_CODE;
    int check = 0;
    check = scanf("%c", &code);
    printf("\n");
    if (check != EOF)
    {
        switch (code)
        {
        case '1':
            result = READ_DATA;
            break;
        case '2':
            result = GENERATE_DATA;
            break;
        case '3':
            result = MULTIPLY;
            break;
        case '4':
            result = CHANGE_SIZE;
            break;
        case '5':
            result = STUDY_TIME;
            break;
        case '0':
            result = END_PROGRAM;
            break;
        case 0:
            printf("EОF! Завершаем программу...\n");
            result = END_PROGRAM;
            break;
        default:
            result = INCORRECT_CODE;
            break;
        }
        if (code)
            myflush();
    }
    return result;
}

void do_action(int code, info *information)
{
    switch (code)
    {
    case 1:
        read_data(information);
        break;
    case 2:
        generate_data(information);
        break;
    case 3:
        multiply(information);
        break;
    case 4:
        change_size(information);
        break;
    case 5:
        study_time(information);
        break;
    case 0:
        end_program(information);
        break;
    default:
        printf("Действие некорректно!\n\n");
        break;
    }
}