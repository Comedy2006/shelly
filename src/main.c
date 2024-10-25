/*

This is just a simple hobby project. Not too big, not too small

Things I'd like to add in the future

Custom scripting language for the terminal
Administrative tools
Besides the windows commands, I also want to make some custom commands

I also want to add some side projects into this one (e.g. mbrData)

*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <direct.h>
#include "commands.h"

char* get_user(){
    char* username = (char*)malloc(256*sizeof(char));
    DWORD username_len = sizeof(username);

    GetUserName(username, &username_len);

    return username;
}

int main(int argc, char** argv){

    scanf("%255s");

    free(usr);
    free(cwd);

    return ERROR_SUCCESS;
}