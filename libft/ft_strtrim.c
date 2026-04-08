#include "libft.h"

static intis_set(char c, char const *set)
{
while (*set)
{
if (c == *set)
return (1);
set++;
}
return (0);
}

char*ft_strtrim(char const *s1, char const *set)
{
size_tstart;
size_tend;
char*trim;

if (!s1 || !set)
return (NULL);
start = 0;
while (s1[start] && is_set(s1[start], set))
start++;
end = ft_strlen(s1);
while (end > start && is_set(s1[end - 1], set))
end--;
trim = malloc(end - start + 1);
if (!trim)
return (NULL);
ft_memcpy(trim, s1 + start, end - start);
trim[end - start] = '\0';
return (trim);
}
