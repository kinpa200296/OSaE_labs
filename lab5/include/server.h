#ifndef SERVER_H
#define SERVER_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define REFRESH_RATE 10

int launch_server(int password_timeout);

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // SERVER_H