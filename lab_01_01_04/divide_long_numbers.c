#include <stdio.h>
#include "long_numbers.h"

void shift_digits(long_int *number_int)
{
    for (int i = 0; i < number_int->end_index - 1; i++)
        number_int->number[i] = number_int->number[i + 1];
    number_int->number[number_int->end_index - 1] = 0;
}

void shift(long_float *number_float)
{
    for (int i = 0; i < number_float->significand_length - 1; i++)
        number_float->significand[i] = number_float->significand[i + 1];
    number_float->significand[number_float->significand_length - 1] = 0;
}

void get_rid_of_dot(long_float *number)
{
    number->base -= (number->significand_length - number->dot_index);
    int i = 0;
    while (number->significand[i] == 0)
    {
        shift(number);
        number->significand_length -= 1;
    }
    number->dot_index = 0;
}

int compare_long(long_int *number_int, long_float *number_float)
{
    int check = 0;
    if ((number_int->end_index - number_int->start_index) == (number_float->end_index - number_float->start_index))
    {
        int i = number_int->start_index, j = number_float->start_index;
        while (i < number_int->end_index - 1 && j < number_float->end_index - 1 && number_int->number[i] == number_float->significand[j])
        {
            i++;
            j++;
        }
        if (number_int->number[i] > number_float->significand[j])
            check = 1;
        else if (number_int->number[i] < number_float->significand[j])
            check = -1;
    }
    else if ((number_int->end_index - number_int->start_index) > (number_float->end_index - number_float->start_index))
        check = 1;
    else if ((number_int->end_index - number_int->start_index) < (number_float->end_index - number_float->start_index))
        check = -1;
    return check;
}

void subract(long_int *number_int, long_float *number_float)
{
    if ((number_int->end_index - number_int->start_index) >= (number_float->end_index - number_float->end_index))
    {
        int i_int = number_int->end_index - 1, i_float = number_float->end_index - 1;
        int debt = 0, current_digit = number_float->significand[i_float];
        while (i_int >= 0 && i_float >= 0 && i_int >= number_int->start_index && i_float >= number_float->start_index)
        {
            if (debt < 0)
            {
                if (number_int->number[i_int] > 0)
                {
                    number_int->number[i_int]--;
                    debt++;
                }
                else
                    number_int->number[i_int] = 9;
            }
            if (number_int->number[i_int] >= current_digit)
                number_int->number[i_int] -= current_digit;
            else 
            {
                number_int->number[i_int] = 10 + number_int->number[i_int] - current_digit;
                debt -= 1;
            }
            i_int -= 1;
            if ((i_float - 1) < number_float->start_index)
                current_digit = 0;
            else
            {
                i_float -= 1;
                current_digit =number_float->significand[i_float];
            }
        }
    }
    while(number_int->number[number_int->start_index] == 0 && number_int->start_index <= MAX_INT_LENGTH)
        number_int->start_index++;
}

void prepare_for_division(long_int *a, long_float *b, int *additional_base)
{
    if (b->dot_index != 0)
        get_rid_of_dot(b);
    a->start_index = 0;
    a->end_index = a->length;
    b->start_index = 0;
    b->end_index = b->significand_length;
    while(a->number[a->length - 1] == 0)
    {
        a->length--;
        a->end_index--;
        (*additional_base) += 1;
    }
    while (compare_long(a, b) < 0)
    {
        (*additional_base) -= 1;
        a->end_index += 1;
        a->length++;
    }
    while (compare_long(a, b) >= 0)
        a->end_index -= 1;
    a->end_index += 1;
}

int is_zero(long_int *number_int)
{
    int check = 1;
    for (int i = 0; i < number_int->length; i++)
        if (number_int->number[i] != 0)
            check = 0;
    return check;
}

int divide(long_int a, long_float b, long_float *c)
{
    int additional_base = 0;
    prepare_for_division(&a, &b, &additional_base);
    int i = 0, current_digit = 0;
    c->significand_length = 0;
    if (is_zero(&a))
    {
        c->significand_length = 1;
        c->end_index = 1;
        c->base = 0;
    }
    else
    {
        while(c->significand_length != MAX_SIGNIFICAND_LENGTH)
        {
            while (compare_long(&a, &b) >= 0)   
            {
                subract(&a, &b);
                current_digit++;
            }
            while(a.number[a.start_index] == 0 && a.start_index <= MAX_INT_LENGTH)
                a.start_index++;
            if (/*i != 0 && */ i < MAX_SIGNIFICAND_LENGTH - 2 && a.end_index >= a.length)
                additional_base--;
            if (a.end_index != MAX_INT_LENGTH)
                a.end_index++;
            else
            {
                shift_digits(&a);
                a.start_index--;
            }
            c->significand[i] = current_digit;
            c->significand_length++;
            current_digit = 0;
            i++;
        }
        i = MAX_SIGNIFICAND_LENGTH - 1;
        if (c->significand[i] >= 5)
        {
            i--;
            c->significand[i]++;
            while (c->significand[i] == 10 && i > 0)
            {
                c->significand[i] = 0;
                i--;
                c->significand[i]++;
            }
            if (i == 0 && c->significand[i] == 10)
            {
                c->significand[i] = 1;
                additional_base++;
            }
        }
        c->significand_length--;
        c->is_significand_negative = (a.is_negative + b.is_significand_negative) % 2;
        c->base = additional_base - (b.base);
        if (c->base < 0)
            c->is_base_negative = 1;
        else
            c->is_base_negative = 0;
        c->end_index = c->significand_length;
        i = c->end_index - 1;
        while(c->significand[i--] == 0)
        {
            c->end_index--;
            c->base++;
        }
    }
    return OK;
}

int print_answer(long_float c)
{
    printf("Результат:\n");
    printf("  1       10         20        30\n");
    printf("  |--------|---------|---------|\n");
    c.base += c.end_index;
    if (c.base < -99999)
        printf("Machine zero!\n");
    else if (c.base > 99999)
        printf("Infinity!\n");
    else
    {
        if (c.is_significand_negative)
            printf("-");
        printf("0.");
        for (int i = 0; i < c.end_index && i < MAX_INT_LENGTH - 1; i++)
            printf("%d", c.significand[i]);
        printf("E");
        printf("%d\n", c.base);
    }
    return OK;
}