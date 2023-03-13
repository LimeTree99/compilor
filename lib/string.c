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

    if (same && c1 != c2){ //this checks for same length
        same = false;
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

char *str_cat(char *str1, char *str2){
    int len1 = str_len(str1);
    int len2 = str_len(str2);
    char *re_str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
    for (int i=0; i<len1; i++){
        *(re_str + i) = *(str1 + i);
    }
    for (int i=0; i<(len2+1); i++){
        *(re_str + i + len1) = *(str2 + i);
    }
    return re_str;
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
    int i=0;
    int offset = 0;
    char *re_str = (char *)malloc(len * sizeof(char));


    while (start + i != end + 1){
        if (*(start + i) == '\0'){
            offset++;
        }else{
            *(re_str + i) = *(start + i + offset);
            i++;
        }
        
    }

    *(re_str + len - 1) = '\0';

    return re_str;
}

