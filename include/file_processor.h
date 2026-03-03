#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#define MAX_FIELDS 15
#define MAX_STRING_LEN 100
#define EXPECTED_FIELDS 15

typedef struct {
    char fields[MAX_FIELDS][MAX_STRING_LEN];
} Record;

void process_file(const char *input_file, const char *output_file);
int parse_line(char *line, Record *record);
int is_vaz(const Record *record);
void write_record(FILE *out, const Record *record);
void write_header(FILE *out);

#endif
