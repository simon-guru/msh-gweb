#include "libft.h"

char*ft_strrchr(const char *s, int c)
{
char*result;

result = NULL;
while (*s)
{
if (*s == (char)c)
result = (char *)s;
s++;
}
if ((char)c == '\0')
return ((char *)s);
return (result);
}
