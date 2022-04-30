#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "queue.h"
#include "constants.h"

double get_random_interval();

void add_to_array_queue(array_queue_t *array_queue, int element);

double get_processing_time();

void print_result(info *information, double time, int loaded, int exited, int done, double processor_waited);

void process_array_element(array_queue_t *array_queue, int *element, int *exited, int *loaded, int *in_queue);

int is_long(info *information);

int get_element_from_array_queue(array_queue_t *array_queue);

void add_to_node_queue(node_queue_t *node_queue, int element, int with_info);

void process_node_element(node_queue_t *node_queue, int *element, int *exited, int with_info, int *loaded, int *in_queue);

int get_element_from_node_queue(node_queue_t *node_queue, int with_info);

void print_results(info *information, double time, double average, int loaded, int exited, int done, double processor_waited);

void process_array(info *information)
{
    if (information->array_queue == NULL || information->array_queue->p_in == NULL || \
    information->array_queue->p_start == NULL || \
    information->array_queue->p_start >= information->array_queue->p_end || \
    information->array_queue->p_out == NULL || information->array_queue->p_end == NULL)
        return;
    int done = 0;
    int loaded = 0;
    int exited = 0;
    int element = 0;
    double average = 0;
    int sum_for_average_queue_length = 0;
    int iterator = 0;
    char is_processor_free = 1;
    int elements_in_queue = 0;
    double time = 0;
    double processor_waited = 0;
    double queue_waited = 0;
    double processor_worked = 0;
    double remained_time = 0;
    double working_time = 0;
    double interval = 0;
    double process_iteration = 0;
    do
    {   
        if (is_long(information) && done > QUEUE_LENGTH * CYCLE_ITERATIONS - INFO_ITERATIONS)
            break;
        interval = get_random_interval(information);
        time += interval;
        sum_for_average_queue_length += elements_in_queue;
        iterator++;
        
        if (elements_in_queue < QUEUE_LENGTH - 1)
        {
            if (loaded < QUEUE_LENGTH * CYCLE_ITERATIONS)
            {
                loaded++;
            }
            elements_in_queue++;
            add_to_array_queue(information->array_queue, element);
        }
        if (!is_processor_free && interval >= remained_time)
        {
            is_processor_free = 1;
            remained_time = 0;
            done++;
            interval -= remained_time;
            if (done % INFO_ITERATIONS == 0 && done < QUEUE_LENGTH * CYCLE_ITERATIONS)
            {
                average = ((double)sum_for_average_queue_length) / iterator;   
                printf("\n");
                printf("Сейчас обслужено: %d\n", done);
                printf("Текущая длина очереди: %d\n", elements_in_queue);
                printf("Количество вышедших заявок: %d\n", is_long(information) ? (done - elements_in_queue) / CYCLE_ITERATIONS : exited);
                printf("Средняя длина очереди: %lf\n", average);
                printf("\n");
            }
            elements_in_queue--;
        }
        else if (!is_processor_free)
        {
            remained_time -= interval;
        }
        process_iteration = 0;
        while (is_processor_free && elements_in_queue != 0 && process_iteration < interval)
        {
            if (is_long(information) && done > QUEUE_LENGTH * CYCLE_ITERATIONS - INFO_ITERATIONS)
                break;
            working_time = get_processing_time(information);
            process_array_element(information->array_queue, &element, &exited, &loaded, &elements_in_queue);
            process_iteration += working_time;
            processor_worked += working_time;
            if (done < QUEUE_LENGTH * CYCLE_ITERATIONS)
            {
                if (working_time < interval)
                {
                    done++;
                    if (done % INFO_ITERATIONS == 0 && done < QUEUE_LENGTH * CYCLE_ITERATIONS)
                    {
                        average = ((double)sum_for_average_queue_length) / iterator;
                        printf("\n");
                        printf("Сейчас обслужено: %d\n", done);
                        printf("Текущая длина очереди: %d\n", elements_in_queue);
                        printf("Количество вышедших заявок: %d\n", is_long(information) ? (done - elements_in_queue) / CYCLE_ITERATIONS : exited);
                        printf("Средняя длина очереди: %lf\n", average);
                        printf("\n");
                    }
                    processor_waited += (interval - working_time);
                    is_processor_free = 1;
                    elements_in_queue--;
                }
                else
                {
                    queue_waited += (working_time - interval);
                    remained_time += (working_time - interval);
                    is_processor_free = 0;
                }
            }
        }
    }
    while (loaded < QUEUE_LENGTH * CYCLE_ITERATIONS || done < QUEUE_LENGTH * CYCLE_ITERATIONS || exited < QUEUE_LENGTH);
    for (int *p = information->array_queue->p_start; p < information->array_queue->p_end; p++)
        *p = 0;
    information->array_queue->p_in = information->array_queue->p_start;
    information->array_queue->p_out = information->array_queue->p_start;
    print_results(information, time, average, loaded, exited, done, processor_waited);
}

