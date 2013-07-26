#include <HDL51001_ccf.h>

#include "util.h"

void MCp_delay(long v)
{
   while (v--);
}

void memset(char *buf, char fill, int len)
{
    while (len-- > 0)
    {
       *buf = fill;
       buf++;
    }
}

int strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 < *str2)
            return -1;
        else if (*str1 > *str2)
            return 1;
        str1++;
        str2++;
    }
    if (*str1 || *str2)
       return 1;
    return 0;
}

int strncmp(char *str1, char *str2, int n)
{
    while (*str1 && *str2 && n-- != 0)
    {
        if (*str1 < *str2)
            return -1;
        else if (*str1 > *str2)
            return 1;
        str1++;
        str2++;
    }
    if (*str1 || *str2)
       return 1;
    return 0;
}

static char *_ltostr2(long cvt, int base, char conv, char *a_it)
{
   /*------------------------------------------------------------------------*/
   /* Local Variables                                                        */
   /*------------------------------------------------------------------------*/
   long  quot,
           rem;
       char  *bnum = "0123456789abcdef0123456789ABCDEF";

   /*------------------------------------------------------------------------*/
   /* The number CVT will be converted to a string by taking the remainder   */
   /* of a division of it by its base, and converting it to a character.     */
   /* The number CVT is then set equal to itself divided by its base, and    */
   /* this continues until CVT is 0.                                         */
   /*------------------------------------------------------------------------*/

   if(! cvt) *(a_it--) = '0';

   while(cvt)
   {
      quot = cvt / base;
      rem = cvt - (quot * base);

      if(conv == 'X') rem += 16;
      *(a_it--) = bnum[rem];
      cvt = quot;
   }

   return a_it + 1;
}

char *itoa(long cvt, int base)
{
	static char buf[20];
	char n;

	memset(buf, '0', 15);
	buf[15] = '\0';
	return _ltostr2(cvt, base, base == 10 ? 'd' : 'X', buf+14);
}

int abs(int value)
{
	return (value > 0 ? value : -value);
}
