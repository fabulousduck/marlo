#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int is_regular_file(const char * path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

char* change_extension(char* const filePath, char* const newEstension ) {
    char* dest;
 
    // We have some exstension?
    char* temp = strrchr(filePath, '.');
    if (temp) {
        dest = malloc(strlen(filePath) + strlen(newEstension) - strlen(temp));
        strncpy(dest, filePath, temp - filePath);
    } else {
        dest = malloc(strlen(filePath) + strlen(newEstension));
        strncpy(dest, filePath, strlen(filePath));
    }

    // Append the new exstension in the file path
    strcat(dest, newEstension);
    return dest;
}
