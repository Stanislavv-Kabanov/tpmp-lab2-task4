#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

typedef struct {
    char country[100];        
    char capital[100];         
    char language[50];         
    int population;            
    float area;               
    char currency[50];         
    char government[100];      
    char head[100];            
} State;


void process_file(const char *input_file, const char *output_file);
void print_state(const State *s, FILE *out);
int is_large_population(const State *s);

#endif