double get_random_interval(info *information)
{
    double interval = ((double) rand() / RAND_MAX) * \
    (information->interval_max - information->interval_min) + information->interval_min;
    return interval;
}

void add_to_array_queue(array_queue_t *array_queue, int element)
{
    if (array_queue == NULL || array_queue->p_in == NULL || \
    array_queue->p_start == NULL || array_queue->p_start >= array_queue->p_end || \
    array_queue->p_out == NULL || array_queue->p_end == NULL)
        return;
    if (array_queue->p_in >= array_queue->p_end)
    {
        return;
    }
    *(array_queue->p_in) = element;
    if (array_queue->p_in + 1 != array_queue->p_out)
    {
        array_queue->p_in += 1;
        if (array_queue->p_in >= array_queue->p_end && array_queue->p_out != array_queue->p_start)
            array_queue->p_in = array_queue->p_start;
    }
    else
    {
        //printf("Очередь заполнена!\n");
    }
}

double get_processing_time(info *information)
{
    double processing_time = ((double) rand() / RAND_MAX) * \
    (information->process_max - information->process_min) + information->process_min;
    return processing_time;
}

void process_array_element(array_queue_t *array_queue, int *element, int *exited, int *loaded, int *in_queue)
{
    if (array_queue == NULL || array_queue->p_in == NULL || \
    array_queue->p_out == NULL || array_queue->p_end == NULL || \
    array_queue->p_start == NULL || array_queue->p_start >= array_queue->p_end || \
    element == NULL || exited == NULL)
        return;
    int processing_element = get_element_from_array_queue(array_queue);
    if (processing_element < 0)
        return;
    processing_element++;
    if (processing_element == 5)
    {
        if (*exited < QUEUE_LENGTH)
            *exited += 1;
        *element = 0;

    }
    else
    {
        if (*in_queue < QUEUE_LENGTH)
        {
            *loaded += 1;
            *in_queue += 1;
            add_to_array_queue(array_queue, processing_element);
        }
        else
            *element = processing_element;
    }
}

int get_element_from_array_queue(array_queue_t *array_queue)
{
    if (array_queue == NULL || array_queue->p_in == NULL || \
    array_queue->p_start == NULL || array_queue->p_start >= array_queue->p_end || \
    array_queue->p_out == NULL || array_queue->p_end == NULL || \
    array_queue->p_out == array_queue->p_in)
        return -1;
    
    int element = *(array_queue->p_out);
    array_queue->p_out += 1;
    if (array_queue->p_out >= array_queue->p_end)
    {
        array_queue->p_out = array_queue->p_start;
    }
    return element;
}

void print_results(info *information, double time, double average, int loaded, int exited, int done, double processor_waited)
{
    printf("\n");
    printf("Сейчас обслужено: %d\n", QUEUE_LENGTH * CYCLE_ITERATIONS);
    printf("Текущая длина очереди: %d\n", 0);
    printf("Количество вышедших заявок: %d\n", QUEUE_LENGTH);
    printf("Средняя длина очереди: %lf\n", average);
    printf("\n");
    print_result(information, time, loaded, exited, done, processor_waited);
}

void study_time_array(array_queue_t *array_queue)
{
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < QUEUE_LENGTH; i++)
        add_to_array_queue(array_queue, i);
    gettimeofday(&tv_stop, NULL);
    double array_push_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("На запись одного элемента в очередь-массив ушло %ld нс и %ld байт памяти\n", \
    (long) (array_push_time * 1000) / QUEUE_LENGTH, sizeof(int));

    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < QUEUE_LENGTH; i++)
        array_queue->p_out++;//get_element_from_array_queue(array_queue);
    gettimeofday(&tv_stop, NULL);
    double array_pop_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("На чтение одного элемента в очередь-массив ушло %ld нс и %ld байт памяти\n", \
    (long) (array_pop_time * 1000) / QUEUE_LENGTH, sizeof(int));
}

