#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system_call.h"

int modtime_compare(const struct dirent **a, const struct dirent **b)
{
    struct stat statbuf_a, statbuf_b;
 
    stat((*a)->d_name, &statbuf_a);
    stat((*b)->d_name, &statbuf_b);
 
    if (statbuf_a.st_mtime > statbuf_b.st_mtime) // a is newer
            return -1;
    else if (statbuf_a.st_mtime < statbuf_b.st_mtime) // b is newer
            return 1;
    else // time stamps match
            return 0;
}

void parse_mode(char *buf, mode_t mode)
{
        static const char perms[3] = { 'r', 'w', 'x' };
        mode_t mask;
        int i;
        
        mask = 1 << 8;
 
        for (i = 0; i < 9; ++i) {
                buf[i] = (mode & mask) ? perms[i % 3] : '-';
                mask >>= 1;
        }
 
        buf[9] = '\0';
}

void recursive_list(const char* dirname)
{
    DIR* dir = opendir(dirname);
    if (dir == NULL) 
    {
        return;
    }
    printf("\nReading files in: %s\n", dirname);

    struct dirent* entry;
    entry = readdir(dir);
    while (entry != NULL) 
    {
        if (entry->d_name[0] != '.' && strcmp(entry->d_name, "..") != 0)
        {
            printf("%s\n", entry->d_name);
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char path[100] = { 0 };
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entry->d_name);
                recursive_list(path);
                
            }
        }
        entry = readdir(dir);
    }
    printf("\nNo longer reading files in: %s\n", dirname);
    closedir(dir);
}