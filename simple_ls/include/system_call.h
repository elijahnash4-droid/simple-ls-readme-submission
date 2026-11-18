#ifndef SYSTEM_CALL_H
#define SYSTEM_CALL_H

int modtime_compare(const struct dirent **a, const struct dirent **b);
void parse_mode(char *buf, mode_t mode);
void recursive_list(const char* dirname);

#endif