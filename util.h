#ifndef _UTIL__H
#define _UTIL__H 1

#define CPU_RATE 100.0
#define DELAY_US(A) MCp_delay(((((float) A * 1000.0L) / (float)CPU_RATE) - 9.0L) / 5.0L)

void MCp_delay(long v);
void memset(char *buf, char fill, int len);
int strcmp(char *str1, char *str2);
int strncmp(char *str1, char *str2, int n);
char *itoa(long cvt, int base);
int abs(int value);

#endif
/* _UTIL__H */
