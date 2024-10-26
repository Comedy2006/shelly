/*

This is just a simple hobby project. Not too big, not too small

Things I'd like to add in the future

Custom scripting language for the terminal
Administrative tools
Besides the windows commands, I also want to make some custom commands

I also want to add some side projects into this one

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <direct.h>
#include "setup.h"
#include "commands.h"
#include "cmd.h"

int main(int argc, char** argv){

    printf("\033[H\033[J");

    shell_cmd();

    return ERROR_SUCCESS;
}