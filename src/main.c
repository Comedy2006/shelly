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

    char* cwd = getcwd(NULL, 0);
    if(cwd == NULL){
        perror("getcwd err");
        return ERROR_INVALID_FUNCTION;
    }

    char* usr = get_user();

    printf("{User: %s} - [%s]\n", usr, cwd);
    printf("Shell>");

    // userinput... need to do that but I am too lazy rn    

    free(usr);
    free(cwd);
    return ERROR_SUCCESS;
}