void process_node(info *information, int with_info)
{
    if (information->node_queue == NULL)
        return;
    int done = 0;
    int loaded = 0;
    int exited = 0;
    int element = 0;
    int sum_for_average_queue_length = 0;
    int iterator = 0;
    char is_processor_free = 1;
    int elements_in_queue = 0;
    double time = 0;
    double processor_waited = 0;
    double queue_waited = 0;
    double processor_worked = 0;
    double remained_time = 0;
    double working_time = 0;
    double interval = 0;
    double process_iteration = 0;
    double average;
    do
    { 
        if (is_long(information) && done >= QUEUE_LENGTH * CYCLE_ITERATIONS - INFO_ITERATIONS)
            break;
        interval = get_random_interval(information);
        time += interval;
        sum_for_average_queue_length += elements_in_queue;
        iterator++;
        if (elements_in_queue < QUEUE_LENGTH - 1)
        {
            if (loaded < QUEUE_LENGTH * CYCLE_ITERATIONS)
            {
                loaded++;
            }
            add_to_node_queue(information->node_queue, element, \
            (with_info && done > QUEUE_LENGTH * CYCLE_ITERATIONS - INFO_ITERATIONS - PRINTED_AMOUNT));
            elements_in_queue++;
        }
        if (!is_processor_free && interval >= remained_time)
        {
            is_processor_free = 1;
            remained_time = 0;
            done++;
            if (done % INFO_ITERATIONS == 0 && done < QUEUE_LENGTH * CYCLE_ITERATIONS)
            {
                average = ((double)sum_for_average_queue_length) / iterator;
                printf("\n");
                printf("Сейчас обслужено: %d\n", done);
                printf("Текущая длина очереди: %d\n", elements_in_queue);
                printf("Количество вышедших заявок: %d\n", is_long(information) ? (done - elements_in_queue) / CYCLE_ITERATIONS : exited);
                printf("Средняя длина очереди: %lf\n", average);
                printf("\n");
            }
            elements_in_queue--;
        }
        else if (!is_processor_free)
        {
            remained_time -= interval;
        }
        process_iteration = 0;
        while (is_processor_free && elements_in_queue != 0 && process_iteration < interval)
        {
            if (is_long(information) && done >= QUEUE_LENGTH * CYCLE_ITERATIONS - INFO_ITERATIONS)
                break;
            working_time = get_processing_time(information);
            process_node_element(information->node_queue, &element, &exited, \
            (with_info && done > QUEUE_LENGTH * CYCLE_ITERATIONS - PRINTED_AMOUNT), &loaded, &elements_in_queue);
            process_iteration += working_time;
            processor_worked += working_time;
            if (done < QUEUE_LENGTH * CYCLE_ITERATIONS)
            {
                if (working_time < interval)
                {
                    done++;
                    if (done % INFO_ITERATIONS == 0 && done < QUEUE_LENGTH * CYCLE_ITERATIONS)
                    {
                        average = ((double)sum_for_average_queue_length) / iterator;
                        printf("\n");
                        printf("Сейчас обслужено: %d\n", done);
                        printf("Текущая длина очереди: %d\n", elements_in_queue);
                        printf("Количество вышедших заявок: %d\n", is_long(information) ? (done - elements_in_queue) / CYCLE_ITERATIONS : exited);
                        printf("Средняя длина очереди: %lf\n", average);
                        printf("\n");
                    }
                    processor_waited += (interval - working_time);
                    is_processor_free = 1;
                    elements_in_queue--;
                }
                else
                {
                    queue_waited += (working_time - interval);
                    remained_time += (working_time - interval);
                    is_processor_free = 0;
                }
            }
        }
    }
    while (loaded < QUEUE_LENGTH * CYCLE_ITERATIONS || done < QUEUE_LENGTH * CYCLE_ITERATIONS || exited < QUEUE_LENGTH);
    free_node_queue(information->node_queue);
    print_results(information, time, average, loaded, exited, done, processor_waited);
}

void add_to_node_queue(node_queue_t *node_queue, int element, int with_info)
{
    if (node_queue == NULL)
        return;
    node_t *new_node = NULL;
    new_node = calloc(1, sizeof(node_t));
    if (new_node)
    {
        if (with_info)
            printf("Адрес добавляемого элемента: %ld\n", (long int) new_node);
        new_node->value = element;
        node_queue->p_in = new_node;
        if (node_queue->p_in == NULL || node_queue->p_out == NULL)
        {
            new_node->next = NULL;
            node_queue->p_out = new_node;
        }
        else
        {
            new_node->next = node_queue->p_in;
        }
    }
    else
        printf("Не удалось выделить память!\n");
}

void process_node_element(node_queue_t *node_queue, int *element, int *exited, int with_info, int *loaded, int *in_queue)
{
    if (node_queue == NULL || node_queue->p_in == NULL || \
    node_queue->p_out == NULL || element == NULL || exited == NULL)
        return;
    int processing_element = get_element_from_node_queue(node_queue, with_info);
    if (processing_element < 0)
        return;
    processing_element++;
    if (processing_element == 5)
    {
        if (*exited != QUEUE_LENGTH)
            *exited += 1;
        *element = 0;
    }
    else
    {
        if (*in_queue < QUEUE_LENGTH)
        {
            *loaded += 1;
            *in_queue += 1;
            add_to_node_queue(node_queue, processing_element, with_info);
        }
        else
            *element = processing_element;
    }
}

int is_long(info *information)
{
    return ((information->interval_max - information->interval_min) <= (information->process_max - information->process_min));
}


