/* shchgrp
 *
 * SHitty
 * CHained
 * GReP
 * 
 * Filter text with multiple regexes. It's an over-engineered way to chain a few
 * regexes together. 
 * 
 * Written by Seungin Lyu, Adam Novotny, Matthew Beaudouin-Lafon
 */

#include "shvec.h"
#include "regexlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>

int arg_parse(int argc, char* argv[]){
    // parse arguments
    char ch;
    while((ch = getopt(argc, argv, "")) != EOF){
        switch (ch){
            default:
                fprintf(stderr, "Error: Unknow Flag");
                return 1;
        }
    }
    return 0;
}
int main(int argc, char *argv[]){
    int num_regexes = 0;
    Regex ** regexes;
    int * matches;

    if(arg_parse(argc, argv)){
        return 1;
    } else {
        num_regexes = argc - optind;
        
        if(num_regexes == 0){
            fprintf(stderr, "Error: At least one regex required\n");
            return 1;
        }
        
        regexes = (Regex **) malloc(sizeof(Regex*) * num_regexes);
        matches = malloc(sizeof(int) * num_regexes);

        for(int index = 0; index < num_regexes; index++){
            regexes[index] = make_regex(argv[index + optind], REG_EXTENDED | REG_NOSUB);
            matches[index] = shvec_create();
        }
    }

    printf("Regexes:\n");
    for(int i = 0; i < num_regexes; i++){
        int match = regexec(regexes[i], "hello world", 0, NULL, 0);
        if(match == 0) {
            printf("regex number %d matches hello world\n", i);
        }
    }

    char in_buf[100];
    while(fgets(in_buf, 100, stdin) != NULL) {
        for(int i = 0; i < num_regexes; i++){
            int match = regexec(regexes[i], in_buf, 0, NULL, 0);
            if(match == 0) {
                printf("regex number %d matches %s\n", i, in_buf);
            }
        }   
    }
    
    // Run these against the stdin
    return 0;
}
