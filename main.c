#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>

int main(){

    char *path = "C:/Users/juanc/Desktop/test";
    HANDLE dirChanges;
    HANDLE fileName;
    DWORD dwStatus;
    int cycle = 1;

    struct dirent *de;  // Pointer for directory entry
    dirChanges = FindFirstChangeNotificationA(path, 0, FILE_NOTIFY_CHANGE_FILE_NAME);
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
        
        DIR *dr = opendir(path); // opendir() returns a pointer of DIR type.  
        if (dr == NULL)  // opendir returns NULL if couldn't open directory 
        { 
            printf("Could not open current directory" ); 
            return 0; 
        } 
        // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
        // for readdir() 
        while ((de = readdir(dr)) != NULL){
            printf("%s\n", de->d_name);
        }

    }

    return 0;
}
