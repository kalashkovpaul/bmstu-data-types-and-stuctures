#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "constants.h"
#include "info.h"

void myflush()
{
    char ch = 0;
    int check = 0;
    while (ch != '\n')
    {
        check = scanf("%c", &ch);
        if (check == EOF)
            break;
    }
}

int **allocate_matrix(int n, int m)
{
    int **ptrs, *data;
    ptrs = malloc(n * sizeof(int *));
    if (!ptrs)
        return NULL;
    data = calloc(n * m, sizeof(int));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        ptrs[i] = data + i * m;
    return ptrs;
}

void free_matrix(int **ptrs)
{
    free(ptrs[0]);
    free(ptrs);
    ptrs = NULL;
}

int *allocate_array(int n)
{
    int *data = calloc(n, sizeof(int));
    return data;
}

void find_size(FILE *src, int *n, int *m)
{
    char space = 0;
    int check = 2, number = 0, i = 0, j = 0;
    int index;
    while (check == 2 && space != '\n')
    {
        check = fscanf(src, "%d%c", &number, &space);
        i++;
    }
    if (space == EOF || check != 2 || space == '\n')
        *n = i;
    else
        *n = -1;
    if (*n != -1)
    {
        check = 2;
        space = 0;
        index = 1;
        while (!feof(src))
        {
            for (j = 0; j < *n && check == 2 && space != '\n'; j++)
                check = fscanf(src,"%d%c", &number, &space);
            if (check != 2 && space != '\n' && !feof(src))
            {
                index = -1;
                break;
            }
            index++;
            space = 0;
        }
        *m = index;
    }
}

int scan_matrix(FILE *src, int **matrix, int n, int m)
{
    int check = 1;
    for (int i = 0; i < n && check == 1; i++)
        for (int j = 0; j < m && check == 1; j++)
        {
            check = fscanf(src, "%d", &matrix[i][j]);
            if (check != 1)
            {
                printf("Некорректный ввод!\n");
                return ERR_READ;
            }
        }
    return OK;
}

void read_matrix(info *information)
{
    FILE *src = fopen(SRC_MATRIX, "r");
    if (src != NULL)
    {
        int n = 0, m = 0, check = 0;
        char ch = 0;
        check = fscanf(src, "%d%d%c", &n, &m, &ch);
        if (check == 3 && n > 0 && m > 0 && ch == '\n')
        {
            information->matrix = allocate_matrix(n, m);
            check = scan_matrix(src, information->matrix, n, m);
            if (check == OK)
            {
                information->is_a_defined = 1;
                information->n = n;
                information->m = m;
                printf("Сделано!\n");
            }
        }
        else
            printf("Некорректные данные в файле!\n");
        fclose(src);
    }
    else
        printf("Некорректное имя файла!\n");
}

void find_column_length(FILE *src, int *n)
{
    int i = 0, check = 2;
    int number = 0;
    char ch = ' ';
    while (!feof(src) && check == 2 && ch == ' ')
    {
        check = fscanf(src, "%d%c", &number, &ch);
        if (check == 2)
            i++;
    }
    if (feof(src) || ch == '\n')
        *n = i;
    else
        *n = -1;
}

int scan_column(FILE *src, int *column, int n)
{
    int length = 0, check = 0;
    for (int i = 0; i < n; i++)
    {
        check = fscanf(src, "%d", &column[i]);
        length++;
        if (check != 1)
            return -1;
    }
    if (src == stdin)
        myflush();
    return length;
}

void read_column(info *information)
{
    int n = 0, check = 0;
    char ch = 0;
    FILE *src = fopen(SRC_COLUMN, "r");
    if (src != NULL)
    {
        check = fscanf(src, "%d%c", &n, &ch);
        if (check == 2 && n > 0 && ch == '\n')
        {
            information->column = allocate_array(n);
            if (information->column != NULL)
            {
                check = scan_column(src, information->column, n);
                if (check == n)
                {
                    information->column_length = n;
                    information->is_b_defined = 1;
                    printf("Сделано!\n");
                }
                else
                    printf("Ошибка чтения!\n");
            }
            else
                printf("Не удалось выделить память!\n");
        }
        else
            printf("Некорректное содержимое файла!\n");
        fclose(src);
    }
    else
        printf("Некорректное имя файла!\n");
}

