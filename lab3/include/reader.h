#ifndef READER_H
#define READER_H

#ifdef __cplusplus
extern "C" {
#endif

void init_reader();
int reader_parse(const int val);
const char* reader_get_buffer();
void release_reader();


#ifdef __cplusplus  
} // extern "C" {
#endif

#endif // READER_H