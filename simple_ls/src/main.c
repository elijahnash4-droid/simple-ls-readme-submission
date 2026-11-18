#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "system_call.h"


int main()
{
    char command[4];
    char default_list[] = "ls";
    char hidden_list[] = "ls_-a";
    char long_list[] = "ls_-l";
    char recursive_ls[] = "ls_-R";
    

    printf("Enter 'ls' to list all files in current directory (-a: includes hidden files, -R: recursive listing, -l: long list (use '_' for space))\n");
    scanf("%s", command);

    if (strcmp(command, default_list) == 0){
        DIR* dir = opendir(".");
        if (dir == NULL) {
            return 1;
        }

        struct dirent* entry;
        entry = readdir(dir);
        while (entry != NULL) {
            if (entry->d_name[0] != '.' && strcmp(entry->d_name, "..") != 0)
            {
                printf("%s\n", entry->d_name);
            }
            entry = readdir(dir);
        }
        closedir(dir);
    }

    else if(strcmp(command, hidden_list) == 11)
    {
        DIR* dir = opendir(".");
        if (dir == NULL) {
            return 1;
        }

        struct dirent* entry;
        entry = readdir(dir);
        while (entry != NULL) {
            if (strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0){
                printf("%s\n", entry->d_name);
            }
            entry = readdir(dir);
        }
        closedir(dir);
    }

    else if (strcmp(command, long_list) == 0)
    {
        char mode_buf[10] = { '\0' };
        struct stat file_info;
        struct dirent **entries = NULL;
        struct dirent **cursor = NULL;
    
        if (scandir(".", &entries, NULL, modtime_compare) == -1) {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
    
        cursor = entries;
        printf("\nrunning list command: \n");
                    
        while (*cursor) {
            if ((*cursor)->d_name[0] != '.' && strcmp((*cursor)->d_name, "..") != 0){
                stat((*cursor)->d_name, &file_info);
                parse_mode(mode_buf, file_info.st_mode);
                printf("filename: %s permissions: %s date: %s size: %d bytes\n", (*cursor)->d_name, mode_buf, ctime(&file_info.st_mtime), (int)file_info.st_size);
            }
            ++cursor;
        }
        
        free(entries);
    }

    else if(strcmp(command, recursive_ls) == 0)
    {
        recursive_list(".");
    }

    else{
        printf("Invalid command.");
    }
    return 0;
}