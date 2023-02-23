#include "string.h"


bool str_cmp(char *str1, char *str2){
    int i = 0;
    char c1 = str1[0];
    char c2 = str2[0];
    bool same = true;

    while(same && c1 != '\0' && c2 != '\0'){
        if (c1 != c2){
            same = false;
        }
        i++;
        c1 = str1[i];
        c2 = str2[i];
    }
    return same;
}

int str_len(char *str){
    char c = str[0];
    int i=0;
    while (c != '\0'){
        i++;
        c = str[i];
    }
    return i;
}

char *str_copy(char *str){
    int len = str_len(str) + 1;
    char *re_str = (char *)malloc(len * sizeof(char));

    for (int i=0; i < len; i++){
        *(re_str + i) = *(str + i);
    }
    return re_str;
}


char *str_cp_sec(char *start, char *end){
    int len = (int)end - (int)start + 1;
    char *re_str = (char *)malloc(len * sizeof(char));

    for (int i=0; i < len-1; i++){
        *(re_str + i) = *(start + i);
    }

    *(re_str + len - 1) = '\0';

    return re_str;
}

bool str_free(char *str){
    free(str);  //this is probably incorrect
    return true;
}