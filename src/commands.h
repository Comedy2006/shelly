#pragma once

int shtdwn;
// variable contains shutdown code for the program

void help_cmd(){
    printf("List of Commands:\n"
    "help\n"
    "exit\n"
    "clear/cls\n");
    return;
}

int shutdown_imm(char** args){

    // acquire priviledges for shutdown
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        perror("Failed to open process token.\n");
        return EXIT_FAILURE;
    }

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS) {
        perror("Failed to adjust token privileges.\n");
        return EXIT_FAILURE;
    }

    if (sizeof(args) == 1){ // shutdown
        if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER)) {
            perror("Failed to shut down the system. Shutdown Aborted...\n");
            return EXIT_FAILURE;
        }
        shtdwn = 0;
    }else{
        if(strcmp(args[1], "-r") == 0){ //reboot
            if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER)) {
                perror("Failed to shut down the system. Reboot Aborted...\n");
                return EXIT_FAILURE;
            }
            shtdwn = 1;
        }else if(strcmp(args[1], "-r") == 0){//shutdown 
            if(!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER)){
                    perror("Failed to shut down the system. Shutdown Aborted...\n");
                    return EXIT_FAILURE;
            }
            shtdwn = 0;
        }else if(strcmp(args[1], "-l") == 0){ //log off
            if(!ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER)){
                    perror("Failed to log off. Log off Aborted...\n");
                    return EXIT_FAILURE;
            }
            shtdwn = 2;
        }

        // missing features: scheduled shutdown
    }

    free(args);
    return ERROR_SUCCESS;
}

int cmd_cmd(char** args){

    if(sizeof(args) == 1){
        perror("Command should have at least 1 more argument to work.");
        return EXIT_FAILURE;
    }

    // put string together
    // execute using system()
    char* str;
    int strlen = 0;

    for(int i = 0; i <= sizeof(args) - 1; i++){
        strlen += sizeof(args[i]); 
    }

    strlen++; // for null terminator
    strlen += ((sizeof(args)/sizeof(args[0])) - 1);

    str = (char*)malloc(strlen*sizeof(char));
    if (str == NULL){
        perror("Memory could not be allocated (str)");
        return EXIT_FAILURE;
    }

    str[0] = '\0';

    //putting str together
    for(int i = 1; i <= ((sizeof(args)/sizeof(args[0])) + 1) - 1; i++){
        strcat(str, args[i]);
        if (i < (sizeof(args)/sizeof(args[0]))){
            strcat(str, " ");
        }
    }

    str[sizeof(str) - 1] = '\0';
    printf("%s\n", str);

    //system(str);
    free(str); // imma do this tomorrow

    return ERROR_SUCCESS;
}