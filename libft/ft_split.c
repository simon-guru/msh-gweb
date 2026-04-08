#include "libft.h"

static size_tcount_words(char const *s, char c)
{
size_tcount;
intin_word;

count = 0;
in_word = 0;
while (*s)
{
if (*s != c && !in_word)
{
in_word = 1;
count++;
}
else if (*s == c)
in_word = 0;
s++;
}
return (count);
}

static char*get_word(char const *s, char c, size_t *i)
{
size_tstart;
size_tlen;
char*word;

while (s[*i] == c)
(*i)++;
start = *i;
while (s[*i] && s[*i] != c)
(*i)++;
len = *i - start;
word = malloc(len + 1);
if (!word)
return (NULL);
ft_memcpy(word, s + start, len);
word[len] = '\0';
return (word);
}

char**ft_split(char const *s, char c)
{
char**result;
size_tn;
size_ti;
size_tk;

if (!s)
return (NULL);
n = count_words(s, c);
result = malloc(sizeof(char *) * (n + 1));
if (!result)
return (NULL);
i = 0;
k = 0;
while (k < n)
{
result[k] = get_word(s, c, &i);
if (!result[k])
{
while (k--)
free(result[k]);
free(result);
return (NULL);
}
k++;
}
result[n] = NULL;
return (result);
}
