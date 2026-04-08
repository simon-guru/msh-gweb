#include "libft.h"

voidft_putstr_fd(char *s, int fd)
{
if (!s)
return ;
write(fd, s, ft_strlen(s));
}
