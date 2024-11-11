#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"


struct textLine *head = nullptr;
struct textLine *tail = nullptr;

char *readLine(FILE *in) {      /*returns a pointer to the text of the line
                                stored in a new allocated memory location,
                                can cause memory leaks if output is lost */
    int size = 100;
    char *line = malloc(size);
    if (line == NULL) return nullptr;
    int length = 0;
    char c = (char) fgetc(in);
    if (c == EOF) return nullptr;
    while (c != EOF && c != '\n') {
        line[length++] = c;
        if (length >= (size-1)) {
            size *= 2;
            char *newline = realloc(line, size);
            if (newline == nullptr) return line;
            line = newline;
        }
        c = (char) fgetc(in);
    }
    line[length] = '\0';
    return line;
}

int main(void)
{
    char *newText;
    struct textLine *curLine = nullptr;
    printf("Enter file name \n");
    char *fileName = readLine(stdin);
    FILE *save = fopen(fileName, "r");
    if (save == NULL){
        printf("New file\n");
    } else {
        printf("Editing existing file\n");
        while ((newText = readLine(save)) != NULL) {
            struct textLine *new = malloc(sizeof(struct textLine));
            new->text = newText;
            if (curLine) curLine->next = new; else head = new;
            new->prev = curLine;
            curLine = new;
        }
        tail = curLine;
    }
    fclose(save);
    char input[100];
    fgets(input, 100, stdin);
    while(*input != 'q') {
        int i = 0;
        int index = 0;
        switch (*input) {
            case 'i':
                printf("insert mode: enter line number \n");
                fgets(input, 100, stdin);
                while (*(input+i) <= '9' && *(input+i) >= '0') {
                    index *= (index * 10);
                    index += *(input+i) - 48;
                    i++;
                }
                printf("enter new text \n");
                insertLine(index, readLine(stdin));
                break;
            case 'd':
                printf("delete mode: enter line number \n");
                fgets(input, 100, stdin);
                while (*(input+i) <= '9' && *(input+i) >= '0') {
                    index *= (index * 10);
                    index += *(input+i) - 48;
                    i++;
                }
                deleteLine(index);
                printf("deleted line %d \n", index);
                break;
            case 'a':
                printf("append mode: enter new text \n");
                appendLine(readLine(stdin));
                break;
            case 'c':
                printf("change mode: enter line number \n");
                fgets(input, 100, stdin);
                while (*(input+i) <= '9' && *(input+i) >= '0') {
                    index *= (index * 10);
                    index += *(input+i) - 48;
                    i++;
                }
                printf("Enter new text for line %d \n", index);
                changeLine(index, readLine(stdin));
                break;
            case 'p':
                printf("Print mode \n");
                fgets(input, 100, stdin);
                while (*(input+i) <= '9' && *(input+i) >= '0') {
                    index *= (index * 10);
                    index += *(input+i) - 48;
                    i++;
                }
                printLine(index);
                break;
            case 's': {
                char  *text;
                search(text = readLine(stdin));
                free(text);
            }
            case 'w':
                save = fopen(fileName, "w");
                curLine = head;
                while (curLine != nullptr) {
                    fputs(curLine->text, save);
                    if (!curLine->next) break;
                    fputc('\n', save);
                    curLine = curLine->next;
                }
                fflush(save);
                break;
            default:
                printf("How to use program: \n");
                printf("The following is a list of commands\n");
                printf("To enter a command mode you type the letter and then enter \n");
                printf("Then you must enter the arguments while pressing enter after each one \n");
                printf("Quit: q \n");
                printf("Append: a (text)\n ");
                printf("Print: p (line number)\n");
                printf("Change: c (line number) (text) \n ");
                printf("Delete: d (line number) \n ");
                printf("Insert: i (line number) (text) \n ");

        }
        fgets(input, 100, stdin);
    }
    return 0;
}
