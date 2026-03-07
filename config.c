#include <string.h>
#include "syntax.h"

#define NUM_LANGUAGES (sizeof(languages) / sizeof(languages[0]))

// C
const char *c_types[] = { "int", "char", "float", "double", "bool", "long", "static", "const" };
const char *c_keywords[] = { "void", "return", "typedef" };
const char *c_statements[] = { "for", "while", "do", "switch", "case", "if", "else", "break", "continue" };
const char *c_headers[] = { "include", "define", "ifndef", "endif" };

// Python
const char *py_types[] = { "True", "False", "None", "int", "str", "float", "list", "dict" };
const char *py_keywords[] = { "def", "return", "lambda", "yield", "class", "global", "nonlocal", "and", "or", "not", "is", "in" };
const char *py_statements[] = { "if", "else", "elif", "for", "while", "break", "continue", "pass", "try", "except", "finally", "raise", "assert", "with", "async", "await" };
const char *py_headers[] = { "import", "from", "as" };

// Zig
const char *zig_types[] = { "bool", "void", "noreturn", "type", "anyopaque", "anyerror", "usize", "isize", "u8", "u16", "u32", "u64", "u128", "i8", "i16", "i32", "i64", "i128" };
const char *zig_keywords[] = { "fn", "pub", "const", "var", "struct", "enum", "union", "error", "test", "comptime", "inline", "extern", "export", "packed" };
const char *zig_statements[] = { "if", "else", "switch", "while", "for", "break", "continue", "return", "try", "catch", "resume", "suspend", "await", "defer", "errdefer", "orelse" 
};
const char *zig_headers[] = { "import", "usingnamespace" };



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

LanguageConfig zig_lang = {
    .extention = ".zig",
    .types = zig_types,
    .type_count = 18,
    .keywords = zig_keywords,
    .keyword_count = 14,
    .statements = zig_statements,
    .statement_count = 16,
    .headers = zig_headers,
    .header_count = 2,
    .single_line_comment = "//"
}; 

LanguageConfig* languages[] = { 
    &c_lang,
    &h_lang,
    &py_lang,
    &zig_lang
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
