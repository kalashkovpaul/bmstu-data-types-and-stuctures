#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 4)
    {
        FILE *dst = fopen(argv[1], "w");
        int n = atoi(argv[2]);
        int chance = 0;
        int percent = atoi(argv[3]);
        fprintf(dst, "%d\n", n);
        for (int j = 0; j < n - 1; j++)
        {
            chance = rand() % 101;
            if (chance < percent)
                fprintf(dst, "%d\n", rand() & 1000);
            else
                fprintf(dst, "%d\n", 0);
        }
        chance = rand() % 101;
        if (chance < percent)
            fprintf(dst, "%d", rand() & 1000);
        else
            fprintf(dst, "%d", 0);
        fclose(dst);
    }
    return 0;
}