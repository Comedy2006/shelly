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

*/

void exec_cmd(char** args){

    if (strcmp(args[0], "exit") == 0){
        free(args);
        exit(0);
    }
    else{
        printf("%s: Command not found. Type 'help' to see a list of available commands.");
        free(args);
        exit(0);
    }

    shell_cmd();
}