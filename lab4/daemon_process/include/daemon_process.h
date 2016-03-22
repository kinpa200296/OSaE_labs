#ifndef DAEMON_PROCESS_H
#define DAEMON_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>

#define usleep_milliseconds(a) a*1000
#define IDENTITY "daemon_process"
#define CONFIG_FILE "config.txt"
#define CONFIG_LOCATION "/var/run/config.txt"

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // DAEMON_PROCESS_H