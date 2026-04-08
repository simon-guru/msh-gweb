#include "libft.h"

intft_atoi(const char *nptr)
{
intsign;
intresult;

sign = 1;
result = 0;
while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v'
|| *nptr == '\f' || *nptr == '\r')
nptr++;
if (*nptr == '-')
{
sign = -1;
nptr++;
}
else if (*nptr == '+')
nptr++;
while (*nptr >= '0' && *nptr <= '9')
{
result = result * 10 + (*nptr - '0');
nptr++;
}
return (result * sign);
}