void read_a_src(FILE *src, info *information)
{
    char ch = 0;
    int check = 0;
    information->a = allocate_array(information->matrix_meaning);
    if (information->a != NULL)
    {
        scan_column(src, information->a, information->matrix_meaning);
        check = fscanf(src, "%c", &ch);
        if (ch != '\n' && check != EOF)
        {
            printf("Некорректное указание массива А в файле %s\n", CRS_SRC);
            information->is_a_crs_defined = -1;
        }
    }
    else
        printf("Не удалось выделить память на A!\n");
}

void read_ja_src(FILE *src, info *information)
{
    char ch;
    int check = 0;
    int n = information->matrix_meaning;
    information->ja = allocate_array(n);
    if (information->ja != NULL)
    {
        scan_column(src, information->ja, n);
        check = fscanf(src, "%c", &ch);
        if (ch != '\n' && check != EOF)
        {
            printf("Некорректноеи указание массива JA в файле %s\n", CRS_SRC);
            information->is_a_crs_defined = -1;
        }
    }
    else
    {
        printf("Не удалось выделить память на JA!\n");
        information->is_a_crs_defined = -1;
    }
}

void read_ia_src(FILE *src, info *information)
{
        allocate_node(&information->ia, information->m);
        if (information->ia != NULL)
        {
            scan_node(src, information->ia, information->m);
            information->ia_length = information->m;
        }
        else
        {
            printf("Не удалось выделить память на IA!\n");
            information->is_a_crs_defined = -1;
        }
}

void read_matrix_crs(info *information)
{
    FILE *src = fopen(CRS_SRC, "r");
    int n = 0, m = 0, meaning = 0, check = 0;
    char ch_1 = 0, ch_2 = 0, ch_3 = 0;
    if (src == NULL)
        printf("Некорректные названия файлов!\n");
    else
    {
        check = fscanf(src, "%d%c%d%c%d%c", &n, &ch_1, &m, &ch_2, &meaning, &ch_3);
        if (check == 6 && ch_1 == ' ' && n > 0 && m > 0 && meaning > 0 && meaning <= n * m && ch_2 == '\n' && ch_3 == '\n')
        {
            information->n = n;
            information->m = m;
            information->matrix_meaning = meaning;
            information->ia_length = m;
            read_a_src(src, information);
            read_ja_src(src, information);
            read_ia_src(src, information);
            information->is_a_crs_defined++;
            printf("Сделано!\n");
        }
        else
            printf("Некорректное содержание файла!\n");
        fclose(src);
    }

}

void read_b_src(FILE *src, info *information)
{
    char ch = 0;
    int check = 0;
    information->b = allocate_array(information->column_meaning);
    if (information->b != NULL)
    {
        scan_column(src, information->b, information->column_meaning);
        check = fscanf(src, "%c", &ch);
        if (ch != '\n' && check != EOF)
        {
            printf("Некорректное указание массива B в файле %s\n", CCS_COLUMN);
            information->is_b_ccs_defined = -1;
        }
    }
    else
            printf("Не удалось выделить память на B!\n");
}

void read_jb_src(FILE *src, info *information)
{
    information->jb = allocate_array(information->column_meaning);
    if (information->jb != NULL)
    {
        scan_column(src, information->jb, information->column_meaning);
    }
    else
        printf("Не удалось выделить память на JB!\n");
}

void read_column_ccs(info *information)
{
    FILE *src = fopen(CCS_COLUMN, "r");
    int length = 0, check = 0, column_meaning = 0;
    char ch_1 = 0, ch_2 = 0;
    if (src == NULL)
        printf("Некорректные названия файлов!\n");
    else
    {
        check = fscanf(src, "%d%c%d%c", &length, &ch_1, &column_meaning, &ch_2);
        if (ch_1 == '\n' && check == 4 && ch_2 == '\n' && column_meaning > 0 && length > 0 && length >= column_meaning)
        {
            information->column_meaning = column_meaning;
            information->column_length = length;
            read_b_src(src, information);
            read_jb_src(src, information);
            information->is_b_ccs_defined++;
            printf("Сделано!\n");
        }
        else
            printf("Некорректное содержимое файла!\n");
        fclose(src);
    }
}

