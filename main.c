#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(){

    char *dir = "C:/Users/Usuario1/Desktop/test";
    HANDLE dirChanges;
    HANDLE fileName;
    DWORD dwStatus;
    int cycle = 1;

    dirChanges = FindFirstChangeNotificationA(dir, 0, FILE_NOTIFY_CHANGE_FILE_NAME);
    //fileName = getfileti;

    if(dirChanges == INVALID_HANDLE_VALUE){
        printf("ERROR con crear el handle\n");
        ExitProcess(GetLastError());
    }

    while(cycle){

        printf("Waiting for changes...\n");

        dwStatus = WaitForSingleObject(dirChanges, INFINITE);

        switch(dwStatus){

        case WAIT_OBJECT_0:
            printf("Change detected\n");
            FindNextChangeNotification(dirChanges);
            break;

        default:
            printf("ERROR\n");
            break;
        }

    }

    return 0;
}
