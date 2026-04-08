#include "libft.h"

voidft_striteri(char *s, void (*f)(unsigned int, char*))
{
size_ti;

if (!s || !f)
return ;
i = 0;
while (s[i])
{
f(i, &s[i]);
i++;
}
}
