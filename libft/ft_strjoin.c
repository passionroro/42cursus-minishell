#include "libft.h"

static int	ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		n;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	k = 0;
	n = ft_len(s1) + ft_len(s2);
	str = (char *)malloc((n + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	i = -1;
	while (s1[++i])
	{
		str[k] = s1[i];
		k++;
	}
	i = -1;
	while (s2[++i])
		str[k++] = s2[i];
	str[k] = '\0';
	free((void *)s1);
	return (str);
}
