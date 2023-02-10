#include "string.h"

/*
return bool
    if str1 matches str2 true else false
-------------
char *str1, *str2
    the strings to be compared
*/
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
/*
return int
    length of string NOT including null ternination
------------
char *str
    string to be counted
*/
int str_len(char *str){
    char c = str[0];
    int i=0;
    while (c != '\0'){
        i++;
        c = str[i];
    }
    return i;
}

/*
return char *
    a pointer to the string
    must use str_free() to dereference
------------
char *str
    the string to copy over 
*/
char *str_copy(char *str){
    int len = str_len(str) + 1;
    char *re_str = (char *)malloc(len * sizeof(char));

    for (int i=0; i < len; i++){
        *(re_str + i) = *(str + i);
    }
    return re_str;
}

bool str_free(char *str){
    
}