void change_a(info *information)
{
    int n, m, meaning, check = 0;
    char space_1 = 0, end = 0;
    printf("Введите размерности n и m: ");
    check = scanf("%d%c%d%c", &n, &space_1, &m, &end);
    if (check == 4 && space_1 == ' ' && end == '\n' && n > 0 && m > 0)
    {
        printf("Введите число ненулевых элеметнов: ");
        check = scanf("%d%c", &meaning, &end);
        if (check == 2 && end == '\n' && meaning > 0 && meaning <= n * m)
        {
            if (information->is_a_defined == 0)
                information->matrix = allocate_matrix(n, m);
            if (information->matrix)
            {
                printf("Введите элементы матрицы: \n");
                check = scan_matrix(stdin, information->matrix, n, m);
                if (check == OK)
                {
                    information->column_meaning = meaning;
                    information->n = n;
                    information->m = m;
                    information->is_a_defined = 1;
                    printf("Сделано!\n");
                }
                else
                    printf("Ошибка чтения!\n");
            }
            else
                printf("Не удалось выделить память!\n");
        }
        else
            printf("Некорректный ввод!\n");
    }
    else
        printf("Некорректный ввод!\n");
}

void change_b(info *information)
{
    int check = 0, column_length = 0;
    char end = 0;
    printf("Введите длину столбца: ");
    check = scanf("%d%c", &column_length, &end);
    if (check == 2 && end == '\n' && column_length > 0)
    {
        printf("Введите элементы столбца: \n");
        if (information->is_b_defined == 0)
            information->column = allocate_array(column_length);
        if (information->column)
        {
            check = scan_column(stdin, information->column, column_length);
            if (check == column_length)
            {
                information->column_length = column_length;
                information->is_b_defined++;
                printf("Сделано!\n");
            }
        }
        else
            printf("Не удалось выделить память!\n");
    }
}

void change(info *information)
{
    printf("Что хотите ввести вручную?\n");
    printf(" 1 - Матрица А\n");
    printf(" 2 - Столбец B\n");
    printf(" Введите решение: ");
    char ch = 0;
    int check = 0;
    check = scanf("%c", &ch);
    if (check != EOF)
    {
        switch (ch)
        {
            case '1':
                change_a(information);
                myflush();
                break;
            case '2':
                myflush();
                change_b(information);
                break;
            default:
                myflush();
                printf("Некорректный ввод!\n");
        }
    }
}

int find_meaning(int **matrix, int n, int m)
{
    int result = 0;
    for (int i = 0; i < n; i++)
        for (int j= 0; j < m; j++)
            if (matrix[i][j] != 0)
                result++;
    return result;
}

void convert_usual_to_crs(info *information)
{
    information->matrix_meaning = find_meaning(information->matrix, information->n, information->m);
    information->ia_length = information->n;
    information->a = allocate_array(information->matrix_meaning);
    int elements_amount = 0;
    if (information->a)
    {
        information->ja = allocate_array(information->matrix_meaning);
        if (information->ja)
        {
            allocate_node(&(information->ia), information->ia_length);
            int index = 0;
            node *nd = information->ia;
            for (int i = 0; i < information->n; i++)
            {
                nd->value = elements_amount;
                for (int j = 0; j < information->m; j++)
                {
                    if (information->matrix[i][j] != 0)
                    {
                        information->a[index] = information->matrix[i][j];
                        information->ja[index] = j;
                        index++;
                        elements_amount++;
                    }
                }
                nd = nd->next;
            }
            // int is_complete = 0;
            // nd = information->ia;
            // while (!is_complete)
            // {
            //     is_complete = 1;
            //     while (nd->next != NULL)
            //     {
            //         if (nd->value == -1 )
            //         {
            //             nd->value = nd->next->value;
            //             is_complete = 0;
            //         }
            //         nd = nd->next;
            //     }
            //     if (nd->value == -1) 
            //     {
            //         nd->value = information->matrix_meaning;
            //         is_complete = 0;
            //     }
            // }
            information->is_a_crs_defined = 1;

        }
        else
            printf("Не удалось выделить память!\n");
    }
    else
        printf("Не удалось выделить память!\n");

}

