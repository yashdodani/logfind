/*
Logfind: command line utility to search "text" in log file

Steps:

FUNCTIONALITIES:

1. Build a functionality to search a single word in a text file.
        // loop over characters
        // match with first letter of word
        // if matched, loop over the word and characters to match further
        //      inside loop, if not match, break come outside, continue looping for next
        // if not matched, go further

2. let the program take file_name and text_to_search from command line

3. get file_names from "~/.logfind" in the program.

4. use these file_names and search for sequences in them.

5. make the program search individual words with "and" and "or" logic. (-o)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "dbg.h"

int search_word_in_file(char *file_name, char *word, int word_length) {
    char ch;
    FILE *fp = fopen(file_name, "r");
    check(fp != NULL, "Cannot open file");

    ch = fgetc(fp);
    while(ch != EOF) {
        int i = 0;
        int match_found = 0;
        if(ch == word[i]) {
            i++;
            while(i < word_length) {
                ch = fgetc(fp); 
                
                if(ch != word[i]) {
                    match_found = 1;
                    break;
                }
                i++;
            }
            
            if(match_found == 0) {
                printf("match found in %s\n", file_name);
                return 0;
            }
        }

        if(ch != word[0]) {
            // get next char
            ch = fgetc(fp);
        }
        // otherwise stay at the starting character
    }

    fclose(fp);
    return 0;

error:
    fclose(fp);
    return -1;
}

int get_line(FILE *fp, char **line_ptr) {
    // check if fp points to end of file.
    if(feof(fp)) {
        return -1;
    }
    char ch;
    int i = 0;

    int line_alloc = 8;
    char *line = malloc(line_alloc);
    check_mem(line);

    while((ch = fgetc(fp)) != EOF && ch != '\n') {
        // reallocate if needed
        if(i >= line_alloc) {
            line_alloc = line_alloc * 2;
            line = realloc(line, line_alloc);
            check_mem(line);
        }

        line[i] = ch;
        i++;
    }

    if(i > 0) {
        line[i] = '\0';
        *line_ptr = line;
        return i; // length excluding null terminator;
    }     

    // EOF reached without any characters appending
    // i == 0
    free(line);
    line_ptr = NULL;
    return 0;
    
error:
    free(line);
    return -1;
}

int main(int argc, char *argv[]) {
    // char *word = "hello";

    if(argc < 2) {
        printf("Usage: logfind TEXT_TO_SEARCH\n");
        return 1;
    }

    char *word = argv[1];
    int word_length = strlen(word);

    char *file_logfind = "/home/yash/.logfind";
    FILE *fp = fopen(file_logfind, "r");
    check(fp != NULL, "Cannot open file");

    char *line_ptr = NULL;
    int line_len = 0;

    while((line_len = get_line(fp, &line_ptr)) > 0) {
        // printf("%d: %s\n", line_len, line_ptr);

        // search a word with line_ptr
        search_word_in_file(line_ptr, word, word_length);
    }

    /*
    // glob
    glob_t pglob;
    char *pattern = "./";
    glob(pattern, GLOB_APPEND, NULL, &pglob);

    int i = 0;
    // while(pglob.gl_pathv[i]) {
    while(i < pglob.gl_pathc) {
        printf("%s\n", pglob.gl_pathv[i]);
        i++;
    }

    globfree(&pglob);
    */

    free(line_ptr);
    return 0;

error:
    free(line_ptr);
    return -1;
}
