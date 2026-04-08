#include "libft.h"

intft_tolower(int c)
{
if (c >= 'A' && c <= 'Z')
return (c + 32);
return (c);
}
