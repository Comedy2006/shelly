void exec_cmd(char** args){

    if (strcmp(args[0], "exit") == 0){
        free(args);
        exit(0);
    }
}