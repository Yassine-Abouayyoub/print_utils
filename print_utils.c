#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <windows.h>
#include <stdio.h>
#include <string.h>

void printCentered(const char* text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
    }
    int width = strlen(text);
    int pad = (columns - width) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; i++) {
        putchar(' ');
    }
    printf("%s\n", text);
}

void printc(const char* bigText, int fixed_width) {
    char buffer[512];
    const char* start = bigText;
    
    while (*start) {
        // Récupérer largeur console
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns = 80;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
        
        // Extraire ligne
        const char* end = strchr(start, '\n');
        if (!end) end = start + strlen(start);
        
        size_t line_len = end - start;
        strncpy(buffer, start, line_len);
        buffer[line_len] = '\0';
        
        // Centrer cette ligne
        int pad = (columns - fixed_width) / 2;
        if (pad < 0) pad = 0;
        for (int i = 0; i < pad; i++) putchar(' ');
        printf("%s\n", buffer);
        
        if (*end == '\n') start = end + 1;
        else break;
    }
}



void printr(const char *text, int line_length) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int width = 80;
    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    COORD cursor = csbi.dwCursorPosition;

    const char *start = text;
    while (*start) {
        const char *end = strchr(start, '\n');
        if (!end) end = start + strlen(start);

        char buffer[512];
        size_t len = end - start;
        if (len > sizeof(buffer) - 1) len = sizeof(buffer) - 1;

        strncpy(buffer, start, len);
        buffer[len] = '\0';

        int col = width - line_length;
        if (col < 0) col = 0;

        cursor.X = col;

        SetConsoleCursorPosition(hOut, cursor);
        printf("%s\n", buffer);
        cursor.Y += 1;

        start = (*end == '\n') ? end + 1 : end;
    }
}

#endif // PRINT_UTILS_C