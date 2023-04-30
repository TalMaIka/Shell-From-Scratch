#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int printCheck(int num, int ver){
    if(num==0 && ver == 1){
        printf("success\n");
        return 0;
        exit(1);
    }
    if(num==0 && ver == 0){
        return 0;
        exit(1);
    }
    if(num==1 && ver == 0){
        return 1;
        exit(1);
    }
    if(num==1 && ver == 1){
        printf("general failure");
        return 1;
        exit(1);
    }
}

int main(int argc, char **argv){
    if(argc<3){
        printf("example: copy file1.txt file2.txt \ntwo flags options '-v' - verbose outputs & '-f' - force/overrwrite dest file.\n");
        exit(1);
    }
    //Flags check
    int verbose = 0;
    int force = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        }
        if (strcmp(argv[i], "-f") == 0) {
            force = 1;
        }
    }
    if(argc<3){
        printCheck(1,verbose);
    }
    // Check if file exists
    FILE* fp = fopen(argv[1],"r");
    FILE* fp1 = fopen(argv[2],"a+");
    if(force == 1){
        fp1 = fopen(argv[2],"w");
    }
    else{
        if(fp1!=NULL){
            printf("target file exist\n");
        }
    }
    //Passed Length Equality Test
    int c;
    while((c = fgetc(fp)) != EOF){
        fprintf(fp1, "%c", c);
    }
    fclose(fp);
    fclose(fp1);
    printCheck(0,verbose);
    return 0;
}