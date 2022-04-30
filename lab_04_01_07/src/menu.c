#include <stdio.h>
#include "constants.h"
#include "info.h"
#include "actions.h"

void print_information()
{
    printf("Лабораторная работа №4, ТиСД, Вариант 7. Работа со стеком\n");
    printf("Данная программа предоставляет возможность выполнять действия со стеком целых чисел, представленным в виде связного списка и массива.\n");
}

void print_menu()
{
    printf("Возможные действия: \n");
    printf(" 1 - Добавить элемент в стек\n");
    printf(" 2 - Достать элемент из стека\n");
    printf(" 3 - Вывести содержимое стека\n");
    printf(" 4 - Очистить стеки\n");
    printf(" 5 - Исследовать время работы программы\n");
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
            result = ADD_ELEMENT;
            break;
        case '2':
            result = POP_ELEMENT;
            break;
        case '3':
            result = PRINT_AND_CLEAN;
            break;
        case '4':
            result = FREE_DATA;
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
        {
            while (code != '\n' && code != EOF)
                scanf("%c", &code);
        }
    }
    return result;
}

void do_action(int code, info *information)
{
    switch (code)
    {
    case 1:
        push_element(information);
        break;
    case 2:
        pop_element(information);
        break;
    case 3:
        print(information);
        break;
    case 4:
        free_data(information);
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