#include "checker.h"

void start_checker()
{
    printf("starting checker...\n");

    int mem_shm, config_shm, *pmem, *pconfig, block_cnt, block_size, correct_blocks = 0;
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

    printf("checker started...\n");

    bool done = false;

    while (!done)
    {
        int i = -1;

        sem_wait(config_sem);
        if (pconfig[4] > pconfig[5])
        {
            i = pconfig[CONFIG_PARAMS_CNT + pconfig[5]];
            pconfig[5]++;
        }
        if (pconfig[6] == block_cnt)
            done = true;
        sem_post(config_sem);

        if (i > -1)
        {
            printf("checking block %d...\n", i);
            bool res = true;
            for (int j = i*block_size; j < (i + 1)*block_size - 1; j++)
            {
                res = res && (pmem[j] <= pmem[j + 1]);
            }
            if (res)
            {
                printf("checked block %d...OK\n", i);
                correct_blocks++;
            }
            else printf("checked block %d...FAIL\n", i);
            sem_wait(config_sem);
            pconfig[6]++;
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

    printf("checker finished...\n");
    printf("checked %d blocks. %d corect.\n", block_cnt, correct_blocks);
}