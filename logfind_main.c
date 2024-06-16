/*
Logfind: command line utility to search "text" in log file

Steps:
1. Build a functionality to search a word sequence in a text file.
        // loop over characters
        // match with first letter of word
        // if matched, loop over the word and characters to match further
        //      inside loop, if not match, break come outside, continue looping for next
        // if not matched, go further
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

int search_word_in_file(char *file_name, char *word, int word_length) {
    char ch;
    FILE *fp = fopen(file_name, "r");
    check(fp != NULL, "Cannot open file");

    ch = fgetc(fp);
    while(ch != EOF) {
        printf("%c", ch);

        int i = 0;
        int match_found = 0;
        if(ch == word[i]) {
            i++;
            while(i < word_length) {
                ch = fgetc(fp); 
                // printf("char matching: %c\n", ch);
                if(ch != word[i]) {
                    match_found = 1;
                    break;
                }
                i++;
            }
            
            if(match_found == 0) {
                printf("\nmatch found\n");
                break;
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

int main(int argc, char *argv[]) {
    char *word = "hello world";
    char *file_name = "temp.txt";

    // finding word length
    int word_length = strlen(word); // strlen does not take null character in length
    printf("%s\n", word);
    printf("word length = %d\n", word_length);

    int word_found = search_word_in_file(file_name, word, word_length);
    if(word_found == 0) {
        printf("word found\n");
    }
}

/*
sizeof(*word) // returns 1 as *word points to first character
*/