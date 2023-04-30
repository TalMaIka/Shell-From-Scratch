#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int LenCheck(FILE *fp,FILE *fp1){
    fseek(fp,0,SEEK_END);
    fseek(fp1,0,SEEK_END);
    if(ftell(fp)!= ftell(fp1)){
        fseek(fp,0,SEEK_SET);
        fseek(fp1,0,SEEK_SET);
        return 0;
    }
    fseek(fp,0,SEEK_SET);
    fseek(fp1,0,SEEK_SET);
    return 1;
}

int printCheck(int a, int ver){
    if(a==1 && ver == 1){
        printf("distinct”\n");
        return 1;
        exit(1);
    }
    else if(a==1 && ver == 0){
        return 1;
        exit(1);
    }
    else if(a==0 && ver == 1){
        printf("equal\n");
        return 0;
        exit(1);
    }
    else if(a==0 && ver == 0){
        return 0;
        exit(1);
    }
}

int main(int argc, char **argv){
    //Flags check
    int verbose = 0;
    int notCS = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        }
        if (strcmp(argv[i], "-i") == 0) {
            notCS = 1;
        }
    }
    ////////////////
    FILE* fp = fopen(argv[1],"r");
    FILE* fp1 = fopen(argv[2],"r");
    //File Length Check.
    if(LenCheck(fp,fp1)!= 1){
        //Files are not equal.
        printCheck(1,verbose);
        exit(1);
    }
    //Passed Length Equality Test
    while(!feof(fp)){
        if(notCS == 1 && tolower(getc(fp)) != tolower(getc(fp1))){
                printCheck(1,verbose);
                exit(1);
        }
        else if(notCS == 0 && getc(fp) != getc(fp1)){
            printCheck(1,verbose);
            exit(1);
        }
    }
    fclose(fp);
    fclose(fp1);
    printCheck(0,verbose);
    return 0;
}