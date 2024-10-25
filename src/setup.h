#pragma once

#define MAX_INPUT_SIZE 1024
#define MAX_NUM_ARGS 100

// acquire username
char* get_user(){
    char* username = (char*)malloc(256*sizeof(char));
    DWORD username_len = sizeof(username);

    GetUserName(username, &username_len);

    return username;
}

// reading user input
char* read_input(){

    char* input = (char*)malloc(MAX_INPUT_SIZE);

    if (input == NULL) {
        perror("Unable to allocate memory for input");
        return NULL;
    }

    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        free(input);
        return NULL; // Error or EOF
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    return input;
}

// parsing the input
char** parse_input(char* input){

    char **args = malloc(MAX_NUM_ARGS * sizeof(char *));
    if (args == NULL) {
        perror("Unable to allocate memory for arguments");
        return NULL;
    }

    char *arg;
    int i = 0;

    arg = strtok(input, " "); // Tokenize the input
    while (arg != NULL && i < MAX_NUM_ARGS - 1) {
        args[i++] = arg;
        arg = strtok(NULL, " ");
    }
    args[i] = NULL;

    free(arg);

    return args;
}

void shell_cmd(){
    
    char** usrinput;
    char* cwd = getcwd(NULL, 0);

    if(cwd == NULL){
        perror("getcwd err");
        return;
    }

    char* usr = get_user();

    printf("{User: %s} - [%s]\n", usr, cwd);
    printf("Shell>");

    usrinput = parse_input(read_input());

    exec_cmd(usrinput);
}