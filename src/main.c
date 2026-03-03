#include <stdio.h>
#include "file_processor.h"

int main() {
    printf("=== Программа обработки данных военнослужащих ===\n");
    printf("Фильтрация: звание 'лейтенант'\n\n");
    
    process_file("data/input.txt", "data/output.txt");
    
    printf("\nПрограмма завершена. Проверьте data/output.txt\n");
    return 0;
}
