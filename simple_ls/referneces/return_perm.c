#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
 
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
 
int main(void)
{
        char mode_buf[10] = { '\0' };
        struct stat statbuf;
 
        stat("file.txt", &statbuf);
        parse_mode(mode_buf, statbuf.st_mode);
        printf("-%s\n", mode_buf);
        return 0;
}