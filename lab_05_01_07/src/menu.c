#include <stdio.h>
#include "constants.h"
#include "queue.h"
#include "actions.h"

void print_information()
{
    printf("Лабораторная работа №5, ТиСД, Вариант 7. Обработка очередей\n");
    printf("Данная программа предоставляет возможность запускать процессы обслуживания очередей, представленных в виде связного списка и массива.\n");
    printf("При этом:\n");
    printf("Система  массового  обслуживания  состоит  из  обслуживающего  аппарата \
    (ОА) и очереди заявок. Заявки поступают в \"хвост\" очереди по случайному закону с интервалом \
    времени Т1,  равномерно распределенным от 0 до 6  единиц времени  (е.в.). В \
    ОА  они  поступают  из  \"головы\"  очереди  по  одной  и  обслуживаются  также \
    равновероятно  за  время  Т2  от  0  до  1  е.в.\n");
}

void print_menu()
{
    printf("Возможные действия: \n");
    printf(" 1 - Запустить очередь-массив\n");
    printf(" 2 - Запустить очередь-стек\n");
    printf(" 3 - Изменить интервалы прихода / обработки заявки\n");
    printf(" 4 - Сравнить очередь-стек и очередь-массив\n");
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
            result = PROCESS_ARRAY_QUEUE;
            break;
        case '2':
            result = PROCESS_NODE_QUEUE;
            break;
        case '3':
            result = CHANGE_INTERVALS;
            break;
        case '4':
            result = STUDY_TIME;
            break;
        case '0':
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
        process_array_queue(information);
        break;
    case 2:
        process_node_queue(information);
        break;
    case 3:
        change_intervals(information);
        break;
    case 4:
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