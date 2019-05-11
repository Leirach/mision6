#define _WIN32_WINNT  0x501 //para compilar con -lws2_32
#define WIN32_LEAN_AND_MEAN //excluir varias funciones de windows.h

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dirent.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "filelist.h"
//incluye 
//int listDirectory(struct dirent filelist[], const char* path) 
//	regresa nuero de archivos en el directorio y sus nombres en filelist
//void printList(const struct dirent filelist[], const int count) 
//	imprime nombres de la lista

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

//variables globales
struct dirent filelist[20];
int count;
char *path = "C:/Users/juanc/Desktop/test"; //CAMBIAR PATH PARA CADA COMPUTADORA

void AddOrDel ()
{
	printf("\tagregado/borrado\n");
	count = listDirectory(filelist, path);
	printList(filelist, count);
}

void Modified ()
{
	printf("\tmodificado\n");
	count = listDirectory(filelist, path);
	printList(filelist, count);
}

int main()
{
    HANDLE dirChanges[2];
    HANDLE fileName;
    DWORD dwStatus;

    //primer handle para archivos creados, borrados, etc
    //segundo handle para archivos modificados
    //https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-findfirstchangenotificationa
    dirChanges[0] = FindFirstChangeNotificationA(path, 0, FILE_NOTIFY_CHANGE_FILE_NAME);
    dirChanges[1] = FindFirstChangeNotificationA(path, 0, FILE_NOTIFY_CHANGE_LAST_WRITE);

    while(TRUE){
        dwStatus = WaitForMultipleObjects(2, dirChanges, FALSE, INFINITE);

        switch (dwStatus)
        {
        	//trigger de dirChanges[0]
        	case WAIT_OBJECT_0 :
        		AddOrDel();
        		FindNextChangeNotification(dirChanges[0]);
        		break;
        	//trigger de dirChanges[1]
        	case WAIT_OBJECT_0 + 1:
        		Modified();
        		FindNextChangeNotification(dirChanges[1]);
        		break;
        	default:
        		printf("\tERROR\n");
        }	

    }

    return 0;
}
