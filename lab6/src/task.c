#include "generator.h"
#include "bubblesort.h"
#include "qsort.h"
#include "checker.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "gen"))
        {
            int block_cnt = 16, block_size = 1024;
            if (argc > 2)
            {
                int tmp;
                if (sscanf(argv[2], "%d", &tmp))
                {
                    block_cnt = tmp;
                }
            }
            if (argc > 3)
            {
                int tmp;
                if (sscanf(argv[3], "%d", &tmp))
                {
                    block_size = tmp;
                }
            }
            start_generator(block_cnt, block_size);
        }
        if (!strcmp(argv[1], "check"))
        {
            start_checker();
        }
        if (!strcmp(argv[1], "qsort"))
        {
            start_qsort();
        }
        if (!strcmp(argv[1], "bubble"))
        {
            start_bubblesort();
        }
    }
    else
    {
        printf("No action specified...\n");
    }

    return 0;
}