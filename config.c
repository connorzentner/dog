#include <string.h>
#include "syntax.h"

#define NUM_LANGUAGES (sizeof(languages) / sizeof(languages[0]))

const char *c_types[] = { "int", "char", "float", "double", "bool", "long", "static", "const" };
const char *c_keywords[] = { "void", "return", "typedef" };
const char *c_statements[] = { "for", "while", "do", "switch", "case", "if", "else", "break", "continue" };
const char *c_headers[] = { "include", "define", "ifndef", "endif" };

const char *py_types[] = { "True", "False", "None", "int", "str", "float", "list", "dict" };
const char *py_keywords[] = { "def", "return", "lambda", "yield", "class", "global", "nonlocal", "and", "or", "not", "is", "in" };
const char *py_statements[] = { "if", "else", "elif", "for", "while", "break", "continue", "pass", "try", "except", "finally", "raise", "assert", "with", "async", "await" };
const char *py_headers[] = { "import", "from", "as" };


LanguageConfig c_lang = {
    .extention = ".c",
    .types = c_types,
    .type_count = 8,
    .keywords = c_keywords,
    .keyword_count = 3,
    .statements = c_statements,
    .statement_count = 9,
    .headers = c_headers,
    .header_count = 4,
    .single_line_comment = "//"
};

LanguageConfig h_lang = {
    .extention = ".h",
    .types = c_types,
    .type_count = 8,
    .keywords = c_keywords,
    .keyword_count = 3,
    .statements = c_statements,
    .statement_count = 9,
    .headers = c_headers,
    .header_count = 4,
    .single_line_comment = "//"
};

LanguageConfig py_lang = {
    .extention = ".py",
    .types = py_types,
    .type_count = 8,
    .keywords = py_keywords,
    .keyword_count = 12,
    .statements = py_statements,
    .statement_count = 16,
    .headers = py_headers,
    .header_count = 3,
    .single_line_comment = "#"
};

LanguageConfig* languages[] = { 
    &c_lang,
    &h_lang,
    &py_lang
};

LanguageConfig* get_config(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot) return NULL;

    for (size_t i = 0; i < NUM_LANGUAGES; i++) {
        if (strcmp(dot, languages[i]->extention) == 0) {
            return languages[i];
        }
    }
    return NULL;
}
