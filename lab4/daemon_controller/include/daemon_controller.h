#ifndef DAEMON_CONTROLLER_H
#define DAEMON_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <signal.h>

#define IDENTITY "daemon_controller"
#define CONFIG_FILE "config.txt"
#define CONFIG_LOCATION "/var/run/config.txt"
#define MIN_DELAY 50
#define DELAY_MULTIPLIER 2

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // DAEMON_CONTROLLER_H