#include "generator.h"

void start_generator(int block_cnt, int block_size)
{
    printf("starting generator...\n");

    int mem_shm, config_shm, *pmem, *pconfig;
    int mem_size = sizeof(int)*block_cnt*block_size;
    int config_size = sizeof(int)*(CONFIG_PARAMS_CNT + block_cnt);
    sem_t *config_sem;

    config_sem = create_semaphore(CONFIG_SEM_NAME, 1);
    if (config_sem == SEM_FAILED)
        return;

    mem_shm = create_shared_mem(SHM_NAME, mem_size, &pmem);
    if (mem_shm == -1)
        return;

    config_shm = create_shared_mem(SHM_CONFIG, config_size, &pconfig);
    if (config_shm == -1)
        return;

    printf("starting config setup...\n");

    sem_wait(config_sem);
    pconfig[0] = block_cnt;
    pconfig[1] = block_size;
    pconfig[2] = 0;
    pconfig[3] = 0;
    pconfig[4] = 0;
    pconfig[5] = 0;
    pconfig[6] = 0;
    sem_post(config_sem);

    printf("finished config setup...\n");

    printf("generator started...\n");

    srand((unsigned int)clock());

    for (int i = 0; i < block_cnt; i++)
    {
        printf("generating block %d...\n", i);
        for (int j = i*block_size; j < (i + 1)*block_size; j++)
        {
            pmem[j] = rand()%(1000000007);
        }
        printf("generated block %d...\n", i);

        sem_wait(config_sem);
        pconfig[2]++;
        sem_post(config_sem);
    }

    bool done = false;

    while (!done)
    {
        sem_wait(config_sem);
        if (pconfig[6] == block_cnt)
            done = true;
        sem_post(config_sem);
        if (!done)
            usleep(usleep_milliseconds(REFRESH_RATE));
    }


    if (release_shared_mem(SHM_CONFIG, config_shm, pconfig, config_size)) 
        return;
    if (release_shared_mem(SHM_NAME, mem_shm, pmem, mem_size)) 
        return;
    if (release_semaphore(CONFIG_SEM_NAME, config_sem))
        return;

    printf("generator finished...\n");
}