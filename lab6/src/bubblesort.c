#include "bubblesort.h"

void bubblesort(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            if (arr[i] > arr[j])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
}

void start_bubblesort()
{
    printf("starting bubblesort...\n");

    int mem_shm, config_shm, *pmem, *pconfig, block_cnt, block_size, sorted_cnt = 0;
    int mem_size, config_size = sizeof(int)*CONFIG_PARAMS_CNT;
    sem_t *config_sem;

    config_sem = create_semaphore(CONFIG_SEM_NAME, 1);
    if (config_sem == SEM_FAILED)
        return;

    config_shm = create_shared_mem(SHM_CONFIG, config_size, &pconfig);
    if (config_shm == -1)
        return;

    printf("loading config...\n");

    sem_wait(config_sem);
    block_cnt = pconfig[0];
    block_size = pconfig[1];
    sem_post(config_sem);

    if (close_shared_mem(SHM_CONFIG, config_shm, pconfig, config_size)) 
        return;
    config_size = sizeof(int)*(CONFIG_PARAMS_CNT + block_cnt);
    config_shm = create_shared_mem(SHM_CONFIG, config_size, &pconfig);
    if (config_shm == -1)
        return;

    printf("config loaded...\n");

    mem_size = sizeof(int)*block_cnt*block_size;

    mem_shm = create_shared_mem(SHM_NAME, mem_size, &pmem);
    if (mem_shm == -1)
        return;

    printf("bubblesort started...\n");

    bool done = false;

    while (!done)
    {
        int i = -1;

        sem_wait(config_sem);
        if (pconfig[2] > pconfig[3])
        {
            i = pconfig[3];
            pconfig[3]++;
        }
        if (pconfig[6] == block_cnt)
            done = true;
        sem_post(config_sem);

        if (i > -1)
        {
            printf("sorting block %d\n", i);
            bubblesort(pmem + i*block_size, block_size);
            printf("sorted block %d\n", i);
            sorted_cnt++;
            sem_wait(config_sem);
            pconfig[CONFIG_PARAMS_CNT + pconfig[4]] = i;
            pconfig[4]++;
            sem_post(config_sem);
        }
        else
        {
            if (!done)
                usleep(usleep_milliseconds(REFRESH_RATE));
        }
    }

    if (close_shared_mem(SHM_NAME, mem_shm, pmem, mem_size)) 
        return;
    if (close_shared_mem(SHM_CONFIG, config_shm, pconfig, config_size)) 
        return;
    if (close_semaphore(CONFIG_SEM_NAME, config_sem))
        return;

    printf("bubblesort finished...\n");
    printf("sorted %d out of %d blocks\n", sorted_cnt, block_cnt);
}