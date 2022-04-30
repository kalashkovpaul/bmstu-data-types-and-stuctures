#include <stdio.h>
#include "constants.h"
#include "get_long_numbers.h"
#include "long_numbers.h"
#include "divide_long_numbers.h"

int main(void)
{
    int check = OK;
    long_int a = { 0 };
    long_float b = { 0 }, c = { 0 };
    printf("Лабораторная работа №1, ТиСД. Вариант 4\n");
    printf("Формат ввода целого числа: ±m, где суммарная длина m - до 30 цифр.\n");
    printf("Операция деления большого целого числа на большое действительное.\n");
    printf("Формат ввода действительного числа: ±m.nЕ±K, где суммарная длина мантиссы (m+n)\
     - до 30 цифр, а величина порядка K - от 1 до 5 цифр\n");
    if (get_long_integer(&a) == OK && get_long_float(&b) == OK)
    {
        check = OK;
        divide(a, b, &c);
        print_answer(c);
    }
    else
    {
        if (check == ERR_ZERO)
            printf("Zero division!\n");
        else
        {
            check = ERR_READ;
            printf("Incorrect input!\n");
        }
    }
    return check;
}