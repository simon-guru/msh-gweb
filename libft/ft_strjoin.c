#include "libft.h"

char*ft_strjoin(char const *s1, char const *s2)
{
char*join;
size_tlen1;
size_tlen2;

if (!s1 || !s2)
return (NULL);
len1 = ft_strlen(s1);
len2 = ft_strlen(s2);
join = malloc(len1 + len2 + 1);
if (!join)
return (NULL);
ft_memcpy(join, s1, len1);
ft_memcpy(join + len1, s2, len2 + 1);
return (join);
}
