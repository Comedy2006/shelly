#pragma once

int shtdwn;
// variable contains shutdown code for the program

void help_cmd(){
    printf("List of Commands:\n"
    "help\n"
    "exit\n"
    "clear/cls\n");
}

int shutdown_imm(char** args){

    // acquire priviledges for shutdown
    HANDLE hTocken;
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

    return ERROR_SUCCESS;
}