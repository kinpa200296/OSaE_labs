#include "stdlib.h"
#include "defs.h"
#include "reader.h"

char *buffer;
int buffer_size, buffer_pos;
bool clear_buffer;

void expand()
{
    buffer_size *= 2;
    buffer = (char*) realloc(buffer, sizeof(char)*buffer_size);
}

void init_reader()
{
    buffer_size = 10;
    buffer = (char*) malloc(sizeof(char)*buffer_size);
    buffer_pos = 0;
    clear_buffer = false;
}

void release_reader()
{
    free(buffer);
}

int reader_parse(const int val)
{
    if (clear_buffer)
    {
        clear_buffer = false;
        buffer_pos = 0;
        buffer[buffer_pos] = 0;
    }
    switch(val)
    {
        case '.':
        case '-':
            if (buffer_pos + 1 >= buffer_size)
            {
                expand();
            }
            buffer[buffer_pos] = (char)val;
            buffer_pos++;
            buffer[buffer_pos] = 0;
            return 1;
        case ' ':
            clear_buffer = true;
            return 2;
        case '\n':
            clear_buffer = true;
            return 3;
        default:
            return 0;
    }
}

const char* reader_get_buffer()
{
    return (const char*)buffer;
}
