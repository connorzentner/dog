#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void syntax_highlight(const char *line) {
    int state = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (state == 0 && line[i] == '"') {
            printf(GREEN "\"");
            state = 1;
        } else if (state == 1 && line[i] == '"') {
            printf("\"" RESET);
            state = 0;
        } else {
            printf("%c", line[i]);
        }
    }
    printf(RESET);
}

int main(int argc, char **argv) {
    char lines[500];
    int number = 0;
    int opt;

    bool show_syntax = false;
    bool show_numbers = false;
    bool show_bullets = false;

    while ((opt = getopt(argc, argv, "sn")) != -1) {
        switch (opt) {
            case 's':
                show_syntax = true;
                break;
            case 'n':
                show_numbers = true;
                break;
        }
    }

    FILE *file = fopen(argv[optind], "r");
    
    if (file == NULL) {
        printf(BOLD RED "%s " RESET "not found.\n", argv[1]);
        return 1;
    } else if (optind >= argc) {
        printf(BOLD RED "ERROR " RESET "expected argument after flag.\n");
        return 1;
    }

    while (fgets(lines, 500, file) != NULL) {
        if (show_syntax) {
            syntax_highlight(lines);
        } else if (show_numbers) {
            number ++;
            printf(BOLD YELLOW "%2d" RESET " │ ", number);
            printf("%s", lines);
        } else {
            printf("%s", lines);
        }
    }

    return 0;
}