void convert_crs_to_usual(info *information)
{
    information->matrix = allocate_matrix(information->n, information->m);
    if (information->matrix)
    {
        node *nd = information->ia;
        int i = 0;
        for (i = 0; i < information->ia_length - 1; i++)
        {
            if (nd->value != -1 && nd->value != nd->next->value)
            {
                for (int j = nd->value; j < nd->next->value; j++)
                {
                    information->matrix[i][information->ja[j]] = information->a[j];
                }
            }
            nd = nd->next;
        }
        if (nd->next != NULL)
            printf("Чекни свой код)\n");
        else
        {
            if (nd->value < information->matrix_meaning)
            {
                for (int j = nd->value; j < information->matrix_meaning; j++)
                {
                    information->matrix[i][information->ja[j]] = information->a[j];
                }
            }
        }
        information->is_a_defined = 1;
    }
    else
        printf("Не удалось выделить память!\n");
}

int find_meaning_in_column(int *column, int length)
{
    int result = 0;
    for (int i = 0; i < length; i++)
    {
        if (column[i] != 0)
            result++;
    }
    return result;
}

void convert_usual_to_ccs(info *information)
{
    information->column_meaning = find_meaning_in_column(information->column, information->column_length);
    information->b = allocate_array(information->column_meaning);
    if (information->b)
    {
        information->jb = allocate_array(information->column_meaning);
        if (information->jb)
        {
            int index = 0;
            for (int i = 0; i < information->column_length; i++)
                if (information->column[i] != 0)
                {
                    information->b[index] = information->column[i];
                    information->jb[index] = i;
                    index++;
                }
            if (index != information->column_meaning)
                printf("Чекни свой код)\n");
            information->is_b_ccs_defined = 1;
        }
        else 
            printf("Не удалось выделить память!\n");
    }
    else
        printf("Не удалось выделить память!\n");
}

void convert_result_to_ccs(info *information)
{
    information->c_meaning = find_meaning_in_column(information->c_column, information->c_column_length);
    information->c = allocate_array(information->c_meaning);
    if (information->c)
    {
        information->jc = allocate_array(information->c_meaning);
        if (information->jc)
        {
            int index = 0;
            for (int i = 0; i < information->c_column_length; i++)
                if (information->c_column[i] != 0)
                {
                    information->c[index] = information->c_column[i];
                    information->jc[index] = i;
                    index++;
                }
            if (index != information->c_meaning)
                printf("Чекни свой код)\n");
            information->is_c_ccs_defined = 1;
        }
        else 
            printf("Не удалось выделить память!\n");
    }
    else
        printf("Не удалось выделить память!\n");
}

void convert_ccs_to_usual(info *information)
{
    information->column = allocate_array(information->column_length);
    if (information->column)
    {
        for (int i = 0; i < information->column_meaning; i++)
            information->column[information->jb[i]] = information->b[i];
        information->is_b_defined = 1;
    }
    else
        printf("Не удалось выделить память!\n");
}

void mlt_old(info *information)
{
    for (int i = 0; i < information->n; i++)
    {
        for (int j = 0; j < information->m; j++)
            information->c_column[i] += information->matrix[i][j] * information->column[j];
    }
}

void file_print_usual(FILE *dst, info *information)
{
    for (int i = 0; i < information->c_column_length; i++)
        fprintf(dst, "%d\n", information->c_column[i]);
}

void free_c(info *information)
{
    information->is_c_defined = 0;
    free(information->c_column);
    information->c_column = 0;
    if (information->is_c_ccs_defined == 0)
    {
        information->c_meaning = 0;
    }
}

void multiply_old(info *information)
{
    if (information->is_a_defined == 0 && information->is_a_crs_defined == 0)
        printf("Не хватает данных, введите матрицу A!\n");
    else if (information->is_b_defined == 0 && information->is_b_ccs_defined == 0)
        printf("Не хватает данных, введите столбец B!\n");
    else
    {
        if (information->is_a_defined == 0)
            convert_crs_to_usual(information);
        if (information->is_b_defined == 0)
            convert_ccs_to_usual(information);
        if (information->m != information->column_length)
            printf("Размерности A и B не совпадают, невозможно умножить!\n");
        else
        {
            if (information->is_c_defined)
                free_c(information);
            information->c_column = allocate_array(information->n);
            if (information->c_column)
            {
                information->c_column_length = information->n;
                FILE *dst = fopen(DST, "w");
                mlt_old(information);
                if (dst)
                {
                    file_print_usual(dst, information);
                    information->is_c_defined = 1;
                    fclose(dst);
                }
                else
                    printf("Не удалось открыть файл для результата!\n");
            }
            else
                printf("Не удалось выделить память под результат!\n");
        }
    }
}

