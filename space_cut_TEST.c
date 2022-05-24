#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*ft_lastgdf(char *tmp, char *arr)
{
	int		i;

	i = 0;
	while (tmp[i])
		i++;
	arr = (char *)malloc((i + 1) * sizeof(char));
	if (arr == NULL)
		return (0);
	i = 0;
	while (tmp[i])
	{
		arr[i] = tmp[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	**ft_setarr(char **arr, const char *s, char c)
{
	int		i;
	int		r;
	int		k;
	char	tmp[1000];

	i = 0;
	r = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		k = 0;
		while (s[i] != c && s[i])
			tmp[k++] = s[i++];
		tmp[k] = '\0';
		if (k > 0)
		{
			arr[r] = ft_lastgdf(tmp, arr[r]);
			r++;
		}
		else
			i++;
	}
	arr[r] = 0;
	return (arr);
}

static int	ft_cnt(const char *s, char c)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			k++;
			break ;
		}
	}
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			if (i > 0 && s[i + 1] != '\0' && s[i + 1] != c)
				k++;
		i++;
	}
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	char	**arr;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		arr = malloc(1);
		arr[0] = 0;
		return (arr);
	}
	a = ft_cnt(s, c);
	arr = (char **)malloc((a + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	arr = ft_setarr(arr, s, c);
	return (arr);
}

void	cut_no_space(char **com, int *l, int *i)
{
	char	*new;
	char	*temp;
	int		c;

	new = (char *)malloc(sizeof(char) * (*i + 1));
	c = -1;
	printf("L : %d\nI : %d\n", *l, *i);
	while (++c < *i)
		new[c] = com[*l][c];
	new[c] = '\0';
	temp = com[*l];
	com[*l] = new;
	free(temp);
}

void	ft_print(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
}

void	cut_space_after(char **com, int *l, int *i)
{
	int	p;

	cut_no_space(com, l, i);
	free(com[*l + 1]);
	p = 0;
	while (com[*l + ++p + 1])
		com[*l + p] = com[*l + p + 1];
	free(com[*l + p]);
	com[*l + p] = NULL;
}

void	cut_space_around(char **com, int *l, int *i)
{
	int	p;

	free(com[*l]);
	free(com[*l + 1]);
	p = 0;
	while (com[*l + ++p + 1])
		com[*l + p - 1] = com[*l + p + 1];
	printf("P->>> %d\n", p);
	free(com[*l + --p]);
	com[*l + p] = NULL;
	free(com[*l + ++p]);
	com[*l + p] = NULL;
}

void	cut_space_before(char **com, int *l, int *i)
{
	int	p;

	free(com[*l]);
	p = 0;
	while (com[*l + ++p])
		com[*l + p - 1] = com[*l + p];
	printf(" P : %d\n", p);
	free(com[*l + --p]);
	com[*l + p] = NULL;
}

int	main()
{
	char	**darray;
	int		i;
	int		l;

	l = 2;
	i = 0;
	darray = ft_split("echo blabla >file.txt >second command", ' ');
	ft_print(darray);
	cut_space_before(darray, &l, &i);
	printf("------------------------\n");
	ft_print(darray);
	return (0);
}
