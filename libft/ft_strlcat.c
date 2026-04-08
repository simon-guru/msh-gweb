#include "libft.h"

size_tft_strlcat(char *dst, const char *src, size_t size)
{
size_tdstlen;
size_tsrclen;
size_ti;

dstlen = ft_strlen(dst);
srclen = ft_strlen(src);
if (size <= dstlen)
return (size + srclen);
i = 0;
while (src[i] && dstlen + i < size - 1)
{
dst[dstlen + i] = src[i];
i++;
}
dst[dstlen + i] = '\0';
return (dstlen + srclen);
}
