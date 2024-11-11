//
// Created by Matthew Gomez on 11/9/24.
//

#ifndef COMMANDS_H
#define COMMANDS_H

struct textLine {
    struct textLine *next;
    struct textLine *prev;
    char *text;
};

int insertLine(int index, char *text);
int deleteLine(int index);
int appendLine(char *text);
int changeLine(int index, char *text);
int printLine(int index);
int search(char *text);

#endif //COMMANDS_H
