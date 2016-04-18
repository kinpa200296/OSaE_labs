#include "common.h"

int create_shared_mem(const char *name, int size, int **mem_ptr)
{
    int shm;

    shm = shm_open(name, O_CREAT | O_RDWR, 0777);
    if (shm == -1)
    {
        perror("create_shared_mem (shm_open)");
        return -1;
    }

    if (ftruncate(shm, size) == -1)
    {
        perror("create_shared_mem (ftruncate)");
        return -1;
    }

    *mem_ptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

    if (*mem_ptr == (int*)-1)
    {
        perror("create_shared_mem (mmap)");
        return -1;
    }

    printf("created shared memory %s, size = %d\n", name, size);

    return shm;
}

int release_shared_mem(const char *name, int shm, int *mem_ptr, int size)
{
    int res = munmap(mem_ptr, size);
    if (res)
    {
        perror("release_shared_mem (munmap)");
        return res;
    }
    res = close(shm);
    if (res)
    {
        perror("release_shared_mem (close)");
        return res;
    }
    res = shm_unlink(name);
    if (res)
    {
        perror("release_shared_mem (shm_unlink)");
        return res;
    }

    printf("released shared memory %s, size = %d\n", name, size);
    return res;
}

int open_shared_mem(const char *name, int size, int **mem_ptr)
{
    int shm;

    shm = shm_open(name, O_RDWR, 0777);
    if (shm == -1)
    {
        perror("shm_open");
        return -1;
    }

    if (ftruncate(shm, size) == -1)
    {
        perror("ftruncate");
        return -1;
    }

    *mem_ptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

    if (*mem_ptr == (int*)-1)
    {
        perror("mmap");
        return -1;
    }

    printf("opened shared memory %s, size = %d\n", name, size);

    return shm;
}

int close_shared_mem(const char *name, int shm, int *mem_ptr, int size)
{
    int res = munmap(mem_ptr, size);
    if (res)
    {
        perror("release_shared_mem (munmap)");
        return res;
    }
    res = close(shm);
    if (res)
    {
        perror("release_shared_mem (close)");
        return res;
    }

    printf("closed shared memory %s, size = %d\n", name, size);
    return res;
}

sem_t* create_semaphore(const char *name, unsigned int val)
{
    sem_t *res = sem_open(name, O_CREAT | O_RDWR, 0777, val);
    if (res == SEM_FAILED)
    {
        perror("create_semaphore");
    }

    printf("created semaphore %s, value = %d\n", name, val);
    return res;
}

int release_semaphore(const char *name, sem_t *sem)
{
    int res = sem_close(sem);
    if (res == -1)
    {
        perror("close_semaphore");
        return res;
    }
    res = sem_unlink(name);
    if (res)
    {
        perror("release_semaphore");
    }

    printf("released semaphore %s\n", name);
    return res;
}

sem_t* open_semaphore(const char *name)
{
    sem_t *res = sem_open(name, O_RDWR);
    if (res == SEM_FAILED)
    {
        perror("open_semaphore");
    }

    printf("opened semaphore %s\n", name);
    return res;
}

int close_semaphore(const char *name, sem_t* sem)
{
    int res = sem_close(sem);
    if (res == -1)
    {
        perror("close_semaphore");
    }

    printf("closed semaphore %s\n", name);
    return res;
}