#include "util.h"
#include "hashfn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*getPrefix(char*filename);
unsigned long getflen(FILE*fp);

char*getPrefix(char*filename){
    char*s=calloc(strlen(filename)*2,1);
    for (int i=0; i<strlen(filename); i++){
        if (filename[i]!='.'){
            s[i]=filename[i];
        }
        else{
            return s;
        }
    }
}

unsigned long getflen(FILE*fp){
    rewind(fp);
    fseek(fp, 0L, SEEK_END);
    unsigned long length=ftell(fp);
    rewind(fp);
    return length;
}



int main(int argc, char*argv[]){
    if (argc!=3){
        fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
    }
    else{
        FILE*fp=fopen(argv[1], "rb");
        char*khsfile=getPrefix(argv[1]);
        strcat(khsfile, ".khs");
        char*vhsfile=getPrefix(argv[1]);
        strcat(vhsfile, ".vhs");
        char*key=calloc(STRLEN,1);
        char*val=calloc(STRLEN,1);
        char*keyval=calloc(STRLEN*2,1);
        int keysize=read_key(fp, 0, key);
        int valsize=read_val(fp, 257, val);
        int keyvalsize=read_keyval(fp, key, val);
        fclose(fp);
        FILE*khsFile=fopen(khsfile, "wb");
        FILE*vhsFile=fopen(vhsfile, "wb");
        write_empty(khsFile, atol(argv[2]));
        write_empty(vhsFile, atol(argv[2]));
        int keyindex=hashfn(key, getflen(khsFile));
        int valindex=hashfn(val, getflen(vhsFile));
        int k=0;
        int v=0;
        read_index(khsFile, keyindex, &k);
        printf("%d\n", k);
        while (read_index(khsFile, keyindex, &k)==-1){
            printf("looping\n");
            keyindex=hashfn(key, getflen(khsFile));
            write_index(khsFile, keyindex, keyindex);
            write_index(vhsFile, valindex, valindex);
        }
        fclose(khsFile);
        fclose(vhsFile);
        khsFile=fopen(khsfile, "rb");
        vhsFile=fopen(vhsfile, "rb");
        fseek(khsFile, keyindex*sizeof(int), 0);
        fseek(vhsFile, valindex*sizeof(int), 0);
        fread(&k, sizeof(int), 1, khsFile);
        fread(&v, sizeof(int), 1, vhsFile);
        fclose(khsFile);
        fclose(vhsFile);
        free(khsfile);
        free(vhsfile);
        free(key);
        free(val);
        free(keyval);
    }
    return 0;
}