#include <stdio.h>
#include <time.h>

#include "constants.h"
#include "actions.h"
#include "queue.h"

void process_array_queue(info *information)
{
    if (information == NULL || information->array_queue == NULL || \
    information->array_queue->p_end == NULL || \
    information->array_queue->p_in == NULL || \
    information->array_queue->p_out == NULL || \
    information->array_queue->p_in > information->array_queue->p_out)
    {
        printf("Не получится, инициализируйте очередь-массив!\n");
        return;
    }
    free_data(information);
    process_array(information);
}

void process_node_queue(info *information)
{
    int check = OK;
    char answer = 0;
    if (information == NULL || information->node_queue == NULL)
        return;
    if (check == OK)
    {
        printf("Выводить информацию об адресах элементов при удалении и добавлении?\n");
        printf(" 1 - Да, выводить\n");
        printf(" 2 - Нет, не выводить\n");
        printf("Введите действие: ");
        check = scanf("%c", &answer);
        if (check == 1)
        {
            switch (answer)
            {
            case '1':
                free_data(information);
                process_node(information, 1);
                break;
            case '2':
                free_data(information);
                process_node(information, 0);
                break;
            default:
                printf("Неверное действие! Возвращаемся в меню...\n");
                break;
            }
            if (answer)
            {
                while (answer != '\n' && answer!= EOF)
                    scanf("%c", &answer);
            }
            printf("\n");
        }
    }
}

void free_data(info *information)
{
    for (int i = 0; i < QUEUE_LENGTH; i++)
    {
        *(information->array_queue->p_start + i) = 0;
    }
    information->array_queue->p_in = information->array_queue->p_start;
    information->array_queue->p_out = information->array_queue->p_start;
    free_node_queue(information->node_queue);
    printf("\n");
}

void change_intervals(info *information)
{
    int interval_min, interval_max, process_min, process_max, check;
    char ch;
    printf("Введите интервалы для прихода заявки: ");
    check = scanf("%d%d%c", &interval_min, &interval_max, &ch);
    if (check == 3 && interval_max >= 0 && interval_min >= 0 && interval_max > interval_min)
    {
        printf("Введите интервалы для обработки заявки: ");
        check = scanf("%d%d%c", &process_min, &process_max, &ch);
        if (check == 3 && process_min >= 0 && process_max >= 0 && process_max > process_min)
        {
            printf("Успех, интервалы изменены!\n");
            information->interval_max = interval_max;
            information->interval_min = interval_min;
            information->process_max = process_max;
            information->process_min = process_min;
        }
        else
            printf("Неверный ввод!\n");
    }
    else
        printf("Неверный ввод!\n");
    while (ch != '\n' && ch != EOF)
    {
        scanf("%c", &ch);
    }
}

void study_time(info *information)
{
    study_time_array(information->array_queue);
    study_time_node(information->node_queue);
    study_average_time(information);
}

void end_program(info *information)
{
    free_data(information);
    printf("Спасибо, что пользовались программой :)\n");
}