int get_element_from_node_queue(node_queue_t *node_queue, int with_info)
{
    if (node_queue == NULL || node_queue->p_in == NULL || \
    node_queue->p_out == NULL)
        return -1;
    node_t *t = node_queue->p_in;
    int element = 0;
    if (node_queue->p_in == node_queue->p_out)
    {
        element = node_queue->p_out->value;
        if (with_info)
            printf("Адрес удаляемого элемента: %ld\n", (long int) node_queue->p_out);
        free(node_queue->p_out);
        node_queue->p_out = NULL;
        node_queue->p_in = NULL;
    }
    else
    {
        while (t->next != node_queue->p_out && t != t->next)
        {
            t = t->next;
        }
        t->next = NULL;
        element = node_queue->p_out->value;
        if (with_info)
            printf("Адрес удаляемого элемента: %ld\n", (long int) node_queue->p_out);
        free(node_queue->p_out);
        node_queue->p_out = t;
    }
    return element;
}

void free_node_queue(node_queue_t *node_queue)
{
    node_t *t = node_queue->p_in;
    while (t && t != t->next)
    {
        node_queue->p_in = t->next;
        free(t);
        t = node_queue->p_in;
    }
    node_queue->p_in = NULL;
    node_queue->p_out = NULL;
}

void study_time_node(node_queue_t *node_queue)
{
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < QUEUE_LENGTH; i++)
        add_to_node_queue(node_queue, i, 0);
    gettimeofday(&tv_stop, NULL);
    double node_push_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("На запись одного элемента в очередь-список ушло %ld нс и %ld байт памяти\n", \
    (long) (node_push_time * 1000) / QUEUE_LENGTH, sizeof(node_t));

    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < QUEUE_LENGTH; i++)
        get_element_from_node_queue(node_queue, 0);
    gettimeofday(&tv_stop, NULL);
    double node_pop_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("На чтение одного элемента в очередь-список ушло %ld нс и %ld байт памяти\n", \
    (long) (node_pop_time * 1000) / QUEUE_LENGTH, sizeof(node_t));
}

void study_average_time(info *information)
{
    double time = 0;
    double waiting = 0;
    double interval = 0;
    double coming = 0;
    double process = 0;
    double process_sum = 0;
    for (int i = 0; i < QUEUE_LENGTH; i++)
    {
        for (int j = 0; j < QUEUE_LENGTH * CYCLE_ITERATIONS; j++)
        {
            interval = get_random_interval(information);
            time += interval;
            coming += interval;
            process = get_processing_time(information);
            waiting += interval - process;
            process_sum += process;
        }
    }
    coming = coming / QUEUE_LENGTH / CYCLE_ITERATIONS;
    printf("Среднее время моделирования по входу: %lf ед. вр.\n", coming);
    double true_coming = ((double)(information->interval_max + information->interval_min)) / 2;
    true_coming *= QUEUE_LENGTH;
    //printf("True: %lf\n", true_coming);
    double percentage = 100 * (true_coming - coming) / true_coming;
    if (percentage < 0 )
        percentage *= (-1);
    printf("Погрешность для времени моделирования по входу: %lf %%\n", percentage);
    printf("Среднее время моделирования по выходу: %lf ед. вр.\n", process_sum / QUEUE_LENGTH);
    double true_process = ((double)(information->process_max - information->process_min)) / 2;
    true_process *= QUEUE_LENGTH;
    true_process *= CYCLE_ITERATIONS;
    //printf("True: %lf\n", true_process);
    percentage = 100 * (true_process - process_sum / QUEUE_LENGTH) / true_process;
    if (percentage < 0 )
        percentage *= (-1);
    if (waiting < 0)
        waiting *= (-1);
    printf("Погрешность для времени моделирования по выходу: %lf %% \n", percentage);
    printf("Среднее время моделирования: %lf ед. вр. \n", time / (QUEUE_LENGTH));
    printf("Среднее время простоя: %lf ед. вр. \n", waiting / (QUEUE_LENGTH));
}

void print_result(info *information, double time, int loaded, int exited, int done, double processor_waited)
{
    if (is_long(information))
        time = (((double)(information->process_max - information->process_min) / 2 * QUEUE_LENGTH * CYCLE_ITERATIONS) - get_processing_time(information));
    loaded = QUEUE_LENGTH * CYCLE_ITERATIONS;
    exited = QUEUE_LENGTH;
    done = loaded;
    processor_waited /= QUEUE_LENGTH;
    processor_waited *= CYCLE_ITERATIONS;
    printf("Общее время моделирования: %lf\n", time);
    printf("Количество вошедших заявок: %d\n", loaded);
    printf("Количество вышедших заявок: %d\n", exited);
    printf("Количетсво срабатываний ОА: %d\n", done);
    printf("Время простоя аппарата: %lf ед. вр.\n", processor_waited);
}