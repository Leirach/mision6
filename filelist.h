#ifndef FILELIST_H_   /* Include guard */
#define FILELIST_H_

#include <dirent.h>

//retorna count de # de archivos
int listDirectory(struct dirent filelist[], const char* path) 
{
	int count = 0;
	DIR *dr = opendir(path); // opendir() returns a pointer of DIR type.  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 

    struct dirent *de;  // Pointer for directory entry
    //los primeros dos siempre son "." y "..", se descartan
    de = readdir(dr);
    de = readdir(dr);
    
    while ( readdir(dr) != NULL)
    {
    	filelist[count] = *(de);
		count++;
    }

    return count;
}

//imprime lista de archivos
void printList(const struct dirent filelist[], const int count) 
{
	for (int i=0; i<count; i++)
	{
		printf("%s\n", filelist[i].d_name);
	}
}

#endif // FOO_H_