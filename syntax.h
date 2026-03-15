#pragma once

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

// Language struct
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

// Function prototypes
void syntax_highlight(const char *line, LanguageConfig *lang);
LanguageConfig* get_config(const char *filename);