void mlt_crs(info *information, int *result)
{
    int i = 0;
    node *nd = information->ia;
    int max = 0;
    if (information->matrix_meaning == 0 || information->column_meaning == 0)
    {
        printf("В результате получится нулевой столбец!\n");
        return;
    }
    max = (information->matrix_meaning > information->column_meaning) ?
        information->matrix_meaning :
        information->column_meaning;

    int *ip = allocate_array(max);

    if (ip)
    {
        for (i = 0; i < information->ia_length - 1; i++)
        {
            if (nd->value != -1 && nd->value != nd->next->value)
            {
                for (int j = nd->value; j < nd->next->value; j++)
                {
                    ip[information->ja[j]] = j + 1;
                }
                for (int j = 0; j < information->column_meaning; j++)
                    if (ip[information->jb[j]] != 0)
                    {
                        result[i] += information->b[j] * information->a[ip[information->jb[j]] - 1];
                    }
                memset(ip, 0, max * sizeof(int));
                //for (int j = 0; j < max; j++)
                //    ip[j] = 0;
            }
            nd = nd->next;
        }

        for (int j = nd->value; j < information->matrix_meaning; j++)
            ip[information->ja[j]] = j + 1;
        for (int j = 0; j < information->column_meaning; j++)
            if (ip[information->jb[j]] != 0)
                result[i] += information->b[j] * information->a[ip[information->jb[j]] - 1];
    }
    else
        printf("Не удалось выделить память под решение!\n");
}

void file_print_ccs(FILE *dst, info *information)
{
    free_c(information);
    information->c_column = allocate_array(information->n);
    if (information->c_column)
    {
        for (int i = 0; i < information->c_meaning; i++)
            information->c_column[information->jc[i]] = information->c[i];
        information->is_c_defined = 1;
        file_print_usual(dst, information);
    }
    else
        printf("Не удалось выделить память!\n");
}

void free_c_ccs(info *information)
{
    information->is_c_ccs_defined = 0;
    free(information->c);
    information->c = NULL;
    free(information->jc);
    information->jc = NULL;
    information->c_column_length = 0;
    if (information->is_c_defined == 0)
    {
        information->c_meaning = 0;
    }
}

void transfer_result(info *information, int *result)
{
    int i = 0;
    information->c_meaning = find_meaning_in_column(result, information->n);
    information->c = allocate_array(information->c_meaning);
    information->jc = allocate_array(information->c_meaning);
    if (information->c && information->jc)
    {
        int index = 0;
        for (i = 0; i < information->n; i++)
            if (result[i] != 0)
            {
                information->c[index] = result[i];
                information->jc[index] = i;
                index++;
            }
        information->is_c_ccs_defined = 1;
    }
}

void multiply_crs(info *information)
{
    if (information->is_a_defined == 0 && information->is_a_crs_defined == 0)
        printf("Не хватает данных, введите матрицу A!\n");
    else if (information->is_b_defined == 0 && information->is_b_ccs_defined == 0)
        printf("Не хватает данных, введите столбец B!\n");
    else
    {
        if (information->is_a_crs_defined == 0)
            convert_usual_to_crs(information);
        if (information->is_b_ccs_defined == 0)
            convert_usual_to_ccs(information);

        if (information->m != information->column_length)
        {
            printf("Размерности A и B не совпадают, невозможно умножить!\n");
        }
        else
        {
            if (information->is_c_ccs_defined)
                free_c_ccs(information);
            information->c = allocate_array(information->n);
            if (information->c)
            {
                information->c_column_length = information->n;
                information->jc = allocate_array(information->n);
                if (information->jc)
                {
                    FILE *dst = fopen(DST, "w");
                    int *result = allocate_array(information->n);
                    mlt_crs(information, result);
                    transfer_result(information, result);
                    free(result);
                    if (dst)
                    {
                        file_print_ccs(dst, information);
                        fclose(dst);
                    }
                    else
                        printf("Не удалось открыть файл для результата!\n");
                } 
                else
                    printf("Не удалось выделить память под результат!\n");
            }
            else
                printf("Не удалось выделить память под результат!\n");
        }
    }
}

