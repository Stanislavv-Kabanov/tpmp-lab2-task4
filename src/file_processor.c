#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_processor.h"

int parse_line(char *line, Record *record) {
    int field = 0;
    char *token = strtok(line, ";");
    
    while (token != NULL && field < MAX_FIELDS) {
        strncpy(record->fields[field], token, MAX_STRING_LEN - 1);
        record->fields[field][MAX_STRING_LEN - 1] = '\0';
        field++;
        token = strtok(NULL, ";");
    }
    
    return field;
}

int is_vaz(const Record *record) {
    const char *mark = record->fields[12];
    return (strcmp(mark, "ВАЗ") == 0);
}

void write_header(FILE *out) {
    fprintf(out, "Фамилия;Имя;Отчество;Телефон;Индекс;Страна;Область;Район;Город;Улица;Дом;Квартира;Марка;НомерАвто;НомерТехпаспорта\n");
}

void write_record(FILE *out, const Record *record) {
    for (int i = 0; i < MAX_FIELDS; i++) {
        fprintf(out, "%s", record->fields[i]);
        if (i < MAX_FIELDS - 1) {
            fprintf(out, ";");
        }
    }
    fprintf(out, "\n");
}

void process_file(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        printf("ОШИБКА: Не удалось открыть файл %s\n", input_file);
        return;
    }
    
    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    if (size == 0) {
        printf("ОШИБКА: Файл пуст\n");
        fclose(in);
        return;
    }
    rewind(in);
    
    FILE *out = fopen(output_file, "w");
    if (!out) {
        printf("ОШИБКА: Не удалось создать файл %s\n", output_file);
        fclose(in);
        return;
    }
    
    char line[1024];
    int line_num = 0;
    int vaz_count = 0;
    Record record;
    
    if (fgets(line, sizeof(line), in)) {
        line[strcspn(line, "\n")] = 0;
        int fields = parse_line(line, &record);
        if (fields == EXPECTED_FIELDS) {
            write_header(out);
        } else {
            printf("ПРЕДУПРЕЖДЕНИЕ: Заголовок содержит %d полей (ожидалось %d)\n", 
                   fields, EXPECTED_FIELDS);
            write_header(out);
        }
        line_num++;
    }
    
    while (fgets(line, sizeof(line), in)) {
        line_num++;
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) == 0) {
            printf("ПРЕДУПРЕЖДЕНИЕ: Строка %d пустая\n", line_num);
            continue;
        }
        
        int fields = parse_line(line, &record);
        
        if (strlen(record.fields[0]) == 0) {
            printf("ПРЕДУПРЕЖДЕНИЕ: Строка %d содержит некорректные данные.\n", line_num);
            continue;
        }
        
        if (fields != EXPECTED_FIELDS) {
            printf("ПРЕДУПРЕЖДЕНИЕ: Строка %d содержит %d полей (ожидалось %d).\n", 
                   line_num, fields, EXPECTED_FIELDS);
            continue;
        }
        
        if (is_vaz(&record)) {
            write_record(out, &record);
            vaz_count++;
        }
    }
    
    if (vaz_count == 0) {
        printf("Автомобилей марки ВАЗ не найдено\n");
        fprintf(out, "Автомобилей марки ВАЗ не найдено\n");
    } else {
        printf("Найдено автомобилей ВАЗ: %d\n", vaz_count);
    }
    
    fclose(in);
    fclose(out);
}
