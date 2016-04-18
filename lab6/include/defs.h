#ifndef DEFS_H
#define DEFS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "time.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "sys/mman.h"
#include "fcntl.h"
#include "semaphore.h"

#ifdef __cplusplus
extern "C" {
#endif

#define bool int
#define true 1
#define false 0

#define usleep_milliseconds(a) a*1000

#define SHM_NAME "lab6_shared_mem"
#define SHM_CONFIG "lab6_config_mem"
#define CONFIG_SEM_NAME "/lab6_semaphore"
#define CONFIG_PARAMS_CNT 7
#define REFRESH_RATE 25

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // DEFS_H