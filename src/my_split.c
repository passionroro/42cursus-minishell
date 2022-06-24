#include "../include/minishell.h"
/*
static int	char_check(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

static int	ft_countwords(char const *s, char *c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] && char_check(s[i], c) == 1)
		i++;
	while (s[i])
	{
		while (char_check(s[i], c) == 1)
		{
			if (char_check(s[i + 1], c))
				nb_words++;
			i++;
		}
		i++;
	}
	if (char_check(s[ft_strlen(s) - 1], c) == 0)
		nb_words++;
	printf("%d\tWORDS\n", nb_words);
	return (nb_words);
}

static int	ft_wordlen(const char *s, char *c, int start)
{
	int	len;

	len = 0;
	while (char_check(s[start], c) == 0 && s[start])
	{
		len++;
		start++;
	}
	return (len);
}

char	**my_split(char const *s, char *c)
{
	char	**tab;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (i < ft_countwords(s, c))
	{
		while (char_check(s[start], c) == 1)
			start++;
		tab[i] = ft_substr(s, start, ft_wordlen(s, c, start));
		if (tab[i][0] == '\0')
		{
			tab[i] = 0;
		}
		i++;
		start += ft_wordlen(s, c, start);
	}
	tab[ft_countwords(s, c)] = NULL;
	return (tab);
}*/
static int	char_check(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

static int	ft_wordlen(char *str, char *charset)
{
	int	count;
	int	part;

	count = 0;
	part = 1;
	while (*str)
	{
		if (!char_check(*str, charset) && part)
		{
			count++;
			part = 0;
		}
		else if (char_check(*str, charset))
			part = 1;
		str++;
	}
	return (count);
}

static char	*ft_splitdup(char *str, char *charset)
{
	char	*ptr;
	char	*buf;
	int		len;

	len = 0;
	buf = str;
	while (*buf && !char_check(*buf++, charset))
		len++;
	ptr = (char *)malloc(sizeof(char) * len);
	buf = ptr;
	while (*str && len-- > 0)
		*buf++ = *str++;
	*buf = '\0';
	return (ptr);
}

char	**my_split(char *s, char *c)
{
	char	**tmp;
	char	**ptr;
	int		part;

	if (!s || !c)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (ft_wordlen(s, c) + 1));
	if (!ptr)
		return (NULL);
	tmp = ptr;
	part = 1;
	while (*s)
	{
		if (!char_check(*s, c) && part)
		{
			part = 0;
			*tmp = ft_splitdup(s, c);
			tmp++;
		}
		else if (char_check(*s, c))
			part = 1;
		s++;
	}
	*tmp = 0;
	return (ptr);
}
