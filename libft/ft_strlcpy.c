#include "libft.h"

size_tft_strlcpy(char *dst, const char *src, size_t size)
{
size_ti;
size_tsrclen;

srclen = ft_strlen(src);
if (size == 0)
return (srclen);
i = 0;
while (src[i] && i < size - 1)
{
dst[i] = src[i];
i++;
}
dst[i] = '\0';
return (srclen);
}
