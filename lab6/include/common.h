#ifndef COMMON_H
#define COMMON_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

int create_shared_mem(const char *name, int size, int **mem_ptr);
int release_shared_mem(const char *name, int shm, int *mem_ptr, int size);

int open_shared_mem(const char *name, int size, int **mem_ptr);
int close_shared_mem(const char *name, int shm, int *mem_ptr, int size);

sem_t* create_semaphore(const char *name, unsigned int val);
int release_semaphore(const char *name, sem_t *sem);

sem_t* open_semaphore(const char *name);
int close_semaphore(const char *name, sem_t* sem);

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // COMMON_H