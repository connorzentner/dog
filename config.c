#include <string.h>
#include "syntax.h"

#define NUM_LANGUAGES (sizeof(languages) / sizeof(languages[0]))

const char *c_types[] = { "int", "char", "float", "double", "bool", "long", "static", "const" };
const char *c_keywords[] = { "void", "return", "typedef" };
const char *c_statements[] = { "for", "while", "do", "switch", "case", "if", "else", "break", "continue" };
const char *c_headers[] = { "include", "define", "ifndef", "endif" };

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

LanguageConfig* languages[] = { 
    &c_lang,
    &h_lang
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
