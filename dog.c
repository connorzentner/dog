#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
    char word[32];
    int word_index = 0;
    
    char types[5][32] = { "int", "char", "float", "double" };
    int type_count = 4;

    char funcs[3][32] = { "void", "return" };
    int func_count = 2;

    char statements[10][32] = { "for", "while", "do", "switch", "case", "if", "else",  "break", "continue" };
    int statement_count = 9;

    char headers[3][32] = { "include", "define" };
    int header_count = 2;

    for (int i = 0; line[i] != '\0'; i++) {
        if (state == 1) {
            printf("%c", line[i]);
            if (line[i] == '"') {
                printf(RESET);
                state = 0;
            }
            continue; 
        }

        if (line[i] == '"') {
            printf(GREEN "\"");
            state = 1;
            continue;
        }

        if (isalnum(line[i]) || line[i] == '_') {
            if (word_index < 31) {
                word[word_index++] = line[i];
            }
            continue; 
        }

        if (word_index > 0) {
            word[word_index] = '\0';

            if (isdigit(word[0])) {
                printf(YELLOW "%s" RESET, word);
            } else {
                bool type_found = false;
                bool func_found = false;
                bool statement_found = false;
                bool header_found = false;

                for (int j = 0; j < type_count; j++) {
                    if (strcmp(word, types[j]) == 0) {
                        type_found = true;
                        break;
                    }
                }
                
                if (!type_found) {
                    for (int j = 0; j < func_count; j++) {
                        if (strcmp(word, funcs[j]) == 0) {
                            func_found = true;
                            break;
                        }
                    }
                }

                if (!func_found) {
                    for (int j = 0; j < statement_count; j++) {
                        if (strcmp(word, statements[j]) == 0) {
                            statement_found = true;
                            break;
                        }
                    }
                }

                if (!statement_found) {
                    for (int j = 0; j < header_count; j++) {
                        if (strcmp(word, headers[j]) == 0) {
                            header_found = true;
                            break;
                        }
                    }
                }

                if (type_found) {
                    printf(BOLD RED "%s" RESET, word);
                } else if (func_found) {
                    printf(BOLD BLUE "%s" RESET, word);
                } else if (statement_found) {
                    printf(MAGENTA "%s" RESET, word);
                } else if (header_found) {
                    printf(BOLD CYAN "%s" RESET, word);
                } else if (line[i] == '(') {
                    printf(YELLOW "%s" RESET, word);
                } else {
                    printf("%s", word);
                }
            }
            word_index = 0;
        }

        switch (line[i]) {
            case '{': case '}': printf(YELLOW "%c" RESET, line[i]); break;
            case '[': case ']': printf(CYAN "%c" RESET, line[i]); break;
            case '(': case ')': printf(BLUE "%c" RESET, line[i]); break;
            case '#': printf(CYAN "%c" RESET, line[i]); break;
            default: printf("%c", line[i]); break;
        }
    }
    printf(RESET);
}

int main(int argc, char **argv) {
    char lines[500];
    int number = 0;
    int opt;

    bool show_syntax = true;
    bool show_numbers = true;

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
        if (show_numbers) {
            number ++;
            printf(BOLD YELLOW "%3d" RESET " │ ", number);
        } 

        if (show_syntax) {
            syntax_highlight(lines);
        } else {
            printf("%s", lines);
        }
    }

    return 0;
}