void free_a_crs(info *information)
{
    information->is_a_crs_defined = 0;
    information->matrix_meaning = 0;
    information->ia_length = 0;
    free(information->a);
    information->a = NULL;
    free(information->ja);
    information->ja = NULL;
    free(information->ia);
    information->ia = NULL;
    if (information->is_a_defined == 0)
    {
        information->n = 0;
        information->m = 0;
    }
}

void free_a(info *information)
{
    information->is_a_defined = 0;
    free_matrix(information->matrix);
    if (information->is_a_crs_defined == 0)
    {
        information->n = 0;
        information->m = 0;
    }
}

void free_b_ccs(info *information)
{
    information->is_b_ccs_defined = 0;
    free(information->b);
    information->b = NULL;
    free(information->jb);
    information->jb = NULL;
    information->column_length = 0;
    if (information->is_b_defined == 0)
    {
        information->column_meaning = 0;
    }
}

void free_b(info *information)
{
    information->is_b_defined = 0;
    free(information->column);
    information->column = 0;
    if (information->is_b_ccs_defined == 0)
    {
        information->column_meaning = 0;
    }
}

void clean_data(info *information)
{
    if (information->is_a_crs_defined)
        free_a_crs(information);
    if (information->is_a_defined)
        free_a(information);
    if (information->is_b_ccs_defined)
        free_b_ccs(information);
    if (information->is_b_defined)
        free_b(information);
    if (information->is_c_ccs_defined)
        free_c_ccs(information);
    if (information->is_c_defined)
        free_c(information);
    FILE *dst = fopen(DST, "w");
    if (dst)
        fclose(dst);
    printf("Сделано!\n");
}

void study_time(info *information)
{
    if (information->is_a_defined == 0 && information->is_a_crs_defined == 0)
        printf("Не хватает данных, введите матрицу A!\n");
    else if (information->is_b_defined == 0 && information->is_b_ccs_defined == 0)
        printf("Не хватает данных, введите столбец B!\n");
    else
    {
        if (information->is_a_defined == 0)
            convert_crs_to_usual(information);
        else
            convert_usual_to_crs(information);
        if (information->is_b_defined == 0)
            convert_ccs_to_usual(information);
        else
            convert_usual_to_ccs(information);
        if (information->is_c_ccs_defined)
            free_c_ccs(information);
        if (information->is_c_defined)
            free_c(information);
        information->c = allocate_array(information->n);
        information->jc = allocate_array(information->n);
        information->c_column = allocate_array(information->n);
        information->c_column_length = information->n;
        long long time_1 = 0, time_2 = 0;
        int measurement_amount = 100;
        if (information->c && information->jc && information->c_column)
        {
            for (int i = 0; i < measurement_amount; i++)
            {
                time_t begin = clock();
                mlt_old(information);
                time_1 += clock() - begin;
                int *result = allocate_array(information->n);
                begin = clock();
                mlt_crs(information, result);
                time_2 += clock() - begin;
                free(result);
            }
        }
        printf("Время работы классического умножения = %lld мкс\n", time_1 / measurement_amount);
        printf("Памяти использовано: %ld байт\n", information->n * information->m * sizeof(int));
        printf("Время работы умножения при помощи CRS = %lld мкс\n", time_2 / measurement_amount);
        printf("Памяти использовано: %ld байт\n", (2 * information->matrix_meaning + information->ia_length + information->n + information->column_meaning) * sizeof(int));
    }
}

void end_program(info *information)
{
    clean_data(information);
    printf("Спасибо за использование программы!\n");
}

void change_size(info *information)
{
    printf("Введите размеры матрицы: n m\n");
    char space = 0, end = 0;
    int n, m, check = 0;
    check = scanf("%d%c%d%c", &n , &space, &m, &end);
    if ((check == 4) && (space == ' ') && (end = '\n') && (n > 0) && (m > 0))
    {
        information->n = n;
        information->m = m;
        information->column_length = m;
        information->are_sizes_defined = 1;
        printf("Принято!\n");
    }
    else
        printf("Некорректный ввод!\n");
}

