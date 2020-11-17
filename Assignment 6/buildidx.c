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
        read_key(fp, 0, key);
        read_val(fp, 257, val);
        read_keyval(fp, 514, keyval);
        fclose(fp);
        FILE*khsFile=fopen(khsfile, "wb");
        FILE*vhsFile=fopen(vhsfile, "wb");
        write_empty(khsFile, atol(argv[2]));
        write_empty(vhsFile, atol(argv[2]));
        int keyindex=hashfn(key, getflen(khsFile));
        int valindex=hashfn(key, getflen(vhsFile));
        write_index(khsFile, keyindex, keyindex);
        write_index(vhsFile, valindex, valindex);
    }
    return 0;
}