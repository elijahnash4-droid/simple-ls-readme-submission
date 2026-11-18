#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
 
 
// int (*compar)(const struct dirent **, const struct dirent **)
// custom comparator to allow scandir() to sort by modified time descending
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
 
int main(void)
{
        struct dirent **entries = NULL;
        struct dirent **cursor = NULL;
 
        // scandir() collects all entries at once (with optional filtering/sorting)
        if (scandir(".", &entries, NULL, modtime_compare) == -1) {
                perror("scandir");
                exit(EXIT_FAILURE);
        }
 
        cursor = entries;
 
        while (*cursor) {
                printf("%s\n", (*cursor)->d_name);
                ++cursor;
        }
 
        free(entries);
        return 0;
}