void print_usual_way(info *information)
{   
    if (information->n > 30 || information->m > 30)
        printf("Обычное представление можно было бы и вывести, да размер большой, некрасиво будет\n");
    else
    {
        printf("Матрица: \n");
        for (int i = 0; i < information->n; i++)
        {
            for (int j = 0; j < information->m; j++)
                printf("%d ", information->matrix[i][j]);
            printf("\n");
        }
        printf("\n");
        printf("Столбец: \n");
        for (int i = 0; i < information->column_length; i++)
            printf("%d\n", information->column[i]);
        printf("\n");
    }
}

void multip_crs(info *information)
{
    multiply_old(information);
    convert_result_to_ccs(information);
}

void print_crs_way(info *information)
{
    if (information->matrix_meaning <= 30 && information->column_meaning <= 30)
    {
    printf("A: ");
    for (int i = 0; i < information->matrix_meaning; i++)
        printf("%d ", information->a[i]);
    printf("\n");
    printf("JA: ");
    for (int i = 0; i < information->matrix_meaning; i++)
        printf("%d ", information->ja[i]);
    printf("\n");
    printf("IA: ");
    node *nd = information->ia;
    for (int i = 0; i < information->ia_length; i++)
    {
        printf("%d ", nd->value);
        nd = nd->next;
    }
    printf("\n");
    printf("B: ");
    for (int i = 0; i < information->column_meaning; i++)
        printf("%d ", information->b[i]);
    printf("\n");
    printf("JB: ");
    for (int i = 0; i < information->column_meaning; i++)
        printf("%d ", information->jb[i]);
    printf("\n");
    }
}

void print_result(info *information)
{
    if (information->c_column_length <= 30)
    {
        printf("Результат: \n");
        for (int i = 0; i < information->c_column_length; i++)
            printf("%d\n", information->c_column[i]);
        printf("\n");
    }
}

void print_result_ccs(info *information)
{
    printf("C: ");
    for (int i = 0; i < information->c_meaning; i++)
        printf("%d ", information->c[i]);
    printf("\n");
    printf("JC: ");
    for (int i = 0; i < information->c_meaning; i++)
        printf("%d ", information->jc[i]);
    printf("\n");
}

void print_data(info *information)
{
    print_usual_way(information);
    print_crs_way(information);
    if (information->is_c_defined)
        print_result(information);
    if (information->is_c_ccs_defined)
        print_result_ccs(information);
}

void read_data(info *information)
{
    if (information->is_a_crs_defined)
        free_a_crs(information);
    if (information->is_b_ccs_defined)
        free_b_ccs(information);
    if (information->is_c_defined)
        free_c(information);
    if (information->is_c_ccs_defined)
        free_c_ccs(information);
    printf("Введите количество ненулевых элементов: \n");
    char space = 0, end = 0;
    int meaning = 0, number = 0, i = 0, j = 0;
    int check = 0;
    check = scanf("%d%c", &meaning, &end);
    if (check == 2 && end == '\n' && meaning > 0 && meaning <= information->n * information->m)
    {
        information->matrix_meaning = meaning;
        information->a = malloc(information->matrix_meaning * sizeof(int));
        information->ja = malloc(information->matrix_meaning * sizeof(int));
        information->ia_length = information->n;
        information->matrix = allocate_matrix(information->n, information->m);
        information->column_length = information->m;
        information->column = allocate_array(information->column_length);
        allocate_node(&(information->ia), information->ia_length);
        if (information->a && information->ja && information->matrix && information->column)
        {
            for (int index = 0; index < information->matrix_meaning; index++)
            {
                printf("Введите индексы ненулевого элемента: ");
                check = scanf("%d%c%d%c", &i, &space, &j, &end);
                if (check == 4 && space == ' ' && end == '\n' && i >= 0 && i < information->n && j >= 0 && j < information->m)
                {
                    printf("Введите ненелевое значение элемента: ");
                    check = scanf("%d%c", &number, &end);
                    if (check == 2 && number != 0 && end == '\n')
                        information->matrix[i][j] = number;
                    else
                        printf("Некорректный ввод!\n");
                }
                else
                    printf("Некорректный ввод!\n");
            }
            convert_usual_to_crs(information);
            printf("Хорошо. Теперь ввод столбца\n");
            printf("Введите количетво ненулевых элементов: ");
            check = scanf("%d%c", &number, &end);
            if (check == 2 && number >= 0 && number <= information->column_length && end == '\n')
            {
                information->column_meaning = number;
                for (int index = 0; index < information->column_meaning; index++)
                {
                    printf("Введите индекс ненулевого элемента: ");
                    check = scanf("%d%c", &i, &end);
                    if (check == 2 && i < information->column_length && end == '\n')
                    {
                        printf("Введите ненулевое значение элемента: ");
                        check = scanf("%d%c", &number, &end);
                        if (check == 2 && number != 0 && end == '\n')
                            information->column[i] = number;
                        else
                            printf("Некорректный ввод!\n");
                    }
                    else
                        printf("Некорректный ввод\n");
                }
                convert_usual_to_ccs(information);
                printf("Сделано!\n");
                print_data(information);
            }
            else
                printf("Некорректный ввод!\n");
        }
        else
            printf("Не удалось выделить память!\n");
    }
    else
        printf("Некорректный ввод!\n");
}

