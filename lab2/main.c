#include "stdio.h"
#include "string.h"
#include "morse.h"
#include "reader.h"

FILE *input_file, *output_file;

void process_unknown_reader_result()
{
    printf("unknown reader result\n");
}

void process_character_ignored(int ch)
{
    //printf("ignoring character '%c'\n", ch);
}

void process_whitespace(FILE *out_stream)
{
    int ch;
    if (try_parse_morse_code(reader_get_buffer(), &ch))
    {
        fputc(ch, out_stream);
    }
}

void process_carriage_return(FILE *out_stream)
{
    process_whitespace(out_stream);
    fputc(' ', out_stream);
}

void process_reader_result(int res, int ch, FILE *out_stream)
{
    switch(res)
    {
        case 1:
            break;
        case 2:
            process_whitespace(out_stream);
            break;
        case 3:
            process_carriage_return(out_stream);
            break;
        case 0:
            process_character_ignored(ch);
            break;
        default:
            process_unknown_reader_result();
            break;
    }
}

void run_manual()
{
    int ch = getc(stdin);

    while (ch != EOF)
    {
        int res = reader_parse(ch);
        process_reader_result(res, ch, stdout);
        ch = getc(stdin);
    }
    process_whitespace(stdout);
    printf("\n");
}

void run_with_string(const char **argc)
{
    const char *buffer = argc[1];
    //char *buffer;

    //buffer = (char*) malloc(sizeof(char)*strlen(argc[1]) + 1);
    //strcpy(buffer, argc[1]);

    int n = strlen(buffer);

    for (int i = 0; i < n; i++)
    {
        int res = reader_parse(buffer[i]);
        process_reader_result(res, buffer[i], stdout);
    }
    process_whitespace(stdout);
    printf("\n");

    //free(buffer);
}

void run_with_files(const char **argc)
{
    const char *input_file_name = argc[1], *output_file_name = argc[2];
    //char *input_file_name, *output_file_name;

    //input_file_name = (char*) malloc(sizeof(char)*strlen(argc[1]) + 1);
    //output_file_name = (char*) malloc(sizeof(char)*strlen(argc[2]) + 1);
    //strcpy(input_file_name, argc[1]);
    //strcpy(output_file_name, argc[2]);

    input_file = fopen(input_file_name, "r");
    output_file = fopen(output_file_name, "w");

    int ch = fgetc(input_file);

    while (ch != EOF)
    {
        int res = reader_parse(ch);
        process_reader_result(res, ch, output_file);
        ch = fgetc(input_file);
    }
    process_whitespace(output_file);
    fprintf(output_file, "\n");

    fclose(output_file);
    fclose(input_file);

    //free(input_file_name);
    //free(output_file_name);
}

int main(int argv, const char **argc)
{
    init_reader();

    switch(argv)
    {
        case 1:
            run_manual();
            break;
        case 2:
            run_with_string(argc);
            break;
        case 3:
            run_with_files(argc);
            break;
        default:
            printf("You should choose one option:\n - use manual input(no args)\n - give a string with morse code(1 arg)\n - specify input and output file(2 args)\n");
            break;
    }

    release_reader();

    return 0;
}