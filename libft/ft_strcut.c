#include "libft.h"
#include <stdlib.h>

static int		h_count(const char *s, char c)
{
	int		n;

	n = 1;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s && *s == c)
		{
			++s;
			++n;
		}
		while (*s && *s != c)
			++s;
	}
	return (n);
}

static size_t	h_len(const char *s, char c)
{
	size_t n;

	n = 0;
	while (*s && *s != c)
	{
		++s;
		++n;
	}
	return (n);
}

static void		h_abort(char ***s, size_t n)
{
	char **todel;

	todel = *s;
	while (*todel && n--)
	{
		free(*todel++);
	}
	free(*s);
	*s = NULL;
}

char			**ft_strcut(const char *s, char c)
{
	char	**fresh;
	char	**start;
	int		n;
	size_t	wlen;
	size_t	abort;

	if ((n = h_count(s, c)) == -1)
		return (NULL);
	wlen = -1;
	if (!(fresh = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	fresh[n] = NULL;
	start = fresh;
	abort = n;
	while (start && n-- && (s += wlen + 1))
	{
		wlen = h_len(s, c);
		if (!(*fresh = ft_strnew(wlen)))
			h_abort(&start, abort - n);
		if (start)
			ft_strncpy(*fresh++, s, wlen);
	}
	return (start);
}