void generate_matrix(info *information, int filling)
{
    if (information->is_a_defined)
        free_a(information);
    information->matrix = allocate_matrix(information->n, information->m);
    int required = information->n * information->m * filling / 100;
    int index = 0;
    if (information->matrix)
    {
        for (int i = 0; i < information->n; i++)
        {
            for (int j = 0; j < information->m; j++)
            {
                if (index++ < required)
                    information->matrix[i][j] = (i + 1) * (j + 1);
                else
                    information->matrix[i][j] = 0;
            }
        }
        int tmp = 0, i_rand, j_rand;
        for (int i= 0; i < information->n; i++)
            for (int j = 0; j < information->m; j++)
            {
                i_rand = rand() % information->n;
                j_rand = rand() % information->m;
                tmp = information->matrix[i][j];
                information->matrix[i][j] = information->matrix[i_rand][j_rand];
                information->matrix[i_rand][j_rand] = tmp;
            }
        information->is_a_defined = 1;
        printf("Хорошо, матрица сгенерирована\n");
    }
    else
        printf("Не удалось выделить память!\n");
    
}

void generate_column(info *information, int filling)
{
    if (information->is_b_defined)
        free_b_ccs(information);
    information->column_length = information->m;
    information->column = allocate_array(information->column_length);
    int required = information->column_length * filling / 100;
    if (information->column)
    {
        int index = 0;
        for (int i = 0; i < information->column_length; i++)
        {
            if (index++ < required)
                information->column[i] = (i + 1) * (i + 1);
            else
                information->column[i] = 0;
        }
        int tmp = 0, i_rand;
        for (int i = 0; i < information->column_length; i++)
        {
            i_rand = rand() % information->column_length;
            tmp = information->column[i_rand];
            information->column[i_rand] = information->column[i];
            information->column[i] = tmp;
        }
        information->is_b_defined = 1;
        printf("Хорошо, столбец сгенерирован\n");
    }
    else
        printf("Не удалось выделить память!\n");
}
void generate_data(info *information)
{
    if (information->is_c_defined)
        free_c(information);
    if (information->is_c_ccs_defined)
        free_c_ccs(information);
    printf("Введите процент заполнения матрицы: ");
    char end = 0;
    int filling = 0, check = 0;
    check = scanf("%d%c", &filling, &end);
    if (check == 2 && filling >= 0 && filling <= 100 && end == '\n')
    {
        generate_matrix(information, filling);
        convert_usual_to_crs(information);
        printf("Введите процент заполения столбца: ");
        check = scanf("%d%c", &filling, &end);
        if (check == 2 && filling >= 0 && filling <= 100 && end == '\n')
        {
            generate_column(information, filling);
            convert_usual_to_ccs(information);
            print_data(information);
            printf("Успех, всё заполнено\n\n");
        }
    }
}

void multiply(info *information)
{
    printf("Каким способом хотите умножить?\n");
    printf(" 1 - Обычным способом\n");
    printf(" 2 - С помощью разреженного строчного формата\n");
    printf(" Введите решение: ");
    char ch = 0;
    int check = 0;
    check = scanf("%c", &ch);
    if (check != EOF)
    {
        switch (ch)
        {
            case '1':
                myflush();
                multiply_old(information);
                print_data(information);
                printf("Сделано!\n");
                break;
            case '2':
                myflush();
                multip_crs(information);
                print_data(information);
                printf("Сделано!\n");
                break;
            default:
                myflush();
                printf("Некорректный ввод!\n");
        }
    }
}