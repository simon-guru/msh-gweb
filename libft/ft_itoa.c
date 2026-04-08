#include "libft.h"

static size_tnum_len(int n)
{
size_tlen;

len = 0;
if (n <= 0)
len = 1;
while (n != 0)
{
n /= 10;
len++;
}
return (len);
}

char*ft_itoa(int n)
{
char*str;
size_tlen;
longnum;

num = n;
len = num_len(n);
str = malloc(len + 1);
if (!str)
return (NULL);
if (num < 0)
{
str[0] = '-';
num = -num;
}
else if (num == 0)
str[0] = '0';
str[len] = '\0';
while (num > 0)
{
str[--len] = (num % 10) + '0';
num /= 10;
}
return (str);
}
