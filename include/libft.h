/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:40:49 by mogawa            #+#    #+#             */
/*   Updated: 2023/12/13 10:30:32 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	void			*content;
}	t_list;

//* lcalloc & lfree related
# define ALL (-1)

typedef struct s_mem
{
	void	*adr;
	int		grp;
}	t_mem;
//* end lcalloc & lfree

//* prototypes
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
//*additional functions
long	ft_strtol(const char *str, char **endptr, int base);//ft_atoi.c
int		ft_isspace(const char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t len);
size_t	ft_cntchar(const char *s, char c);
void	ft_free_null(void *ptr);
int		ft_swap(int *a, int *b);
int		ft_get_max(int a, int b);//ft_get_int.c
int		ft_get_min(int a, int b);//ft_get_int.c
int		ft_get_abs(int a);//ft_get_int.c
int		ft_isdigit_hex(int c);//ft_isdigit.c
//* ft_lcalloc.c & ft_lalloc_utils.c
void	*ft_lalloc(size_t count, size_t size, t_list **head, int grp);
void	ft_lfree(t_list **head, int grp);
int		ft_lalloc_init(t_list *head);
void	ft_lalloc_destroy(t_list *head);
//* ft_lstcalloc.c
void	*ft_lstcalloc(size_t count, size_t size, t_list **head);
void	ft_free_lstcalloc(t_list **head);

#endif