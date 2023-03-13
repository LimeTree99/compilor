/*! \file string.h
 \brief Functions for use in manipulating strings.
 This is a replacement for the standard library functions.

 This library operates where each function allocates the exact memory size for the string, 
 if there is a char* returned. This means that delocating is very important to keep in mind. 
*/

#include <stdlib.h>
#include "build.h"


//! find if two strings are the same
/*!
    \param str1
    \param str2
    \return true if same, false if not
*/
bool str_cmp(char *str1, char *str2);


//! Get length of string NOT including null ternination
/*!
    \param str string to be counted
    \return Length of string NOT including null ternination
*/
int str_len(char *str);


//! Generate copy of string, use str_free() to derefrence
/*!
    \param str the string to copy over 
    \return Pointer to the copied string
*/
char *str_copy(char *str);

char *str_cat(char *str1, char *str2);


//! Create a copy of a string bounded between two pointers, use str_free() to derefrence
/*!
    \param start pointer to first character in string
    \param end pointer to last character in string
    \returns pointer to new string
*/
char *str_cp_sec(char *start, char *end);