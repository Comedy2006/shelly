/*
Commands:

exit - done
ls
shutdown - halfway through
print
cd
cls - done
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
cmd - done

custom commands: 
trust - WIP
mbr - WIP
*/

#pragma once

void exec_cmd(char** args){

    int check;

    if (strcmp(args[0], "clear") == 0 || strcmp(args[0], "cls") == 0){
        printf("\033[H\033[J");
        free(args);
    }
    else if(strcmp(args[0], "cmd") == 0){
        cmd_cmd(args);
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
    else if(strcmp(args[0], "mbr") == 0){
        printf("WIP");
        free(args);
    }
    else if (strcmp(args[0], "shutdown") == 0){
        check = shutdown_imm(args);
        free(args); 
    }
    else{
        printf("%s: Command not found. Type 'help' to see a list of available commands.\n", args[0]);
        free(args);
    }

    printf("\n");

    shell_cmd();
}