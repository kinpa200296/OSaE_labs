#include "defs.h"

#ifndef MORSE_H
#define MORSE_H

#ifdef __cplusplus
extern "C" {
#endif

bool try_parse_morse_code(const char *morse_str, int *ch);
bool has_morse_code(const char ch);
const char *get_morse_code(const char ch);

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // MORSE_H