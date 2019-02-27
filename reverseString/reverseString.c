/*
* Reverse a string. For example,
*   Input: "I have a pen."
*   Output: ".nep a evah I"
*
* Author: Lijun SUN
* Date: Feb 27, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readString(char *userinput)
{
    printf("Type a sentence: ");
    scanf("%[^\n]", userinput);
    return 1;
}

int reverseIt(char *buf, char **reversed)
{
    int stringlen = strlen(buf), stringidx;
    *reversed = (char *)malloc(stringlen + 1);
    for(stringidx = 0; stringidx < stringlen; stringidx++){
        (*reversed)[stringidx] = buf[stringlen - 1 - stringidx];
    }
    (*reversed)[stringlen] = '\0';

    return 1;
}

int main(int argc, char *arg[])
{
    char userinput[100];
    char *reversed;

    readString(userinput);
    reverseIt(userinput, &reversed);
    printf("The reversed sentence is: %s\n", reversed);

    return 0;
}