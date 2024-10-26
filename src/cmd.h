/*
Commands:

exit
ls
shutdown
print
cd
cls
del
tree
registry
taskmgr
cp
ren
xcp
find
attr
mkdir
rmdir
ping

custom commands: 
trust
mbr
*/

#pragma once

void exec_cmd(char** args){

    int check;

    if (strcmp(args[0], "clear") == 0 || strcmp(args[0], "cls") == 0){
        printf("\033[H\033[J");
        free(args);
    }
    else if (strcmp(args[0], "exit") == 0){
        printf("Exiting...\n");
        free(args);
        exit(0);
    }
    else if (strcmp(args[0], "help") == 0){
        help_cmd();
        free(args);
    }
    else if (strcmp(args[0], "shutdown") == 0){
        check = shutdown_imm(args); // normally, the system would shut down. We'll still do the error handling
        free(args); 
    }
    else{
        printf("%s: Command not found. Type 'help' to see a list of available commands.\n", args[0]);
        free(args);
    }

    shell_cmd();
}