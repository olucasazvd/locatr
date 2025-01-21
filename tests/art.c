#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void to_lowercase(char* str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

void print_ascii_art(const char* continent_code) {
    // Copia o código do continente para garantir que podemos modificá-lo
    char continent_code_lower[10];
    snprintf(continent_code_lower, sizeof(continent_code_lower), "%s", continent_code);

    // Converte o código para minúsculas
    to_lowercase(continent_code_lower);

    // Monta o caminho do arquivo com base no código do continente em minúsculo
    char filename[256];
    snprintf(filename, sizeof(filename), "assets/countries_ascii/%s/%s.txt", continent_code_lower, continent_code_lower);

    // Abre o arquivo
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Não foi possível encontrar a arte para o continente %s!\n", continent_code_lower);
        return;
    }

    // Imprime o conteúdo do arquivo
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

int main() {
    // Exemplo de uso: supondo que você tenha o código do continente
    char continent_code[] = "BR";  // Mude para o código do continente desejado
    print_ascii_art(continent_code);
    return 0;
}

