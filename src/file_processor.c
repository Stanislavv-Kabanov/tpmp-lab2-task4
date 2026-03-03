#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_processor.h"

int is_large_population(const State *s) {
    return s->population > 20;
}

void print_state(const State *s, FILE *out) {
    fprintf(out, "=====================================\n");
    fprintf(out, "Страна: %s\n", s->country);
    fprintf(out, "Столица: %s\n", s->capital);
    fprintf(out, "Язык: %s\n", s->language);
    fprintf(out, "Население: %d млн\n", s->population);
    fprintf(out, "Площадь: %.1f тыс. км²\n", s->area);
    fprintf(out, "Валюта: %s\n", s->currency);
    fprintf(out, "Гос. строй: %s\n", s->government);
    fprintf(out, "Глава: %s\n", s->head);
}

void process_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        printf("Error: Cannot open input file %s\n", input_file);
        return;
    }
    
    FILE *out = fopen(output_file, "w");
    if (!out) {
        printf("Error: Cannot create output file %s\n", output_file);
        fclose(in);
        return;
    }
    
    State states[100];  
    int count = 0;
    int large_count = 0;
    
    fprintf(out, "ГОСУДАРСТВА С НАСЕЛЕНИЕМ БОЛЕЕ 20 МЛН ЧЕЛОВЕК\n");
    fprintf(out, "=============================================\n\n");
    
    while (fscanf(in, "%s %s %s %d %f %s %s %s", 
                  states[count].country,
                  states[count].capital,
                  states[count].language,
                  &states[count].population,
                  &states[count].area,
                  states[count].currency,
                  states[count].government,
                  states[count].head) == 8) {
        
        if (is_large_population(&states[count])) {
            print_state(&states[count], out);
            large_count++;
        }
        
        count++;
    }
    
    fprintf(out, "\n=====================================\n");
    fprintf(out, "Всего государств: %d\n", count);
    fprintf(out, "Государств с населением > 20 млн: %d\n", large_count);
    
    printf("Прочитано %d государств\n", count);
    printf("Найдено %d государств с населением > 20 млн\n", large_count);
    printf("Результаты сохранены в %s\n", output_file);
    
    fclose(in);
    fclose(out);
}
