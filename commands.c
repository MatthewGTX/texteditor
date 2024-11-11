//
// Created by Matthew Gomez on 11/9/24.
//
#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern struct textLine *head;
extern struct textLine *tail;
int insertLine(int index, char *text){
    struct textLine* curLine = head;
    if (curLine == NULL) {
        printf("This file has no lines \n");
        return -1;
    }
    for (int i = 2; i <= index; i++){
        curLine = curLine->next;
        if (curLine == NULL) {
            printf("This file only has %d lines \n", i-1);
            return -1;
        }
    }
    int length = 0;
    while (*(text+length++))
        ;
    struct textLine* newLine = malloc(sizeof(struct textLine));
    newLine->text = text;
    newLine->prev = curLine->prev;
    newLine->next = curLine;
    newLine->prev->next = newLine;
    curLine->prev = newLine;
    return 0;
}
int deleteLine(int index){
    struct textLine* curLine = head;
    if (curLine == NULL) {
        printf("This file has no lines \n");
        return -1;
    }
    for (int i = 2; i <= index; i++){
        curLine = curLine->next;
        if (curLine == NULL) {
            printf("This file only has %d lines \n", i-1);
            return -1;
        }
    }
    if (curLine == head) head = curLine->next;
    if (curLine == tail) tail = curLine->prev;
    if (curLine->next) curLine->next->prev = curLine->prev;
    if (curLine->prev) curLine->prev->next = curLine->next;
    free (curLine->text);
    free (curLine);
    return 0;
}
int appendLine(char *text){
    if (tail == nullptr) {
        head = tail = malloc(sizeof(struct textLine));
        tail->text = text;
        return 0;
    }
    tail->next = malloc(sizeof(struct textLine));
    tail->next->prev = tail;
    tail = tail->next;
    tail->text = text;
    return 0;
}

int changeLine(int index, char *text) {
    struct textLine* curLine = head;
    if (curLine == NULL) {
        printf("This file has no lines \n");
        return -1;
    }
    for (int i = 2; i <= index; i++){
        curLine = curLine->next;
        if (curLine == NULL) {
            printf("This file only has %d lines \n", i-1);
            return -1;
        }
    }
    int length = 0;
    while (*(text+length++))
        ;
    free (curLine->text);
    curLine->text = text;
    return 0;
}
int printLine(int index){
    struct textLine* curLine = head;
    if (curLine == NULL) {
        printf("This file has no lines \n");
        return -1;
    }
    for (int i = 2; i <= index; i++){
        curLine = curLine->next;
        if (curLine == NULL) {
            printf("This file only has %d lines \n", i-1);
            return -1;
        }
    }
    printf("%s \n", curLine->text);
    return 0;
}
int search(char *text) {
    struct textLine* curLine = head;
    int i = 0, j = 0, lineNo = 1;
    while (curLine != nullptr) {
        i=0;
        j=0;
        while (*(curLine->text + i) != '\0') {
            if (*(curLine->text + i++) == *(text + j)) j++; else j = 0;
            if (*(text+j) == '\0') {
                printf("found text at line %d, position %d ", lineNo, i-j+1);
                return 1;
            }
        }
        curLine = curLine->next;
        lineNo++;
    }
    printf("search: text not found");
    return -1;
}