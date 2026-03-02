#include <stdio.h>
// #include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
// #include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Color macros
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
#define NUM_LANGUAGES (sizeof(languages) / sizeof(languages[0]))

// Struct for language configs
typedef struct {
    const char *extention;
    const char **types;
    int type_count;
    const char **keywords;
    int keyword_count;
    const char **statements;
    int statement_count;
    const char **headers;
    int header_count;
    const char *single_line_comment;
} LanguageConfig;

// C config
const char *c_types[] = { "int", "char", "float", "double", "bool", "long", "static", "const" };
const char *c_keywords[] = { "void", "return" };
const char *c_statements[] = { "for", "while", "do", "switch", "case", "if", "else", "break", "continue" };
const char *c_headers[] = { "include", "define" };
LanguageConfig c_lang = {
    .extention = ".c",
    .types = c_types,
    .type_count = 8,
    .keywords = c_keywords,
    .keyword_count = 2,
    .statements = c_statements,
    .statement_count = 9,
    .headers = c_headers,
    .header_count = 2,
    .single_line_comment = "//"
};

// Function for handling syntax highlighting
void syntax_highlight(const char *line, LanguageConfig *lang) {
    int state = 0;
    char word[32];
    int word_index = 0;
    char active_quote = '\0';

    for (int i = 0; line[i] != '\0'; i++) {
        // Single line comment detection
        if (state == 0 && lang->single_line_comment != NULL) {
            if (strncmp(&line[i], lang->single_line_comment, strlen(lang->single_line_comment)) == 0) {
                printf(GREEN "%s" RESET, &line[i]);
                return;
            }
        }
    
        if (state == 1) {
            printf("%c", line[i]);
            if (line[i] == active_quote && (i == 0 || line[i - 1] != '\\')) {
                printf(RESET);
                state = 0;
                active_quote = '\0';
            }
            continue; 
        }

        if (line[i] == '"' || line[i] == '\'') {
            active_quote = line[i];
            printf(GREEN "%c", active_quote);
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
                bool keyword_found = false;
                bool statement_found = false;
                bool header_found = false;

                for (int j = 0; j < lang->type_count; j++) {
                    if (strcmp(word, lang->types[j]) == 0) {
                        type_found = true;
                        break;
                    }
                }
                
                if (!type_found) {
                    for (int j = 0; j < lang->keyword_count; j++) {
                        if (strcmp(word, lang->keywords[j]) == 0) {
                            keyword_found = true;
                            break;
                        }
                    }
                }

                if (!keyword_found) {
                    for (int j = 0; j < lang->statement_count; j++) {
                        if (strcmp(word, lang->statements[j]) == 0) {
                            statement_found = true;
                            break;
                        }
                    }
                }

                if (!statement_found) {
                    for (int j = 0; j < lang->header_count; j++) {
                        if (strcmp(word, lang->headers[j]) == 0) {
                            header_found = true;
                            break;
                        }
                    }
                }

                if (type_found) {
                    printf(BOLD RED "%s" RESET, word);
                } else if (keyword_found) {
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
            case '{': case '}': printf(WHITE "%c" RESET, line[i]); break;
            case '[': case ']': printf(CYAN "%c" RESET, line[i]); break;
            case '(': case ')': printf(BLUE "%c" RESET, line[i]); break;
            case '#': printf(CYAN "%c" RESET, line[i]); break;
            default: printf("%c", line[i]); break;
        }
    }
    printf(RESET);
}

LanguageConfig* languages[] = {
    &c_lang
};

LanguageConfig* get_config(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot) {
        return NULL;
    }

    for (int i = 0; i < NUM_LANGUAGES; i++) {
        if (strcmp(dot, languages[i]->extention) == 0) {
            return languages[i];
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    char lines[500];
    int number = 0;
    int opt;
    bool show_syntax = true;
    bool show_numbers = false;

    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
            case 'n':
                show_numbers = true;
                break;
        }
    }

    FILE *file = fopen(argv[optind], "r");

    if (optind >= argc) {
        printf(BOLD RED "ERROR " RESET "expected argument after flag.\n");
        return 1;
    } else if (file == NULL) {
        printf(BOLD RED "%s " RESET "not found.\n", argv[1]);
        return 1;
    }

    const char *filename = argv[optind];

    LanguageConfig *current_lang = get_config(filename);

    if (current_lang == NULL) {
        show_syntax = false;
    }
    

    if (show_numbers) {
        printf(YELLOW "┌─────┬" RESET); 
        for (int i = 0; i < 100; i++) {
            printf(YELLOW "─" RESET);
        }
        printf("\n");
    }

    while (fgets(lines, 500, file) != NULL) {
        if (show_numbers) {
            number ++;
            printf(YELLOW "│" RESET BOLD BLUE "%4d" RESET YELLOW " │ " RESET, number);
        } 

        if (show_syntax && current_lang != NULL) {
            syntax_highlight(lines, current_lang);
        } else {
            printf("%s", lines);
        }
    }

    if (show_numbers) {
        printf(YELLOW "└─────┴" RESET);
        for (int i = 0; i < 100; i++) {
            printf(YELLOW "─" RESET);
        }
        printf("\n");
    }
    
    fclose(file);
    return 0;
}
