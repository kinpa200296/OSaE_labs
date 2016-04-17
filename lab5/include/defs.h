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
#include "fcntl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define bool int
#define true 1
#define false 0

#define NAMEDPIPE "/tmp/lab5_pipe"
#define PASSBUFSIZE 50

#define usleep_milliseconds(a) a*1000

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // DEFS_H