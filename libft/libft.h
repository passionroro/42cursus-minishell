/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:45:19 by rohoarau          #+#    #+#             */
/*   Updated: 2021/11/02 16:37:39 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef long unsigned int	t_size;
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_calloc(t_size count, t_size size);
char				*ft_strdup(const char *s1);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, t_size n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, t_size n);
int					ft_memcmp(const void *s1, const void *s2, t_size n);
void				*ft_memcpy(void *dst, const void *src, t_size n);
void				*ft_memmove(void *dst, const void *src, t_size len);
void				*ft_memset(void *b, int c, t_size len);
char				*ft_strchr(const char *s, int c);
t_size				ft_strlcat(char *dst, const char *src, t_size dstsize);
t_size				ft_strlcpy(char *dst, const char *src, t_size dstsize);
t_size				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, t_size n);
char				*ft_strnstr(const char *haystack, const char *needle, \
		t_size len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_substr(char const *s, unsigned int start, t_size len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*BONUS*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);

#endif
